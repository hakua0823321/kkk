// Huffman������
#define _CRT_SECURE_NO_WARNINGS
#define SENTINEL 511
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>


struct NODE
{
	int count;
	int parent;
	int child0;
	int child1;
};
NODE g_node[512]; 

// Huffman������
void EncodeHuffman(unsigned char* data, unsigned len)
{
	// TODO: ������Huffman�������������L�q.
	printf("---====���f�[�^====---\n");
	for (unsigned i = 0; i < len; ++i) {
		if (isprint(data[i]))
		{
			putchar(data[i]);
		}
		else
		{
			printf("\\x%02x", data[i]);
		}
		printf("\n\n");

		//������
		for (unsigned i = 0; i < _countof(g_node); i++)
		{
			g_node[i].count = 0;
			g_node[i].parent = g_node[i].child0 = g_node[i].child1 = -1;
		}


		//�o���p�x
		unsigned char* p = data;
		for (unsigned i = 0; i < len; i++)
			g_node[*p].count++;

		printf("---====�����̏o���p�x====---\n");

		for (int i = 0; i < 256; ++i)
		{
			if (g_node[i].count > 0)
			{
				if (isprint(i))
				{
					printf("%c = %d\n",i,g_node[i].count);
				}
				else
				{
					printf("\\x%02x = $d\n",i,g_node[i].count);
				}
			}
		}
		putchar('\n');

		g_node[SENTINEL].count = INT_MAX;
		int min1, min2;
		int parent = 256;
		for (;;)
		{
			min1 = min2 = SENTINEL;
			for (int i = 0; i < parent; i++)
			{
				if (g_node[i].count <= 0 || g_node[i].parent >= 0)
					continue;

				//���݂�菬����
				if (g_node[i].count < g_node[min1].count)
				{
					min2 = min1;
					min1 = i;
					continue;
				}
				
				//��Ԗڂɏ�����
				if (g_node[i].count < g_node[min2].count)
				{
					min2 = i;

				}
			}

			if (min2 == SENTINEL)
				break;

			g_node[min1].parent = g_node[min2].parent = parent;
			g_node[parent].count = g_node[min1].count + g_node[min2].count;
			g_node[parent].child0 = min1;
			g_node[parent].child1 = min2;
			++parent;

		}

		printf("---====�����Ɋ��蓖�Ă�����====---\n");
		for (int i = 0; i < 256; i++)

		{
			if (g_node[i].count <= 0)
				continue;
			if (isprint(i))
				printf("%c = ", i);
			else
				printf("\\x%02x = ", i);

			putchar('\n');
		}
	}


}

int main(void)
{
	const char* pszData[] = {
		"CHFGHEGFCABFGDEGHAEFGHHGHBGFCEFACCFG",
		"aabcdeafagagfedadhaeedefahhh",
	};
	int n;
	char buff[1024];
	const char* data;

	//SetConsoleTitleA("GQ41�ۑ�06���");
	for (;;) {
		system("cls");
		do {
			printf("1.\"%s\"\n", pszData[0]);
			printf("2.\"%s\"\n", pszData[1]);
			printf("3.�C�ӂ̕�����\n");
			printf("0.�I��\n>");
			rewind(stdin);
			scanf("%d", &n);
			if (n == 0) {
				return 0;
			}
		} while (n < 1 || n > 3);

		switch (n) {
		case 1:
		case 2:
			data = pszData[n - 1];
			break;
		default:
			rewind(stdin);
			scanf("%s", buff);
			data = buff;
			break;
		}

		system("cls");
		printf("*** HUFFMAN : Code Make Test ***\n");
		EncodeHuffman((unsigned char*)data, (unsigned)strlen(data));

		printf("\n[Enter]�������Ă��������B");
		rewind(stdin);
		getchar();
	}

	return 0;
}
