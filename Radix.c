#include<stdio.h>
#include<stdlib.h>

struct node
{
	int val;
	struct node *next; 
};
typedef struct node key;

key *dig[10]; 

void push(int,int);
int pop(int);

int main()
{
	int n,*arr;
	
	printf("Enter the size of array:\n");
	scanf("%d",&n);
	arr = (int*)malloc(n*sizeof(int));
	printf("Enter the array:\n");
	for(int i=0;i<n;i++)
		scanf("%d",arr+i);

	int flag=0,t=1;

	while(1)
	{
		flag=0;
		for(int i=0;i<10;i++)
			dig[i]=NULL;
		for(int i=0;i<n;i++)
		{
			int k=(arr[i]/t)%10;
			push(arr[i],k);
			if(k>0)
				flag=1;
		}	
		if(flag==0)
			break;
		for(int i=0,j=0;i<10;i++)
		{
			while(dig[i]!=NULL)
			{
				arr[j]=pop(i);
				j++;
			}
		}
		t*=10;
	}
	for(int i=0;i<n;i++)
		printf("%d\t",arr[i]);
	printf("\n");
}

void push(int n,int i)
{
	key *p=(key*)malloc(sizeof(key));
	p->val=n;
	p->next=dig[i];
	dig[i]=p;
}

int pop(int i)
{
	int k;
	key *p=dig[i];
	if(dig[i]->next==NULL)
	{
		k=dig[i]->val;
		dig[i]=NULL;
		return k;
	}
	while(p->next->next!=NULL)
		p=p->next;
	k=p->next->val;
	p->next=NULL;
	return k;
}
	














