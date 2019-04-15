#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int DataType;
typedef struct LinkList LinkList;

typedef struct LinkList 
{
	struct LinkList*_next;
	DataType _data;

}LinkList;

//创建一个节点
LinkList*BuyNode(DataType x)
{
	LinkList*newNode = (LinkList*)malloc(sizeof(LinkList));
	if (newNode != NULL)//如果创建成功
	{
		newNode->_data = x;
		newNode->_next = NULL;
	}
	return newNode;

}

swap(int*x, int*y)
{
	DataType tmp = *x;
	*x = *y;
	*y = tmp;
}
//1.从尾到头打印单链表
//思路：双重循环，非递归——每次遍历一遍，打印最后一个节点，范围缩小一个

void LinkListPrint(LinkList*head)
{
	assert(head != NULL);
	LinkList*end = NULL;
	while (end != head)
	{
		LinkList*cur = head;
		while (cur->_next!=end)
		{
			cur = cur->_next;
		}
		printf("%d\n", cur->_data);
		end = cur;//每次范围会缩小一个
	}

}



//2.删除一个无头单链表的非尾节点（不能遍历链表）
//

void Remove(LinkList*node)
{
	assert(node != NULL);
	LinkList*cur = node->_next;
	node->_data = cur->_data;
	node->_next = cur->_next;
	free(cur);

}


//3.在无头单链表的一个非尾节点前插入一个节点（不能遍历单链表）

void Insert(LinkList*node, size_t x)
{
	assert(node != NULL);
	LinkList*cur = BuyNode(x);
	cur->_next = node->_next;
	node->_next = cur;
	swap(cur->_data, node->_data);
}

//4.单链表实现约瑟夫环
//思路：约瑟夫环是一个环，每走k步，就将第k个节点删除，
//然后从当前节点开始，再往前找第k个节点


LinkList*JosephCircle(LinkList*node, size_t k)
{
	if (node == NULL || node->_next == node)
		return node;
	LinkList*cur = node;
	while (cur != cur->_next)
	{
		int i = 0;
		while (i != k)
		{
			cur = cur->_next;
			i++;
		}
		//删除第k个节点
		LinkList*tmp = cur->_next;
		cur->_data = tmp->_data;
		cur->_next = tmp->_next;
		free(tmp);
	}
	
	return cur;

}


//5.逆置单链表——头插法（改变指针指向）
LinkList* Reserve(LinkList*node)
{
	if (node == NULL || node->_next == node)
		return node;
	LinkList*newNode = NULL;
	while (node != NULL)
	{
		LinkList*cur = node->_next;
		node->_next = newNode;
		newNode = node;
		node = cur;

	}
	return newNode;
}
//三指针法
LinkList*ReserveList(LinkList*node)
{
	LinkList*n1, *n2, *n3;
	if( node==NULL||node->_next=NULL)
	{
		return node;
	}
	n1 = node;
	n2 = n1->_next;
	n3 = n2->_next;

	n1->_next = NULL;//方便逆置过来时，原来的头结点应该指向空

	while (n2 != NULL)
	{
		n2->_next = n1;
		n1 = n2;
		n2 = n3;
		while (n3 != NULL)
		{
			n3 = n3->_next;
		}
	}
	return n1;//返回头结点
}

//6.链表排序——冒泡排序
void LinkListBubbleSort(LinkList*node)
{
	LinkList*tail = NULL;
	DataType flag = 0;
	if (node = NULL || node->_next == NULL)
	{
		return node;
	}
	while (node!=tail)//链表不能为空
	{
		LinkList*cur = node;
		LinkList*next = cur->_next;
		while (next != tail)
		{
			if (cur->_data > next->_data)
			{
				flag = 1;
				DataType tmp = cur->_data;
				cur->_data = next->_data;
				next->_data = tmp;
			}
			cur = cur->_next;
			next = next->_next;
		}

		if (flag == 0)
		{
			return;
		}
		tail = cur;//缩小范围
	}

}


//7.合并两个有序链表,合并后依然有序——以排升序为例
LinkList* MergeLinkList(LinkList* pHead1, LinkList* pHead2)
{
	if (pHead1 == NULL)
	{
		return pHead2;
	}
	if (pHead2 == NULL)
	{
		return pHead1;
	}
	LinkList*newHead = NULL;//把排序好的链表存放在这个里面
	LinkList* tail = NULL;//记录当前链表的最后一个位置

	if (pHead1->_data < pHead2->_data)
	{
		newHead = pHead1;
		pHead1 = pHead1->_next;
	}
	else
	{
		newHead = pHead2;
		pHead2 = pHead2->_next;
	}

	tail = newHead;//确定新链表的头结点

	while (pHead1 != NULL&&pHead2 != NULL)
	{
		if (pHead1->_data < pHead2->_data)
		{
			tail->_next = pHead1;
			pHead1 = pHead1->_next;
		}
		else
		{
			tail->_next = pHead2;
			pHead2 = pHead2->_next;

		}
		tail = tail->_next;//插入一个节点，tail便向后挪一个
	}

	if (NULL == pHead1)
	{
		tail->_next = pHead2;
	}
	else if (NULL == pHead2)
	{
		tail->_next = pHead1;
	}

	return newHead;
}

//递归
LinkList* MergeLinkList(LinkList* pHead1, LinkList* pHead2)
{
	if (pHead1 == NULL)
	{
		return pHead2;
	}
	if (pHead2 == NULL)
	{
		return pHead1;
	}

	LinkList*newHead = NULL;//把排序好的链表存放在这个里面

	while (pHead1 != NULL && pHead2 != NULL)
	{
		if (pHead1->_data < pHead2->_data)
		{
			newHead = pHead1;
			newHead->_next = MergeLinkList(pHead1->_next, pHead2);
		}

		else
		{
			newHead = pHead2;
			newHead->_next = MergeLinkList(pHead1, pHead2->_next);
		}
			
	}
}

	


//8.查找一个链表的中间节点，要求只能遍历一次

LinkList* FindMidNode(LinkList* node) // 遍历一遍找到链表中间节点
{
	if (node != NULL&&node->_next != NULL)
	{
		return node;
	}
	LinkList*fast = node;
	LinkList*slow = node;
	while (fast->_next != NULL)
	{
		fast = fast->_next->_next;
		slow = slow->_next;
	}
	return slow;
}



//9.查找单链表的倒数第k个节点，要求只能遍历一次链表
LinkList* FindReciprocalKNode(LinkList* node, size_t k) //遍历一遍查找倒数第K个节点
{
	assert(node!= NULL&&k!=0);

	LinkList*fast = node;
	LinkList*slow = node;
	while (fast->_next != NULL)
	{
		k--;
		if (k <= 0)
		{
			slow = slow->_next;//当快指针走了k-1步后，即走到第k个节点时，慢指针再开始走
		}
		fast = fast->_next;
		
	}
	
	//当k=链表长度时，k--之后得到——k的最大值，是1
	if (k <= 1)  
	{
		return slow;
	}
	else  //当k的值大于1时，代表查找失败(此种情况是k的值>链表长度时)
	{
		return NULL;
	}
	
}


//10.删除链表的倒数第k个节点（不能遍历链表）
void RemoveReciprocalKNode(LinkList*node, size_t k)
{
	//首先用快慢指针法找到倒数第k个节点
	//然后调用删除节点的函数进行删除
	assert(node != NULL&&k != 0);
	LinkList*fast = node;
	LinkList*slow = node;

	while (fast->_next != NULL)
	{
		--k;
		if (k <= 0)//快指针先走k-1步，慢指针才开始走。
		{
			slow = slow->_next;
		}

		fast = fast->_next;

		if (k <= 1)//当k=链表长度时，k有最大值，k=1
		{
			Remove(slow);
		}

	}

}


//11.判断链表是否带环？若带环，求环长？求环入口点？

//判断是否带环
LinkList* HasCircle(LinkList*node)
{
	LinkList*fast = node;
	LinkList*slow = node;
	while (fast->_next != NULL);
	{
		slow = slow->_next;
		fast = fast->_next->_next;
	}
	if (slow == fast)//快慢指针相遇——带环
	{
		return slow;
	}
}

//求环长
size_t GetCircleLength(LinkList*pMeetNode)
{
	assert(pMeetNode != NULL);
	size_t length = 1;
	LinkList*cur = pMeetNode->_next;
	while (cur != pMeetNode)//环中至少有大于2个节点
	{
		cur = cur->_next;
		length++;
	}

	return length;

}

//求环入口点
//从起点和相遇点出发，再相遇时就是入口点
LinkList*CetEntranceNode(LinkList*node, LinkList*pMeetNode)
{
	assert(node != NULL);
	LinkList*cur = node;
	while (cur!=pMeetNode)
	{
		cur = cur->_next;//从起点出发
		pMeetNode = pMeetNode->_next;//从相遇点出发
	}
	return cur;//两者相遇时，跳出循环，此时的相遇点就是入口点
}


//12.判断链表是否相交（不带环）

//定义两个指针，cur1和cur2，分别遍历两个链表，当两个指针相等时，则两个链表相交
int LinkListIsCrossNode(LinkList*list1, LinkList*list2)
{
	assert(list1 !=NULL&&list2 != NULL);
	LinkList*cur1 = list1;
	LinkList*cur2 = list2;
	while (cur1 != NULL)
	{
		cur1 = cur1->_next;
	}

	while (cur2 != NULL)
	{
		cur2 = cur2->_next;
	}

	if (cur1 == cur2)
	{
		return 1;
		printf("链表相交");
	}

	else
	{
		return 0;
	}


}

//上述情况是在默认两个链表长度一样的基础上进行操作的
//如果两个链表长度不等，它们之间必定有一个差值k，让长的链表先遍历，
//指向长链表的指针走完k个节点之后，两个链表再同时遍历

//所以需要先计算两个链表的长度
int GetListLength(LinkList*node)
{
	LinkList*cur = node;
	int length;
	while (cur->_next != NULL)
	{
		cur = cur->_next;
		length++;
	}
	return length;
}

//移动链表，开始进行判断，是否相交，找交点
LinkList* MoveToCrossNode(LinkList*LongList, LinkList*ShortList, size_t gap)
{
	while (gap--)
	{
		LongList = LongList->_next;
	}
	while (LongList != NULL)
	{
		LongList = LongList->_next;
		ShortList = ShortList->_next;
		
		if (ShortList == LongList)
		{
			return ShortList;
		}
	}
	return NULL;
}

//求交点
LinkList*GetCrossNode(LinkList*list1, LinkList*list2)
{
	assert(list1 != NULL&&list2 != NULL);
	int k = GetListLength(list1) - GetListLength(list2);

	LinkList*CrossNode = NULL;

	if (k < 0)//list2比list1长
	{
		CrossNode = MoveToCrossNode(list2, list1, abs(k));
	}

	else
	{
		CrossNode = MoveToCrossNode(list1, list2, abs(k));
	}
	return CrossNode;
}




//13.判断两个链表是否相交，若相交，求交点。（假设两个链表带环）
//
//1.两个都不带环——转换为第十二题
//2.一个带环，一个不带环（一定不相交）
//3.两个都带环（3种情况）
//	1）不相交
//	2）环内相交——入口点不同
//	3）环外相交——入口点相同
//
//利用两个相遇点判断是否带环（若带环，快慢指针相遇）
//利用两个相遇点来判断是否相交(两个相遇点M1 M2,M1不动，M2走一圈，若相遇，则相交)
//

int LinkListRingIsCrossNode(LinkList*list1, LinkList*list2)
{
	assert(list1 != NULL&&list2 != NULL);
	LinkList*pMeetNode1 = HasCircle(list1);//上一题的函数
	LinkList*pMeetNode2 = HasCircle(list2);

	LinkList*entry1 = NULL;
	LinkList*entry2 = NULL;



	if (pMeetNode1 = NULL&& pMeetNode2 == NULL)//两者都不带环
	{
		return 0;
	}
	if (pMeetNode1 != NULL&& pMeetNode2 == NULL)//一个带环，一个不带环
	{
		return -1;
	}
	else//两个都带环
	{
		LinkList*cur = pMeetNode1->_next;
		while (cur != pMeetNode1)
		{
			if (cur == pMeetNode2)//两者相交，进而判断是环内相交还是环外相交
			{
				entry1 = GetEntranceNode(list1, pMeetNode1);//上一题的函数
				entry2 = GetEntranceNode(list2, pMeetNode2);

				if (entry1 == entry2)//入口点相同，环外相交
				{
					return 1;
				}
				else//环外相交
				{
					return 2;
				}
			}
			cur = cur->_next;
		}
		return - 1;//不相交
	}
}

//获取相交点
LinkList*GetRingCrossNode(LinkList*list1, LinkList*list2)
{
	assert(list1 != NULL&&list2 != NULL);
	LinkList*CrossNode = NULL;

	int result = LinkListRingIsCrossNode(list1, list2);

	if (result == 0)//两个链表都不带环
	{
		CrossNode = GetCrossNode(list1, list2);//转向不带环的链表相交问题
	}
	else if (result == -1)//不相交
	{
		CrossNode = NULL;
	}


	else if (result == 2)//环外相交
	{
		//转换为不带环链表相交情况
		LinkList*entry = GetEntranceNode(list1, HasCircle(list1));//获取环的入口点
		entry->_next = NULL;

		CrossNode = GetCrossNode(list1, list2);

	}

	//若是环内相交，环中所有的点相同

	return CrossNode;

}


//14.复杂链表的复制。 
 /*——链表的每一个节点，
都有一个next指针指向下一个节点，还有一个random指针指向这个链表中的一个随机节点或者NULL
现在要求实现复制这个链表，返回复制后的新链表。*/

//创建一个复杂链表的结构体
typedef struct ComplexNode
{
	DataType data;
	struct ComplexNode*_next;
	struct ComplexNode*_random;//——指向这个链表的任意一个节点或者NULL

}ComplexNode;

//创建一个节点
ComplexNode*BuyComplexNode(DataType x)
{
	ComplexNode*newComplexNode = (ComplexNode*)malloc(sizeof(ComplexNode));
	if (newComplexNode != NULL)//如果创建成功
	{
		newComplexNode->data = x;
		newComplexNode->_next = NULL;
		newComplexNode->_random = NULL;
	}
	return newComplexNode;

}


ComplexNode*CopyComplexList(ComplexNode*list)
{
	//复制链表
	ComplexNode*cur = list;
	while (cur != NULL)
	{
		ComplexNode*newComplexNode = BuyComplexNode(cur->data);
		newComplexNode->_next = cur->_next;
		cur->_next = newComplexNode;

		cur = newComplexNode->_next;
	}

	//置random
	cur = list;
	while (cur != NULL)//链表非空
	{
		if (cur->_random != NULL)//_random非空，否则对它解引用造成空指针
		{
			cur->_next->_random = cur->_random->_next;
		}
		cur = cur->_next->_next;
	}

	//拆链表
	cur = list;
	ComplexNode*newHead = cur->_next;//生成新链表的头

	ComplexNode*next = cur->_next;
	ComplexNode*Nextnext = next->_next;
	while (cur != NULL)
	{
		cur->_next = Nextnext;
		if (next->_next != NULL)//非空，否则对它解引用造成空指针
		{
			newHead->_next = Nextnext->_next;
		}

		cur = Nextnext;

		if (cur != NULL)//非空，否则对它解引用造成空指针
		{
			next = cur->_next;
			Nextnext = next->_next;
		}
	}

	return newHead;
}


//void ComplexNodePrint(ComplexNode*node)
//{
//	assert(node != NULL);
//	ComplexNode*cur = node;
//
//	while (cur != NULL)
//	{
//		if (cur->_random = NULL)
//			printf("%d:NULL->NULL\n", cur->data);
//		else
//		{
//			printf("%d:%d->NULL\n", cur->data, cur->_random->data);
//		}
//		cur = cur->data;
//	}
//}
//


//15.求两个已经排序的单链表照片那个的相同数据

void TheSameNode(LinkList*list1, LinkList*list2)
{
	while (list1 != NULL&&list2 != NULL)
	{
		if (list1->_data > list2->_data)
		{
			list2 = list2->_next;
		}

		else if (list1->_data < list2->_data)
		{
			list1 = list1->_next;
		}
		else
		{
			printf("%d->", list1->_data);
			list1 = list1->_next;
			list2 = list2->_next;
		}

	}
}


int main()
{
	//int list1[] = { 1,2,3,4,5 };
	//int list2[] = { 1,2,3,4,5,6,7,8 };

	LinkList N1, N2, N3;
	N1._data = 1;
	N2._data = 2;
	N3._data = 3;

	N1._next = &N2;
	N2._next = &N3;
	N3._next = NULL;
	LinkList* cur = Reserve(&N1);
	while (cur != NULL) {
		printf("%d ", cur->_data);
		cur = cur->_next;
	}

	//TheSameNode(list1, list2);

	system("pause");
	return 0;
}





















