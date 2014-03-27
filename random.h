#ifndef __random_H
#define __random_H
#include <iostream>
#include <vector>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;

template <class K, class D>
struct random_node
{
  K key;
  D data;
  random_node *prev, *next;
};

template <class K, class D>
class Cache {

        private:
                hash_map<K, random_node<K,D>* > cache_enteries;
                vector< random_node<K,D>* > free_entries;
                random_node<K,D> *head, *tail;
                random_node<K,D> *no_of_entries;

                random_node<K,D>* delete_random_node()
                {
	        
			random_node<K,D>* node =head;
			int random= rand()%(size-1);
			while(random!=0)
			{
				node=node->next;
				random--;
			}
			if(node ==head)
			{
				// delete node from head;
				head->next= node->next;
                                node->next->prev =head; 
                                node->next=node->prev= NULL;
                                return node;

			}
			else
			{
				if(node == tail)
				{	
					tail->prev =node->prev->next;
                                        node->prev->next=tail;
                                        node->prev=node->next=NULL;
                                        return node;
					
				}
				else
				{
					node->prev->next = node->next;
		                        node->next->prev = node->prev;
					node->next=node->prev =NULL;
					return node;

				}
			}
                }
                 // insert the node at tail
                void addnode(random_node<K,D>* node)
                {
                        node->prev = tail->prev;
                        node->next = tail;
                        node->prev->next = node;
                        node->next->prev = node;
                }

        public:
		size_t size;
                Cache(size_t size)
                {
                        no_of_entries = new random_node<K,D>[size];

                        for(int i=0; i<size; ++i)
                                {
                                        free_entries.push_back(no_of_entries+i);
                                }
                        head = new random_node<K,D>;
                        tail = new random_node<K,D>;
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
                                random_node<K,D> *node = cache_enteries[key];
                                if(node)
                                { // node exists
                                        node->data = data;
                                }
                                else
                                {
                                        if(free_entries.empty())
                                        {// cache is full
                                                node =delete_random_node();
                                                cache_enteries.erase(node->key);
                                        }
                                        else
                                        { //get a free node from _free_entries
                                                node = free_entries.back();
                                                free_entries.pop_back();
                                        }
                                node->key = key; 
                                node->data = data;
                                cache_enteries[key] = node;
                                addnode(node);
                                }
                        }

                 D search_cache(K key)
                        {
              			random_node<K,D> *node = cache_enteries[key];
                                if(node)
                                { // hit
                                        return node->data;
                                }
                                else
                                { //miss
                                        return D();
                                }                                                                                                                             		 }
};


#endif
