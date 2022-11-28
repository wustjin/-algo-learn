/*
*日期：2022-11-27
*作者：wustjin
*内容：链表的顺序实现
*/
#include <stdio.h>
//c语言中最基本的顺序存储结构就是数组
//1.定义状态码
#define OK 1
#define ERROR 0
//2.定义bool类型
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20
typedef int ElemType;
typedef struct 
{
    ElemType data[MAXSIZE];
    int length;
}SqList;
typedef int Status;

/*打印元素 */
Status visit(ElemType c){
    printf("%d ",c);
    return c;
}

/*初始化*/
Status InitList(SqList *L){
    L->length = 0;
    return OK;
}

/*判断链表是否为空，前提L已经存在*/
Status ListEmpty(SqList L){
    if(L.length != 0) return FALSE;
    else return TRUE;
}

/*清除链表元素*/
Status ClearList(SqList* L){
    L->length = 0;
    return OK;
}

/*返回链表元素长度*/
int ListLength(SqList L){
    return L.length;
}

/*获取第i个元素*/
/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值,注意i是指位置，第1个位置的数组是从0开始 */
Status GetElem(SqList L,int i, ElemType* e){
    //判断参数是否合法
    if(i<1 || i>L.length || L.length==0)//注意这里不能为空表 
        return ERROR;
    
    *e = L.data[i-1]; //O(1)
    return OK;
}

/*定位元素*/
/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
/*O(L.length) O(n)*/
int LoacteElem(SqList L, ElemType e){
    int i;
    if(L.length == 0)
        return 0;
    for(i = 0; i<L.length; i++){
        if(L.data[i] == e) break;
    }

    if(i>=L.length) return 0;
    else return i+1;
}

/*插入一个元素*/
//O(n)
Status ListInsert(SqList* L, int i, ElemType e){
    int k;
    //表已经满了
    if(MAXSIZE == L->length)
        return ERROR;
    //插入范围： [0, L.length]
    if(i<1 || i>L->length+1)
        return ERROR;

    if(i<=L->length){
        for(k=L->length; k>=i; k--){
            L->data[k] = L->data[k-1];
        }
    }
    L->data[i-1] = e;
    L->length++;
    
    return OK;
}

/*删除一个元素*/
/*O(n)*/
Status ListDelete(SqList* L, int i, ElemType* e){
    int k;
    if(L->length == 0) 
        return ERROR;
    if(i<1 || i>L->length)
        return ERROR;

    *e = L->data[i-1];
    if(i<L->length){
        for(k=i; k<L->length; k++){
            L->data[k-1] = L->data[k];
        }
    }
    L->length--;
    return OK;
}

/*遍历元素*/
Status ListTraverse(SqList L){
    int i;
    for(i = 0; i<L.length; i++){
        visit(L.data[i]);
    }
    printf("\n");
    return OK;
}

/*将Lb中和La不同的元素插入La中*/
void unionL(SqList *La, SqList Lb){
    int La_len,Lb_len,i;
	ElemType e;                        /*声明与La和Lb相同的数据元素e*/
	La_len=ListLength(*La);            /*求线性表的长度 */
	Lb_len=ListLength(Lb);
    for(i = 1;i<=Lb_len; i++){
        GetElem(Lb,i,&e);
        if(LoacteElem(*La, e) == 0){
            ListInsert(La, ++La_len, e);
        }
    }
}

int main() {
    SqList L;
    SqList Lb;

    //printf("L = %p , Lb = %p\n",&L, &Lb);
    ElemType e;
    Status i;
    int j,k;
    i = InitList(&L);
    i = InitList(&Lb);
    printf("初始化L后：L.length=%d\n",L.length);
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);
    for(j=1; j<=5; j++){
        i = ListInsert(&L, 1, j);
    }
    printf("在L的表头依次插入1～5后：L.data=");
    ListTraverse(L); 

    printf("L.length=%d \n",L.length);
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    i=ClearList(&L);
    printf("清空L后：L.length=%d\n",L.length);
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    for(j=1;j<=10;j++)
            ListInsert(&L,j,j);
    printf("在L的表尾依次插入1～10后：L.data=");
    ListTraverse(L); 

    printf("L.length=%d \n",L.length);

    ListInsert(&L,1,0);
    printf("在L的表头插入0后：L.data=");
    ListTraverse(L); 
    printf("L.length=%d \n",L.length);

    k=ListLength(L); /* k为表长 */
    for(j=k+1;j>=k;j--)
    {
            i=ListDelete(&L,j,&e); /* 删除第j个数据 */
            if(i==ERROR)
                    printf("删除第%d个数据失败\n",j);
            else
                    printf("删除第%d个的元素值为：%d\n",j,e);
    }
    printf("依次输出L的元素：");
    ListTraverse(L); 

    j=5;
    ListDelete(&L,j,&e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为：%d\n",j,e);

    printf("依次输出L的元素：");
    ListTraverse(L); 

	//构造一个有10个数的Lb
	i=InitList(&Lb);
    for(j=6;j<=15;j++)
            i=ListInsert(&Lb,1,j);
    ListTraverse(Lb); 
	unionL(&L,Lb);

	printf("依次输出合并了Lb的L的元素：");
    ListTraverse(L); 

    return 0;
}