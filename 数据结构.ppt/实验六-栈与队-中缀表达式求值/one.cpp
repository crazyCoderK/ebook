

#include <iostream>
#define STACK_INIT_SIZE 100 //�洢�ռ��ʼ������ 
#define STACKINCREMENT 10 //�洢�ռ�������� 
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1 
#define FALSE 0
using namespace std;
typedef double ElemType;
typedef struct
{
    ElemType *base;//��ջ����֮ǰ������֮��base��ֵΪNULL 
    ElemType *top;//ջ��ָ�� 
    int stacksize;//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ 
}SqStack;
int InitStack(SqStack &S){//����һ����ջS 
    S.base=(ElemType*)malloc(STACK_INIT_SIZE*sizeof(ElemType));
    if(!S.base) return OVERFLOW;
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return OK;
}//--------------------------------------------------------------------InitStack
int DestroyStack(SqStack &S){//����ջS��S���ٴ��� 
if(!S.base) return ERROR;
    S.stacksize=0;
free(S.base);
free(S.top);
    return OK;
}//-----------------------------------------------------------------DestroyStack
int ClearStack(SqStack &S){//��ջS��Ϊ��ջ
    if(!S.base) return ERROR;
    if(S.top==S.base) return OK;
    S.stacksize=0;
    S.top=S.base;
    return OK;
}//-------------------------------------------------------------------ClearStack
double GetTop(SqStack &S){//��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
    if(!S.base) return ERROR;
if(S.top==S.base) return ERROR;
ElemType e;
e=*(S.top-1); 
return e;
}//-----------------------------------------------------------------------GetTop
int Push(SqStack &S,ElemType e){//����Ԫ��eΪ�µ�ջ��Ԫ��
    if(S.top-S.base>=S.stacksize){
        S.base=(ElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(ElemType));
        if(!S.base) return OVERFLOW;
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }//if
    *S.top++=e;
    return OK;
}//-------------------------------------------------------------------------Push
int Pop(SqStack &S,ElemType &e){
//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
    if(!S.base) return ERROR;
if(S.top==S.base) return ERROR;
    e=*--S.top;
    return OK;
}//--------------------------------------------------------------------------Pop
int In(char c){//�ж�c�Ƿ�Ϊ����������򷵻�TRUE,���򷵻�FALSE 
switch(c){
        case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '#': return TRUE;break;
    default: return FALSE;break;
    }//switch
}//---------------------------------------------------------------------------In
int Transfer(int c){//����c�����ȹ�ϵ���е�λ�� 
    switch(c){ 
        case 43: return 0;break;
        case 45: return 1;break;
        case 42: return 2;break;
        case 47: return 3;break;
        case 40: return 4;break;
        case 41: return 5;break;
        case 35: return 6;break;
    }//swicth
}//---------------------------------------------------------------------Transfer
int Precede(int c1,int c2)
{
	//����c1��c2�����ȹ�ϵ���е����ȹ�ϵ 
int a[7][7]={{62,62,60,60,60,62,62},
                  {62,62,60,60,60,62,62},
      {62,62,62,62,60,62,62},
      {62,62,62,62,60,62,62},
      {60,60,60,60,60,61,32},
                  {62,62,62,62,32,62,62},
      {60,60,60,60,60,32,61}};
    int i=Transfer(c1);
    int j=Transfer(c2);
    return a[i][j];
}//----------------------------------------------------------------------Precede
double Operate(double a,int theta,double b){
    switch(theta){
        case 43: return a+b; break;
        case 45: return a-b; break;
        case 42: return a*b; break;
        case 47: return a/b; break;
    }//switch
}//----------------------------------------------------------------------Operate
int main(){//�������ʽ��ֵ������������㷨����OPTR��OPND�ֱ�Ϊ�����ջ��������ջ
    SqStack OPTR;//�����ַ�ջ 
    SqStack OPND;//��������ջ 
double a,b,theta,x,e,m;
char c,n[100];
int i=1;
InitStack(OPTR);
Push(OPTR,35);
n[0]='#';
InitStack(OPND);
cout<<"��������ʽ����'#'������"<<endl;
c=getchar();
while(c!='#'||GetTop(OPTR)!='#'){
        n[i]=c;
        if(!In(c)){
            if(!In(n[i-1])){
             Pop(OPND,e);
     Push(OPND,10*e+c-'0');
     c=getchar();
         }//if
            else{
                Push(OPND,c-'0');
     c=getchar();
         }//else
        }//else             
        else{
            switch(Precede((int)GetTop(OPTR),(int)c)){
                case 60:Push(OPTR,(int)c); //'<'
             c=getchar(); 
       break;
                case 61:Pop(OPTR,x); //'='
             c=getchar(); 
       break;
     case 62:Pop(OPTR,theta);//'>'
                         Pop(OPND,b); 
       Pop(OPND,a);
                         Push(OPND,Operate(a,(int)theta,b));
       break;
             }//switch
        }//else
        i++;
    }//while
    m=GetTop(OPND);
    cout<<m<<endl;
    DestroyStack(OPND);
    DestroyStack(OPTR);
    system ("PAUSE");
    return 0;
}//--------------------------------------------------------------------------END
                                      