#include<iostream>
#include<stdio.h>


struct BTNode 
{
	BTNode*_left;
	BTNode*_right;
	int _data;
};

//ǰ����������������ݹ�
void BTreePrevOrder(BTNode* root)
{
	if (root = NULL)
		return;
	printf("%d", root->_data);
	BTreePrevOrder(root->_left);
	BTreePrevOrder(root->_right);

}


//������������������ݹ�
void BTreeMidOrder(BTNode* root)
{
	if (root == NULL)
		return;;
	BTreeMidOrder(root->_left);
	printf("%d", root->_data);
	BTreeMidOrder(root->_right);
}