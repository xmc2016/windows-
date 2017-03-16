#pragma once
#include<iostream>
using namespace std;
template<class K,class V>
struct AVLTreeNode
{
	K _k;
	V _value;
	 
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;//ƽ������(�������߶ȼ�ȥ�������߶�)
	AVLTreeNode(const K& k = K(),const V& value = V())
		:_k(k)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		,_bf(0)
	{}
};
template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V>  Node;
public:
	AVLTree() :_root(NULL)
	{}
	bool Insert(const K& k, const V& v)
	{
		return _Insert(_root, k, v);
	}

	void  InOrder()
	{
		_InOrder(_root);
	}
	int Height()
	{
		return _Height(_root);
	}
	bool IsBalance()
	{
		return _IsBalance(_root);
	}
protected:
	bool _Insert(Node* root, const K& k, const V& v)
	{
		if (root == NULL)
		{
			_root = new Node(k, v);
			return true;
		}
		Node* cur = root;
		Node* parent = NULL;
		while (cur)
		{
			if (k > cur->_k)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (k < cur->_k)
			{
				parent = cur;
				cur = cur->_left;
			}

			else //�ýڵ��Ѿ����ڣ�����
				return false;
		}
		// ����ڵ�
		Node* tmp = new Node(k, v);
		if (k < parent->_k)
		{
			parent->_left = tmp;
			tmp->_parent = parent;
		}
		else
		{
			parent->_right = tmp;
			tmp->_parent = parent;
		}
		//����ƽ������
		cur = tmp;
		while (parent)
		{
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
				parent->_bf++;
		     // bf == 0 ��������Ҫ����
			 // bf== 1����-1���ϲ�ڵ���Ҫ����
			// bf == -2����2 ����Ҫ����
			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2) //��ʼ����
			{
				if (parent->_bf == 2 && cur->_bf == 1) //(2,1)  ����
				{
					_RotateL(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1) //(2,-1������˫��
				{
					_RotateRL(parent);
				}

				if (parent->_bf == -2 && cur->_bf == -1) //(-2,-1) �ҵ���
				{
					_RotateR(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1) //(2,1)����˫��
				{
					_RotateLR(parent);
				}
				break;
			}

		}
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		Node* cur = root;
		_InOrder( cur->_left);
		cout << cur->_k << " ";
		_InOrder( cur->_right);

	}
	
protected:
	void _RotateL(Node* parent)//����
	{
		Node* subR= parent->_right; //�Һ���
		Node* subRL = subR->_left;  //�Һ��ӵ���
		Node* ppNode = parent->_parent;//��ǰ���ڵ�ĸ���
	    // ���ڵ����Һ��ӵ���
		subR->_left = parent;
		parent->_parent = subR;
		
		//�Һ��ӵ������������ڵ����
		   parent->_right = subRL;
		if (subRL) //���subRL��Ϊ��
		{
			subRL->_parent = parent;
		}
		if (ppNode == NULL)  // ppNodeΪ�� ˵������������ͷ���
		{
			subR->_parent = ppNode;
			_root = subR;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}
		
		parent->_bf = subR->_bf = 0;
	}
	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;
		//���ڵ��ɺ��ӵ���
		subL->_right = parent;
		parent->_parent = subL;
		//���ӵ������������ڵ����
		parent->_left = subLR;		
		if (subLR)
		{
			subLR->_parent = parent;
		}
		if (ppNode == NULL) // ppNodeΪ��˵�� ����������ͷ���
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
				subL->_parent = ppNode;
			}
			else
			{
				ppNode->_right = subL;
				subL->_parent = ppNode;
			}
		}
		subL->_bf = parent->_bf = 0; //�������parent ��subL��ƽ������Ϊ0
	}
	void _RotateLR(Node* parent)
	{   
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		_RotateL(parent->_left);
		_RotateR(parent);
		 //bf ȡֵ -1��0��1
		if (bf == 0)
		{
			subL->_bf = parent->_bf = 0;
		}
		else if (bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
		}
		else if (bf ==1)
		{
			subL->_bf = -1;
			parent->_bf = 0;
		}
	}
	void _RotateRL(Node* parent)
	{
	
		Node* subR= parent->_right;
		Node* subLR = subR->_left;
			int bf = subLR->_bf;

		_RotateR(parent->_right);
		_RotateL(parent);
		if (bf == 0)
		{
			subR->_bf = parent->_bf = 0;
		}
		else if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
		}
	}
	int _Height(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		else
		{
			int leftH = _Height(root->_left) + 1;
			int rightH = _Height(root->_right) + 1;
			return leftH > rightH ? leftH : rightH;
		}
	}
	bool _IsBalance(Node* root)
	{
		if (root == NULL)
		{
			return true;
		}
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		if (abs(root->_bf) != abs(rightHeight - leftHeight))
		{
			cout << "�ýڵ�ƽ�������쳣:" << " ";
			cout << root->_k << endl;
		}
		return abs(rightHeight - leftHeight) < 2 && 
			_IsBalance(root->_left) && 
			_IsBalance(root->_right);
	}
protected:
	Node* _root;
};



