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
