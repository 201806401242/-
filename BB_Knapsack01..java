//P338，第7题。写一个程序用分支界限算法对背包问题求解。
//分支限界算法实现0-1背包问题
import java.util.Stack;  
  class HeapNode {
     double upbound; // 结点的价值上界
     double value; // 结点所对应的价值
     double weight; // 结点所相应的重量
     int level; // 活节点在子集树中所处的层序号

  public HeapNode() {
   }
 }
 
   // 分支限界法实现01背包问题
     public class BB_Knapsack01 { 
     int[] weight;
     int[] value;
     int max; // 背包的最大承重量  
     int n;  
     double c_weight; // 当前背包重量
     double c_value; // 当前背包价值
     double bestv; // 最优的背包价值
     Stack<HeapNode> heap;
   public BB_Knapsack01() {        
     weight = new int[] { 16, 15, 20, 6};
     value = new int[] { 25, 45, 25, 7};
     max = 30;
     n = weight.length - 1;
     c_weight = 0;   //初始化
     c_value = 0;
     bestv = 0;
     heap = new Stack<HeapNode>();
    }
  
  // maxBound求子树的最大上界
   private double maxBound(int t) {
      double left = max - c_weight;  //left为剩余空间
      double bound = c_value;
  // 剩余容量和价值上界
   while (t < n && weight[t] <= left)   //n表示物品总数
     {//以物品单位重量价值递减装填剩余容量
      left -= weight[t];   // weight[t]表示t所占的空间
      bound += value[t];   //value[t]表示t的价值
      t++;
    }
      if (t < n)
      bound += (value[t] / weight[t]) * left; // 装填剩余容量装满背包        
      return bound;     //bound为上界函数
    }

   // 将一个新的活结点插入到子集树和最大堆heap中
   private void addLiveNode(double upper, double cvalue, double cweight,
       int level) {
       HeapNode node = new HeapNode();
       node.upbound = upper;  //新活结点的上界
       node.value = cvalue;
       node.weight = cweight;
       node.level = level;
       if (level <= n)
       heap.push(node);  //放入结点的操作
      }

    // 利用分支限界法，返回最大价值bestv
   private double knapsack() {
       int i = 0;
       double upbound = maxBound(i);
     // 调用maxBound求出价值上界，bestv为最优值
    //主算法循环体
       while (true) // 非叶子结点        
     {     
       double wt = c_weight + weight[i];  //检查当前扩展结点的左儿子结点
       if (wt <= max)// 左儿子结点为可行结点           
         {
       if (c_value + value[i] > bestv)      //若此时的背包价值比当前bestv的背包价值更优
       bestv = c_value + value[i];   //二者更新
       addLiveNode(upbound, c_value + value[i], c_weight + weight[i],i + 1);  //将其加入到子集树和活结点优先队列中
 }
       upbound = maxBound(i + 1);   //仅当右儿子结点满足上界约束时，检查当前扩展结点的右儿子结点
       if (upbound >= bestv) // 右子树可能含最优解
       addLiveNode(upbound, c_value, c_weight, i + 1);  //将其加入子集树和活结点优先队列中
       if (heap.empty())
       return bestv;
       HeapNode node = heap.peek();
       // 取下一扩展结点
       heap.pop();  //数据取出操作
       c_weight = node.weight;
       c_value = node.value;
       upbound = node.upbound;
       i = node.level;
     }
 }
  
    public static void main(String[] args) {
         BB_Knapsack01 knap = new BB_Knapsack01();
         double opt_value = knap.knapsack();
         System.out.println("最大价值为："+opt_value);
     }
 }
