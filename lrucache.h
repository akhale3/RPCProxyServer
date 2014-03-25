#ifndef __lrucache_H
#define __lrucache_H
#include <iostream>
#include <vector>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;

template <class K, class T>
struct LRUCacheEntry 
{
  K key;
  T data;
  LRUCacheEntry *prev, *next;
};

template <class K, class T>
class LRUCache {

	public:
    		LRUCache(size_t size) 
		{
      			_entries = new LRUCacheEntry<K,T>[size];

      			for(int i=0; i<size; ++i) 
				{
        				_free_entries.push_back(_entries+i);
      				}
      			_head = new LRUCacheEntry<K,T>;
      			_tail = new LRUCacheEntry<K,T>;
      			_head->prev = NULL;
      			_head->next = _tail;
      			_tail->prev = _head;
      			_tail->next = NULL;
    		}

    		~LRUCache() 
		{
      			delete _head;
      			delete _tail;
      			delete[] _entries;
   		 }

		void Put(K key, T data) 
			{
      				LRUCacheEntry<K,T> *node = _hashmap[key];
      				if(node) 
				{ // node exists
        				detach(node);
        				node->data = data;
        				attach(node);
      				}	 
				else 
				{
        				if(_free_entries.empty()) 
					{// cache is full
          					node = _tail->prev;
          					detach(node);
          					_hashmap.erase(node->key);
        				} 
					else 	
					{ //get a free node from _free_entries
          					node = _free_entries.back();
          					_free_entries.pop_back();
       			 		}
        			node->key = key; //put into hashmap and insert into link
        			node->data = data;
              //cout << node->key << "\n";
              //cout << node->data << "\n";
        			_hashmap[key] = node;
        			attach(node);
      				}
    			}	

		 T Get(K key) 
			{
      				//cout << "Get" << "\n";
              LRUCacheEntry<K,T> *node = _hashmap[key];
              //cout << key << "\n";
      				if(node)
		 		{ // hit
        				detach(node);
        				attach(node);
                //cout << "Hit" << "\n";
        				return node->data;
      				}
      				else
				{ // fail to hit
        				return NULL;
      				}

			}
	private: 
 		void detach(LRUCacheEntry<K,T>* node) 
		{
      			node->prev->next = node->next;
      			node->next->prev = node->prev;
    		}
   		 // insert the node into head
 		void attach(LRUCacheEntry<K,T>* node) 
		{
      			node->prev = _head;
      			node->next = _head->next;
      			_head->next = node;
      			node->next->prev = node;
    		}
	private:
    		hash_map<K, LRUCacheEntry<K,T>* > _hashmap;
    		vector< LRUCacheEntry<K,T>* > _free_entries;
    		LRUCacheEntry<K,T> *_head, *_tail;
    		LRUCacheEntry<K,T> *_entries;
};


#endif
