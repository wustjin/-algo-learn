#include <stdio.h>
#include <stdlib.h>
//状态值
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;

Status visit(ElemType c){
    printf("%d ",c);
    return OK;
}

//结点数据结构
typedef struct Node
{
    ElemType data; //数据域
    struct Node* next; //指针域
}Node;
typedef struct Node* LinkList;

/*初始化 */
Status InitList(LinkList* L){
    //开辟一个头节点
    *L = (LinkList)malloc(sizeof(Node));
    if(!(*L)) return ERROR;
    (*L)->next = NULL;
    
    return OK;
}

/*判断不为空*/
Status ListEmpty(LinkList L){
    if(L->next)
        return FALSE;
    else
        return TRUE;
}

/*清空list*/
Status ClearList(LinkList* L){
    LinkList p,q;
    p = (*L)->next;
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL;
    return OK;
}

/*获取链表长度*/
//O(n)
 int ListLength(LinkList L){
    int count = 0;
    LinkList p = L->next;
    while(p){
        count++;
        p = p->next;
    }
    return count;
 }

/*获取第i个元素的值*/
Status GetElem(LinkList L, int i, ElemType* e){
    int j;
    LinkList p;
    p = L->next;
    j = 1;
    //由于单链表中以结点形式存放数据
    //不清楚结点个数，必须一个个找
    while(p && j<i){
        p = p->next;
        j++;
    }
    if(!p || j>i)//这里j>i，是防止i<=0情况 
        return ERROR;
    *e = p->data;
    return OK;
}

/*定位元素*/
int LocateElem(LinkList L, ElemType e){
    int i = 0;
    LinkList p;
    p = L->next;
    while(p){
        i++;
        if(p->data == e)
            return i;
        p = p->next;
    }
    return 0;
}

/*在第i个位置前插入元素操作*/
Status ListInsert(LinkList* L, int i, ElemType e){
    int j;
    LinkList p  = *L,s;
    j = 1;//插入第一个位置就是头结点后面，
    while(p && j<i){
        p = p->next;
        j++;
    }
    if(!p || j>i){
        return ERROR;
    }
    s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}
/*删除第i个元素*/
Status ListDelete(LinkList* L, int i, ElemType* e){
    int j;
    LinkList p = *L,q;
    j = 1;
    /*这里思路和前面有点区别，在于删除第i个元素，只要找到第i-1个元素即可*/
    while(p->next && j<i){
        p = p->next;
        j++;
    }
    if(!(p->next) || j>i)
        return 0;
    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}

Status ListTraverse(LinkList L){
    LinkList p = L->next;
    while(p){
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return 0;
}

/*从插入删除上
如果仅针对插入一个元素的话，通过顺序存储结构实现的和链式的时间复杂度为O(n)
但是对于多个元素插入
链式的存储仅第一次为O（n）找位置，之后为O(1)
*/
/*  随机产生n个元素的值，建立带表头结点的单链线性表L（头插法） */
void CreateListHead(LinkList *L, int n) 
{
	LinkList p;
	int i;
	srand(time(0));                         /* 初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;                      /*  先建立一个带头结点的单链表 */
	for (i=0; i<n; i++) 
	{
		p = (LinkList)malloc(sizeof(Node)); /*  生成新结点 */
		p->data = rand()%100+1;             /*  随机生成100以内的数字 */
		p->next = (*L)->next;    
		(*L)->next = p;						/*  插入到表头 */
	}
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法） */
void CreateListTail(LinkList *L, int n) 
{
	LinkList p,r;
	int i;
	srand(time(0));                      /* 初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node)); /* L为整个线性表 */
	r=*L;                                /* r为指向尾部的结点 */
	for (i=0; i<n; i++) 
	{
        //插入操作O（1）
		p = (Node *)malloc(sizeof(Node)); /*  生成新结点 */
		p->data = rand()%100+1;           /*  随机生成100以内的数字 */
		r->next=p;                        /* 将表尾终端结点的指针指向新结点 */
		r = p;                            /* 将当前的新结点定义为表尾终端结点 */
	}
	r->next = NULL;                       /* 表示当前链表结束 */
}
int main(){
LinkList L;
    ElemType e;
    Status i;
    int j,k;
    i=InitList(&L);
    printf("初始化L后：ListLength(L)=%d\n",ListLength(L));
    for(j=1;j<=5;j++)
            i=ListInsert(&L,1,j);
    printf("在L的表头依次插入1～5后：L.data=");
    ListTraverse(L); 

    printf("ListLength(L)=%d \n",ListLength(L));
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    i=ClearList(&L);
    printf("清空L后：ListLength(L)=%d\n",ListLength(L));
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    for(j=1;j<=10;j++)
            ListInsert(&L,j,j);
    printf("在L的表尾依次插入1～10后：L.data=");
    ListTraverse(L); 

    printf("ListLength(L)=%d \n",ListLength(L));

    ListInsert(&L,1,0);
    printf("在L的表头插入0后：L.data=");
    ListTraverse(L); 
    printf("ListLength(L)=%d \n",ListLength(L));

    GetElem(L,5,&e);
    printf("第5个元素的值为：%d\n",e);
    for(j=3;j<=4;j++)
    {
            k=LocateElem(L,j);
            if(k)
                    printf("第%d个元素的值为%d\n",k,j);
            else
                    printf("没有值为%d的元素\n",j);
    }
    

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

    i=ClearList(&L);
    printf("\n清空L后：ListLength(L)=%d\n",ListLength(L));
    CreateListHead(&L,20);
    printf("整体创建L的元素(头插法)：");
    ListTraverse(L); 
    
    i=ClearList(&L);
    printf("\n删除L后：ListLength(L)=%d\n",ListLength(L));
    CreateListTail(&L,20);
    printf("整体创建L的元素(尾插法)：");
    ListTraverse(L); 


    return 0;
}