#include "requestor.h"
#include <boost/algorithm/string.hpp>
Resquestor::Resquestor(boost::asio::io_service &io_service) :
    m_io_service(io_service), mSocket(m_io_service), mResolver(m_io_service)
{

}

void Resquestor::connect(const std::string &host, const std::string &port)
{
    boost::asio::connect(mSocket, mResolver.resolve({host, port}));
}

void Resquestor::sendRequest(ReqtuestData &reqData)
{
    boost::asio::streambuf request;
    reqData.buildRequest(request);
    boost::asio::write(mSocket, request);
}

void Resquestor::readResponseStatus(unsigned int &code, std::string &message, std::string &otherInfo)
{

    boost::asio::read_until(mSocket, mResponse, "\r\n");
    std::istream response_stream(&mResponse);
    //get http version as other info...
    response_stream >> otherInfo;
    response_stream >> code;
    std::getline(response_stream, message);
}

void Resquestor::readResponseHeaders(std::unordered_map<std::string, std::string> &headers)
{
    std::istream response_stream(&mResponse);
    boost::asio::read_until(mSocket, mResponse, "\r\n\r\n");
    std::string header;
    while(std::getline(response_stream, header) && header != "\r"){
        std::vector<std::string> result;
        boost::algorithm::split(result, header, boost::is_any_of(":"));
        headers[result[0]] = result[1];
    }

}

void Resquestor::readResponseData(std::string &resData)
{
    std::stringstream ss;
    if(mResponse.size() > 0){
        ss<<&mResponse;
    }

    boost::system::error_code error;
    while(boost::asio::read(mSocket, mResponse, boost::asio::transfer_at_least(1), error)){
        if(error != boost::asio::error::eof){
            throw boost::system::system_error(error);
        }
        if(mResponse.size() > 0){
            ss<<&mResponse;
        }
    }
    resData = ss.str();

}
