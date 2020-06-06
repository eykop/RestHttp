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

#define BOOST_ASIO_NO_DEFAULT_LINKED_LIBS
#include "include/request/requestdata.h"
#include "include/request/requestor.h"
#include "ioservice.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    // fill the request headers...
    std::unordered_map<std::string, std::string> inHeaders;

    inHeaders["Accept"] = "*/*";
    inHeaders["Connection"] = "Close";

    RequestData reqData("date.jsontest.com", "http", "GET", "/", inHeaders,
        "HTTP/1.1");
    //    RequestData reqData("httpbin.org", "http", "GET", "/get", inHeaders,
    //        "HTTP/1.1");
    //    RequestData reqData("www.wikipedia.org", "https", "GET", "/", inHeaders,
    //        "HTTP/1.1");

    Requestor requestor(io_service);
    requestor.sendRequest(reqData);
    ResponseData respData(requestor.getResponse());

    const auto& statusLine = respData.getStatusCode();

    // print received data ...
    std::cout << statusLine.HttpVersion << " " << statusLine.StatusCode << " "
              << statusLine.Message << std::endl;
    std::unordered_map<std::string, std::string> headers = respData.getHeaders();
    for (const auto& header : headers) {
        std::cout << header.first << ": " << header.second << std::endl;
        std::cout << std::flush;
    }

    std::cout << respData.getBody() << std::endl;
    if (200 > statusLine.StatusCode || statusLine.StatusCode > 299) {
        return -1;
    } else {
        return 0;
    }
}
