#include<stdio.h>
#include<stdlib.h>

enum  Status
{
	OVERFLOW = -1,
    ERROR = 0,
	OK = 1
};

///////////////////////////////////////////////////
//树的二叉链表存储表示
typedef char TelemType;
typedef struct BiTNode
{
	TelemType data;
	BiTNode *lchild, *rchild;
	int tag;				//访问标志域
} BiTNode, *BiTree;

///////////////////////////////////////////////////
//栈的顺序存储表示
#define STACK_INIT_SIZE		 100
#define STACK_INCREMENT_SIZE 10
typedef BiTree SElemType;
typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
} SqStack;

///////////////////////////////////////////////////
//函数声明
Status CreateBiTree(BiTree& T);
Status DestroyBiTree(BiTree& T);
void   PreOrderTraverse(BiTree root, void (*visit) (BiTree));
void   PostOrderTraverse(BiTree root, void (*visit) (BiTree));
void   PrintNodeData(BiTree root);
void   InitNodeTag(BiTree root);
void   DestroyNode(BiTree root);

Status		InitStack(SqStack& S);
Status		DestroyStack(SqStack& S);
Status		ClearStack(SqStack& S);
bool		StackEmpty(SqStack& S);
Status		Push(SqStack& S, SElemType e);
SElemType	GetTop(SqStack& S);
SElemType	Pop(SqStack& S);
void		PrintStack(SqStack& S);

void   PrintStar(void);
///////////////////////////////////////////////////
int main()
{
	BiTree T = NULL;
	char chos;

	while(1)
	{
		printf("1.Creat a binary tree:\n2.Traverse binary tree(postorder)\n3.Quit\n");

		printf("So choose what you want to do now: ");	
		scanf_s("%c", &chos);
		while(chos == 10)
		{
			scanf_s("%c", &chos);
		}
		
		putchar(10);

		switch(chos)
		{
			case '1':
				{
					if (T != NULL)
					{
						printf("You have creat one already.\nDo you want to creat another one?\n");
						printf("1.Yes      2.No\n");
						printf("So give me your choice: ");
						scanf_s("%c", &chos);
						while(chos == 10)
						{
							scanf_s("%c", &chos);
						}

						switch(chos)
						{
							case '1': DestroyBiTree(T), putchar(10); break;
							case '2': goto NG; break;
							default : printf("CHOOSE ERROR!\n");
						}		
					}

					printf("You will create a binary tree.\n");
					printf("Please input the extended preorder sequence of this tree: ");
					CreateBiTree(T);
					printf("Congratulations! The binary tree has been created!\n");

					NG:;
				}break;
			
			case '2':
				{
					if (T == NULL)
					{
						printf("You have to creat a tree first.\n"); break;
					}

					printf("Its postorder sequence is :");
					PostOrderTraverse(T, PrintNodeData);
				}break;
			case '3':
				{
					if (T != NULL)
					{
						DestroyBiTree(T);
						T = NULL;
					}

					exit (0);
				}break;
			case '4':
				{
					DestroyBiTree(T);
					T = NULL;
				}break;
			default : printf("CHOOSE ERROR!\n");
		}
	
		putchar(10);
	}
	
	system("pause");
	return 0;
}


///////////////////////////////////////////////////
//函数定义(树)
Status CreateBiTree(BiTree& T)
{
	char ch;
	ch = getchar();
	while(ch == 10)
	{
		ch = getchar();
	}

	if( ch == '.')
	{
		T = NULL;
	}
	else
	{
		if (!(T = (BiTree) malloc(sizeof(BiTNode))))
		{
			return ERROR;
		}

		T->data = ch;
		T->tag  = 0;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}

Status DestroyBiTree(BiTree& T)
{
	if (T == NULL)
	{
		return ERROR;
	}

	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);

	DestroyNode(T);
	return OK;
}

void PreOrderTraverse(BiTree root, void (*visit) (BiTree))
{
	if (root != NULL)
	{
		visit(root);

		PreOrderTraverse(root->lchild, visit);
		PreOrderTraverse(root->rchild, visit);
	}
}

void PostOrderTraverse(BiTree root, void (*visit) (BiTree))
{    
	  SqStack S;	//工作栈
      InitStack(S);   
	  BiTree p=root; 
      while(p || !StackEmpty(S))
	  {
		if (p)     
		{
			Push(S, p);
            p=p->lchild; 
        }
        else   
		{
            p = GetTop(S);
			if (p->tag == 0)
			{	
				p->tag = 1;
				p = p->rchild;
			}
			else
			{
				p = Pop(S);
				visit(p);	//访问根结点
				p = NULL;
			}
        }
      }

	  putchar(10);
	  PreOrderTraverse(root, InitNodeTag);
 }

void PrintNodeData(BiTree root)
{
	printf("%c ", root->data);
}

void InitNodeTag(BiTree root)
{
	root->tag = 0;
}

void DestroyNode(BiTree root)
{
	free(root);
}



///////////////////////////////////////////////////
//函数定义(栈)
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
SElemType Pop(SqStack& S)
{
	if (S.base == S.top)
	{
		return NULL;
	}

	return *--S.top;
}

SElemType GetTop(SqStack& S)
{
	if (S.base == S.top)
	{
		return NULL;
	}

	return *(S.top - 1);
}


void PrintStack(SqStack& S)
{
	SElemType *p = S.base;
	
	PrintStar();
	while (p < S.top)
	{
		printf("%c ", (*p)->data);
		++p;
	}
	putchar(10);
	PrintStar();
}	

void PrintStar(void)
{
	printf("****************************\n");
} 