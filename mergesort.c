#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int count,p_count,c_count;


void mergesort(int*,int,int);
int main()
{
	int n,*arr;
	FILE *fp=fopen("merge_Data.txt","w+"),*f=fopen("merge_comp.txt","w+"),*g=fopen("merge_pointer.txt","w+");
	srand(time(NULL));
	for(n=100;n<=1000;n=n+100)
	{
		arr=(int*)malloc(n*sizeof(int));
		for(int i=0;i<100;i++)
		{	
			count=p_count=c_count=0;
			for(int j=0;j<n;j++)
			{
				arr[j]=rand()%12345;
			}
			mergesort(arr,0,n-1);
			fprintf(fp,"%d\t",count);
			fprintf(f,"%d\t",c_count);
			fprintf(g,"%d\t",p_count);
		}
		fprintf(fp,"\n");
		fprintf(f,"\n");
		fprintf(g,"\n");
		free(arr);
	}
}
void mergesort(int*arr,int i,int t)
{
	int r=(i+t)/2;
	if(i==t)
		return;
	mergesort(arr,i,r);
	
	mergesort(arr,r+1,t);
	
	for(int m=r+1,l=i;m<=t && l<=r;l++,p_count++)
	{
		int p=m,val=arr[m];
		c_count++;
		if(arr[m]<arr[l])
		{
			while(p>l)
			{
				++count;
				arr[p]=arr[p-1];
				p--;
			}
			arr[p]=val;
			m++;
			p_count++;
			r++;
		}
	}
	
}
