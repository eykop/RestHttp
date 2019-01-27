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

using namespace std;

struct ResponseStatusLine {
	ResponseStatusLine() = default;
    ResponseStatusLine(unsigned int statusCode,
        std::string&& httpVersion, std::string&& message)
        : HttpVersion(std::move(httpVersion))
        , Message(std::move(message))
        , StatusCode(statusCode)
    {
    }

    std::string HttpVersion;
    std::string Message;
    unsigned int StatusCode = 0;
};

class ResponseData {
public:
	ResponseData(const ResponseData&) = delete;
	ResponseData(ResponseData&&) = default;
	ResponseData() = default;
    ResponseData(ResponseStatusLine&& statusCode,
        std::unordered_map<std::string, std::string>&& headers,
        std::string&& body);
    virtual ~ResponseData();
    const ResponseStatusLine& getStatusCode() const { return mResponseStatusLine; };
    const string& getBody() const { return mBody; };
    const std::unordered_map<std::string, std::string>& getHeaders() const { return mHeaders; };

    void setBody(std::string&& body);
    void setResponseStatusLine(ResponseStatusLine&& responseStatusLine);
    void setHeaders(std::unordered_map<std::string, std::string>&& headers);

private:
    std::unordered_map<std::string, std::string> mHeaders;
    std::string mBody;
    ResponseStatusLine mResponseStatusLine;
};
