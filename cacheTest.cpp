#include "cacheTest.h"
#include <iostream>
#include <ctime>

using namespace std;

CacheTest::CacheTest()
{
	m = new metrics();
}

void CacheTest::updateTCache(clock_t start, clock_t stop)
{
	m->tCache = m->tCache + ((stop - start) / (double) CLOCKS_PER_SEC);
}

void CacheTest::updateTMem(clock_t start, clock_t stop)
{
	m->tMem = m->tMem + ((stop - start) / (double) CLOCKS_PER_SEC);
}

void CacheTest::updateHits()
{
	m->hits++;
}

void CacheTest::updateMisses()
{
	m->misses++;
}

double CacheTest::calcHitRatio()
{
	if((m->hits + m->misses) == 0.0)
	{
		return 0.0;
	}
	else
	{
		return (m->hits / (m->hits + m->misses));
	}
}

double CacheTest::calcTAvg()
{
	return ((m->hits * m->tCache) + (m->misses * m->tMem));
}