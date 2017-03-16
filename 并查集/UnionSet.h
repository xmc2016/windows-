#pragma once 
#include<iostream>
#include<stdio.h>
#include<assert.h>
using namespace std;
class UnionSet
{
public:
	UnionSet(int size) :_size(size)
	{
	     _parent  = new int[size];
		for (int i = 0; i < size; i++)
		{
			_parent[i] = -1;
		}
	}
	//将root2合并到root1中
	void Union(int x, int y)
	{
		int root1 = FindRoot(x);
		int root2 = FindRoot(y);
		if (root1 != root2)
		{
			_parent[root1] += _parent[root2];
			_parent[root2] = root1;
		}
	}
	int FindRoot(int x)
	{
		int cur = x;
		while (_parent[cur] >=0)
		{
			cur = _parent[cur];
		}
		return cur;
	}
	void Display()
	{
		for (int i = 0; i < _size; i++)
		{
			cout << _parent[i] << " ";
		}
		cout << endl;
	}
	~UnionSet()
	{
		delete[] _parent;
	}

protected:
	int *_parent;
	int _size;
};


