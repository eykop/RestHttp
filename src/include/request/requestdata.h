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
#pragma once

#include <string>
#include <unordered_map>

#include <boost/asio.hpp>

class ReqtuestData {
public:
    ReqtuestData() = delete ;

    ReqtuestData(std::string&& host, std::string&& port,
        std::string&& method, std::string&& path,
        const std::unordered_map<std::string, std::string>& headers,
        std::string&& httpVersion = "HTTP/1.1");

    boost::asio::streambuf* buildRequest();

	const std::string& host() const { return mHost; };
	const std::string& port() const { return mPort; };
	const std::string& method() const { return mMethod; };
	const std::string& path() const { return mPath; };
	const std::unordered_map<std::string, std::string>& headers() const { return mHeaders; };
	const std::string& httpVersion() const { return mHttpVersion; };
	char* body() const { return mBody; };
	void setBody(char* body) { mBody = body; };

private:
    std::string mHost;
    std::string mPort;
    std::string mMethod;
    std::string mPath;
    std::string mHttpVersion;
    char* mBody = nullptr;
    std::unordered_map<std::string, std::string> mHeaders;
    boost::asio::streambuf mRequest;
};
