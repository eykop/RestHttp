/*
    This file is part of RestHttp Project.
    RestHttp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    RestHttp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see<http://www.gnu.org/licenses/>.
*/

#define D_SCL_SECURE_NO_WARNINGS 1

#include "requestor.h"
#include "responsedata.h"

#include <boost/algorithm/string.hpp>

Resquestor::Resquestor(boost::asio::io_service& io_service)
    : mSocket(io_service)
    , mResolver(io_service)
{
}

bool Resquestor::connect(const std::string& host, const std::string& port)
{
    try {
        boost::asio::connect(mSocket, mResolver.resolve({ host, port }));
    } catch (boost::system::system_error& err) {
        std::cout << "error occured: " << err.what();
        return false;
    } catch (...) {
        std::cout << "unknown error occured. ";
        return false;
    }

    return true;
}

void Resquestor::sendRequest(const ReqtuestData& reqData)
{
    if (!mSocket.is_open()) {
        mIsConnected = connect(reqData.host(), reqData.port());
        if (!mIsConnected) {
            mSocket.close();
            return;
        }
    }
    boost::asio::streambuf request;
    std::ostream request_stream(&request);
    request_stream << reqData.method() << " " << reqData.path() << " " << reqData.httpVersion() << "\r\n";
    request_stream << "Host: " << reqData.host() << "\r\n";
    for (const auto& header : reqData.headers()) {
        request_stream << header.first << ": " << header.second << "\r\n";
    }
    request_stream << "\r\n";
    boost::asio::write(mSocket, request);
}

void Resquestor::readResponseStatus(ResponseData& responseData)
{
    unsigned int code;
    std::string message;
    std::string otherInfo;
    if (!mIsConnected)
        return;
    boost::asio::read_until(mSocket, mResponse, "\r\n");
    std::istream response_stream(&mResponse);
    // get http version as other info...
    response_stream >> otherInfo;
    response_stream >> code;
    std::getline(response_stream, message);
    ResponseStatusLine resStatusLine(code, otherInfo, message);
    responseData.setResponseStatusLine(resStatusLine);
}

void Resquestor::readResponseHeaders(ResponseData& responseData)

{
    std::unordered_map<std::string, std::string> headers;
    if (!mIsConnected)
        return;
    std::istream response_stream(&mResponse);
    boost::asio::read_until(mSocket, mResponse, "\r\n\r\n");
    std::string header;
    while (std::getline(response_stream, header) && header != "\r") {
        std::vector<std::string> result;
        boost::algorithm::split(result, header, boost::is_any_of(":"));
        headers[result[0]] = result[1];
    }
    responseData.setHeaders(headers);
}

void Resquestor::readResponseData(ResponseData& responseData)
{
    if (!mIsConnected) {
        return;
    }
    std::stringstream ss;
    ss.clear();
    if (mResponse.size() > 0) {
        ss << &mResponse;
    }

    boost::system::error_code error;
    while (boost::asio::read(
        mSocket, mResponse, boost::asio::transfer_at_least(1), error)) {
        if (error != boost::asio::error::eof) {
            throw boost::system::system_error(error);
        }
        if (mResponse.size() > 0) {
            ss << &mResponse;
        }
    }
    responseData.setBody(ss.str());
    mSocket.close();
}

void Resquestor::getResponse(ResponseData& responseData)
{
    readResponseStatus(responseData);
    readResponseHeaders(responseData);
    try {
        readResponseData(responseData);
    } catch (boost::system::system_error& ee) {
        std::cout << "some error occured" << std::endl;
        std::cout << ee.what();
    }
}
