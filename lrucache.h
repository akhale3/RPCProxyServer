
/*****************************************Header file for LRU Cache Replacement Policy*********************************************************/

#ifndef __lrucache_H
#define __lrucache_H
#include <iostream>
#include <vector>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;

template <class K, class D>

//Implementing Doubly linked List
struct LRUnode 
{
  K key;
  D data;
  LRUnode *prev, *next;
};

template <class K, class D>
class Cache
{
	private:
    		hash_map<K, LRUnode<K,D>* > cache_entries;
    		vector< LRUnode<K,D>* > free_entries;
    		LRUnode<K,D> *head, *tail;
    		LRUnode<K,D> *entries;

    	//delete node from the end
    	void deletenode(LRUnode<K,D>* node)
    	{
      		node->prev->next = node->next;
      		node->next->prev = node->prev;
    	}
    
    	// insert the node at head
    	void addnode(LRUnode<K,D>* node)
    	{
      		node->prev = head;
      		node->next = head->next;
      		head->next = node;
      		node->next->prev = node;
    	}

  	public:
		
		// parameterized constructor which inserts into vector array the number of free enteries.	
    		Cache(size_t size) 
    		{
      			entries = new LRUnode<K,D>[size];

      			for(int i=0; i<size; ++i) 
      			{
        			free_entries.push_back(entries+i);
      			}
      			head = new LRUnode<K,D>;
      			tail = new LRUnode<K,D>;
      			head->prev = NULL;
      			head->next = tail;
      			tail->prev = head;
      			tail->next = NULL;
    		}
                // destructor to remove  link list and vector enteries
    		~Cache() 
    		{
     			delete head;
     			delete tail;
     			delete[] entries;
    		}

    		size_t size() const
    		{
      			return cache_entries.size();
    		}

                // if cache miss then insert entry into cache
    		void insert_into_cache(K key, D data) 
    		{
      			LRUnode<K,D> *node = cache_entries[key];
      			if(node) 
    			{ 
				// if node exists then delete node and attach this node in the front
        			deletenode(node);
        			node->data = data;
        			addnode(node);
     	 		}	 
      			else 
      			{
        			if(free_entries.empty()) 
    				{
                                        // vector is empty => cache is full
                                        // delete entry from hash map and delete that node from the linked list.
          				node = tail->prev;
          				cache_entries.erase(node->key);
          				deletenode(node);
        			} 
        			else 	
    				{
          				//get a free node from _free_entries
          				node = free_entries.back();
          				free_entries.pop_back();
        			}
                                // insert into hash map and insert the node into linked list
  				node->key = key;
  				node->data = data;
  				cache_entries[key] = node;
  				addnode(node);
      			}
    		}	

    		D search_cache(K key) 
    		{
			// search into cache to get the data;
      			LRUnode<K,D> *node = cache_entries[key];

      			if(node)
      			{ 
				// if hit delete mode and add that node in front and return data;
       	 			deletenode(node);
        			addnode(node);
        			return node->data;
      			}
      			else
      			{
        			// if miss return null
        			return D();
      			}
    		}
};

#endif
