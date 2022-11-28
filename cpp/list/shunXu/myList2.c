/*这种写法在上一种方法基础上进行改良*/
#include <stdio.h>
#include <stdlib.h>

//1.定义状态码
#define OK 1
#define ERROR 0
//2.定义bool类型
#define TRUE 1
#define FALSE 0
#define List_Init_Size 100
#define LISTINCREMENT 10

typedef int ElemType;
typedef int Status;
typedef struct
{
    ElemType* data;
    int length;//现有长度
    int listsize;//容量
}SqList;

/*初始化*/
Status InitList(SqList *L){
    L->data = (ElemType*)malloc(sizeof(ElemType)*List_Init_Size);
    if(! L->data) 
        return ERROR;
    L->length = 0;
    L->listsize = List_Init_Size;
    return OK;
}

/*销毁*/
Status DestroyList(SqList* L){
    if(! L->data){
        return ERROR;
    }
    free(L->data);
    L->data = NULL;
    L->length = 0;
    L->listsize = 0;
    return OK;
}

/*插入一个元素*/
//O(n)
Status ListInsert(SqList* L, int i, ElemType e){
    int k;
    //插入范围： [0, L.length]
    if(i<1 || i>L->length+1)
        return ERROR;

    //表已经满了
    if(L->length >= L->listsize){
        //重新开一块空间
        ElemType* ptr = (ElemType*)realloc(L->data,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!ptr) return ERROR;
        //把原空间中数据转移
        L->data = ptr;
        L->listsize += LISTINCREMENT;
    }
    
    ElemType *p;
    ElemType *q = &(L->data[i-1]);
    for(p = &(L->data[L->length-1]); p>=q; --p)
        *(p+1) = *p;
    *q = e;
    L->length++;
    
    return OK;
}


int main(){

}