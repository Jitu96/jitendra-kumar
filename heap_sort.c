#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n,*arr,j,i,t;
	printf("Enter the array size:\n");
	scanf("%d",&n);
	arr=(int*)malloc(n*sizeof(int));
	
	printf("Enter the array:\n");
	for(i=0;i<n;i++)
		scanf("%d",arr+i);
	
	for(i=1;i<n;i++)
	{	
		int k=i;
		do{	j=(k-1)/2;
			if(arr[k]>arr[j])
				arr[k]^=arr[j]^=arr[k]^=arr[j];
			k=j;
		  }while(j!=0);
	}
	for(i=n-1; i>0 ; i--)
	{	
		
		arr[0]^=arr[i]^=arr[0]^=arr[i];
		j=0;
		do
		{
			t=2*j+1;
			if(t<i-1 && arr[t]<arr[t+1])
				t++;
			if(t<i && arr[t]>arr[j])
				arr[j]^=arr[t]^=arr[j]^=arr[t];
			j=t;
		}while(j<i);
	}
	for(i=0;i<n;i++)
	{
		printf("%d\t",arr[i]);
	}
	printf("\n");
}
