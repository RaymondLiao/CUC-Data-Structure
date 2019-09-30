#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define EQ(a, b) (!strcmp((a), (b)))
#define LT(a, b) (strcmp((a), (b)) < 0)
#define LQ(a, b) (strcmp((a), (b)) <= 0)

enum Status
{
	OVERFLOW = -1,
	ERROR    =  0,
	OK       =  1
} ;

////////////////////////////////////////////////////
//静态查找表顺序存储结构
typedef char* KeyType;
typedef struct
{
	KeyType key;
}SElemType;

typedef struct
{
	SElemType* elem;
	int length;
}SSTable;

////////////////////////////////////////////////////
//函数声明
Status CreatSSTable(SSTable& ST);
int Search_Bin(SSTable& ST, KeyType key);
int Search_Bin_Rec(SSTable& ST, KeyType key);
void SBR(SSTable& ST, KeyType key, int low, int high, int& pos);
//void PrintRecord(SElemType* objRec);

////////////////////////////////////////////////////
//主函数
int main()
{
	SSTable ST;
	ST.elem = NULL;

	char chos;
	char keyword[50];
	int pos;

	while(1)
	{
		printf("1.Creat a static search table\n2.Binary Search\n3.Binary Search(recursion)\n4.Exit\n");
		printf("Please choose what you want to do: ");
		scanf_s("%c", &chos);
		while ((chos == 10) || (chos == 32))
		{
			scanf_s("%c", &chos);
		}

		switch(chos)
		{
		case '1':
			{
				if (ST.elem != NULL)
				{
					free(ST.elem);
				}

				printf("\nHow long: ");
				scanf_s("%d" ,&ST.length);
				CreatSSTable(ST);
			}break;
		case '2':
			{
				printf("Please input the keyword: ");
				scanf_s("%s", keyword);
				if ((pos = Search_Bin(ST, keyword)) > 0)
				{
					printf("\nFind this record!\nIts position is No.%d.\n", pos);
				}
				else
				{
					printf("No record!\n");
				}
			}break;
		case '3':
			{
				printf("Please input the keyword: ");
				scanf_s("%s", keyword);
				if ((pos = Search_Bin_Rec(ST, keyword)) > 0)
				{
					printf("\nFind this record!\nIts position is No.%d\n", pos);
				}
				else
				{
					printf("No record!\n");
				}
			}break;
		case '4':
			{
				if (ST.elem != NULL) free(ST.elem);
				exit(0);
			}break;
		default:
			{
				printf("CHOS ERROR!\n");
			};
		}

		putchar(10);
	}

	//system("pause");
	return 0;
}

////////////////////////////////////////////////////
//函数定义
Status CreatSSTable(SSTable& ST)
{
	char keyword[50];
	ST.elem = (SElemType*) malloc ((ST.length + 1) * sizeof(SElemType));
	
	if (ST.elem == NULL) return OVERFLOW;

	for (int i=1; i<=ST.length; ++i)
	{
		printf("No%d. info: ", i);
		scanf_s("%s", keyword);
		ST.elem[i].key = (KeyType) malloc (strlen(keyword));
		const char* cnt_keyword = keyword;
		strcpy_s(ST.elem[i].key, strlen(keyword), cnt_keyword);
	}

	return OK;
}

int Search_Bin(SSTable& ST, KeyType key)
{
	int low = 1;
	int high = ST.length;
	int mid;

	while (low <= high)
	{
		mid = (low + high) / 2;
		if (EQ(key, ST.elem[mid].key))			return mid;
		else if (LT (key, ST.elem[mid].key))	high = mid - 1;
		else									low  = mid + 1;
	}

	return 0;
}

int Search_Bin_Rec(SSTable& ST, KeyType key)
{
	int low = 1;
	int high = ST.length;
	int pos = 0;

	SBR(ST, key, low, high, pos);

	return pos;
}

void SBR(SSTable& ST, KeyType key, int low, int high, int& pos)
{
	if (low <= high)
	{
		int mid = (low + high) / 2;
		if (EQ(key, ST.elem[mid].key)) 
		{
			pos = mid;
		}
		else if (LT(key, ST.elem[mid].key))
		{
			SBR(ST, key, low, mid - 1, pos);
		}
		else
		{
			SBR(ST, key, mid + 1, high, pos);
		}
	}
}