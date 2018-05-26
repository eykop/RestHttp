#include "responsedata.h"

ResponseData::ResponseData() {}

ResponseData::ResponseData(
    const ResponseStatusLine& statusCode,
    const std::unordered_map<std::string, std::string>& headers,
    const string& body)
    : mHeaders(std::move(headers)),
      mBody(body),
      mResponseStatusLine(std::move(statusCode)) {}

ResponseData::~ResponseData() {}

const ResponseStatusLine& ResponseData::getStatusCode() {
  return mResponseStatusLine;
}

const std::string& ResponseData::getBody() { return mBody; }

std::unordered_map<std::string, std::string> ResponseData::getHeaders() {
  return mHeaders;
}
