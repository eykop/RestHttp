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
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <string>
#include "requestdata.h"
#include "requestor.h"
#include "ioservice.h"
using namespace std;

int main()
{
    std::string http_version;
    unsigned int httpStatusCode = 0 ;
    std::string http_status_message;
    std::string resData;

    //fill the request headers...
    std::unordered_map<std::string, std::string> headers;
    headers["Accept"] = "*/*";
    headers["Connection"] = "Close";

    ReqtuestData reqData("date.jsontest.com",
                 "http",
                 "GET",
                 "/",
                 headers,
                 "HTTP/1.1");


    //reuse headers after clearing request ones...
    headers.clear();

    Resquestor requestor(io_service);
    requestor.connect("date.jsontest.com", "http");
    requestor.sendRequest(reqData);
    requestor.readResponseStatus(httpStatusCode, http_status_message, http_version);

    //check status for error...
    if(200 > httpStatusCode || httpStatusCode > 299){
        return -1;
    }

    requestor.readResponseHeaders(headers);
    requestor.readResponseData(resData);

    //print recived data ...
    std::cout<<http_version<< " "<< httpStatusCode <<" "<<http_status_message<<std::endl;

    for(const auto& header : headers){
        std::cout<< header.first << ": " << header.second << std::endl;
    }

    std::cout<<std::endl;
    std::cout<<resData<<std::endl;

    return 0;
}
