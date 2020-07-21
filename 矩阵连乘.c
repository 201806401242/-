//P234，第11题。矩阵连乘 考虑如何使得在计算n个矩阵的乘积A1A2…An时，总的乘法次数最小，这些矩阵的维度分别为d0×d1,d1×d2,…,dn-1×dn。
//a.给出一个三个矩阵连乘的例子
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int matrix(int *p, int n, int **m, int **s)
{
    //a[][]最小乘次数
    //s[][]最小乘数时的断开点
    int i,j,r,k;   
    for (i = 0; i < n; i++)   //单一矩阵的最小乘次都置为0
    {
        m[i][i] = 0;
    }
    
    for (r = 2; r <= n; r++)  //r为连乘矩阵的个数
    {
        for (i = 0; i <= n-r; i++)   //i表示连乘矩阵中的第一个
        {
            j = i + r -1;         //j表示连乘矩阵中的最后一个
            m[i][j] = 99999;
            for (k = i; k <= j-1; k++)  //在第一个与最后一个之间寻找最合适的断开点，注：这是从i开始，即要先计算两个单独矩阵相乘的乘次
            {
                int t = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1]; //t表示连乘积，这个部分的计算方法其实就是计算两个矩阵相乘时总共的乘次数
                if (t < m[i][j])  
                {//若当前相乘次数更小
                    m[i][j] = t;   //则更新t和m[i][j]的值
                    s[i][j] = k;   //用s[i][j]记录下k的位置，该值表示最后一次切割的位置是在k处
                }
            }
        }
    }
    return m[0][n-1];
}

void printmatrix(int i, int j, char **a,int **s)
{    //递归的方式来把最小乘数的表达式输出

    if (i == j)
    {
        printf("%s",a[i]);
    }
    else
    {
        printf("(");
        printmatrix(i,s[i][j],a,s);
        printmatrix(s[i][j]+1,j,a,s);
        printf(")");
    }
}

int main()
{
	//定义一个一维数组存放矩阵的行或列
    //min_time[i][j]存储的是i+1到j+1的最小乘次，因为是从0开始
    //min_point[i][j]存储的是i+1到j+1之间最小乘次时的分割点
    int *p, **min_time, **min_point;
    char **a;
    int n = 3;
	int i;
    int result;
    
    p = (int *)malloc((n+1)*sizeof(int));  //分配内存单元
    a = (char **)malloc(n*sizeof(char*));
    min_time = (int **)malloc(n*sizeof(int *));
    min_point = (int **)malloc(n*sizeof(int *));
    
    for (i = 0; i < n; i++)
    {
        min_time[i] = (int *)malloc(n*sizeof(int));  
        min_point[i] = (int *)malloc(n*sizeof(int));
        a[i] = (char *)malloc(n*sizeof(char));
    }
    
    p[0] = 10;   //第一个矩阵的行数
    p[1] = 100;     //第二个矩阵的行数
    p[2] = 5;     //第三个矩阵的行数
    p[3] = 50;     //第三个矩阵的列数   
    
    a[0] = "A1";
    a[1] = "A2";
    a[2] = "A3";
    a[3] = "A4";
    
    result = matrix(p,n,min_time,min_point);
    printf("最小乘次为:%d.\n",result);
    printmatrix(0,n-1,a,min_point);
    printf("\n");
    return 0;
}
