#!/usr/local/bin/thrift --gen cpp

namespace cpp serverns

service server
{
	string getHtml(1: string url)
}
