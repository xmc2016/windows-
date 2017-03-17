//开链发哈希表
#pragma once
#include<iostream>
#include<vector>
using namespace std;
template <class K,class V>
struct KVNode
{
	K _k;
	V _v;
	KVNode<K, V>* _next;
	KVNode(const K& key = K(), const V value = V())
		:_k(key)
		, _v(value)
		, _next(NULL){}
};
template<class K>
struct __HashFunc
{
	size_t  operator()(const K& key)
	{
		return key;
	}
};
template<>  //对string类实行偏特化
	struct __HashFunc<string>
	{
		size_t operator()(const string& str)
		{
			size_t hash = 0;
			for (int i = 0; i < (int)str.size(); i++)
			{
				hash += hash * 131 + str[i];
			}
			return hash;
		}
	};
template<class K,class V,class HashFunc = __HashFunc<K>>
class HashTables
{
	typedef KVNode<K, V> Node;
public:
	HashTables()
		:_size(0)
	{
	 _tables.resize(_GetNextPrime(0));
	}
	~HashTables()
	{
		for (size_t i = 0; i < _tables.size(); i++)
		{
			Node* cur = _tables[i];
			Node* del = NULL;
			while (cur)
			{
				del = cur;
				cur = cur->_next;
				delete del;
			}
		}
	}
	bool Insert(K key,V value)
	{
		_CheckSize();
		if (Find(key))
		{
			return false;
		}
		size_t index = __HushFunc(key, _tables.size());
			//头插 ,使用替换法
		Node* tmp = new Node(key, value);
		/*Node* cur = _tables[index];
		_tables[index] = tmp;
		_tables[index]->_next = cur;*/
		tmp->_next = _tables[index];
		_tables[index] = tmp;
		_size++;
		return true;

	}
	Node* Find(const K key)
	{
		size_t index = __HushFunc(key, _tables.size());
			Node* cur = _tables[index];
		while (cur)
		{
			if (cur->_k == key)
			{
				cout << "该元素存在" << " ";
				return cur;
			}
			cur = cur->_next;
		}
		cout << "该元素不存在" << " ";
		return NULL;
	}
	bool Remove(K key) 
	{
		size_t index =  __HushFunc(key,_tables.size());
		Node* cur = _tables[index];
		Node* prev = NULL;
		while (cur)
		{
			if (cur->_k = key)
			{
				if (prev == NULL) //删除的是第一个节点
				{
					_tables[index] = cur->_next;
				}
				else //删除的是中间节点或者是最后一个节点
				{
					prev->_next = cur->_next;
				}
				delete cur;
				--_size;
				return true;
			}
			prev = cur;
			cur = cur->_next;
		}
		
	}
void Print()
	{
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			Node* cur = _tables[i];
			printf("_tables[%d]->", i);
			while (cur)
			{
				printf("%d->", cur->_k);
				cur = cur->_next;
			}
			cout << "NULL" << endl;
		}
	}

void Swap( HashTables<K, V, HashFunc>& hash)
	{
		_tables.swap(hash._tables);
		swap(_size, hash._size);
	}
protected:
int __HushFunc(K key,size_t size)
 {
	return (HashFunc()(key)) % size;
 }
  void _CheckSize()
   {
		if ((_tables.size()== 0) || (_size ==_tables.size()))
		{
			HashTables<K,V,HashFunc> hash;
			hash._tables.resize( _GetNextPrime(_tables.size()));
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					hash.Insert(cur->_k, cur->_v);
					cur = cur->_next;
				}
			}
			Swap(hash);
		}
   }
unsigned long  _GetNextPrime(size_t num)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] = 
		{
			53, 97, 193, 389, 769,
			1543, 3079, 6151, 12289, 24593,
			49157, 98317, 196613, 39324, 786433,
			1572869, 3145739, 6291469, 12582917, 25165843,
			50331653, 100663319, 201326611, 402653189, 805306457,
			1610612741, 3221225473, 4294967291
		};
		for (size_t i = 0; i < _PrimeSize; i++)
		{
			if ( _PrimeList[i]> num)
			{
				return _PrimeList[i];
			}
		}
	}
protected:
	vector<Node*> _tables;
	size_t _size;
};
