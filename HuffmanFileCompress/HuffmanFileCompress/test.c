#include "FileCompress.h"

void menu()
{
	printf("****************** ��ӭʹ��huffman�ļ�ѹ�� ******************\n");
	printf("\n");
	printf("****************** 1.ѹ���ļ�   2.��ѹ�ļ� ******************\n");
	int select = 0;
	scanf("%d", &select);
	switch (select)
	{
	case 1:
	{
		printf("�������ļ�����·�����ļ���ʽ�����磺D:\\test\\filename.txt��\n");
		char filename[100] = { 0 };
		scanf("%s", filename);
		TestCompress(filename);
	}
	break;
	case 2:
	{
		printf("�������ļ�����·�����ļ���ʽ�����磺D:\\test\\filename.huffman��\n");
		char filename[100] = { 0 };
		scanf("%s", filename);
		TestUnCompress(filename);
	}
	break;
	default:
		break;
	}
}

int main()
{
	menu();
	system("pause");
	return 0;
}
