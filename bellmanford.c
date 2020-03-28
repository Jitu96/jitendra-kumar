#include<stdio.h>
#include<stdlib.h>

unsigned long q;

void relax(int n, int u, int v, int graph[n][n], int dist[n], int parent[n])
{
	if (dist[v] > dist[u]+graph[u][v])
	{
		dist[v]=dist[u]+graph[u][v];
		parent[v]=u;
	}
}

int bellmanFord(int n, int graph[n][n], int dist[n], int parent[n])
{
	while (q>0)
	{
		q=q>>1;
		for (int i=0; i<n; i++)
		{
			for (int j=0; j<n; j++)
			{
				if (graph[i][j]>0)
					relax(n, i, j, graph, dist, parent);
			}
		}	
	}
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			if (dist[j] > dist[i]+graph[i][j])
				return 0;
		}
	}
	return 1;
}

int main()
{
	int n;
	printf("Enter the number of nodes: ");
	scanf("%d",&n);
	int graph[n][n];
	q=(1<<n)-1;
	int dist[n], parent[n], visited[n], path[n];
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			if (i==j)
				graph[i][j]=0;
			else
				graph[i][j]=rand()%100-40;
			printf("%d\t",graph[i][j]);
		}
		dist[i]=100*n;
		parent[i]=-1;
		path[i]=-1;
		printf("\n");
	}
	int src, dst;
	printf("Enter the source and the destination of the required path.\nSource: ");
	scanf("%d",&src);
	printf("Destination: ");
	scanf("%d",&dst);
	dist[src]=0;
	int flag=bellmanFord(n, graph, dist, parent);
	if (flag==1)
	{
		int i=dst;
		int j=0;
		while (i!=src)
		{
			path[j]=i;
			i=parent[i];
			j++;
		}
		path[j]=i;
		printf("The required path is,\n");
		for (int i=j; i>=0; i--)
		{
			if (i!=j)
				printf(" --> ");
			printf("%2d",path[i]);
		}
		printf("\nAnd the required distance is= %d.\n",dist[dst]);
	}
	else
		printf("There is a nagetive cycle.\n");
	return 0;
}
