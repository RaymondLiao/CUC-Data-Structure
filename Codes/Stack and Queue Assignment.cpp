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
//函数声明
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
//主函数
int main()
{
	SqList  l;
	
	SqQueue Q;
	InitQueue(Q);

	char   chos;
	char   ch[40];
	

	while(1)
	{
		printf("1.括号匹配检验\n2.整数入队列\n3.退出\n");
		printf("请选择您要运行的程序: ");
		scanf_s("%c", &chos);
		while (chos == '\n')
		{
			scanf_s("%c", &chos);
		}

		switch(chos)
		{
			case '1':
				{
					printf("请输入需要检验的字符串: ");
					scanf_s("%s", ch);

					if (match(ch))
					{
						printf("该字符串括号匹配\n");
					}
					else
					{
						printf("该字符串括号不匹配\n");
					}				
				}break;
			case '2':
				{
					int    temp;
					int	   get;

					printf("请输入整数的序列(以0结束): ");
					scanf_s("%d", &temp);
					printf("出队的整数组成的序列是:\n");
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

					printf("现在队列中的整数序列为:\n");
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
					printf("选择错误！\n");
				}
		}

		putchar(10);
	}
}

/////////////////////////////////////
//函数定义


//初始化栈
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

//销毁栈
Status DestroyStack(SqStack& S)
{
	if (!S.base)
	{
		free(S.base);
		S.stacksize = 0;
	}

	return OK;
}

//将栈置为空栈
Status ClearStack(SqStack& S)
{
	if (!S.base)
	{
		return ERROR;
	}

	S.top = S.base;

	return OK;
}

//栈判空
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

//插入元素e为新的栈顶元素
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

//删除栈顶元素并用e返回其值
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

//括号匹配检验
bool match(char *exp)
{
	bool match = true;

	SqStack S;
	InitStack(S);

	char ch;	//ch存放出栈元素
	int i = 0;  //i是当前字符下标

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
				if (ch != '(')	//情况1
				{
					match = false;
				}
			}
			else	//情况2
			{
				match = false;
			}
		}

		++i;
	}

	if(!StackEmpty(S))	//情况3
	{
		match = false;
	}
	printf("现在栈中存储的所有元素是:\n");
	PrintStack(S);

	DestroyStack(S);

	return match;
}





//初始化顺序队列
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

//销毁循环队列Q
Status DestroyQueue(SqQueue& Q)
{
	if (Q.base == NULL)
	{
		return ERROR;
	}

	free(Q.base);
	return OK;
}

//将循环队列Q清为空队列
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

//求循环队列Q长度
int QueueLenth_M2(SqQueue& Q)
{
	return (Q.rear - Q.front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

//插入元素e为Q的新的队尾元素
Status EnQueue(SqQueue& Q, QElemType e)
{
	if ((Q.rear + 1) % MAX_QUEUE_SIZE == Q.front)
	{
		printf("队列已满，无法添加新的元素!\n");
		return ERROR;
	}
	
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAX_QUEUE_SIZE;

	return OK;
}
 
//若循环队列Q不为空，则删除Q的队头元素并用e返回其值
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