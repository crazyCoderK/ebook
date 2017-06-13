/*�ڳ�������и������ע�س�����߼��ԣ�����������֤ʵ������У�������ǿ��ǳ��������ԣ�
  Ҳ��������Ƴ���ʱ��һ��������˼·������������о������������ĳ���������Ե�ǰ���£�
  �Գ����������͵��˽��Եø�Ϊ��Ҫ������ʵ��֮ǰ�������Ҫ֪������Ĺ��ܣ��Ա���Ƹ�Ϊ���Ի�
  ����
*/
/*��ʵ������ڽӾ�����Ϊ�洢�ṹ
  ���Ƚ������ڽӾ���Ϊ�洢�ṹ��ͼ�ĳ�����������
  ������ʵ�֣��Խ���������ͼ��������ȼ�������ȱ�������˸�ʵ����Ҫ����Ƴ����������ͣ�
  �������㷨��ʵ������á�
*/
#include<iostream.h>
const int MaxSize=10;
template<class T>
class MGraph
{
	public:
		MGraph(T a[],int n,int e);    //���캯��
		~MGraph()  {}                 //��������
		void DFSTraverse(int v);      //������ȱ���
		void DFSTraverse1(int v);     //������ȷǵݹ��㷨 ,�����v��������Ԫ�ص��±�
		void DFSTraverse2(int v);
		void BFSTraverse(int v);      //������ȱ���
	private:
		T vertex[MaxSize];            //���ͼ�ж��������
		int arc[MaxSize][MaxSize];     //���ͼ�бߵ����飬�ڽӴ洢�ĺ��Ĳ��֣���ȡֵ������������֮����û�б�����
		int vertexNum,arcNum;
		int visited[MaxSize];
};
//���캯��
template<class T>
MGraph<T>::MGraph(T a[],int n,int e)
{
	vertexNum=n; arcNum=e;
	for(int i=0;i<vertexNum;i++)
		vertex[i]=a[i];           //��ʼ���������飬���������鸳ֵ
	for(i=0;i<MaxSize;i++)
		visited[i]=0;
	for(i=0;i<vertexNum;i++)       //��ʼ���ڽӾ���
		for(int j=0;j<vertexNum;j++)
			arc[i][j]=0;
	for(int k=0;k<arcNum;k++)      //�����ڴ˴���ת��ԭ���ǣ�arcNum�����ĳ�ֵΪ��
	{   
		int i,j;
		cout<<"��������λ��������"<<endl;
		cin>>i>>j;
		arc[i][j]=1;
		arc[j][i]=1;               //������Ϊ����ͼ�ڽӾ��󣬾�����ڶԽ��߶Գ�
	}
}
template<class T>
void MGraph<T>::DFSTraverse(int v)    //������ȱ����ݹ��㷨
{
	//int visited[MaxSize];               //visited[����һ��Ҫ��ʼ����,��ʼ��������һ���൱��Ҫ�����⣬��������ж�����У����Ե���Ϊ��Ҫ����Ȼ�Ļ���������ѭ����������ִ��
	/*for(int i=0;i<MaxSize;i++)
		visited1[i]=0;*/
	cout<<vertex[v]<<" ";                //visited ���鲻����������г�ʼ�����ݹ���ý�ʹ���鲻�ϵس�ʼ����������ѭ��
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
	s[++top]=v;               //����ջ��˼��
	while(top!=-1)
	{
		v=s[top];              //����������ջ��Ԫ���޷�ȡ����vû�н�ջ
		for(int j=0;j<vertexNum;j++)
			if(arc[v][j]==1&&visited1[j]==0)
			{
				cout<<vertex[j]<<" ";
				visited1[j]=1;  //�����visited1�ú����е�visited�������������е�visited����
				s[++top]=j;
				//break;
			}
			if(j==vertexNum) top--;
	}
}
/*������㷨��������Ҫע����ǣ�visited1����ļ�¼���⣬�����������Ѿ�������һ��visited���飬һ��Ҫ�������ߣ��ڱ�д������������󣬲����������Ǿ��Ѿ��ɹ�����
Ҫ���Ļ�Ҫ��֤�����Ƿ��������Ľ�����ڵ��Գ���Ĺ����У�Ѱ�ҵ����ַ��������ǲ����ڱ�д������Ѱ�ҵ���Ȥ���ڷǵݹ��㷨��һ��Ҫ���ջ�ĸ�����ܰ�������������߼���
�ڵ��Գ���������������Ҫ������*/
template<class T>
void MGraph<T>::DFSTraverse2(int v)
{
	int s[MaxSize];
	int visited1[MaxSize];
	for(int i=0;i<MaxSize;i++)
		visited1[i]=0;
	int top=-1;
	cout<<vertex[v]<<" ";
	visited1[v]=1;        //�����visited1Ϊ��ȷ�����Ժ�ĳ�������û���κα仯
	s[++top]=v;               //����ջ��˼��
	while(top!=-1)
	{
		v=s[top];              //����������ջ��Ԫ���޷�ȡ����vû�н�ջ��  ����Ĺؼ������ʼ�Ķ����ջ
		for(int j=0;j<vertexNum;j++)
		{	if(arc[v][j]==1&&visited1[j]==0)
			{
				//cout<<vertex[j]<<" ";
				visited1[j]=1;  //�����visited1�ú����е�visited�������������е�visited����
				s[++top]=j;
				//break;
			}
			//if(j==vertexNum) top--;
		}
		
		if(top>0)      //�˺����������ջ��Ԫ���޷���ջ
		{
			cout<<vertex[s[top]]<<" ";
			top--;
		}
		if(top==0)
			top--;
	}
}
/*
1��visited2�����ʼ��
2,�ظ�����Ĳ���ֱ��front==rear
    ��ͷԪ�غ��ƣ�
    ��v����δ�����ʵĽ��
     ���ʱ�־��1��
     ��β�����±����
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
		v=q[++front];                  //���ַ���ģ����ӣ�����ͷ�����±����
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
	//char a[4]={"we","are","good","!"};    ����һ�����飬��洢����ͼ�еĽ��Ԫ��,��������Ԫ�ز���Ҫ��˫���ţ���Ϊ����������Ϊ��Ϊ�ַ�������������
	int a[4]={1,3,4,5};
	MGraph<int> g(a,4,4);        //����ĳ�ʼ�������ö�����ö���Ĺ��캯�������ݺ��������أ�����Զ�ƥ�䶨��Ĺ��캯����������Ĭ�ϵĹ��캯��,ע��ͼ���߼��ԣ�
	//int a[5]={1,2,3,4,5,};
	//MGraph<int> g(a,5,5);
	cout<<"������ȱ����ݹ��㷨�Ľ��Ϊ��";
    g.DFSTraverse(0);cout<<endl;
	cout<<"������ȷǵݹ��㷨�Ľ��Ϊ��";
	g.DFSTraverse2(0);   cout<<endl;
	cout<<"��������㷨2�Ľ��Ϊ��";
	g.DFSTraverse1(0);cout<<endl;
	cout<<"������ȱ����ǵݹ��㷨��";
	g.BFSTraverse(0); cout<<endl;
}