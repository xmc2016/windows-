#pragma once
#include<iostream>
#include<assert.h>
#include<vector>
using namespace std;
template<class T>
// 利用仿函数特性实现代码的复用性
struct Small
{
	bool operator()(const T& a, const T& b)
	{
		return a < b;
	}
};
template< class T>
struct Large
{
	bool operator()(const T& a, const T& b)
	{
		return a>b;
	}
};
template<class T, class Compare = Large<T>> // 默认建大堆
class Heap
{
public:
	Heap(const T* a, int size) 
	{
		assert(a);
		_a.reserve(size);
		for (int i = 0; i < size; i++) // 先将所有元素放到vector里
		{
			_a.push_back(a[i]);
		}
		// 建堆的时候从倒数第一个非叶子节点开始
		for (int j = (size - 2) / 2; j >= 0; j--) // 堆在数组存放时，父节点的下标等于子节点的下标减一除二取整
		{
			_AdjustDown(j);
		}
	}
	void Push(const T& x)
	{
		_a.push_back(x);
		_AdjustUp(_a.size() - 1);
	}
	void Pop()// 删除堆顶元素
	{
		assert(!_a.empty());
		swap(_a[0], _a[_a.size() - 1]);
		_a.pop_back();
		_AdjustDown(0);
	}
     size_t Size()
	{
		 return _a.size();
	}
	 bool Empty()
	 {
		 return _a.empty();
	 }
	 void Display()
	 {
		 for (size_t i = 0; i < _a.size(); i++)
		 {
			 cout << _a[i] << " ";
		 }
		 cout << endl;
	 }
	const T& Top()  const 
	 {
		 assert(!_a.empty());
		 return _a[0];
	 }
protected:
	void _AdjustDown(int parent) //向下调整
	{
		size_t child = 2 * parent + 1; //praent的左孩子
		while (child < _a.size())
		{
			Compare com;
			if (child +1< _a.size()&& com(_a[child+1], _a[child]))
			{
				child++;
			}
			if (com(_a[child], _a[parent]))
			{
				swap(_a[parent], _a[child]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
			{
				break;
			}
		}
		
	}
	void _AdjustUp(int child) //向上调整
	{
		int parent = (child - 1) / 2;
		while (parent >= 0)
		{
			Compare com;
			if (com(_a[child], _a[parent]))
			{
				swap(_a[child] ,_a[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}
protected:
	vector<T> _a;
};
template< class T,class Compare = Large<T>>
class PriorityQueue // 优先级队列
{
public:
	PriorityQueue( T* a, size_t size)
		:_pq(a, size){}
	const T& Top() const
	{
		return _pq.Top();
	}
	void Push(  const T& x)
	{
		_pq.Push(x);
	}
	void Pop()
	{
		_pq.Pop();
	}
	void Display()
	{
		_pq.Display();
	}
protected:
	Heap<T, Compare> _pq;
};