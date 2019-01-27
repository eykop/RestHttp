#include "asyncrequestor.h"

AsyncRequestor::AsyncRequestor(boost::asio::io_service &io_service,
		const std::string& server,
		const std::string& path) :
		mSocket(io_service), mResolver(io_service)
{

}
