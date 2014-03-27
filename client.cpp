#include "server.h"

#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include <string.h>
#include <fstream>
#include <iostream>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace serverns;

void getUrl(serverClient client, char * urlListFile)
{
	std::string body;
	std::string line;
    std::ifstream myFile(urlListFile);

    if(myFile.is_open())
   	{
    	while(std::getline(myFile, line))
    	{
    		printf("Requesting URL %s\n\n", line.c_str());
    		client.getHtml(body, line);
    		printf("%s\n\n", body.c_str());
    	}
    }
}

int main(int argc, char ** argv)
{
	boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

	/* Check proper usage */
	if(argc < 2)
	{
		fprintf(stderr, "Usage: ./webclient [urlListFile]\n");
		exit(0);
	}

	serverClient client(protocol);
	transport->open();
	getUrl(client, argv[1]);
	transport->close();

	return 0;
}
