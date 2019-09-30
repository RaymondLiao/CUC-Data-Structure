#include <stdio.h>
#include <stdlib.h>
 
#define EQ(a, b) ((a) == (b))
#define LT(a, b) ((a) <  (b))
#define LQ(a, b) ((a) <= (b))

enum Status
{
	OVERFLOW = -1,
	ERROR    =  0,
	OK       =  1
} ;

////////////////////////////////////////////////////
//线性表顺序存储结构
typedef int KeyType;
typedef struct
{
	KeyType key;
}RecType;

typedef struct
{
	RecType* elem;
	int length;
	int first;
	int last;
}STable;

////////////////////////////////////////////////////
//函数声明
Status CreatSTable(STable& ST, bool nul);
void   TRInsertionSort(STable& ST);
int	   FindInsertPos(STable& ST, KeyType key, int low, int high, bool kind);
void   PrintSTable(STable& ST);

////////////////////////////////////////////////////
//主函数
int main()
{
	STable ST;
	ST.elem = NULL;

	char chos;

	while(1)
	{
		printf("1.创建查找表\n2.2-路插入排序\n3.打印查找表\n4.退出\n");
		printf("请选择: ");
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

				printf("\n请输入查找表长度: ");
				scanf_s("%d" ,&ST.length);
				CreatSTable(ST, false);
			}break;
		case '2':
			{
				TRInsertionSort(ST);
			}break;
		case '3':
			{
				PrintSTable(ST);
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

	return 0;
}

////////////////////////////////////////////////////
//函数定义
Status CreatSTable(STable& ST, bool nul)
{
	ST.elem = (RecType*) malloc ((ST.length + 1) * sizeof(RecType));	//零号单元另作他用
	
	if (ST.elem == NULL) return OVERFLOW;

	if (!nul)	//不创建空表
	{
		printf ("请输入%d个关键字: ", ST.length);
		for (int i=1; i<=ST.length; ++i)
		{
			scanf_s("%d", &ST.elem[i].key);
		}

		ST.first = 1;
		ST.last  = ST.length;
	}
	else
	{
		ST.first = ST.last = 1;
	}
	return OK;
}

void   TRInsertionSort(STable& ST)
{
	int insertPos;
	STable AT;		//辅助空间
	AT.length = ST.length;
	CreatSTable(AT, true);
	AT.elem[1] = ST.elem[1];

	for (int i=2; i<=ST.length; ++i)
	{
		if (LT(ST.elem[i].key, ST.elem[1].key))		//插入位在后半部分
		{
			if (AT.first == 1)
			{
				insertPos = AT.length;
				AT.first = insertPos;
			}
			else
			{
				insertPos = FindInsertPos(AT, ST.elem[i].key, AT.first, AT.length, true);
				
				for (int i = AT.first; i <= insertPos; ++i)		//记录前移,空出插入位
				{
					AT.elem[i - 1] = AT.elem[i];
				}
				--AT.first;
			}
		}
		else	//插入位在前半部分
		{
			insertPos = FindInsertPos(AT, ST.elem[i].key, 1, AT.last, false);
			for (int i = AT.last; i >= insertPos; --i)		//记录后移,空出插入位
			{
				AT.elem[i + 1] = AT.elem[i];
			}
			++AT.last;
		}
		printf ("frist: %d  last: %d  插入位：%d \n", AT.first, AT.last, insertPos);

		AT.elem[insertPos] = ST.elem[i];
	}

	//拷贝
	for (int i=0; i<=AT.length; ++i)
	{
		ST.elem[i] = AT.elem[i];
	}
	ST.first = AT.first;
	ST.last = AT.last;
}

int FindInsertPos(STable& ST, KeyType key, int low, int high, bool kind)		//折半查找插入位
{
	int insertPos;
	int mid;

	while (low <= high)
	{
		mid = (low + high) / 2;
		if (LT (key, ST.elem[mid].key))	high = mid - 1;
		else						    low  = mid + 1;
	}

	if (kind == true)	insertPos = high;
	else				insertPos = high + 1;

	return insertPos;
}

void   PrintSTable(STable& ST)
{
	for (int i=ST.first; i!=ST.last; ++i)
	{
		printf("%d ", ST.elem[i]);
		if (i >= ST.length)
		{
			i = 0;
		}
	}
	printf("%d ", ST.elem[ST.last]);
	putchar (10);
}