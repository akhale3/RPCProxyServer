#ifndef __lrucache_H
#define __lrucache_H
#include <iostream>
#include <vector>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;

template <class K, class D>
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
    LRUnode<K,D> *no_of_entries;

    void deletenode(LRUnode<K,D>* node)
    {
      node->prev->next = node->next;
      node->next->prev = node->prev;
    }
    
    // insert the node into head
    void addnode(LRUnode<K,D>* node)
    {
      node->prev = head;
      node->next = head->next;
      head->next = node;
      node->next->prev = node;
    }

  public:
    Cache(size_t size) 
    {
      no_of_entries = new LRUnode<K,D>[size];

      for(int i=0; i<size; ++i) 
      {
        free_entries.push_back(no_of_entries+i);
      }
      head = new LRUnode<K,D>;
      tail = new LRUnode<K,D>;
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
      LRUnode<K,D> *node = cache_entries[key];
      if(node) 
    	{ // node exists
        deletenode(node);
        node->data = data;
        addnode(node);
      }	 
      else 
      {
        if(free_entries.empty()) 
    		{
          // cache is full
          node = tail->prev;
          deletenode(node);
          cache_entries.erase(node->key);
        } 
        else 	
    		{
          //get a free node from _free_entries
          node = free_entries.back();
          free_entries.pop_back();
        }
  			node->key = key; //put into hashmap and insert into link
  			node->data = data;
        //cout << node->key << "\n";
        //cout << node->data << "\n";
  			cache_entries[key] = node;
        //cout << _hashmap[key] << "\n";
  			addnode(node);
      }
    }	

    D search_cache(K key) 
    {
  		//cout << "Get" << "\n";
      LRUnode<K,D> *node = cache_entries[key];
      //cout << _hashmap[key] << "\n";
      if(node)
      { // hit
        deletenode(node);
        addnode(node);
        //cout << "Hit" << "\n";
        return node->data;
      }
      else
      {
        // fail to hit
        //cout << T() << "\n";
        return D();
      }
    }
};

#endif