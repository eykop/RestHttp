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
#include "../include/request/requestdata.h"

RequestData::RequestData(
    std::string&& host, std::string&& port, std::string&& method,
    std::string&& path, const std::unordered_map<std::string, std::string>& headers,
    std::string&& httpVersion)
    : mHost(std::move(host))
    , mPort(std::move(port))
    , mMethod(std::move(method))
    , mPath(std::move(path))
    , mHttpVersion(std::move(httpVersion))
    , mHeaders(std::move(headers))
{
}

boost::asio::streambuf* RequestData::buildRequest()
{

    std::ostream request_stream(&mRequest);
    request_stream << mMethod << " " << mPath << " "
                   << mHttpVersion << "\r\n";
    request_stream << "Host: " << mHost << "\r\n";
    for (const auto& header : mHeaders) {
        request_stream << header.first << ": " << header.second << "\r\n";
    }
    request_stream << "\r\n";
    return &mRequest;
}
