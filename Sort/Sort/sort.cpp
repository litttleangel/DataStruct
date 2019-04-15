#include<stdio.h>
#include<stdlib.h>
#include<assert.h>



void Swap(int* a, int* b)
{
	int* tmp = 0;
	tmp = a;
	a = b;
	b = tmp;
}

void InsertSort(int *a, int n)
{
	assert(a != NULL && n > 1);
	for (int i = 1;i < n; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (a[j] > a[j + 1])
				Swap(&(a[j]), &(a[j + 1]));
			else
				break;
		}
	}
	return;
}