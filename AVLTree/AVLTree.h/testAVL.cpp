#include"AVLTree.h"
void test()
{
	AVLTree<int, int> tree;
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14,15};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	/*for (size_t i = 0; i < size; i++)
	{
		tree.Insert(arr[i], i);
	}*/
	tree.Insert(16, 1);
	tree.Insert(3, 1);
	tree.Insert(7, 1);
	tree.Insert(11, 1);
	tree.Insert(9, 1);
	tree.Insert(26, 1);
	tree.Insert(18, 1);
	tree.Insert(14, 1);
	tree.Insert(15, 1);
	tree.InOrder();
	cout << endl;
	cout << tree.Height() << endl;
	cout << "isbalance" << tree.IsBalance() << endl;;
	AVLTree<int, int> tree2;
	int arr2[] =  {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); i++)
	{
		tree2.Insert(arr2[i], i);
	}
	tree2.InOrder();
	cout << endl;
	cout << tree2.Height() << endl;
	cout << " isbalance?"<<tree2.IsBalance() << endl;;

}

int main()
{
	test();
	system("pause");
	return 0;
}