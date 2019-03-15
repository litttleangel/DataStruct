#pragma once

#ifndef __FILECOMPRESS_H__
#define __FILECOMPRESS_H__
#include "HuffmanTree.h"
#include <fstream>
#include <assert.h>
#include <time.h>
typedef long long LongType;

#define FORM_LENGTH 4   //常见的文件格式长度，如*.txt，扩展名长度为4
#define COMPRESS_FORM ".huffman"    //压缩文件格式

struct CharInfo
{
	char _ch;           //字符
	LongType _count;    //字符出现的次数
	string _code;       //字符对应的huffman编码

	CharInfo operator+(const CharInfo& info)//重载 +
	{
		CharInfo tmp;
		tmp._count = _count + info._count;
		return tmp;
	}
	bool operator>(const CharInfo& info) const//重载 >
	{
		return _count > info._count;
	}
	bool operator!=(const CharInfo& info) const//重载 !=
	{
		return _count != info._count;
	}
};

class FileCompress
{
	typedef HuffmanTreeNode<CharInfo> Node;

public:
	//专门用于在压缩文件里保存字符出现次数的结构体
	//没必要使用CharInfo，因为有string code这一项的浪费开销
	struct ConfigInfo
	{
		char _ch;
		LongType _count;
	};


	FileCompress()//初始化哈希表
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_hashInfos[i]._ch = i;
			_hashInfos[i]._count = 0;
		}
	}

	//统计文件中字符出现的次数
	void GetCharCount(ifstream& ifs, const char*file)
	{
		char ch;
		while (ifs.get(ch))
		{
			++_hashInfos[(unsigned char)ch]._count;//这里的ch必须转换成无符号的，因为_hashInfos的下标是从0到255
		}
	}

	bool IsExist(const char* file)//判断文件是否存在
	{
		ifstream ifs(file);
		if (!ifs)
		{
			return false;//不存在
		}
		return true;//存在
	}

	string CompressForm(const char* file, char* form)//压缩前的准备和检验
	{
		string compressfile = file;
		size_t index = compressfile.rfind('.');//从后往前找到文件名中的“.”
		assert(index != string::npos);
		strcpy(form, file + index);//保存源文件格式
		compressfile.erase(index);//删除后缀
		index = compressfile.rfind('\\');//从后往前找到文件名中的第一个“\”
		++index;
		string name;
		for (size_t i = index; file[i] != '.'; ++i)//保存源文件名
		{
			name.push_back(file[i]);
		}
		compressfile.erase(index);//删除源文件名


		printf("是否压缩到指定文件？\n");
		printf("1.是\t\t\t2.否\n");

		int select = 0;
		while (1)
		{
			scanf("%d", &select);
			if (select == 1)
			{
				char newRoad[100] = { 0 };
				printf("请输入指定目录：(如：D:\\Game\\ “\\”不能漏写)\n");
				scanf("%s", newRoad);
				string road(newRoad);
				if (IsExist((road + name + COMPRESS_FORM).c_str()))
				{
					printf("文件已存在，请选择：\n");
					printf("1.替换\t\t\t2.重命名\n");
					scanf("%d", &select);
					if (select == 2)
					{
						char newName[100] = { 0 };
						scanf("%s", newName);
						road += newName;
					}
					else
					{
						road += name;
					}
				}
				else
				{
					road += name;
				}
				road += COMPRESS_FORM;
				return road;
			}
			else if (select == 2)
			{
				if (IsExist((compressfile + name + COMPRESS_FORM).c_str()))
				{
					printf("文件已存在，请选择：\n");
					printf("1.替换\t\t\t2.重命名\n");
					scanf("%d", &select);
					if (select == 2)
					{
						char newName[100] = { 0 };
						scanf("%s", newName);
						compressfile += newName;
					}
					else
					{
						compressfile += name;
					}
				}
				else
				{
					compressfile += name;
				}
				compressfile += COMPRESS_FORM;//替换成指定的压缩文件格式
				return compressfile;
			}
			else
			{
				printf("输入有误，重新选择:\n");
			}
		}
	}

	string UncompressForm(const char* file, char* form)//解压缩前的准备和检验
	{
		string compressfile = file;
		size_t index = compressfile.rfind('.');//从后往前找到文件名中的“.”
		assert(index != string::npos);
		compressfile.erase(index);//删除后缀
		index = compressfile.rfind('\\');//从后往前找到文件名中的第一个“\”
		++index;
		string name;
		for (size_t i = index; file[i] != '.'; ++i)//保存源文件名
		{
			name.push_back(file[i]);
		}
		compressfile.erase(index);//删除压缩文件名

		printf("是否解压到指定文件夹？\n");
		printf("1.是\t\t\t2.否\n");

		int select = 0;
		while (1)
		{
			scanf("%d", &select);
			if (select == 1)
			{
				char str[100] = { 0 };
				printf("请输入指定目录：(如：D:\\Game\\ “\\”不能漏写)\n");
				scanf("%s", str);
				string road(str);
				if (IsExist((road + name + form).c_str()))
				{
					printf("文件已存在，请选择：\n");
					printf("1.替换\t\t\t2.重命名\n");
					scanf("%d", &select);
					if (select == 2)
					{
						char newName[100] = { 0 };
						printf("请输入新的名字：\n");
						scanf("%s", newName);
						road += newName;
					}
					else
					{
						road += name;
					}
				}
				else
				{
					road += name;
				}
				road += form;
				return road;
			}
			else if (select == 2)
			{
				if (IsExist((compressfile + name + form).c_str()))
				{
					printf("文件已存在，请选择：\n");
					printf("1.替换\t\t\t2.重命名\n");
					scanf("%d", &select);
					if (select == 2)
					{
						char newName[100] = { 0 };
						printf("请输入新的名字：\n");
						scanf("%s", newName);
						compressfile += newName;
					}
					else
					{
						compressfile += name;
					}
				}
				else
				{
					compressfile += name;
				}
				compressfile += form;//替换成指定的压缩文件格式
				return compressfile;
			}
			else
			{
				printf("输入有误，重新选择:\n");
			}
		}
	}

	void GenerateHuffmanCode(Node* root)//获取huffman编码
	{
		if (root == NULL)
			return;
		if (root->_left == NULL&&root->_right == NULL)
		{
			_hashInfos[(unsigned char)root->_w._ch]._code = root->_w._code;
			return;
		}
		if (root->_left != NULL)
		{
			root->_left->_w._code = root->_w._code + '0';
			GenerateHuffmanCode(root->_left);
		}
		if (root->_right != NULL)
		{
			root->_right->_w._code = root->_w._code + '1';
			GenerateHuffmanCode(root->_right);
		}
	}

	void Compress(const char* file)
	{
		ifstream ifs(file, ios::in | ios::binary);//0.打开源文件

		GetCharCount(ifs, file);//1.统计文件中字符出现的次数

		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree(_hashInfos, 256, invalid);//2.生成huffman树

		GenerateHuffmanCode(tree.GetRoot());//3.生成huffman编码

		char form[FORM_LENGTH + 1] = { 0 };
		string compressfile = CompressForm(file, form);//4.压缩前的准备和检验
		ofstream ofs(compressfile.c_str(), ios::out | ios::binary);//创建该文件名的文件，并写入内容

																   //计时器
		clock_t start = 0, end = 0;
		start = clock();

		//5.压缩
		//压缩三部分内容：源文件格式+字符出现次数信息+源文件内容信息
		for (size_t i = 0; i < FORM_LENGTH + 1; ++i)//5.1将源文件后缀，即格式写入压缩文件，方便解压缩的时候恢复原格式
		{
			ofs.put(form[i]);
		}

		for (size_t i = 0; i < 256; ++i)//5.2将_hashInfos中字符出现次数>0的元素写入压缩文件
		{
			if (_hashInfos[i]._count>0)
			{
				ConfigInfo info;
				info._ch = _hashInfos[i]._ch;
				info._count = _hashInfos[i]._count;
				ofs.write((const char*)&info, sizeof(ConfigInfo));
			}
		}

		ConfigInfo over;
		over._count = 0;
		ofs.write((const char*)&over, sizeof(ConfigInfo));//5.3设置分界线

		char ch;
		char value = 0;
		int pos = 0;
		ifs.clear();
		ifs.seekg(0);
		while (ifs.get(ch))//5.4将huffman编码写入
		{
			string& code = _hashInfos[(unsigned char)ch]._code;
			for (size_t i = 0; i < code.size(); ++i)
			{
				if (code[i] == '0')
					value &= (~(1 << pos));
				else if (code[i] == '1')
					value |= (1 << pos);
				else
					assert(false);
				++pos;
				if (pos == 8)
				{
					ofs.put(value);
					pos = 0;
					value = 0;
				}
			}

		}
		if (pos > 0)
		{
			ofs.put(value);
		}
		end = clock();
		printf("压缩用时：%d ms\n", end - start);
	}

	void UnCompress(const char* file)
	{
		ifstream ifs(file, ios::in | ios::binary);//0.打开压缩文件

												  //2.读取三部分信息：源文件格式+字符出现次数信息+源文件内容信息

		char form[FORM_LENGTH + 1];
		for (size_t i = 0; i < FORM_LENGTH + 1; ++i)//2.读取源文件格式信息
		{
			ifs.get(form[i]);
		}

		string uncompressfile = UncompressForm(file, form);//3.解压缩前的准备和检验
		ofstream ofs(uncompressfile.c_str(), ios::out | ios::binary);//创建该文件名的文件，并写入内容

		while (1)//4.读取字符串出现次数信息
		{
			ConfigInfo info;
			ifs.read((char*)&info, sizeof(ConfigInfo));
			if (info._count > 0)
			{
				_hashInfos[(unsigned char)info._ch]._count = info._count;
			}
			else
			{
				break;
			}
		}

		//计时器
		clock_t start = 0, end = 0;
		start = clock();

		//5.重建huffman树
		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree(_hashInfos, 256, invalid);

		//6.解压缩
		//根据读取的huffman编码在huffman树中找到对应字符，写入到文件中
		Node* root = tree.GetRoot();
		LongType filecount = root->_w._count;
		Node* cur = root;
		char ch;
		while (ifs.get(ch))
		{
			for (size_t i = 0; i < 8; ++i)
			{
				if (ch&(1 << i))//1
					cur = cur->_right;
				else//0
					cur = cur->_left;
				if (cur->_left == NULL&&cur->_right == NULL)
				{
					ofs.put(cur->_w._ch);
					cur = root;
					if (--filecount == 0)
					{
						break;
					}
				}
			}
		}
		end = clock();
		printf("解压用时：%d ms\n", end - start);
	}
private:
	CharInfo _hashInfos[256];
};

void TestCompress(const char* filename)
{
	FileCompress fc;
	fc.Compress(filename);
}

void TestUnCompress(const char* filename)
{
	FileCompress fc;
	fc.UnCompress(filename);
}

#endif //__FILECOMPRESS_H__
