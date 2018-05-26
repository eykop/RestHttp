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

Resquestor::Resquestor(boost::asio::io_service &io_service)
    : m_io_service(io_service),
      mSocket(m_io_service),
      mResolver(m_io_service) {}

bool Resquestor::connect(const std::string &host, const std::string &port) {
  try {
    boost::asio::connect(mSocket, mResolver.resolve({host, port}));
  } catch (boost::system::system_error &err) {
    std::cout << "error occured: " << err.what();
    return false;
  } catch (...) {
    std::cout << "unknown error occured. ";
    return false;
  }

  return true;
}

void Resquestor::sendRequest(ReqtuestData &reqData) {
  boost::asio::streambuf request;
  if (!mSocket.is_open()) {
    mIsConnected = connect(reqData.host(), reqData.port());
    if (!mIsConnected) {
      mSocket.close();
      return;
    }
  }
  reqData.buildRequest(request);
  boost::asio::write(mSocket, request);
}

void Resquestor::readResponseStatus(unsigned int &code, std::string &message,
                                    std::string &otherInfo) {
  if (!mIsConnected) return;
  boost::asio::read_until(mSocket, mResponse, "\r\n");
  std::istream response_stream(&mResponse);
  // get http version as other info...
  response_stream >> otherInfo;
  response_stream >> code;
  std::getline(response_stream, message);
}

void Resquestor::readResponseHeaders(
    std::unordered_map<std::string, std::string> &headers) {
  if (!mIsConnected) return;
  std::istream response_stream(&mResponse);
  boost::asio::read_until(mSocket, mResponse, "\r\n\r\n");
  std::string header;
  while (std::getline(response_stream, header) && header != "\r") {
    std::vector<std::string> result;
    boost::algorithm::split(result, header, boost::is_any_of(":"));
    headers[result[0]] = result[1];
  }
}

void Resquestor::readResponseData(std::string &resData) {
  if (!mIsConnected) return;
  std::stringstream ss;
  ss.clear();
  if (mResponse.size() > 0) {
    ss << &mResponse;
  }

  boost::system::error_code error;
  while (boost::asio::read(mSocket, mResponse,
                           boost::asio::transfer_at_least(1), error)) {
    if (error != boost::asio::error::eof) {
      throw boost::system::system_error(error);
    }
    if (mResponse.size() > 0) {
      ss << &mResponse;
    }
  }
  resData = ss.str();
  mSocket.close();
}

void Resquestor::getResponse(ResponseData &responseData) {
  unsigned int code;
  std::string message;
  std::string otherInfo;
  this->readResponseStatus(code, message, otherInfo);
  ResponseStatusLine resStatusLine(code, message, otherInfo);
  std::unordered_map<std::string, std::string> headers;
  this->readResponseHeaders(headers);
  std::string resData;
  this->readResponseData(resData);
  responseData = ResponseData(resStatusLine, headers, resData.c_str());
}
