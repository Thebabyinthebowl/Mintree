#include "stdio.h"
#define OK 1
#define ERROR 0
#define MAX_VERTEX_NUM 20
#define INFINITY 32768 
typedef struct
{
	int adjvex;//顶点值 
	int lowcost;//权值 
}Closedge;
Closedge closedge[MAX_VERTEX_NUM];
typedef struct ArcNode
{
	int adj;
	int info;
}ArcNode; 
typedef struct
{
	char vertex[MAX_VERTEX_NUM];
	ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum,arcnum;//图的顶点数和弧数
}AdjMatrix;
int LocateVertex(AdjMatrix *G,char v)//求顶点位置函数 
{
	int j = ERROR,k;
	for(k = 0;k<G->vexnum;k++)
	{
		if(G->vertex[k]==v)
		{
			j = k;
			break;
		}
	}
	return j;
  }  
  int CreateUDN(AdjMatrix *G)//创建一个无向网 
  {
  	int i,j,k;
  	printf("请输入结点数目和弧数\n");
  	scanf("%d,%d",&G->vexnum,&G->arcnum);
  	for(i = 0;i<G->vexnum;i++)
  	{
  		for(j = 0;j<G->vexnum;j++)
  		{
  			G->arcs[i][j].adj =INFINITY ;
		  }
	  }
	scanf("%s",G->vertex);
	for(k = 0;k<G->arcnum;k++)
	{
		char v1,v2;
		int weight;
		printf("请输入两个顶点以及权重\n");
		scanf(" %c",&v1);
		scanf(" %c",&v2);
		scanf("%d",&weight);
		i = LocateVertex(G,v1);
		j = LocateVertex(G,v2);
		G->arcs[i][j].adj = weight;
		G->arcs[j][i].adj = weight;
	}
	return OK;
  }
  void MiniSpanTree_Prim(AdjMatrix *gn,int u)
//从顶点u出发，按照普利姆算法构造连通图gn最小生成树，并输出生成树的每条边 
{
	closedge[u].lowcost = 0;//初始化，U={u} 
	for(int i = 1;i<=gn->vexnum;i++)
	{
		if(i!=u)//对V-U中的顶点i初始化为closedge[i] 如果u并不是第一个结点，那么将i的顶点置为u，并且将gn中的第u行第i列的值赋给i的边 
		{
			closedge[i].adjvex = u;
			closedge[i].lowcost = gn->arcs[u][i].adj;
		}
	}
		for(int j = 1;j<=gn->vexnum-1;j++)//找其余n-1条边 
		{
			int min =INFINITY;
			int t = 0;	
			for(int l = 1;l<=gn->vexnum-1;l++)
			{				
				if(closedge[l].lowcost!=INFINITY&&closedge[l].lowcost!=0&&min>closedge[l].lowcost) 
				{
				min = closedge[l].lowcost;
			 	t = l;
				}
			 } 
			int v = t;//找到最小的那条边 
			u = closedge[t].adjvex;
			printf("顶点为：%d,顶点为：%d",u,v);//输出生成树的当前最小边（u，v）
			closedge[v].lowcost = 0;
			for(int i = 1;i<=gn->vexnum;i++)
			{
				if(gn->arcs[v][i].adj<closedge[i].lowcost)
				{
					closedge[i].lowcost = gn->arcs[v][i].adj;
					closedge[i].adjvex = v;
				}
			 } 
		}
	
  } 
 void print(AdjMatrix G)
 {
 	for(int i = 0;i<G.vexnum;i++)
 	{
 		for(int j = 0;j<G.vexnum;j++)
 		{
 			printf("%d ",G.arcs[i][j].adj);
		 }
		 printf("\n");
	 }
  } 
  int main()
  {
  	AdjMatrix G;
  	CreateUDN(&G);
  	print(G);
  	MiniSpanTree_Prim(&G,0);
  }
