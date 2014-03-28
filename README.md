RPCProxyServer
==============

A cache coherent client-server application based on Apache Thrift.

==============

1. Dependencies
The application uses a host of third-party libraries, viz. libcurl, thrift, boost, and a C++ external library called hash_map.

IMPORTANT NOTE: The current file - curl/curlbuild.h - works only on 64-bit machines. To successfully compile the application on a 32-bit machine, replace curlbuild.h with curlbuild32.h.

2. Installation
Simply type 'make' in the root directory of the project folder.

3. Execution
	3.1. Start the server
	./webserver
	3.2. Start the client
	./webclient [path_to_workload_file]

4. Running tests
	4.1. Connect to a server
	With the server running on a machine, plug in the server IP in the main() of client.cpp by replacing "localhost" with "X.X.X.X".

	4.2. Choose cache size and cache policy
	In webserver.cpp, vary the required cache size (number of entries in cache) from 0 onwards, 0 indicating "no-cache" or "cache-bypass".
	To choose from one of the three implementations of Random, FIFO and LRU cache policies, simply uncomment the desired include file and comment the rest in webserver.cpp.

	4.3. Workload files
	Two workloads (uniformly random and statistically distributed) are defined in workload1.txt and workload2.txt, respectively, one URL per line. Currently, there are 5 unique URLs and 15 combinations of the same.

	4.4. Test metrics output
	The server outputs the cumulative hit ratio and average memory access time for each URL requested by the client per workload.