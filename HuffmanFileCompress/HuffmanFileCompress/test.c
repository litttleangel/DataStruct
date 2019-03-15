#include "FileCompress.h"

void menu()
{
	printf("****************** 欢迎使用huffman文件压缩 ******************\n");
	printf("\n");
	printf("****************** 1.压缩文件   2.解压文件 ******************\n");
	int select = 0;
	scanf("%d", &select);
	switch (select)
	{
	case 1:
	{
		printf("请输入文件所在路径和文件格式：（如：D:\\test\\filename.txt）\n");
		char filename[100] = { 0 };
		scanf("%s", filename);
		TestCompress(filename);
	}
	break;
	case 2:
	{
		printf("请输入文件所在路径和文件格式：（如：D:\\test\\filename.huffman）\n");
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
