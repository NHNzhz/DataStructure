#include<cstdio>
#include<cstdlib>
#include"CircleList.h"
void JosephRing(CircleList &L,int pasw){
    int da,nu,i=1,len=L.len;
    LNode *p=L.head;
    while(L.head){
        pasw%=len;
        if(!pasw) pasw=len;
        if(len+2-pasw>pasw){
            printf("顺时针遍历较快,");
            p=ListDeleteSeq(L,p,pasw,da,nu);
        }
        else{
            printf("逆时针遍历较快,");
            p=ListDeleteDeq(L,p,len-pasw+2,da,nu);
        }
        printf("第%d个出列的位序是：%d\n",i++,nu);
        pasw=da;
        len--;
    }
}
int main(){
    int n,m,i,dat;
    CircleList L;
    IniList(L);
    printf("《约瑟夫环》\n");
    printf("请输入人数：");
    scanf("%d",&n);
    printf("请输入第1个人的密码：");
    scanf("%d",&dat);
    ListAppend(L,dat,1);
    for(i=2;i<=n;i++){
        printf("请输入第%d个人的密码：",i);
        scanf("%d",&dat);
        ListAppend(L,dat,i);
    }
    printf("\n当前循环双向链表中的数据元素依序为：\n\n");
    ListTraverse(L);
    printf("请输入初始密码：");
    scanf("%d",&m);
    JosephRing(L,m);
    system("pause");
    return 0;
}
