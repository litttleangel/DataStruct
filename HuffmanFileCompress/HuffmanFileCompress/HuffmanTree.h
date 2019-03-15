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
		//�º�����ʹ֮���ս���ڵ�Ȩֵ�Ƚϴ�С�������ǰ�ָ��
		//����ֻ�Ƚϣ����޸ĵ�д��const���
		//������֮������������ǣ����w���Զ������ͣ�������������������
		//��ô��Ҫע�⣬const���ε�l��r�ܲ��ܵ���w�ڲ��ĺ���
		//��const�����ܵ��÷�const����
		bool operator()(const Node* l, const Node* r)
		{
			return l->_w > r->_w;
		}
	};

	HuffmanTree(W* w, size_t n, const W& invalid)//�жϷǷ�ֵ����_count>1�Ų��룬��ʡ�ռ�
	{
		//����huffman��
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
		//�ͷ����Ŀռ�
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
	//��������C++11�Ļ�����ֱ���ڹ��캯�������delete
	HuffmanTree(const HuffmanTree<W>& h);
	HuffmanTree<W>& operator=(const HuffmanTree<W>& h);
};

#endif //__HUFFMAN_H__
