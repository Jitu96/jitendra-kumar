#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//					small functions
int* binary(int a){
  int *ptr,a_new;
  ptr=(int*)malloc(15*sizeof(int));
  for(int i=0;i<15;i++){
    a_new=a/2;  
    ptr[i]=a-(2*a_new);
    a=a_new;
    }  
  return ptr;
  }   
  
  
long power(int a,int b){
  long count=1;
  for(int i=0;i<b;i++)
    count=count*a;
  return count;  
  }
    

long dec(int* a){
  long count=0;
  for(int i=0;i<15;i++){
    count=count+(a[i]*power(2,i));
    }
  return count;
  }      
  
  
int* mult(int* a, int* b){
  int *c;
  c=(int*)malloc(15*sizeof(int));  
  for(int k=0;k<=14;k++){
    c[k]=0;
    for(int i=0;i<15;i++)
      for(int j=0;j<15;j++)
        if(i+j==k){
          c[k]=(a[i]*b[j])+c[k];
          c[k]=c[k]%2;
          }
    }
  return c;
  }           
  
  
int deg(int* a){
  int deg_a=0;
  for(int i=0;i<15;i++)
    if(a[i]==1)
      deg_a=i;  
  return deg_a;
  } 
  

    
int* mod(int* a,int* b){
  int c[15],*c1,deg_a,deg_b;
  
  while(deg(a)>=deg(b)){
    for(int i=0;i<15;i++)
      c[i]=0;
    
    c[deg(a)-deg(b)]=1;
    c1=mult(b,&c[0]);
    for(int i=0;i<15;i++)
      a[i]=(a[i]+c1[i])%2;  
    }
  return a;
  }
  
  
//					functions for AES
  
int* field_mult(int* a,int* b){
  int *c,*gen_poly;
  c=mult(a,b);  
  int gen_poly1[15]={1,1,0,1,1,0,0,0,1,0,0,0,0,0,0};
  gen_poly=&gen_poly1[0];
  a=mod(c,gen_poly);
  return a;
  }        
  
   
int* field_inv(int* a){
  int *c,*gen_poly,count;
  c=(int*)malloc(15*sizeof(int));
  int gen_poly1[15]={1,1,0,1,1,0,0,0,1,0,0,0,0,0,0};
  gen_poly=&gen_poly1[0];
  
  for(int i=1;i<256;i++){
    c=binary(i);
    c=mult(c,a);
    c[0]=(c[0]+1)%2;		// addition  of c(x) with polynomial 1
    c=mod(c,gen_poly);
    count=0;
    for(int j=0;j<15;j++)
      if(c[j]==0)
        count++;
    if(count==15)
      return binary(i);
    }
  }
    

int* subbytes(int* z){
  int count=0,*c,b[15];
  for(int i=0;i<15;i++)
    if(z[i]==0)
      count++;
  if(count!=15)
    z=field_inv(z);  
   
  int c1[15]={1,1,0,0,0,1,1,0,0,0,0,0,0,0,0};
  c=&c1[0];  
    
  for(int i=0;i<8;i++)
    b[i]=(z[(i%8)]+z[(i+4)%8]+z[(i+5)%8]+z[(i+6)%8]+z[(i+7)%8]+c[i])%2;
    
  for(int i=8;i<15;i++)
    b[i]=0;  
  z=&b[0];
  return z;
  }
  


int** shift_rows(int** a){
  int c,d;
  c=a[1][0];
  for(int i=0;i<3;i++)
    a[1][i]=a[1][i+1];
  a[1][3]=c;
      
  c=a[2][0];  d=a[2][1];
  for(int i=0;i<2;i++)
    a[2][i]=a[2][i+2];
  a[2][2]=c;  
  a[2][3]=d;
  
  c=a[3][3];
  for(int i=3;i>0;i--)
    a[3][i]=a[3][i-1];
  a[3][0]=c;
  return a;
  }
  
  
int** mix_column(int** s,int c){
  int **t,**u,**u_1,x[15]={0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},x_plus_1[15]={1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
  t=(int**)malloc(4*sizeof(int*));
  u=(int**)malloc(4*sizeof(int*));  
  u_1=(int**)malloc(4*sizeof(int*));    
  
  for(int i=0;i<4;i++)
    t[i]=binary(s[i][c]);
  
  u[0]=field_mult(t[0],&x[0]);  u_1[0]=field_mult(t[1],&(x_plus_1[0]));
  for(int i=0;i<8;i++)
    u[0][i]=(u[0][i]^u_1[0][i]^t[2][i]^t[3][i]);


  u[1]=field_mult(t[1],&x[0]);  u_1[1]=field_mult(t[2],&(x_plus_1[0]));
  for(int i=0;i<8;i++)
    u[1][i]=(u[1][i]^u_1[1][i]^t[3][i]^t[0][i]);


  u[2]=field_mult(t[2],&x[0]);  u_1[2]=field_mult(t[3],&(x_plus_1[0]));
  for(int i=0;i<8;i++)
    u[2][i]=(u[2][i]^u_1[2][i]^t[0][i]^t[1][i]);


  u[3]=field_mult(t[3],&x[0]);  u_1[3]=field_mult(t[0],&(x_plus_1[0]));
  for(int i=0;i<8;i++)
    u[3][i]=(u[3][i]^u_1[3][i]^t[1][i]^t[2][i]);


  for(int i=0;i<4;i++)
    s[i][c]=dec(&u[i][0]);
    
  return s;
  }
  
  
int* sub_word(int *a){  
  for(int i=0;i<4;i++)
    a[i]=dec(subbytes(binary(a[i])));
  return a;
  }  
  
  
int* rot_word(int* a){
  int *b;
  b=(int*)malloc(4*sizeof(int));
  
  for(int i=1;i<=4;i++)
    b[i-1]=a[i%4];
  return b;
  }  
    

int** key_expansion(char* key){
  int **rcon,r_con1[10][4],**w,*temp;
  rcon=(int**)malloc(10*sizeof(int*));
  temp=(int*)malloc(4*sizeof(int));
  
  w=(int**)malloc(44*sizeof(int*));
  for(int i=0;i<44;i++)
    w[i]=(int*)malloc(4*sizeof(int));
  
  int rcon_1[10][4]={{0x01,0x00,0x00,0x00},{0x02,0x00,0x00,0x00},{0x04,0x00,0x00,0x00},{0x08,0x00,0x00,0x00},{0x10,0x00,0x00,0x00},{0x20,0x00,0x00,0x00},{0x40,0x00,0x00,0x00},{0x80,0x00,0x00,0x00},{0x1b,0x00,0x00,0x00},{0x36,0x00,0x00,0x00}};
  
  
  for(int i=0;i<10;i++)
    rcon[i]=&rcon_1[i][0];
    
  for(int i=0;i<4;i++)
    for(int j=0;j<4;j++)
      w[i][j]=key[(4*i)+j];  
      
  for(int i=4;i<44;i++){
    for(int j=0;j<4;j++)
      temp[j]=w[i-1][j];
      
    if(i%4==0){
      temp=sub_word(rot_word(temp));  
      for(int j=0;j<4;j++)
        temp[j]=temp[j]^rcon[(i/4)-1][j];
      }
    for(int j=0;j<4;j++)
      w[i][j]=w[i-4][j]^temp[j];
    }
  return w;  
  }         
          
    
int** add_round_key(char* round_key,char* state){
  int **r_key,**s;
  r_key=(int**)malloc(4*sizeof(int*));
  s=(int**)malloc(4*sizeof(int*));  
  for(int i=0;i<4;i++){
    r_key[i]=(int*)malloc(4*sizeof(int));
    s[i]=(int*)malloc(4*sizeof(int));
    }
        
  for(int i=0;i<16;i++){
    r_key[i-(4*(i/4))][i/4]=round_key[i];         
    s[i-(4*(i/4))][i/4]=state[i];   
    }      
   
  for(int i=0;i<4;i++)
    for(int j=0;j<4;j++)
      s[i][j]=r_key[i][j]^s[i][j];  
      
  return s;     
  }
 
    
int** aes(int** s,int **round_key){
  int **key;
  key=(int**)malloc(4*sizeof(int*));
  for(int i=0;i<4;i++)
    key[i]=(int*)malloc(4*sizeof(int));    
  
  for(int i=0;i<(10-1);i++){
    int *a;
        
    for(int j=0;j<4;j++)
      for(int k=0;k<4;k++)
        s[j][k]=dec(subbytes(binary(s[j][k])));

    s=shift_rows(s);
      
    for(int j=0;j<4;j++)
      s=mix_column(s,j);  
    
    for(int j=0;j<4;j++)
      for(int k=0;k<4;k++)
        key[k][j]=round_key[(4*(i+1))+j][k];  		//transpose
    
    for(int j=0;j<4;j++)
      for(int k=0;k<4;k++)
        s[j][k]=s[j][k]^key[j][k];
    }
    
//	last round    
  int *a;    
  for(int j=0;j<4;j++)
    for(int k=0;k<4;k++)
      s[j][k]=dec(subbytes(binary(s[j][k])));
 
  s=shift_rows(s);  
    
  for(int j=0;j<4;j++)
    for(int k=0;k<4;k++)
      key[k][j]=round_key[(4*(9+1))+j][k];  		//transpose
    
  for(int j=0;j<4;j++)
    for(int k=0;k<4;k++)
      s[j][k]=s[j][k]^key[j][k];
        
  return s;    
  }  
    
  
int main(){
  int len_msg=0,len_key=0;
  char *msg_taken,*msg,key[16];
  msg=(char*)malloc(16*sizeof(char));
  msg_taken=(char*)malloc(100*sizeof(char));  
  
//	message entering
  printf("enter the message:");
  scanf("%c",&msg_taken[0]); 
  while(msg_taken[len_msg]!='\n'){
    len_msg++;
    scanf("%c",&msg_taken[len_msg]);
    }  
      
//	key entering  
  printf("enter the key:");
  scanf("%c",&key[0]);  
  while(key[len_key]!='\n'){
    len_key++;
    scanf("%c",&key[len_key]);
    } 
    
  int **round_key,**state,count=0;
  printf("\nencrypted text:\n");
    
  while(len_msg>0){
    for(int i=0;(i<len_msg && i<16);i++)
      msg[i]=msg_taken[i+(16*count)];
      
    if(len_msg<16)
      for(int i=len_msg;i<16;i++)
        msg[i]=' ';  
  
    state=add_round_key(&key[0],msg); 
    round_key=key_expansion(&key[0]);

    state=aes(state,round_key);
  
    for(int i=0;i<4;i++)
      for(int j=0;j<4;j++)
        printf("%x  ",state[j][i]);
        
printf("-------------------------------------------------------------------------------------------");        
    for(int i=0;i<4;i++)
      for(int j=0;j<4;j++)
        printf("%d  ",state[j][i]);
  
    len_msg=len_msg-16;
    count++;  
    }
  printf("\n");
  }
  
  
  
//	sample msg=  "Two One Nine Two"
//	sample key=  "Thats my Kung Fu"  
//	sample in dec= "41 195 80 95 87 20 32 246 64 34 153 179 26 2 215 58"

//	encrypted text  
