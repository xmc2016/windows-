#include"heap.hpp"
void TestHeap()
{
	int a[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	int size = sizeof(a) / sizeof(a[0]);
	Heap<int> heap(a, size);
	heap.Display();
	cout << heap.Size() << endl;;
	/*heap.Push(28);
	heap.Display();
	heap.Pop();
	heap.Display();
	cout << heap.Top() << endl;
	Heap<int, Small<int>> h2(a, size);
	h2.Display();
	cout << h2.Top() << endl;*/
}
void testPriQueue()
{
	int a[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	int size = sizeof(a) / sizeof(a[0]);
	PriorityQueue<int> pq1(a, size);
	pq1.Display();  //19  17  18  14  16  13  15  12  10
	cout << "Top?" << pq1.Top() << endl;  //19

	pq1.Push(20);
	pq1.Display();  //20  19  18  14  17  13  15  12  10  11  16
	pq1.Pop();
	pq1.Display();

	PriorityQueue<int, Small<int>> pq2(a, size);
	pq2.Display();  //10  11  13  12  16  18  15  17  14  19
}

int main()
{
   TestHeap();
	//testPriQueue();
	system("pause");
	return 0;
}