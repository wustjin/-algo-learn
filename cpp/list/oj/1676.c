//题目：https://www.dotcpp.com/oj/problem1676.html
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*要求实现功能
1.输入顺序和存储顺序相反 ==》 头插入
2.get 获取元素
3.insert 插入元素
4.delete 删除元素 
5.show 遍历元素
*/
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;

typedef struct LNode{
    ElemType data;
    struct LNode* next;
}LNode, *LinkList;

Status InitList(LinkList* L){
    //创建头节点
    (*L) = (LinkList)malloc(sizeof(LNode));
    if(! (*L))
        return ERROR;
    (*L)->next = NULL;
    return OK;
}

void visit(ElemType e){
    printf("%d ",e);
}

//插入 
Status ListInsert(LinkList* L, int i, ElemType e){
    int j;
    LinkList p,s;
    p = *L;
    j = 1;
    while(p && j<i){
        p = p->next;
        j++;
    }
    if(!p || j>i)
        return ERROR;
    //如果到这里，表示j == i找到第i-1个位置
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

Status GetElem(LinkList L, int i, ElemType* e){
    LinkList p = L->next;
    int j = 1;
    while(p && j<i){
        p = p->next;
        j++;
    }
    if(!p || j>i){
        return ERROR;
    }
    *e = p->data;
    return OK;
}

Status DeleteList(LinkList* L, int i, ElemType* e){
    //删除第i个元素 ==》 找到第i-1个元素，并确保第i个元素存在
    LinkList p = *L,s;
    int j = 1;
    while(p->next && j<i){
        p = p->next;
        j++;
    }
    if(! (p->next) || j>i){
        return ERROR;
    }
    s = p->next;
    p->next = s->next;
    *e = s->data;
    free(s);
    return OK;
}

Status TravelList(LinkList L){
    LinkList p = L->next;
    int count = 0;
    while(p){
        count++;
        visit(p->data);
        p = p->next;
    }
    if(count == 0)
        printf("Link list is empty");
    printf("\n");
}

int main() {
    int n,i,m,j;
    LinkList p;
    InitList(&p);
    char str[20];
    int num1,num2,result,status;
    char* cmd[4] = {"get","insert","delete","show"};
    scanf("%d",&n);
    for(i = 0; i<n; i++){
        int mid;
        scanf("%d",&mid);
        ListInsert(&p,1,mid);
    }
    TravelList(p);
    scanf("%d",&m);
    for(i = 0; i<m; i++){
        scanf("%s",str);
        for(j = 0; j<4; j++)
        {
            if(strstr(str,cmd[j])){
                //不为空说明匹配
                switch (j)
                {
                    case 0: //get
                        scanf("%d",&num1);
                        status = GetElem(p,num1,&result);
                        if(status) printf("%d\n",result);
                        else printf("get fail\n");
                        break;
                    case 1: //insert
                        scanf("%d %d",&num1,&num2);
                        status = ListInsert(&p,num1,num2);
                        if(status) printf("insert OK\n");
                        else printf("insert fail\n");
                        break;
                    case 2: //delete
                        scanf("%d",&num1);
                        status = DeleteList(&p,num1,&result);
                        if(status) printf("delete OK\n");
                        else printf("delete fail\n");
                        break;
                    case 3: //show
                        TravelList(p);
                        break;
                    default:
                        break;
                }
                break;//处理完成后跳出循环 
            }
        }
    }
}