#pragma once
#include<iostream>
#include<vector>
using namespace std;
enum Status
{
	EMPTY,
	EXITS,
	DELETE
};
template<class K,class V>
struct KVNode
{
	K _k;
	V _v;
	Status _status;
	KVNode(const K key = K(), const V value = V())
		:_k(key)
		, _v(value)
		, _status(EMPTY){}
};
template<class K,class V>
class HashTable
{
	typedef KVNode<K, V>  Node;
public:
	HashTable()
		:_size(0)
	{
		_tables.resize(_GetNextPrime(0));
	}
	bool Insert(K key,V value)
	{
		_CheckSize();
		size_t index = _HashFunc(key);
		while (_tables[index]._status == EXITS)
		{
			if (_tables[index]._k == key)
				return false;
			++index;
			if (index == _tables.size())
				index = 0;

		}
		_tables[index]._k = key;
		_tables[index]._v = value;
		_tables[index]._status = EXITS;
		_size++;
		return true;
	}
	bool Erase(K key)
	{
		size_t index = _HashFunc(key);
		while (_tables[index]._k != key&&_tables[index]._status == EXITS)
		{
			size_t tag = index;
			index++;
			if (index == _tables.size())
				index = 0;
			else if (index == tag)
			{
				break;
			}
		}
		if (_tables[index]._k == key&&_tables[index]._status == EXITS)
		{
			_tables[index]._status = DELETE;
			cout << "删除成功" << endl;
			_size--;
			return true;
		}
		else
		{
			cout << "无该元素" << endl;
			return false;
		}

	}
	void Find(K key)
	{
		Node* cur = _Find(key);
		if (cur)
		{
			cout << cur->_k << " " << cur->_v << " " << cur->_status;
		}
		else
		{
			cout << "无该元素";
      }
		cout << endl;
	}
	void Display()
	{
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			if (_tables[i]._status == EXITS)
			{
				cout << _tables[i]._k<<" ";
			}

		}
		cout << endl;
	}
protected:
	
	Node* _Find(const K& key)
	{
		size_t index = _HashFunc(key);
		while (_tables[index]._k != key &&_tables[index]._status == EXITS)
		{
			size_t tag = index;
			index++;
			if (index == _tables.size())
				index = 0;
			if (index == tag)
			{
				break;
			}
		}
		if (_tables[index]._k == key&&_tables[index]._status == EXITS)
		{
			return &_tables[index];
		}
		else
		{
			return NULL;
		}
	}
	size_t _HashFunc(K key)
	{
		return  key % _tables.size();
	}
unsigned long  _GetNextPrime(size_t num) //最大容量为4G
	{
		const int _Primesize = 28;
		unsigned long  _PrimeList[_Primesize] =
		{
			53,    97,    193,  389,   769,
			1543,  3079,6151,12289,24593,
			49157, 98317,196613, 39324, 786433,
			1572869, 3145739,6291469,12582917,25165843,
			50331653, 100663319, 201326611,402653189,805306457,
			1610612741, 3221225473, 4294967291
		};
		for (size_t i = 0; i < _Primesize; ++i)
		{
			if (_PrimeList[i]>num)
			{
				return _PrimeList[i];
			}		    
		}
	}
	void _CheckSize()
	{
		if (_tables.size() == 0 || _size * 10 / _tables.size() >= 8)
		{
			unsigned long  newSize = _GetNextPrime(_tables.size());
			HashTable<K, V> hash;
			hash._tables.resize(newSize);
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i]._status == EXITS)
					hash.Insert(_tables[i]._k, _tables[i]._v);
			}
			this->_Swap(hash);
		}
		
	}
	void _Swap(HashTable hash)
	{
		_tables.swap(hash._tables);
		swap(_size, hash._size);
	}
protected:
	vector<Node> _tables;
	size_t  _size;
};