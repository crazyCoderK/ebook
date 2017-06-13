/*在程序设计中更多的是注重程序的逻辑性，因此在设计验证实验程序中，更多的是考虑程序完整性，
  也就是在设计程序时有一个清晰地思路，经过认真的研究，对面向对象的程序设计语言的前提下，
  对抽象数据类型的了解显得更为重要，在做实验之前更多的是要知道程序的功能，以便设计更为人性化
  程序
*/
/*该实验采用邻接矩阵作为存储结构
  首先建立以邻接矩阵为存储结构的图的抽象数据类型
  方法的实现：对建立的无向图，进行深度及广度优先遍历，因此该实验主要是设计抽象数据类型，
  并做好算法的实现与调用。
*/
#include<iostream.h>
const int MaxSize=10;
template<class T>
class MGraph
{
	public:
		MGraph(T a[],int n,int e);    //构造函数
		~MGraph()  {}                 //析构函数
		void DFSTraverse(int v);      //深度优先遍历
		void DFSTraverse1(int v);     //深度优先非递归算法 ,这里的v代表数组元素的下标
		void DFSTraverse2(int v);
		void BFSTraverse(int v);      //广度优先遍历
	private:
		T vertex[MaxSize];            //存放图中顶点的数组
		int arc[MaxSize][MaxSize];     //存放图中边的数组，邻接存储的核心部分，其取值就是两个顶点之间有没有边相连
		int vertexNum,arcNum;
		int visited[MaxSize];
};
//构造函数
template<class T>
MGraph<T>::MGraph(T a[],int n,int e)
{
	vertexNum=n; arcNum=e;
	for(int i=0;i<vertexNum;i++)
		vertex[i]=a[i];           //初始化定点数组，将定点数组赋值
	for(i=0;i<MaxSize;i++)
		visited[i]=0;
	for(i=0;i<vertexNum;i++)       //初始化邻接矩阵
		for(int j=0;j<vertexNum;j++)
			arc[i][j]=0;
	for(int k=0;k<arcNum;k++)      //程序在此处跳转的原因是，arcNum赋给的初值为零
	{   
		int i,j;
		cout<<"请输入两位正整数："<<endl;
		cin>>i>>j;
		arc[i][j]=1;
		arc[j][i]=1;               //由于其为无向图邻接矩阵，矩阵关于对角线对称
	}
}
template<class T>
void MGraph<T>::DFSTraverse(int v)    //深度优先遍历递归算法
{
	//int visited[MaxSize];               //visited[数组一定要初始化】,初始化问题是一个相当重要的问题，在下面的判断语句中，其显得尤为重要，不然的话程序将跳出循环，不向下执行
	/*for(int i=0;i<MaxSize;i++)
		visited1[i]=0;*/
	cout<<vertex[v]<<" ";                //visited 数组不能再这里进行初始化，递归调用将使数组不断地初始化，陷入死循环
	visited[v]=1;
 	for(int j=0;j<vertexNum;j++)
	{	if(arc[v][j]==1&&visited[j]==0)
	    DFSTraverse(j);
	}
}
template<class T>
void MGraph<T>::DFSTraverse1(int v)
{
	int s[MaxSize];
	int visited1[MaxSize];
	for(int i=0;i<MaxSize;i++)
		visited1[i]=0;
	int top=-1;
	cout<<vertex[v]<<" ";
	visited1[v]=1;
	s[++top]=v;               //利用栈的思想
	while(top!=-1)
	{
		v=s[top];              //初步调试是栈顶元素无法取出，v没有进栈
		for(int j=0;j<vertexNum;j++)
			if(arc[v][j]==1&&visited1[j]==0)
			{
				cout<<vertex[j]<<" ";
				visited1[j]=1;  //这里的visited1该函数中的visited独立与主函数中的visited数组
				s[++top]=j;
				//break;
			}
			if(j==vertexNum) top--;
	}
}
/*在这个算法中我们需要注意的是：visited1数组的记录问题，由于在类中已经定义了一个visited数组，一定要区别两者，在编写程序运行无误后，并不等于我们就已经成功，我
要做的还要验证程序是否符合运算的结果，在调试程序的过程中，寻找到这种方法，我们才能在编写程序中寻找到乐趣。在非递归算法中一定要理解栈的概念，它能帮助你理解程序的逻辑性
在调试程序总起着至关重要的作用*/
template<class T>
void MGraph<T>::DFSTraverse2(int v)
{
	int s[MaxSize];
	int visited1[MaxSize];
	for(int i=0;i<MaxSize;i++)
		visited1[i]=0;
	int top=-1;
	cout<<vertex[v]<<" ";
	visited1[v]=1;        //这里的visited1为正确，在以后的程序中其没有任何变化
	s[++top]=v;               //利用栈的思想
	while(top!=-1)
	{
		v=s[top];              //初步调试是栈顶元素无法取出，v没有进栈；  问题的关键是让最开始的顶点出栈
		for(int j=0;j<vertexNum;j++)
		{	if(arc[v][j]==1&&visited1[j]==0)
			{
				//cout<<vertex[j]<<" ";
				visited1[j]=1;  //这里的visited1该函数中的visited独立与主函数中的visited数组
				s[++top]=j;
				//break;
			}
			//if(j==vertexNum) top--;
		}
		
		if(top>0)      //此函数设计是让栈顶元素无法出栈
		{
			cout<<vertex[s[top]]<<" ";
			top--;
		}
		if(top==0)
			top--;
	}
}
/*
1，visited2数组初始化
2,重复下面的操作直到front==rear
    队头元素后移；
    以v存在未被访问的结点
     访问标志置1；
     队尾数组下标后移
*/
template<class T>
void MGraph<T>::BFSTraverse(int v)
{  
	int front,rear;
	int visited2[MaxSize],q[MaxSize];
	for(int i=0;i<MaxSize;i++)
		visited2[i]=0;
	front=rear=-1;
	cout<<vertex[v]<<" ";
	visited2[v]=1;
	q[++rear]=v;
	while(front!=rear)
	{
		v=q[++front];                  //此种方法模拟出队，就是头数组下标后移
		for(int j=0;j<vertexNum;j++)
			if(arc[v][j]==1&&visited2[j]==0)
			{
				cout<<vertex[j]<<" ";
				visited2[j]=1;
				q[++rear]=j;
			}
	}
}

void main()
{
	//char a[4]={"we","are","good","!"};    定义一个数组，其存储的是图中的结点元素,对于整数元素不需要将双引号，因为编译器会认为其为字符，引起编译错误
	int a[4]={1,3,4,5};
	MGraph<int> g(a,4,4);        //对象的初始化，采用对象调用定义的构造函数，根据函数的重载，其会自动匹配定义的构造函数，而不是默认的构造函数,注意图的逻辑性，
	//int a[5]={1,2,3,4,5,};
	//MGraph<int> g(a,5,5);
	cout<<"深度优先遍历递归算法的结果为：";
    g.DFSTraverse(0);cout<<endl;
	cout<<"深度优先非递归算法的结果为：";
	g.DFSTraverse2(0);   cout<<endl;
	cout<<"深度优先算法2的结果为：";
	g.DFSTraverse1(0);cout<<endl;
	cout<<"广度优先遍历非递归算法：";
	g.BFSTraverse(0); cout<<endl;
}