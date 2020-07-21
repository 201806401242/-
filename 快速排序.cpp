/*140页第7题
a.对于一个包含100万随机数的数组排序，快速排序、插入排序*/
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

//快速排序
void QuickSort(int a[],int low,int high)  
{
	int temp,i,j;
	i=low;
	j=high;
	temp=a[i];    //初始化，temp中存的就是基准数 
	while(i<j)    //完成比temp大的在右边，比temp小的在左边
	{
		while((i<j)&&(a[j]>temp))  //顺序很重要，要先从右往左找 
			j--;
		a[i]=a[j];
		while((i<j)&&(a[i]<=temp))  //再从左往右找 
			i++;
		a[j]=a[i];
	}
	a[i]=temp;  //最终将基准数归位 
	if((i-1)>low)	           //递归调用左半部数组部分
		QuickSort(a,low,i-1);  //对左侧区域进行快速排序	
	if(high>(i+1))                //递归调用右半部数组部分
		QuickSort(a,i+1,high);    //对右侧区域进行快速排序
}

//插入排序 
void insert(int a[] , int len)
{
	for(int i=1;i<len;i++)
	{   //a[i]是最左边的无序元素，每次循环将a[i]放到合适位置
		int temp = a[i];
		int j;
		for(j=i-1;j>=0;j--)
		{
			if(a[j]>temp)   //要把a[i]放到位置j，原下标j到i-1的元素都往后移一位
			   a[j+1] =a[j];
			else
			  break;
		 } 
		a[j+1] = temp;
	}
 } 

//主程序调用 
int main()
{
    int i;
	int m[N];
    //初始化随机数 
    srand((unsigned)time(NULL));
	for(i=0;i<N;m[++i]=rand());
	insert(m,N);   //插入排序调用 
	printf("插入排序从小到大排序后:\n");
	for(i=0;i<N;i++)
	{
	printf("    %d",m[i]);     //输出排序结果
	}
	printf( "\n" );
	QuickSort(m,0,N);   //快速排序调用 
	printf("快速排序从小到大排序后:\n");
	for(i=0;i<N;i++)
	{
	printf("    %d",m[i]);     //输出排序结果
	}
	printf( "\n" );
}

