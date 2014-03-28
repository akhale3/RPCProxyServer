
/***************************************Header file for Random Cache Replacement Policy*******************************************************/

#ifndef __random_H
#define __random_H
#include <iostream>
#include <vector>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;

template <class K, class D>

// implementing doubly linked list
struct random_node
{
  K key;
  D data;
  random_node *prev, *next;
};

template <class K, class D>
class Cache 
{
	private:
    		hash_map<K, random_node<K,D>* > cache_entries;
    		vector< random_node<K,D>* > free_entries;
    		random_node<K,D> *head, *tail;
    		random_node<K,D> *entries;
    		size_t cacheSize;
		// delete a randomly selected node
    		random_node<K,D>* delete_random_node()
    		{

       			random_node<K,D>* node =head;
	        	// Random number must be in the range (0, cacheSize - 1)
       			int random= rand()%(cacheSize);
       			while(random >= 0)
       			{
        			node = node->next;
        			random--;
        		}
			//if node selected to be delete is the last node
        		if(node == tail)
       	 		{	
            			tail->prev =node->prev->next;
            			node->prev->next=tail;
            			node->prev=node->next=NULL;
            			return node;

        		}
        		else
        		{
				// else case
            			node->prev->next = node->next;
            			node->next->prev = node->prev;
            			node->next=node->prev =NULL;
            			return node;

        		}
    		}

                // insert the node at tail
    		void addnode(random_node<K,D>* node)
    		{
        		node->prev = tail->prev;
        		node->next = tail;
        		node->prev->next = node;
        		tail->prev = node;
    		}

		public:
                // parameterized constructor which inserts into vector array the number of free enteries.
  		Cache(size_t size)
  		{
    			entries = new random_node<K,D>[size];
    			cacheSize = size;

    			for(int i=0; i<size; ++i)
    			{
        			free_entries.push_back(entries+i);
    			}
    			head = new random_node<K,D>;
    			tail = new random_node<K,D>;
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
    			random_node<K,D> *node = cache_entries[key];
    			if(node)
                        { 
				// node exists
				// do nothing
                       		node->data = data;
                        }
                        else
                        {
                        	if(free_entries.empty())
                                   	{

                                            // vector is empty => cache is full
                                            // delete entry from hash map and delete that node from the linked list.
                                            node =delete_random_node();
                                            cache_entries.erase(node->key);
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
                	random_node<K,D> *node = cache_entries[key];
                        if(node)
                                { 
				    //if hit return the data;
                                    return node->data;
                                }
                        else
                                { //if miss return null
                                    return D();
                                }                                                                                                                           	}
};


#endif
