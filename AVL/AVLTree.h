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
	int _bf;//平衡因子(右子数高度减去左子树高度)
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

			else //该节点已经存在，返回
				return false;
		}
		// 插入节点
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
		//更新平衡因子
		cur = tmp;
		while (parent)
		{
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
				parent->_bf++;
		     // bf == 0 则树不需要调整
			 // bf== 1或者-1则上层节点需要调整
			// bf == -2或者2 则需要调整
			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2) //开始调整
			{
				if (parent->_bf == 2 && cur->_bf == 1) //(2,1)  左单旋
				{
					_RotateL(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1) //(2,-1）右左双旋
				{
					_RotateRL(parent);
				}

				if (parent->_bf == -2 && cur->_bf == -1) //(-2,-1) 右单旋
				{
					_RotateR(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1) //(2,1)左右双旋
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
	void _RotateL(Node* parent)//左单旋
	{
		Node* subR= parent->_right; //右孩子
		Node* subRL = subR->_left;  //右孩子的左
		Node* ppNode = parent->_parent;//当前父节点的父亲
	    // 父节点变成右孩子的左
		subR->_left = parent;
		parent->_parent = subR;
		
		//右孩子的左子树给父节点的右
		   parent->_right = subRL;
		if (subRL) //如果subRL不为空
		{
			subRL->_parent = parent;
		}
		if (ppNode == NULL)  // ppNode为空 说明传进来的是头结点
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
		//父节点变成孩子的右
		subL->_right = parent;
		parent->_parent = subL;
		//左孩子的右子树给父节点的左
		parent->_left = subLR;		
		if (subLR)
		{
			subLR->_parent = parent;
		}
		if (ppNode == NULL) // ppNode为空说明 传进来的是头结点
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
		subL->_bf = parent->_bf = 0; //调整完后，parent 和subL的平衡因子为0
	}
	void _RotateLR(Node* parent)
	{   
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		_RotateL(parent->_left);
		_RotateR(parent);
		 //bf 取值 -1，0，1
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
			cout << "该节点平衡因子异常:" << " ";
			cout << root->_k << endl;
		}
		return abs(rightHeight - leftHeight) < 2 && 
			_IsBalance(root->_left) && 
			_IsBalance(root->_right);
	}
protected:
	Node* _root;
};



