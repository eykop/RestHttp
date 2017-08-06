#ifndef RESQUESTOR_H
#define RESQUESTOR_H

#include <sstream>
#include <string>
#include <unordered_map>
#include <boost/asio.hpp>
#include "requestdata.h"

class Resquestor
{
public:
    Resquestor(boost::asio::io_service &io_service);
    void connect(const std::string &host, const std::string &port);
    void sendRequest(ReqtuestData &reqData);
    void readResponseStatus(unsigned int &code, std::string &message, std::string &otherInfo);
    void readResponseHeaders(std::unordered_map<std::string, std::string> &headers);
    void readResponseData(std::string &resData);
private:
    boost::asio::io_service &m_io_service;
    boost::asio::ip::tcp::socket mSocket;
    boost::asio::ip::tcp::resolver mResolver;
    boost::asio::streambuf mResponse;

};

#endif // RESQUESTOR_H
