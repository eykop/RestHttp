#ifndef REQTUESTDATA_H
#define REQTUESTDATA_H


#include <unordered_map>
#include <string>
#include <iostream>
#include <boost/asio.hpp>

class ReqtuestData
{
public:
    ReqtuestData();
    ReqtuestData(const std::string &host,
                 const std::string &port,
                 const std::string &method,
                 const std::string &path,
                 const std::unordered_map<std::string, std::string> &headers,
                 const std::string &httpVersion="HTTP/1.1");
    std::string host() const;
    void setHost(const std::string &host);

    std::string port() const;
    void setPort(const std::string &port);

    std::string method() const;
    void setMethod(const std::string &method);

    std::string path() const;
    void setPath(const std::string &path);

    std::unordered_map<std::string, std::string> headers() const;
    void setHeaders(const std::unordered_map<std::string, std::string> &headers);

    std::string httpVersion() const;
    void setHttpVersion(const std::string &httpVersion="HTTP/1.1");

    char *body() const;
    void setBody(char *body);
    void buildRequest(boost::asio::streambuf &request);

private:
    std::string mHost;
    std::string mPort;
    std::string mMethod;
    std::string mPath;
    std::string mHttpVersion;
    char* mBody;
    std::unordered_map<std::string, std::string> mHeaders;

};

#endif // REQTUESTDATA_H
