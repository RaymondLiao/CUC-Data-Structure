#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////
#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10
typedef int ElemType;
typedef struct 
{
	ElemType *base;		
	int length;			
	int listsize;		
} SqList;



#define STACK_INIT_SIZE		 100
#define STACK_INCREMENT_SIZE 10
typedef char SElemType;
typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
} SqStack;
/////////////////////////////////////
#define MAX_QUEUE_SIZE		 100
typedef int QElemType;
typedef struct
{
	QElemType	*base;
	int			front;
	int			rear;
} SqQueue;
/////////////////////////////////////

enum Status
{
	OVERFLOW = -1,
	ERROR	 =  0,
	OK		 =  1
};


/////////////////////////////////////
//��������
Status InitStack(SqStack& S);
Status DestroyStack(SqStack& S);
Status ClearStack(SqStack& S);
bool StackEmpty(SqStack& S);
Status Push(SqStack& S, SElemType e);
Status Pop(SqStack& S, SElemType& e);
void PirntStack(SqStack& S);

Status InitQueue(SqQueue& Q);
Status DestroyQueue(SqQueue& Q);
Status ClearQueue(SqQueue& Q);
int QueueLenth_M2(SqQueue& Q);
Status EnQueue(SqQueue& Q, QElemType e);
Status DeQueue(SqQueue& Q, QElemType& e);
void PrintQueue(SqQueue& Q);

bool match(char *exp);
void PrintStar(void);

/////////////////////////////////////
//������
int main()
{
	SqList  l;
	
	SqQueue Q;
	InitQueue(Q);

	char   chos;
	char   ch[40];
	

	while(1)
	{
		printf("1.����ƥ�����\n2.���������\n3.�˳�\n");
		printf("��ѡ����Ҫ���еĳ���: ");
		scanf_s("%c", &chos);
		while (chos == '\n')
		{
			scanf_s("%c", &chos);
		}

		switch(chos)
		{
			case '1':
				{
					printf("��������Ҫ������ַ���: ");
					scanf_s("%s", ch);

					if (match(ch))
					{
						printf("���ַ�������ƥ��\n");
					}
					else
					{
						printf("���ַ������Ų�ƥ��\n");
					}				
				}break;
			case '2':
				{
					int    temp;
					int	   get;

					printf("����������������(��0����): ");
					scanf_s("%d", &temp);
					printf("���ӵ�������ɵ�������:\n");
					PrintStar();
					while (temp)
					{
						if (temp > 0)
						{
							EnQueue(Q, temp);
						}
						else
						{
							if (DeQueue(Q, get))
							{
								printf("%d ", get);
							}
						}

						scanf_s("%d", &temp);
					}
					putchar(10);
					PrintStar();

					printf("���ڶ����е���������Ϊ:\n");
					PrintQueue(Q);
					ClearQueue(Q);
				}break;
			case '3':
				{
					DestroyQueue(Q);
					exit (0);
				}break;
			default:
				{
					printf("ѡ�����\n");
				}
		}

		putchar(10);
	}
}

/////////////////////////////////////
//��������


//��ʼ��ջ
Status InitStack(SqStack& S)
{
	S.base = (SElemType *) malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
	{
		exit(OVERFLOW);
	}
	
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;

	return OK;
}

//����ջ
Status DestroyStack(SqStack& S)
{
	if (!S.base)
	{
		free(S.base);
		S.stacksize = 0;
	}

	return OK;
}

//��ջ��Ϊ��ջ
Status ClearStack(SqStack& S)
{
	if (!S.base)
	{
		return ERROR;
	}

	S.top = S.base;

	return OK;
}

//ջ�п�
bool StackEmpty(SqStack& S)
{
	if (!S.base)
	{
		return false;
	}

	if (S.base == S.top)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//����Ԫ��eΪ�µ�ջ��Ԫ��
Status Push(SqStack& S, SElemType e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType *) realloc (S.base, (S.stacksize + STACK_INCREMENT_SIZE) * sizeof(SElemType));
		if (!S.base)
		{
			exit(OVERFLOW);
		}

		S.top = S.base + S.stacksize;
		S.stacksize += STACK_INCREMENT_SIZE;
	}

	*(S.top++) = e;

	return OK;
}

//ɾ��ջ��Ԫ�ز���e������ֵ
Status Pop(SqStack& S, SElemType& e)
{
	if (S.base == S.top)
	{
		return ERROR;
	}

	e = *--S.top;

	return OK;
}

void PrintStack(SqStack& S)
{
	SElemType *p = S.base;
	
	PrintStar();
	while (p < S.top)
	{
		printf("%c ", *p);
		++p;
	}
	putchar(10);
	PrintStar();
}	

//����ƥ�����
bool match(char *exp)
{
	bool match = true;

	SqStack S;
	InitStack(S);

	char ch;	//ch��ų�ջԪ��
	int i = 0;  //i�ǵ�ǰ�ַ��±�

	while ((exp[i]!='\0') && (match==true))
	{
		if (exp[i] == '(')
		{
			Push(S, exp[i]);
		}
		else if (exp[i] == ')')
		{
			if (!StackEmpty(S))
			{
				Pop(S,ch);
				if (ch != '(')	//���1
				{
					match = false;
				}
			}
			else	//���2
			{
				match = false;
			}
		}

		++i;
	}

	if(!StackEmpty(S))	//���3
	{
		match = false;
	}
	printf("����ջ�д洢������Ԫ����:\n");
	PrintStack(S);

	DestroyStack(S);

	return match;
}





//��ʼ��˳�����
Status InitQueue(SqQueue& Q)
{
	Q.base = (QElemType *) malloc(MAX_QUEUE_SIZE * sizeof(QElemType));
	if (!Q.base)
	{
		exit(OVERFLOW);
	}
	Q.front = Q.rear = 0;
	
	return OK;
}

//����ѭ������Q
Status DestroyQueue(SqQueue& Q)
{
	if (Q.base == NULL)
	{
		return ERROR;
	}

	free(Q.base);
	return OK;
}

//��ѭ������Q��Ϊ�ն���
Status ClearQueue(SqQueue& Q)
{
	if (Q.base == NULL)
	{
		return ERROR;
	}
	else
	{
		Q.front = Q.rear;
	}

	return OK;
}

//��ѭ������Q����
int QueueLenth_M2(SqQueue& Q)
{
	return (Q.rear - Q.front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

//����Ԫ��eΪQ���µĶ�βԪ��
Status EnQueue(SqQueue& Q, QElemType e)
{
	if ((Q.rear + 1) % MAX_QUEUE_SIZE == Q.front)
	{
		printf("�����������޷�����µ�Ԫ��!\n");
		return ERROR;
	}
	
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAX_QUEUE_SIZE;

	return OK;
}
 
//��ѭ������Q��Ϊ�գ���ɾ��Q�Ķ�ͷԪ�ز���e������ֵ
Status DeQueue(SqQueue& Q, QElemType& e)
{
	if(Q.front == Q.rear)
	{
		return ERROR;
	}

	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAX_QUEUE_SIZE;

	return OK;
}

void PrintQueue(SqQueue& Q)
{
	int i = Q.front;

	PrintStar();
	while (i < Q.rear)
	{
		printf("%d ", Q.base[i++]);
		if (i > MAX_QUEUE_SIZE) 
		{
			i = 0;
		}
	}
	putchar(10);
	PrintStar();
}

void PrintStar(void)
{
	printf("****************************\n");
} 