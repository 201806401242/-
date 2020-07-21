//(正确版)回溯法2--用回溯法生成{1,2,3,4}的所有排列
/*比如1234，在第一个位置摆放的时候，有4种情况，用一个for循环，第一次找的是1,1就被标记了，再找第二位第三位第四位的时候，1就不可以用了。再找第二位，剩下2、3和4，由于1被标记了，只可以找2、3或者4，先取的是2，取后标记2；再找第三位，剩下了3和4，由于1和2都被标记了，先取3，取后标记3；再找第四位，因1、2、3都被标记了，只可以找4，所以直接就是4.第一个1234就出来了。由于4只有一种情况，执行一次就完了。*/
/*1取过了，则下一位取到了2，相应的第二位、第三位和第四位就剩下了1、3和4，也是一样的操作原理，最后一位取4.*/
/*有路则通，无路则返*/
import java.util.Arrays;
public class Recall2
{ 
    static int count=0;
    public static void main(String args[])
    {
      int a[]={1,2,3,4};
      test(a,0);
      System.out.println(count);
   }
    public static void test(int a[],int b)
    {
       if(b>=a.length){
         count++;
        System.out.println(java.util.Arrays.toString(a));
       } 
       for(int i=b;i<a.length;i++)
       {//从for循环中找出未标记过的一个数，把他标记了，再把剩下未标记的数去递归，交给子方法去做。如果都选完了，那么输出就可以了。
	 if(!used(a,b,i))
	 continue;
	 {//两个数字，进行交换。每一次都是位置b和位置i进行交换。那个判断重复的话，如果i之前，有和i一样的数字（假设为位置k）和b进行交换了，那么将位置i和b交换，与位置k和b交换，是一样的
	   int k=a[b];
	   a[b]=a[i];
	   a[i]=k;
          }
	   test(a,b+1);//利用递归进行下一个数的交换
	   {//再次交换两个数字，换回来
	     int k=a[b];
	     a[b]=a[i];
	     a[i]=k;
          }
       }
    }
 /*排除重复情况的组合*/
    public static boolean used(int a[],int b,int i)
      {
        for(int j=b;j<i;j++)
         {
           if(a[i]==a[j])
           {
	      return false;
	    }
          }
	     return true;
     }
 }
