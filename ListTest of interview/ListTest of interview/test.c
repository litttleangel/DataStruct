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

//����һ���ڵ�
LinkList*BuyNode(DataType x)
{
	LinkList*newNode = (LinkList*)malloc(sizeof(LinkList));
	if (newNode != NULL)//��������ɹ�
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
//1.��β��ͷ��ӡ������
//˼·��˫��ѭ�����ǵݹ顪��ÿ�α���һ�飬��ӡ���һ���ڵ㣬��Χ��Сһ��

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
		end = cur;//ÿ�η�Χ����Сһ��
	}

}



//2.ɾ��һ����ͷ������ķ�β�ڵ㣨���ܱ�������
//

void Remove(LinkList*node)
{
	assert(node != NULL);
	LinkList*cur = node->_next;
	node->_data = cur->_data;
	node->_next = cur->_next;
	free(cur);

}


//3.����ͷ�������һ����β�ڵ�ǰ����һ���ڵ㣨���ܱ���������

void Insert(LinkList*node, size_t x)
{
	assert(node != NULL);
	LinkList*cur = BuyNode(x);
	cur->_next = node->_next;
	node->_next = cur;
	swap(cur->_data, node->_data);
}

//4.������ʵ��Լɪ��
//˼·��Լɪ����һ������ÿ��k�����ͽ���k���ڵ�ɾ����
//Ȼ��ӵ�ǰ�ڵ㿪ʼ������ǰ�ҵ�k���ڵ�


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
		//ɾ����k���ڵ�
		LinkList*tmp = cur->_next;
		cur->_data = tmp->_data;
		cur->_next = tmp->_next;
		free(tmp);
	}
	
	return cur;

}


//5.���õ�������ͷ�巨���ı�ָ��ָ��
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
//��ָ�뷨
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

	n1->_next = NULL;//�������ù���ʱ��ԭ����ͷ���Ӧ��ָ���

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
	return n1;//����ͷ���
}

//6.�������򡪡�ð������
void LinkListBubbleSort(LinkList*node)
{
	LinkList*tail = NULL;
	DataType flag = 0;
	if (node = NULL || node->_next == NULL)
	{
		return node;
	}
	while (node!=tail)//������Ϊ��
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
		tail = cur;//��С��Χ
	}

}


//7.�ϲ�������������,�ϲ�����Ȼ���򡪡���������Ϊ��
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
	LinkList*newHead = NULL;//������õ����������������
	LinkList* tail = NULL;//��¼��ǰ��������һ��λ��

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

	tail = newHead;//ȷ���������ͷ���

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
		tail = tail->_next;//����һ���ڵ㣬tail�����Ųһ��
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

//�ݹ�
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

	LinkList*newHead = NULL;//������õ����������������

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

	


//8.����һ��������м�ڵ㣬Ҫ��ֻ�ܱ���һ��

LinkList* FindMidNode(LinkList* node) // ����һ���ҵ������м�ڵ�
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



//9.���ҵ�����ĵ�����k���ڵ㣬Ҫ��ֻ�ܱ���һ������
LinkList* FindReciprocalKNode(LinkList* node, size_t k) //����һ����ҵ�����K���ڵ�
{
	assert(node!= NULL&&k!=0);

	LinkList*fast = node;
	LinkList*slow = node;
	while (fast->_next != NULL)
	{
		k--;
		if (k <= 0)
		{
			slow = slow->_next;//����ָ������k-1���󣬼��ߵ���k���ڵ�ʱ����ָ���ٿ�ʼ��
		}
		fast = fast->_next;
		
	}
	
	//��k=������ʱ��k--֮��õ�����k�����ֵ����1
	if (k <= 1)  
	{
		return slow;
	}
	else  //��k��ֵ����1ʱ���������ʧ��(���������k��ֵ>������ʱ)
	{
		return NULL;
	}
	
}


//10.ɾ������ĵ�����k���ڵ㣨���ܱ�������
void RemoveReciprocalKNode(LinkList*node, size_t k)
{
	//�����ÿ���ָ�뷨�ҵ�������k���ڵ�
	//Ȼ�����ɾ���ڵ�ĺ�������ɾ��
	assert(node != NULL&&k != 0);
	LinkList*fast = node;
	LinkList*slow = node;

	while (fast->_next != NULL)
	{
		--k;
		if (k <= 0)//��ָ������k-1������ָ��ſ�ʼ�ߡ�
		{
			slow = slow->_next;
		}

		fast = fast->_next;

		if (k <= 1)//��k=������ʱ��k�����ֵ��k=1
		{
			Remove(slow);
		}

	}

}


//11.�ж������Ƿ���������������󻷳�������ڵ㣿

//�ж��Ƿ����
LinkList* HasCircle(LinkList*node)
{
	LinkList*fast = node;
	LinkList*slow = node;
	while (fast->_next != NULL);
	{
		slow = slow->_next;
		fast = fast->_next->_next;
	}
	if (slow == fast)//����ָ��������������
	{
		return slow;
	}
}

//�󻷳�
size_t GetCircleLength(LinkList*pMeetNode)
{
	assert(pMeetNode != NULL);
	size_t length = 1;
	LinkList*cur = pMeetNode->_next;
	while (cur != pMeetNode)//���������д���2���ڵ�
	{
		cur = cur->_next;
		length++;
	}

	return length;

}

//����ڵ�
//�����������������������ʱ������ڵ�
LinkList*CetEntranceNode(LinkList*node, LinkList*pMeetNode)
{
	assert(node != NULL);
	LinkList*cur = node;
	while (cur!=pMeetNode)
	{
		cur = cur->_next;//��������
		pMeetNode = pMeetNode->_next;//�����������
	}
	return cur;//��������ʱ������ѭ������ʱ�������������ڵ�
}


//12.�ж������Ƿ��ཻ����������

//��������ָ�룬cur1��cur2���ֱ������������������ָ�����ʱ�������������ཻ
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
		printf("�����ཻ");
	}

	else
	{
		return 0;
	}


}

//�����������Ĭ������������һ���Ļ����Ͻ��в�����
//������������Ȳ��ȣ�����֮��ض���һ����ֵk���ó��������ȱ�����
//ָ�������ָ������k���ڵ�֮������������ͬʱ����

//������Ҫ�ȼ�����������ĳ���
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

//�ƶ�������ʼ�����жϣ��Ƿ��ཻ���ҽ���
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

//�󽻵�
LinkList*GetCrossNode(LinkList*list1, LinkList*list2)
{
	assert(list1 != NULL&&list2 != NULL);
	int k = GetListLength(list1) - GetListLength(list2);

	LinkList*CrossNode = NULL;

	if (k < 0)//list2��list1��
	{
		CrossNode = MoveToCrossNode(list2, list1, abs(k));
	}

	else
	{
		CrossNode = MoveToCrossNode(list1, list2, abs(k));
	}
	return CrossNode;
}




//13.�ж����������Ƿ��ཻ�����ཻ���󽻵㡣�������������������
//
//1.����������������ת��Ϊ��ʮ����
//2.һ��������һ����������һ�����ཻ��
//3.������������3�������
//	1�����ཻ
//	2�������ཻ������ڵ㲻ͬ
//	3�������ཻ������ڵ���ͬ
//
//���������������ж��Ƿ������������������ָ��������
//�����������������ж��Ƿ��ཻ(����������M1 M2,M1������M2��һȦ�������������ཻ)
//

int LinkListRingIsCrossNode(LinkList*list1, LinkList*list2)
{
	assert(list1 != NULL&&list2 != NULL);
	LinkList*pMeetNode1 = HasCircle(list1);//��һ��ĺ���
	LinkList*pMeetNode2 = HasCircle(list2);

	LinkList*entry1 = NULL;
	LinkList*entry2 = NULL;



	if (pMeetNode1 = NULL&& pMeetNode2 == NULL)//���߶�������
	{
		return 0;
	}
	if (pMeetNode1 != NULL&& pMeetNode2 == NULL)//һ��������һ��������
	{
		return -1;
	}
	else//����������
	{
		LinkList*cur = pMeetNode1->_next;
		while (cur != pMeetNode1)
		{
			if (cur == pMeetNode2)//�����ཻ�������ж��ǻ����ཻ���ǻ����ཻ
			{
				entry1 = GetEntranceNode(list1, pMeetNode1);//��һ��ĺ���
				entry2 = GetEntranceNode(list2, pMeetNode2);

				if (entry1 == entry2)//��ڵ���ͬ�������ཻ
				{
					return 1;
				}
				else//�����ཻ
				{
					return 2;
				}
			}
			cur = cur->_next;
		}
		return - 1;//���ཻ
	}
}

//��ȡ�ཻ��
LinkList*GetRingCrossNode(LinkList*list1, LinkList*list2)
{
	assert(list1 != NULL&&list2 != NULL);
	LinkList*CrossNode = NULL;

	int result = LinkListRingIsCrossNode(list1, list2);

	if (result == 0)//��������������
	{
		CrossNode = GetCrossNode(list1, list2);//ת�򲻴����������ཻ����
	}
	else if (result == -1)//���ཻ
	{
		CrossNode = NULL;
	}


	else if (result == 2)//�����ཻ
	{
		//ת��Ϊ�����������ཻ���
		LinkList*entry = GetEntranceNode(list1, HasCircle(list1));//��ȡ������ڵ�
		entry->_next = NULL;

		CrossNode = GetCrossNode(list1, list2);

	}

	//���ǻ����ཻ���������еĵ���ͬ

	return CrossNode;

}


//14.��������ĸ��ơ� 
 /*���������ÿһ���ڵ㣬
����һ��nextָ��ָ����һ���ڵ㣬����һ��randomָ��ָ����������е�һ������ڵ����NULL
����Ҫ��ʵ�ָ�������������ظ��ƺ��������*/

//����һ����������Ľṹ��
typedef struct ComplexNode
{
	DataType data;
	struct ComplexNode*_next;
	struct ComplexNode*_random;//����ָ��������������һ���ڵ����NULL

}ComplexNode;

//����һ���ڵ�
ComplexNode*BuyComplexNode(DataType x)
{
	ComplexNode*newComplexNode = (ComplexNode*)malloc(sizeof(ComplexNode));
	if (newComplexNode != NULL)//��������ɹ�
	{
		newComplexNode->data = x;
		newComplexNode->_next = NULL;
		newComplexNode->_random = NULL;
	}
	return newComplexNode;

}


ComplexNode*CopyComplexList(ComplexNode*list)
{
	//��������
	ComplexNode*cur = list;
	while (cur != NULL)
	{
		ComplexNode*newComplexNode = BuyComplexNode(cur->data);
		newComplexNode->_next = cur->_next;
		cur->_next = newComplexNode;

		cur = newComplexNode->_next;
	}

	//��random
	cur = list;
	while (cur != NULL)//����ǿ�
	{
		if (cur->_random != NULL)//_random�ǿգ����������������ɿ�ָ��
		{
			cur->_next->_random = cur->_random->_next;
		}
		cur = cur->_next->_next;
	}

	//������
	cur = list;
	ComplexNode*newHead = cur->_next;//�����������ͷ

	ComplexNode*next = cur->_next;
	ComplexNode*Nextnext = next->_next;
	while (cur != NULL)
	{
		cur->_next = Nextnext;
		if (next->_next != NULL)//�ǿգ����������������ɿ�ָ��
		{
			newHead->_next = Nextnext->_next;
		}

		cur = Nextnext;

		if (cur != NULL)//�ǿգ����������������ɿ�ָ��
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


//15.�������Ѿ�����ĵ�������Ƭ�Ǹ�����ͬ����

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





















