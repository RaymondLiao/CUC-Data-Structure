#include <stdio.h>
#include <stdlib.h>

enum Status
{
	OVERFLOW = -1,
	ERROR    =  0,
	OK		 =  1
};

///////////////////////////////////////
//图的邻接表存储表示
#define MAX_VERTEXT_NUM 20
#define INFINITY        4294967296
enum GraphKind{DG, DN, UDG, UDN};
typedef int  VertexType;

typedef struct ArcNode
{
	VertexType  adjVex;
	ArcNode    *nextArc;
	int		    weight;
} ArcNode;

typedef struct VNode
{
	VertexType  data;
	ArcNode	   *firstArc;
}VNode, AdjList[MAX_VERTEXT_NUM + 1];

typedef struct
{
	AdjList	  vertices;
	int		  vexNum;
	int		  arcNum;
	GraphKind kind;
} ALGraph;

///////////////////////////////////////

///////////////////////////////////////
//函数声明
Status GreateGraph(ALGraph& G);
Status GreateUDN(ALGraph& G);
void TraverseGraph(ALGraph& G, bool* visited, VertexType vex);
void DFSSearch(ALGraph& G, bool* visited, VertexType vex);
void PrintVexData(VNode* vnode);
Status DestroyGraph(ALGraph& G);

///////////////////////////////////////
//主函数
int main()
{
	ALGraph G;
	bool visited[MAX_VERTEXT_NUM];
	bool w = false;			//检测图是否被建立
	char chos;

	while(1)
	{
		printf("1.Great a graph|network\n2.DFSTraverse\n3.Exit\n");
		printf("Choose what you want to do: ");
		scanf_s("%c", &chos);
		while(chos == 10)
		{
			scanf_s("%c", &chos);
		}

		switch(chos)
		{
		case '1':
			{
				if (w == true)
				{
					printf("You have created one. You will creat another.\n");
					DestroyGraph(G);
				}

				GreateGraph(G);

				w = true;
			}break;
		case '2':
			{
				if (w == false)
				{
					printf("You have to create a graph or network first!\n");
					break;
				}

				TraverseGraph(G, visited, 1);
			}break;
		case '3':
			{
				DestroyGraph(G);

				exit(0);
			}break;
		default:
			{
				printf("CHOS ERROR!\n");
			}break;
		}

		putchar(10);
	}
	
	system("pause");
}

///////////////////////////////////////
//函数定义
Status GreateGraph(ALGraph& G)
{
	char chos;
	GT:
	printf("1.DiGraph  2.UdiGraph  3.DiNet  4.UdiNet\n");
	printf("Please choose what kind of graph you want to create: \n");
	scanf_s("%c", &chos);
	while (chos == 10)
	{
		scanf_s("%c", &chos);
	}

	switch (chos)
	{
		case '1': printf("NOT IMPLEMENT\n"); putchar(10); goto GT; break;
		case '2': printf("NOT IMPLEMENT\n"); putchar(10); goto GT; break;
		case '3': printf("NOT IMPLEMENT\n"); putchar(10); goto GT; break;
		case '4': GreateUDN(G); break;
		default : printf("CHOS ERROR!\n"); putchar(10); goto GT;
	}

	return OK;
}

Status GreateUDN  (ALGraph& G)
{
	VertexType v1;
	VertexType v2;
	int        weight;


	printf("You will create a undirected network soon.\n");
	printf("Please input the information of his network.\n");
	printf("vexNum: "); scanf_s("%d", &G.vexNum);
	printf("arcNum: "); scanf_s("%d", &G.arcNum);

	for (int i=1; i<=G.vexNum; ++i)		//初始化表头结点向量
	{
		G.vertices[i].data = i;
		G.vertices[i].firstArc = NULL;
	}

	for (int i=1; i<=G.arcNum; ++i)		//构造邻接表
	{
		printf("Please input the information of No.%d edge & its weight.\n", i);
		printf("vex1: ");   scanf_s("%d", &v1);
		printf("vex2: ");   scanf_s("%d", &v2);
		printf("weight: "); scanf_s("%d", &weight);

		ArcNode *arcNode1 = (ArcNode*) malloc(sizeof(ArcNode));
		ArcNode *arcNode2 = (ArcNode*) malloc(sizeof(ArcNode));
		if ((arcNode1 == NULL) || (arcNode2 == NULL))
		{
			return OVERFLOW;
		}

		arcNode1->nextArc = G.vertices[v1].firstArc;
		arcNode1->adjVex  = v2;
		arcNode1->weight  = weight;
		G.vertices[v1].firstArc = arcNode1;

		arcNode2->nextArc = G.vertices[v2].firstArc;
		arcNode2->adjVex  = v1;
		arcNode2->weight  = weight;
		G.vertices[v2].firstArc = arcNode2;
	}

	printf("Congratulations! The undirected network has been created!\n");
	return OK;
}

Status DestroyGraph(ALGraph& G)
{
	ArcNode *p1;
	ArcNode *p2;

	for (int i=1; i<=G.vexNum; ++i)
	{
		if (G.vertices[i].firstArc == NULL)
		{
			continue;
		}

		p1 = G.vertices[i].firstArc;
		p2 = p1->nextArc;

		while(p2 != NULL)
		{
			free(p1);
			p1 = p2;
			p2 = p2->nextArc;
		}
		free(p1);
	}

	printf("The graph has been destroyed.\n");
	return OK;
}

void TraverseGraph(ALGraph& G, bool* visited, VertexType vex)
{
	printf("The DFS sequence of this graph is:\n");
	for (int i=1; i<=G.vexNum; ++i)
	{
		*(visited + i) = false;
	}
	
	DFSSearch(G, visited, vex);
	putchar(10);

	for (int i=1; i<=G.vexNum; ++i)
	{
		if (visited[i] == false)
		{
			DFSSearch(G, visited, G.vertices[i].data);
			putchar(10);
		}
	}

	putchar(10);
}

void DFSSearch(ALGraph& G, bool* visited, VertexType vex)
{
	PrintVexData(&G.vertices[vex]);
	visited[vex] = true;

	ArcNode* p;
	p = G.vertices[vex].firstArc;

	while(p != NULL)
	{
		if (visited[p->adjVex] == false)
		{
			printf(" ->(%d) ", p->weight);
			DFSSearch(G, visited, p->adjVex);

			//该路径走到尽头，换行输出下一路径
			printf("*(end:v%d)\n   ", p->adjVex);
		}
		p = p->nextArc;
	}
}

void PrintVexData(VNode* vnode)
{
	printf("v%d ", vnode->data);
}