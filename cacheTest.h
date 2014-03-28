#ifndef __cacheTest_H
#define __cacheTest_H
#include <ctime>

using namespace std;

struct metrics
{
	double tCache;
	double tMem;
	double hits;
	double misses;
};

class CacheTest
{
private:
	metrics * m;
public:
	CacheTest();
	void updateTCache(clock_t start, clock_t stop);
	void updateTMem(clock_t start, clock_t stop);
	void updateHits();
	void updateMisses();
	double calcHitRatio();
	double calcTAvg();
};

#endif