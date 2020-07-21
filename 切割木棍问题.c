//225页第6题  为下列问题设计一个动态规划算法。已知小木棍的销售价格pi和长度i相关，i=1，2，3...,n,如何把长度为n的木棍切割为
//若干根长度为 整数的小木棍，使得所获的总销售价格最大？该算法的时间效率和空间效率各是多少？ 
// 此算法的时间效率是O(n^2)，空间效率是O (N)
//令长度为n的木棍通过切割获得的最大价格利益为p[n]，递推公式为：p[n]=max(price[n],p1+pn-1,p2+pn-2,...pn-1+p1),只需计算出p1至pn-1的值，便可计算出p[n]的值。边界条件p[0]=0 
#include <iostream>    
using namespace std; //自底向上，两个循环，不用递归；   
int main()  
{  
    int num = 10; 
	int  INT_MIN;
    int price[11] = { 0, 1, 5, 9, 6, 10, 15, 16, 20, 25, 30 };   
    int *p = new int[num + 1]; //用于记录p0-pn-1的值 
    for (int i = 0; i <= num; ++i)  
        p[i] = 0;  //初始化  
  
    for (int i = 1; i <= num; ++i)//规模长度为i    
    {  
        int q = INT_MIN;  
        for (int j = 1; j <= i; ++j)//计算规模为i的最大收益    
        {  //针对长度为i时，遍历所有的分割情况，寻找到最佳的效果 
            if (q < (price[j] + p[i - j]))//因为i>i-j，所以当计算p[i]时，p[i-j]已经解决，可以直接使用    
                q = (price[j] + p[i - j]);  //迭代q；  
        }  
        p[i] = q;  //找出i这个位置的最优解；  
    }  
    cout<<"最大总销售价值为：";
    cout << p[num];  //最后是num这个位置，就是num米长的木头的最大价值。     
} 
