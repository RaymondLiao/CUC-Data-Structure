#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct LNode  
{
	ElemType data;
	LNode  *next;
}LNode, *LinkList;

enum  Status
{
	OVERFLOW = -1,
    ERROR = 0,
	OK = 1
};

//函数声明
LinkList CreateList_L(int n);
Status	 ListInsert_L(LinkList &L, int i, LNode* &q);
Status	 ListDelet_L(LinkList &L, int i, LNode *&q);
Status	 Reverse_L(LinkList &L);
Status   Divide_L(LinkList &La, LinkList &Lb);
Status   Connect_L(LinkList &La, LinkList &Lb);
void     Print_L(LinkList &L);
void	 Destroy_L(LinkList &L);

int main()
{
	int n;
	char chos;
	LinkList La;
	LinkList Lb;

	printf("You will creat a linked list(La) first\n");
	printf("How many elements in La: ");
	scanf_s("%d", &n);
	printf("Please input %d integer numbers(inverted sequence): \n", n);
	La = CreateList_L(n);
	Lb = CreateList_L(0);
	printf("Congratulations! La has been created:\nLa: ");
	Print_L(La);
	while(1)
	{
		printf("1.Reverse La\n2.Divide La to La&Lb\n3.Connect La&Lb to La\n4.Exit\n");
		printf("So choose what you want to do now: ");
		scanf_s("%c", &chos);
		while(chos == 10)
		{
			scanf_s("%c", &chos);
		}

		switch(chos)
		{
			case '1':
				{
					Reverse_L(La);
				}break;
			case '2':
				{
					Divide_L(La, Lb);
				}break;
			case '3':
				{
					Connect_L(La, Lb);
				}break;
			case '4':
				{
					Destroy_L(La);
					Destroy_L(Lb);
					exit(0);
				}break;
			default:
				{
					printf("Error!\n");
				}break;
		}
		putchar(10);
	}
	system("pause");
	return 0;
}


// 逆位序输入n个元素的值，建立带头结点的单链线性表L
LinkList CreateList_L(int n) 
{   
	LNode *p;
	LinkList L;

	L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;   

    for (int i=n; i>0; --i) 
	{              
		p=(LinkList)malloc(sizeof(LNode)); 
        scanf_s("%d",&p->data);  
        p->next=L->next; L->next=p;     
    }

	return L;
}

// 在带头结点的单链线性表L中的第i个位置之前插入结点q
Status ListInsert_L(LinkList &L, int i, LNode* &q)
{
	LinkList p = L;
	int count = 0;

	//p指向第i-1个位置
	while (p && count <i-1)
	{
		p = p->next;
		++count;
	}
	if (!p || count>i-1)
	{
		return ERROR;
	}

	q->next = p->next;
	p->next = q;

	return OK;
}

//在带头结点的单链表中删除第i个结点,用指针q返回删除的结点
Status ListDelet_L(LinkList &L, int i, LNode* &q)
{
	LNode *p = L;
	int count = 0;
	while (p->next && count<i-1)
	{
		p = p->next;
		++count;
	}
	if (!(p->next) || count>i-1)
	{
		q = NULL;
		return ERROR;
	}

	q = p->next;
	p->next = q->next;

	return OK;
}

//倒置链表
Status Reverse_L(LinkList &L)
{
	if(!L->next)
	{
		printf("There is no element in La!\n");
		return ERROR;
	}

	LNode *p, *q;
	p = L->next->next;
	L->next->next = NULL;

	while(p)
	{
		q = p;
		p = p->next;
		q->next = L->next;
		L->next = q;
	}
	printf("La has been reversed:\n");
	printf("La: ");
	Print_L(L);

	return OK;
}

Status Divide_L(LinkList &La, LinkList &Lb)
{
	if (Lb->next)
	{
		printf("Lb must be a empty list!\n");
		return ERROR;
	}
	
	printf("La: ");
	Print_L(La);
	putchar(10);

	LNode *p = La->next;
	LNode *q = NULL;
	int count = 2;

	while (p)
	{
		ListDelet_L(La, count, q);
		if(q)	ListInsert_L(Lb, count-1, q);

		++count;
		p = p->next;
	}

	printf("The La have been Divided:\n");
	printf("La: ");
	Print_L(La);
	printf("Lb: ");
	Print_L(Lb);
	
	return OK;
}

Status Connect_L(LinkList &La, LinkList &Lb)
{
	if (!Lb->next)
	{
		printf("Lb is a empty list!\n");
		return ERROR;
	}

	LNode *p = La;
	while(p->next)
	{
		p = p->next;
	}

	p->next = Lb->next;
	Lb->next = NULL;

	printf("La&Lb has been connected:");
	printf("La: ");
	Print_L(La);

	return OK;
}

void Print_L(LinkList &L)
{
	LNode *p = L;
	p = p->next;
	
	while(p)
	{
		printf("%d ",p->data);
		p = p->next;
	}
	putchar(10);
}

void Destroy_L(LinkList &L)
{
	LNode *p, *q;
	p = L;
	q = L->next;
	while(q)
	{
		free(p);
		p = q;
		q = q->next;
	}
	free(p);
}