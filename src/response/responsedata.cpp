#include "../include/response/responsedata.h"

ResponseData::ResponseData(
    ResponseStatusLine&& statusCode,
    std::unordered_map<std::string, std::string>&& headers,
    string&& body)
    : mHeaders(std::move(headers))
    , mBody(std::move(body))
    , mResponseStatusLine(std::move(statusCode))
{
}

void ResponseData::setBody(std::string&& body)
{
    mBody = std::move(body);
}

void ResponseData::setResponseStatusLine(ResponseStatusLine&& responseStatusLine)
{
    mResponseStatusLine = std::move(responseStatusLine);
}

void ResponseData::setHeaders(std::unordered_map<std::string, std::string>&& headers)
{
    mHeaders = std::move(headers);
}
