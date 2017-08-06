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
#include "requestdata.h"

ReqtuestData::ReqtuestData()
{

}

ReqtuestData::ReqtuestData(const std::string &host,
                           const std::string &port,
                           const std::string &method,
                           const std::string &path,
                           const std::unordered_map<std::string, std::string> &headers,
                           const std::string &httpVersion) :
    mHost(host), mPort(port), mMethod(method), mPath(path),
    mHttpVersion(httpVersion), mHeaders(headers){

}

void ReqtuestData::buildRequest(boost::asio::streambuf& request){
    std::ostream request_stream(&request);
    request_stream << mMethod << " " << mPath << " " << mHttpVersion << "\r\n";
    request_stream << "Host: "<< mHost << "\r\n";
    for(const auto& header : mHeaders){
        request_stream << header.first << ": " << header.second << "\r\n";
    }
    request_stream << "\r\n";
}

std::string ReqtuestData::host() const
{
    return mHost;
}

void ReqtuestData::setHost(const std::string &host)
{
    mHost = host;
}

std::string ReqtuestData::port() const
{
    return mPort;
}

void ReqtuestData::setPort(const std::string &port)
{
    mPort = port;
}

std::string ReqtuestData::method() const
{
    return mMethod;
}

void ReqtuestData::setMethod(const std::string &method)
{
    mMethod = method;
}

std::string ReqtuestData::path() const
{
    return mPath;
}

void ReqtuestData::setPath(const std::string &path)
{
    mPath = path;
}

std::unordered_map<std::string, std::string> ReqtuestData::headers() const
{
    return mHeaders;
}

void ReqtuestData::setHeaders(const std::unordered_map<std::string, std::string> &headers)
{
    mHeaders = headers;
}

std::string ReqtuestData::httpVersion() const
{
    return mHttpVersion;
}

void ReqtuestData::setHttpVersion(const std::string &httpVersion)
{
    mHttpVersion = httpVersion;
}

char *ReqtuestData::body() const
{
    return mBody;
}

void ReqtuestData::setBody(char *body)
{
    mBody = body;
}
