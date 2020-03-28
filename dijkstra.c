#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct
{
	int p;
	double d;
}node;

typedef struct 
{
	int n;
	node *ver;
}queue;

queue *Q;
node *V;
int N,**I,Q_size;
double **W;

void initialize(int);
void relax(int,int);
void swap_Q(int,int);
void create_queue(void);
int extractmin(void);
void Dijkstra(int s);
char* path(int);
char *strrev(char*);

int main()
{
	int i,j,k,s;
	printf("Enter the number of vertices:\n");
	scanf("%d",&N);

	I = (int**)malloc(N*sizeof(int*));
	for(i=0;i<N;i++)
		I[i] = (int*)malloc(N*sizeof(int));
	W = (double**)malloc(N*sizeof(double*));
	for(i=0;i<N;i++)
		W[i] = (double*)malloc(N*sizeof(double));

	printf("Enter the adjacent matrix:\n");
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			scanf("%d",&I[i][j]);
	
	for(i=0;i<N;i++)	
		for(j=0;j<N;j++)
			if(I[i][j]==1)
			{
				printf("Edge (%d ,%d ) ; Weight : ",i+1,j+1);
				scanf("%lf",&W[i][j]);
				if(W[i][j] < 0)
				{
					fprintf(stderr,"\n\nError : Negative weights are not allowed\n");
					return 0;
				}
			}
			else
				W[i][j] = INFINITY;
	
	printf("\nEnter the source vertex in {1, 2, ... ,%d } :\n",N);
	scanf("%d",&s);

	initialize(s-1);
	Dijkstra(s-1);

	printf("\n\nThe distance vector is:\n");
	for(i=0;i<N;i++)
	{
		printf("%.3lf ",V[i].d);
	}			
	printf("\n");
	printf("\n\nThe paths are :\n");
	for(i=0;i<N;i++)
	{
		printf("path to %d : %s\n",i+1,path(i));
	}
	printf("\n");
	
}

void initialize(int s)
{
	int i;
	V = (node*)malloc(N*sizeof(node));
	Q = (queue*)malloc(N*sizeof(queue));

	for(i=0;i<N;i++)
	{
		V[i].p = -1;
		V[i].d = INFINITY;
	}
	V[s].d = 0;
	
}
void relax(int i,int j)
{
	double k = V[i].d + W[i][j];
	if(V[j].d > k)
	{	
		V[j].d = k;
		V[j].p = i;
	}
}
void swap_Q(int i,int j)
{
	int q;
	node* p;
	q = Q[i].n;
	Q[i].n = Q[j].n;
	Q[j].n = q;

	p = Q[i].ver;
	Q[i].ver = Q[j].ver;
	Q[j].ver = p;	
}
void create_queue(void)
{
	int i,j,k,l,r;
	Q_size = N;
	for(i=0;i<N;i++)
	{
		Q[i].n = i;
		Q[i].ver = &V[i];
	}
	for(j=N/2;j>=0;j--)
	{
		k=j;
		l=2*j;
		r=l+1;
		if(l<N && Q[l].ver->d < Q[k].ver->d)
			k=l;
		if(r<N && Q[r].ver->d < Q[k].ver->d)
			k=r;
		if(k!=j)
			swap_Q(k,j);
	}
}
int extractmin(void)
{
	int i,k,l,r;
	swap_Q(0,Q_size-1);
	Q_size--;
	for(i=0;i<Q_size;)
	{
		k=i;
		l=2*i;
		r=l+1;
		if(l<Q_size && Q[l].ver->d < Q[k].ver->d)
			k=l;
		if(r<Q_size && Q[r].ver->d < Q[k].ver->d)
			k=r;
		if(k!=i)
		{
			swap_Q(i,k);
			i=k;
		}
		else
			break;
	}
	return Q[Q_size].n;
}
void Dijkstra(int s)
{
	int i,j;
	create_queue();
	while(Q_size != 0)
	{
		i = extractmin();
		for(j=0;j<N;j++)
		{
			if(I[i][j] == 1)
				relax(i,j);
		}
	}
}
char* path(int i)
{
	char *str = (char*)malloc(10*N*sizeof(char));
	int k=i;
	while(V[i].p != -1)
	{
		sprintf(str,"%s>-- %d ",str,V[i].p+1);
		i=V[i].p;
	}
	strrev(str);
	sprintf(str,"%s%2d",str,k+1);
	return str;
}
char *strrev(char* str)
{
	if(strlen(str)<=1)
		return str;
	int p=0,q=strlen(str)-1;
	while(p<q)
	{
		*(str+p)^=*(str+q)^=*(str+p)^=*(str+q);
		p++;
		q--;
	}
	return str;
}




