#include "stdio.h"
#define OK 1
#define ERROR 0
#define MAX_VERTEX_NUM 20
#define INFINITY 32768 
typedef struct
{
	int adjvex;//����ֵ 
	int lowcost;//Ȩֵ 
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
	int vexnum,arcnum;//ͼ�Ķ������ͻ���
}AdjMatrix;
int LocateVertex(AdjMatrix *G,char v)//�󶥵�λ�ú��� 
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
  int CreateUDN(AdjMatrix *G)//����һ�������� 
  {
  	int i,j,k;
  	printf("����������Ŀ�ͻ���\n");
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
		printf("���������������Լ�Ȩ��\n");
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
//�Ӷ���u��������������ķ�㷨������ͨͼgn��С���������������������ÿ���� 
{
	closedge[u].lowcost = 0;//��ʼ����U={u} 
	for(int i = 1;i<=gn->vexnum;i++)
	{
		if(i!=u)//��V-U�еĶ���i��ʼ��Ϊclosedge[i] ���u�����ǵ�һ����㣬��ô��i�Ķ�����Ϊu�����ҽ�gn�еĵ�u�е�i�е�ֵ����i�ı� 
		{
			closedge[i].adjvex = u;
			closedge[i].lowcost = gn->arcs[u][i].adj;
		}
	}
		for(int j = 1;j<=gn->vexnum-1;j++)//������n-1���� 
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
			int v = t;//�ҵ���С�������� 
			u = closedge[t].adjvex;
			printf("����Ϊ��%d,����Ϊ��%d",u,v);//����������ĵ�ǰ��С�ߣ�u��v��
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
