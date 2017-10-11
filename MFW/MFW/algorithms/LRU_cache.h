#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

using namespace std;

namespace MFWAlg {
	template<typename K,typename V>
		class LRUCache {
			typedef struct _Node_{
				K key;
				V value;

				struct _Node_ *next;
				struct _Node_ *pre;
			} CacheNode;

		public:
			LRUCache(int cache_size=10) {
				cache_size_ = cache_size;
				p_cache_list_head = new CacheNode();
				p_cache_list_near = new CacheNode();
				p_cache_list_head->next = p_cache_list_near;
				p_cache_list_head->pre = NULL;
				p_cache_list_near->pre = p_cache_list_head;
				p_cache_list_near->next = NULL;
			}

			~LRUCache() {
				CacheNode *p;
				p = p_cache_list_head->next;
				while(p!=NULL) {	
					delete p->pre;
					p=p->next;
				}

				delete p_cache_list_near;
				cache_hash.clear();
			}

			V getValue(K key) {
				//put the value in front of the list if find the key
				if(cache_hash.find(key) != cache_hash.end()){
					CacheNode *p=cache_hash[key];
					detachNode(p);
					addFristNode(p);
					return (cache_hash[key]->value);
				}else{

					cout << "[ERROR]No key with name ::" << key << endl;
					return V();
				}

			}

			bool putValue(K key,V value) {
				if (cache_hash.find(key) != cache_hash.end()) {
					cache_hash[key]->value=value;
					detachNode((CacheNode *)cache_hash[key]);
					addFristNode((CacheNode *)cache_hash[key]);
					if (cache_hash.size()>cache_size_) {
						delEndNode();					
					}
				} else {
					CacheNode *p=new CacheNode();
					p->key=key;
					p->value=value;
					addFristNode(p);
					cache_hash[key]=p;
					if(cache_hash.size()>cache_size_){
						cout << "[INFO]LRU Cache is full ... Delete Last One..." << endl;
						delEndNode();
					}
				}

				return true;	
			}

			void display(){	
				CacheNode *p=p_cache_list_head->next;
				while(p->next!=NULL) {
					std::cout << " KEY[" << p->key << "]<==>VALUE[" << p->value <<"]" << std::endl; 
					p=p->next;
				}
				std::cout << std::endl;			
			}

		private:
			int cache_size_;
			CacheNode *p_cache_list_head;
			CacheNode *p_cache_list_near;
			map<K,CacheNode*>cache_hash;


			void detachNode(CacheNode *node){
				node->pre->next=node->next;
				node->next->pre=node->pre;		
			}

			void addFristNode(CacheNode *node){
				node->pre=p_cache_list_head;			
				if(cache_hash.empty()) {
					node->next=p_cache_list_near;
					p_cache_list_near->pre=node;
					p_cache_list_head->next=node;
				} else {
					node->next=p_cache_list_head->next;
					p_cache_list_head->next->pre=node;
					p_cache_list_head->next=node;
				}
			}

			void delEndNode(){
				CacheNode *p=p_cache_list_near->pre;
				detachNode(p);
				cout << "[INFO]Delete key ::: " << p->key <<endl;
				cache_hash.erase(p->key);
				free(p);
			}
		};
}

