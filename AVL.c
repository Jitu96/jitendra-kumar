#include<stdio.h>
#include<stdlib.h>

struct NODE
{
	int val;
	int depth;
	struct NODE *L,*R;
};
typedef struct NODE node;

node* insert(node*,int);
node* delete(node*);
node* rotate_r(node*);
node* rotate_l(node*);
void in_print(node*);
void pre_print(node*);
void post_print(node*);
void print(node*);
node* AVL(node*);

int main()
{
	node *root=NULL;
	int a[20],n;
	printf("Enter the array size:\n");
	scanf("%d",&n);
	printf("Enter the array:\n");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		root = insert(root,a[i]);
		
	}
	//root = (node*)malloc(sizeof(node));
	
		
	print(root);
	printf("\n");
	root=AVL(root);
	printf("\n\n-----------------AFTER AVL----------------------\n\n");
	print(root);	
	printf("\n");
}

node* insert (node *root,int a)
{
		
	if(root==NULL)
	{	
		root = (node*)malloc(sizeof(node));
		root->val = a;
		root->L = root->R = NULL;
		root->depth = 0;
		return root;
	}
	if(root->val<=a)
	{	
		root->R = insert(root->R,a);
		
	}
	else
	{	
		root->L = insert(root->L,a);
		
	}
	if(root->L==NULL)
		if(root->R==NULL)
			root->depth=0;
		else
			root->depth=root->R->depth+1;
	else 	if(root->R==NULL)
			root->depth=root->L->depth+1;
		else
			root->depth = root->R->depth >= root->L->depth ? root->R->depth+1 : root->L->depth+1;
	
	return root;
}
node* rotate_r(node* root)
{
	node*p=root;
	node*q=root->R;
	p->R=q->L;
	q->L=root;
	int pr,pl,qr,ql;
	if(p->R!=NULL)
		pr=p->R->depth;
	else pr=-1;
	if(p->L!=NULL)
		pl=p->L->depth;
	else pl=-1;
	if(p->R!=NULL)
		pr=p->R->depth;
	else qr=-1;
	if(q->L!=NULL)
		ql=q->L->depth;
	else ql=-1;
	
	p->depth=pr>=pl?pr+1:pl+1;
	q->depth=qr>=ql?qr+1:ql+1;
	return q;
}
node* rotate_l(node* root)
{
	node*p=root;
	node*q=root->L;
	p->L=q->R;
	q->R=root;
	int pr,pl,qr,ql;
	if(p->R!=NULL)
		pr=p->R->depth;
	else pr=-1;
	if(p->L!=NULL)
		pl=p->L->depth;
	else pl=-1;
	if(p->R!=NULL)
		pr=p->R->depth;
	else qr=-1;
	if(q->L!=NULL)
		ql=q->L->depth;
	else ql=-1;
	
	p->depth=pr>=pl?pr+1:pl+1;
	q->depth=qr>=ql?qr+1:ql+1;
	return q;
}
node* AVL(node *root)
{
	if(root==NULL)
		return NULL;
	
	int left,right;
	while(1)
	{	
		if(root->L==NULL)
			left=0;
		else 
			left=root->L->depth;
		if(root->R==NULL)
			right=0;
		else 
			right=root->R->depth;
		
		if(left-right<=-2)
			root=rotate_r(root);
		else 	if(left-right>=2)
				root=rotate_l(root);
			else
				break;
	}
	root->R=AVL(root->R);
	root->L=AVL(root->L);
	return root;
}
void in_print(node* root)
{
	if(root==NULL)
		return;
	in_print(root->L);
	printf("%d\t",root->val);
	in_print(root->R);
}
void pre_print(node* root)
{
	if(root==NULL)
		return;
	printf("%d\t",root->val);
	pre_print(root->L);
	pre_print(root->R);
}
void post_print(node* root)
{
	if(root==NULL)
		return;
	post_print(root->L);
	post_print(root->R);
	printf("%d\t",root->val);
}
void print(node* root)
{
	printf("preorder is:\n");
	pre_print(root);
	printf("\n\ninorder is:\n");
	in_print(root);
	printf("\n\npostorder is:\n");
	post_print(root);
}
