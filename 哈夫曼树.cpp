//P264，第9题
//a.写一个程序，为给定的数构造一套哈夫曼编码，生成一套哈夫曼编码。
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define N 50 //叶子结点数目的最大数
#define M 2*N-1 //树中结点总数。完全二叉树中n2=n0-1,n=n0+n2=2n0-1 
typedef struct{
	char data[5];//结点值 
	int weight;//权重 
	int parent;
	int lchild;
	int rchild;
}HTNode;//定义哈夫曼树存储结构
 
typedef char **HuffmanCode;//定义哈夫曼编码存储结构 

//构造具有n个结点的哈夫曼树
void CreateHT(HTNode ht[], int n){
	char *str[]={"8","4","5","9","13","20","26","10"};//待编码字符，这是一个字符串数组
	int num[]={8,4,5,9,13,20,26,10};//待编码字符出现的频率
	int i,k,lnode,rnode;
	int m1,m2;
	
	for(i=0;i<n;i++){
		//用待编码字符以及频率初始化ht[]数组
		strcpy(ht[i].data,str[i]);//strcpy将str[]复制到ht[]中,strcpy只用于字符串复制，并且它不仅复制字符串内容之外，还会复制字符串的结束符
		ht[i].weight=num[i]; 
	} 
	
	for(i=0;i<2*n-1;i++){
		//n个叶子结点，总共2n-1个结点 
		//ht[]数组中所有结点的相关域初值设置为-1 
		ht[i].parent=-1;
		ht[i].lchild=-1;
		ht[i].rchild=-1;
	} 
	
	for(i=n;i<2*n-1;i++){
		m1=32767;m2=32767;//存放最小和次小权重值
		lnode=-1;rnode=-1;//最小和次小权重的结点位置
		
		for(k=0;k<=i-1;k++){//循环遍历寻找权值最小和次小的结点 
			if(ht[k].parent==-1){
			//根据parent是否等于-1来判断此结点是否已经跟另一结点结合成新结点。
			//那么循环结束后需要更新此轮所选出的最小和次小结点的parent值。 
				if(ht[k].weight<m1){
					m2=m1;
					rnode=lnode;
					m1=ht[k].weight;
					lnode=k;
				}
				else{
					if(ht[k].weight<m2){
						m2=ht[k].weight;
						rnode=k;
					}
				}		
			}	 
		}
		
		//设置双亲结点和权值 
		ht[rnode].parent=i;
		ht[lnode].parent=i;//最小和次小权重结点的双亲
		ht[i].weight=ht[rnode].weight+ht[lnode].weight;// 最小和次小权重结点双亲的权值
		
		//设置双亲结点的lchild和rchild。位序小的放在左子树上，位序大的放在右子树上 
		if(lnode>rnode){
			ht[i].lchild=lnode;
			ht[i].rchild=rnode;
		}
		else{
			ht[i].lchild=rnode;
			ht[i].rchild=lnode;
		} 	
	}
}

//构造哈夫曼编码hcd 
void CreateHCode(HTNode ht[], HuffmanCode hcd, int n){
	int i,f,c,temp;
	char *hc;//存放哈夫曼编码的工作数组
	
	//根据哈夫曼树求n个叶子的哈夫曼编码 
	for(i=0;i<n;i++){
		hc=(char *)malloc(n*sizeof(char));//分配存放编码的工作区间 
		hc[n]='\0';
		temp=n-1;//temp指示编码字符在hc中首位置
		c=i;//c为被编码字符串位置
		f=ht[i].parent;//f为c的双亲位置
		while(f!=-1){
			if(ht[f].lchild==c)
				hc[temp--]='0';//左孩子的编码 
			else
				hc[temp--]='1';//右孩子的编码
			c=f;
			f=ht[f].parent;  
		} 
		hcd[i]=(char*)malloc((n-temp)*sizeof(char));//给第i个字符编码分配空间
		strcpy(hcd[i],hc+temp+1);
	} 
}

//输出哈夫曼编码 
 void DispHCode(HTNode ht[], HuffmanCode hcd, int n){
	int i;
	int sum=0,m=0,j;
	printf("输出哈夫曼编码:\n");
	for(i=0;i<n;i++){
		j=0;
		printf("%s:\n",ht[i].data);
		while(hcd[i][j]!='\0'){
			printf("%c",hcd[i][j]);
			j++;
		}
		printf("\n");
	}
}

int main(){
	int n=8;
	HTNode ht[M];
	HuffmanCode hcd;
	hcd=(HuffmanCode)malloc((2*n)*sizeof(char*));
	CreateHT(ht,n);
	CreateHCode(ht,hcd,n);
	DispHCode(ht,hcd,n);
	printf("\n");
	return 0;
}
