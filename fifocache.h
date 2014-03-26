#ifndef __fifocache_H
#define __fifocache_H
#include <iostream>
#include <vector>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;

template <class K, class D>
struct FIFOnode 
{
  K key;
  D data;
  FIFOnode *prev, *next;
};

template <class K, class D>
class Cache {

	private:
                hash_map<K, FIFOnode<K,D>* > cache_enteries;
                vector< FIFOnode<K,D>* > free_entries;
                FIFOnode<K,D> *head, *tail;
                FIFOnode<K,D> *no_of_entries;

                // delete node from head
                void deletenode()
                {
                  	head->next = head->next->next;
        		head->next->next->prev = head;
                }
                 // insert the node at tail
                void addnode(FIFOnode<K,D>* node)
                {
			node->prev = tail->prev;
		        node->next = tail;
        		node->prev->next = node;
        		node->next->prev = node;
                      
                }

	public:
    		Cache(size_t size) 
		{
      			no_of_entries = new FIFOnode<K,D>[size];

      			for(int i=0; i<size; ++i) 
				{
        				free_entries.push_back(no_of_entries+i);
      				}
      			head = new FIFOnode<K,D>;
      			tail = new FIFOnode<K,D>;
      			head->prev = NULL;
      			head->next = tail;
      			tail->prev = head;
      			tail->next = NULL;
    		}

    		~Cache() 
		{
      			delete head;
      			delete tail;
      			delete[] no_of_entries;
   		 }

		void insert_into_cache(K key, D data) 
			{
      				FIFOnode<K,D> *node = cache_enteries[key];
      				if(node) 
				{ // node exists
        				//detach(node);
        				node->data = data;
        				//attach(node);
      				}	 
				else 
				{
        				if(free_entries.empty()) 
					{// cache is full
          				//	node = tail->prev;
          					deletenode();
          					cache_enteries.erase(node->key);
        				} 
					else 	
					{ //get a free node from _free_entries
          					node = free_entries.back();
          					free_entries.pop_back();
       			 		}
        			node->key = key; //put into hashmap and insert into link
        			node->data = data;
              			//cout << node->key << "\n";
              			//cout << node->data << "\n";
        			cache_enteries[key] = node;
              			//cout << _hashmap[key] << "\n";
        			addnode(node);
      				}
    			}	

		 D search_cache(K key) 
			{
      				//cout << "Get" << "\n";
             			FIFOnode<K,D> *node = cache_enteries[key];
              			//cout << _hashmap[key] << "\n";
      				if(node)
		 		{ // hit
        				//detach(node);
        				//attach(node);
                			//cout << "Hit" << "\n";
        				return node->data;
      				}
      				else
				{ // fail to hit
                		  //cout << T() << "\n";
        				return D();
      				}

			}
};


#endif
