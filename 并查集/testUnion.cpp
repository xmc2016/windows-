//#include"UnionSet.h"
#include<iostream>
using namespace std;
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
////void TestUnion()
//{
//	UnionSet s(10);
//	s.Union(0, 6);
//	s.Union(0, 7);
//	s.Union(0, 8);
//	s.Union(1, 4);
//	s.Union(1, 9);
//	s.Union(2, 3);
//	s.Union(2, 5);
//	s.Display();
//
//}
// С�׵�2016��������==���������μ��μ�
void UnionSet(int* unionSet, int root1, int root2)
{
	unionSet[root1] += unionSet[root2];
	unionSet[root2] = root1;
}
int FindRoot(int* unionSet, int x) //����
{
	int cur = x;
	while (unionSet[cur]>=0)
	{
		cur = unionSet[cur];
	}
	return cur;
}
int Friends(int arr[][2], int m, int n)
{
	//�������鼯
	const int N = n + 1;
	int* unionSet = new int[N];
	memset(unionSet, -1, N*sizeof(unionSet));
	for (int i = 0; i < m; ++i)
	{
		int first = arr[i][0];
		int second = arr[i][1];

		int parent1 = FindRoot(unionSet, first);
		int parent2 = FindRoot(unionSet, second);
		if (parent1 != parent2)
		{
			UnionSet(unionSet, parent1, parent2);
		}
	}
	int count = 0; //ͳ������Ȧ����
	for (int i = 0; i < n; i++)
	{
		if (unionSet[i] < 0)
		{
			++count;
		}
	}
	delete[] unionSet;
	return count;
}

int main()
{
//	TestUnion();
	int r[5][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 }, { 1, 3 }, { 2, 4 } };
	cout << "N������Ȧ?" << Friends(r,5,5) << endl;
	system("pasue");
	return 0;
}