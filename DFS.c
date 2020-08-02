#include<stdio.h>
#include<stdlib.h>
int adj[20][20];
int visit[20];
int parent[20];
int Q[20];
int q_end,q_start;
int* path(int sor,int des,int* d)
{
	int *p=(int*)malloc(sizeof(int));
	int k=des;
	*p=des;
	*d=1;
	while(k!=sor)
	{
		p=(int*)realloc(p,sizeof(int)*(1+*d));
		p[*d]=parent[k];
		k=parent[k];
		++*d;	
	}
	
	return p;
}
void DFS(int sor,int des,int n);
int main()
{
	int n;
	printf("Enter the number of nodes:\n");
	scanf("%d",&n);
	printf("Enter the whole adjacent matrix:\n");
	for(int i=0;i<n;i++)
		printf("\t%d",i);
	printf("\n");
	
	for(int i=0;i<n;i++)
	{
		printf("%d\t",i);
		for(int j=0;j<n;j++)	
			scanf("%d",&adj[i][j]);
	}
	int sor,des;
	do{
		printf("\nEnter Source:\n");
		scanf("%d",&sor);
		if(sor<0||sor>n-1)
			continue;
		else
			break;
	}while(1);
	do{
		printf("\nEnter Destination:\n");
		scanf("%d",&des);
		if(des<0||des>n-1)
			continue;
		else
			break;
	}while(1);
	if(sor==des)
	{
		printf("\nsource is the destination\n");
		return 0;
	}
	DFS(sor,des,n);
	for(int i=0;i<n;i++)
		printf("%d ",parent[i]);
	printf("\n\n");
	int *p,k;
	p=path(sor,des,&k);
	for(int i=k-1;i>=0;i--)
	{	
		if(i==0)
		{
			printf("%d\n",p[i]);
			continue;
		}
		printf("%d -> ",p[i]);
	}
	
}

void DFS(int sor,int des,int n)
{
	visit[sor]=1;
	
	for(int i=0;i<n;i++)
		if(adj[sor][i]==1 && visit[i]!=1)
		{
			visit[i]=1;
			DFS(i,des,n);
			parent[i]=sor;
		}
}
