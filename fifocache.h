
/****************************************Header file for FIFO Cache Replacement Policy*********************************************************/

#ifndef __fifocache_H
#define __fifocache_H
#include <iostream>
#include <vector>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;

template <class K, class D>
//implementing doubly linked list
struct FIFOnode 
{
  K key;
  D data;
  FIFOnode *prev, *next;
};

template <class K, class D>
class Cache {

	private:
                hash_map<K, FIFOnode<K,D>* > cache_entries;
                vector< FIFOnode<K,D>* > free_entries;
                FIFOnode<K,D> *head, *tail;
                FIFOnode<K,D> *entries;

                // delete node from head
                void deletenode()
                {
                  	head->next = (head->next)->next;
        		((head->next)->next)->prev = head;
                }
                 // insert the node at tail
                void addnode(FIFOnode<K,D>* node)
                {
			node->prev = tail->prev;
		        node->next = tail;
        		(node->prev)->next = node;
        		tail->prev = node;
                      
                }

	public:
		// parameterized constructor which inserts into vector array the number of free enteries.
    		Cache(size_t size) 
		{
      			entries = new FIFOnode<K,D>[size];

      			for(int i=0; i<size; ++i) 
				{
        				free_entries.push_back(entries+i);
      				}
      			head = new FIFOnode<K,D>;
      			tail = new FIFOnode<K,D>;
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
      				FIFOnode<K,D> *node = cache_entries[key];
      				if(node) 
				{ 
					// node exists
        				//do nothing
      				}	 
				else 
				{
        				if(free_entries.empty()) 
					{
						// vector is empty => cache is full
						// delete entry from hash map and delete that node from the linked list.
          					cache_entries.erase((head->next)->key);
                   				deletenode();
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
      				//search into cache to get the data
             			FIFOnode<K,D> *node = cache_entries[key];
      				if(node)
		 		{ 
					//if hit return the data;
        				return node->data;
      				}
      				else
				{ 
					// if miss return null;
        				return D();
      				}

			}
};


#endif
