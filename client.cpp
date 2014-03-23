#include "server.h"

#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include <string.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace serverns;

int main(int argc, char ** argv)
{
	std::string body;
	boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

	serverClient client(protocol);
	transport->open();
	client.getHtml(body);
	printf("%s", body.c_str());
	transport->close();

	return 0;
}
