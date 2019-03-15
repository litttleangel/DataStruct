#pragma once

#ifndef __FILECOMPRESS_H__
#define __FILECOMPRESS_H__
#include "HuffmanTree.h"
#include <fstream>
#include <assert.h>
#include <time.h>
typedef long long LongType;

#define FORM_LENGTH 4   //�������ļ���ʽ���ȣ���*.txt����չ������Ϊ4
#define COMPRESS_FORM ".huffman"    //ѹ���ļ���ʽ

struct CharInfo
{
	char _ch;           //�ַ�
	LongType _count;    //�ַ����ֵĴ���
	string _code;       //�ַ���Ӧ��huffman����

	CharInfo operator+(const CharInfo& info)//���� +
	{
		CharInfo tmp;
		tmp._count = _count + info._count;
		return tmp;
	}
	bool operator>(const CharInfo& info) const//���� >
	{
		return _count > info._count;
	}
	bool operator!=(const CharInfo& info) const//���� !=
	{
		return _count != info._count;
	}
};

class FileCompress
{
	typedef HuffmanTreeNode<CharInfo> Node;

public:
	//ר��������ѹ���ļ��ﱣ���ַ����ִ����Ľṹ��
	//û��Ҫʹ��CharInfo����Ϊ��string code��һ����˷ѿ���
	struct ConfigInfo
	{
		char _ch;
		LongType _count;
	};


	FileCompress()//��ʼ����ϣ��
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_hashInfos[i]._ch = i;
			_hashInfos[i]._count = 0;
		}
	}

	//ͳ���ļ����ַ����ֵĴ���
	void GetCharCount(ifstream& ifs, const char*file)
	{
		char ch;
		while (ifs.get(ch))
		{
			++_hashInfos[(unsigned char)ch]._count;//�����ch����ת�����޷��ŵģ���Ϊ_hashInfos���±��Ǵ�0��255
		}
	}

	bool IsExist(const char* file)//�ж��ļ��Ƿ����
	{
		ifstream ifs(file);
		if (!ifs)
		{
			return false;//������
		}
		return true;//����
	}

	string CompressForm(const char* file, char* form)//ѹ��ǰ��׼���ͼ���
	{
		string compressfile = file;
		size_t index = compressfile.rfind('.');//�Ӻ���ǰ�ҵ��ļ����еġ�.��
		assert(index != string::npos);
		strcpy(form, file + index);//����Դ�ļ���ʽ
		compressfile.erase(index);//ɾ����׺
		index = compressfile.rfind('\\');//�Ӻ���ǰ�ҵ��ļ����еĵ�һ����\��
		++index;
		string name;
		for (size_t i = index; file[i] != '.'; ++i)//����Դ�ļ���
		{
			name.push_back(file[i]);
		}
		compressfile.erase(index);//ɾ��Դ�ļ���


		printf("�Ƿ�ѹ����ָ���ļ���\n");
		printf("1.��\t\t\t2.��\n");

		int select = 0;
		while (1)
		{
			scanf("%d", &select);
			if (select == 1)
			{
				char newRoad[100] = { 0 };
				printf("������ָ��Ŀ¼��(�磺D:\\Game\\ ��\\������©д)\n");
				scanf("%s", newRoad);
				string road(newRoad);
				if (IsExist((road + name + COMPRESS_FORM).c_str()))
				{
					printf("�ļ��Ѵ��ڣ���ѡ��\n");
					printf("1.�滻\t\t\t2.������\n");
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
					printf("�ļ��Ѵ��ڣ���ѡ��\n");
					printf("1.�滻\t\t\t2.������\n");
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
				compressfile += COMPRESS_FORM;//�滻��ָ����ѹ���ļ���ʽ
				return compressfile;
			}
			else
			{
				printf("������������ѡ��:\n");
			}
		}
	}

	string UncompressForm(const char* file, char* form)//��ѹ��ǰ��׼���ͼ���
	{
		string compressfile = file;
		size_t index = compressfile.rfind('.');//�Ӻ���ǰ�ҵ��ļ����еġ�.��
		assert(index != string::npos);
		compressfile.erase(index);//ɾ����׺
		index = compressfile.rfind('\\');//�Ӻ���ǰ�ҵ��ļ����еĵ�һ����\��
		++index;
		string name;
		for (size_t i = index; file[i] != '.'; ++i)//����Դ�ļ���
		{
			name.push_back(file[i]);
		}
		compressfile.erase(index);//ɾ��ѹ���ļ���

		printf("�Ƿ��ѹ��ָ���ļ��У�\n");
		printf("1.��\t\t\t2.��\n");

		int select = 0;
		while (1)
		{
			scanf("%d", &select);
			if (select == 1)
			{
				char str[100] = { 0 };
				printf("������ָ��Ŀ¼��(�磺D:\\Game\\ ��\\������©д)\n");
				scanf("%s", str);
				string road(str);
				if (IsExist((road + name + form).c_str()))
				{
					printf("�ļ��Ѵ��ڣ���ѡ��\n");
					printf("1.�滻\t\t\t2.������\n");
					scanf("%d", &select);
					if (select == 2)
					{
						char newName[100] = { 0 };
						printf("�������µ����֣�\n");
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
					printf("�ļ��Ѵ��ڣ���ѡ��\n");
					printf("1.�滻\t\t\t2.������\n");
					scanf("%d", &select);
					if (select == 2)
					{
						char newName[100] = { 0 };
						printf("�������µ����֣�\n");
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
				compressfile += form;//�滻��ָ����ѹ���ļ���ʽ
				return compressfile;
			}
			else
			{
				printf("������������ѡ��:\n");
			}
		}
	}

	void GenerateHuffmanCode(Node* root)//��ȡhuffman����
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
		ifstream ifs(file, ios::in | ios::binary);//0.��Դ�ļ�

		GetCharCount(ifs, file);//1.ͳ���ļ����ַ����ֵĴ���

		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree(_hashInfos, 256, invalid);//2.����huffman��

		GenerateHuffmanCode(tree.GetRoot());//3.����huffman����

		char form[FORM_LENGTH + 1] = { 0 };
		string compressfile = CompressForm(file, form);//4.ѹ��ǰ��׼���ͼ���
		ofstream ofs(compressfile.c_str(), ios::out | ios::binary);//�������ļ������ļ�����д������

																   //��ʱ��
		clock_t start = 0, end = 0;
		start = clock();

		//5.ѹ��
		//ѹ�����������ݣ�Դ�ļ���ʽ+�ַ����ִ�����Ϣ+Դ�ļ�������Ϣ
		for (size_t i = 0; i < FORM_LENGTH + 1; ++i)//5.1��Դ�ļ���׺������ʽд��ѹ���ļ��������ѹ����ʱ��ָ�ԭ��ʽ
		{
			ofs.put(form[i]);
		}

		for (size_t i = 0; i < 256; ++i)//5.2��_hashInfos���ַ����ִ���>0��Ԫ��д��ѹ���ļ�
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
		ofs.write((const char*)&over, sizeof(ConfigInfo));//5.3���÷ֽ���

		char ch;
		char value = 0;
		int pos = 0;
		ifs.clear();
		ifs.seekg(0);
		while (ifs.get(ch))//5.4��huffman����д��
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
		printf("ѹ����ʱ��%d ms\n", end - start);
	}

	void UnCompress(const char* file)
	{
		ifstream ifs(file, ios::in | ios::binary);//0.��ѹ���ļ�

												  //2.��ȡ��������Ϣ��Դ�ļ���ʽ+�ַ����ִ�����Ϣ+Դ�ļ�������Ϣ

		char form[FORM_LENGTH + 1];
		for (size_t i = 0; i < FORM_LENGTH + 1; ++i)//2.��ȡԴ�ļ���ʽ��Ϣ
		{
			ifs.get(form[i]);
		}

		string uncompressfile = UncompressForm(file, form);//3.��ѹ��ǰ��׼���ͼ���
		ofstream ofs(uncompressfile.c_str(), ios::out | ios::binary);//�������ļ������ļ�����д������

		while (1)//4.��ȡ�ַ������ִ�����Ϣ
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

		//��ʱ��
		clock_t start = 0, end = 0;
		start = clock();

		//5.�ؽ�huffman��
		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree(_hashInfos, 256, invalid);

		//6.��ѹ��
		//���ݶ�ȡ��huffman������huffman�����ҵ���Ӧ�ַ���д�뵽�ļ���
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
		printf("��ѹ��ʱ��%d ms\n", end - start);
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
