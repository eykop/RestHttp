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

#include "../response/responsedata.h"
#include "requestdata.h"

#include <string>

#include <boost/asio.hpp>

class Resquestor {
public:
    Resquestor(boost::asio::io_service& io_service);
    bool connect(const std::string& host, const std::string& port);

    void sendRequest(ReqtuestData& reqData);
    
    
	ResponseData getResponse();


private:
	std::string readResponseData();
	ResponseStatusLine readResponseStatus();
	std::unordered_map<std::string, std::string> readResponseHeaders();
    //  boost::asio::io_service &m_io_service;
    boost::asio::ip::tcp::socket mSocket;
    boost::asio::ip::tcp::resolver mResolver;
    boost::asio::streambuf mResponse;
    bool mIsConnected = false;
    
};
