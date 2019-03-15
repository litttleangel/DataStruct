#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__
#include <queue>
#include <vector>
#include<iostream>
using namespace std;


template <class W>
struct HuffmanTreeNode
{
	HuffmanTreeNode<W>* _left;
	HuffmanTreeNode<W>* _right;
	W _w;
	HuffmanTreeNode(const W& w)
		:_w(w)
		, _left(NULL)
		, _right(NULL)
	{}
};

template <class W>
class HuffmanTree
{
	typedef HuffmanTreeNode<W> Node;
public:
	HuffmanTree()
		:_root(NULL)
	{}

	struct NodeComp
	{
		//仿函数，使之按照结点内的权值比较大小，而不是按指针
		//这种只比较，不修改的写成const最好
		//但是随之而来的问题就是，如果w是自定义类型，而不仅仅是内置类型
		//那么就要注意，const修饰的l和r能不能调用w内部的函数
		//即const对象不能调用非const函数
		bool operator()(const Node* l, const Node* r)
		{
			return l->_w > r->_w;
		}
	};

	HuffmanTree(W* w, size_t n, const W& invalid)//判断非法值，即_count>1才插入，节省空间
	{
		//构建huffman树
		priority_queue<Node*, vector<Node*>, NodeComp> minHeap;
		for (size_t i = 0; i < n; ++i)
		{
			if (w[i] != invalid)
				minHeap.push(new Node(w[i]));
		}
		while (minHeap.size() > 1)
		{
			Node* left = minHeap.top();
			minHeap.pop();
			Node* right = minHeap.top();
			minHeap.pop();
			Node* parent = new Node(left->_w + right->_w);
			parent->_left = left;
			parent->_right = right;
			minHeap.push(parent);
		}
		_root = minHeap.top();

	}

	~HuffmanTree()
	{
		//释放树的空间
		Destroy(_root);
		_root = NULL;
	}
	void Destroy(Node* root)
	{
		if (root == NULL)
			return;
		Destroy(root->_left);
		Destroy(root->_right);
		delete(root);
	}
	Node* GetRoot()
	{
		return _root;
	}
protected:
	Node* _root;
private:
	//防拷贝，C++11的话可以直接在构造函数后面加delete
	HuffmanTree(const HuffmanTree<W>& h);
	HuffmanTree<W>& operator=(const HuffmanTree<W>& h);
};

#endif //__HUFFMAN_H__
