//#include"Hash.h"
#include"hash2.h"
void TestHush()
{

	int a[15] = { 160, 159, 440, 251, 252, 263, 24, 285, 241, 202, 230, 25, 265,758,100};
	HashTables<int,int>  ht;
	for (size_t i = 0; i < 15; i++)
	{
		ht.Insert(a[i], i);
	}
	ht.Print();
	ht.Find(26);
	ht.Find(100);
    ht.Find(1000);
	ht.Remove(24);
     ht.Print();
	

}
int main()
{
	TestHush();
	system("pause");
	return 0;
}
//struct HashNode
//{
//	K _k,
//	V _v; 
//	Status _status;
//	HashNode* next;
//};
//
//
//
//
////·Âº¯Êý
//template <class K>
//struct __HushFunc
//{
//	size_t operator()(const K& key)
//	{
//		return key;
//	}      
//};
//struct _STringHashFUnc
//{
//	size_t operator()(const string& str)
//	{
//
//	}
//};
//size_t _HushFunc(const K& key)
//{
// 
//	__HushFunc hf;
//	return hf(key) % _tables.size()
//}