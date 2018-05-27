#include "responsedata.h"

ResponseData::ResponseData() {}

ResponseData::ResponseData(
    const ResponseStatusLine& statusCode,
    const std::unordered_map<std::string, std::string>& headers,
    const string& body)
    : mHeaders(headers)
    , mBody(body)
    , mResponseStatusLine(statusCode)
{
}

ResponseData::~ResponseData() {}

const ResponseStatusLine& ResponseData::getStatusCode()
{
    return mResponseStatusLine;
}

const std::string& ResponseData::getBody() { return mBody; }

std::unordered_map<std::string, std::string> ResponseData::getHeaders()
{
    return mHeaders;
}

void ResponseData::setBody(const std::string& body)
{
    mBody = body;
}

void ResponseData::setResponseStatusLine(const ResponseStatusLine& responseStatusLine)
{
    mResponseStatusLine = responseStatusLine;
}

void ResponseData::setHeaders(const std::unordered_map<std::string, std::string>& headers)
{
    mHeaders = headers;
}
