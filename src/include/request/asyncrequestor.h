#pragma once

#include <boost/asio.hpp>
#include <functional>

#include <string>

class ReqtuestData;

class AsyncRequestor {
public:
    AsyncRequestor(boost::asio::io_service &io_service,
					const std::string& server,
					const std::string& path);
private:
    bool connect(const std::string& host, const std::string& port);
    void sendRequest(ReqtuestData& reqData);

    boost::asio::ip::tcp::socket mSocket;
    boost::asio::ip::tcp::resolver mResolver;
};
