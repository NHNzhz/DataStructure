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
            printf("˳ʱ������Ͽ�,");
            p=ListDeleteSeq(L,p,pasw,da,nu);
        }
        else{
            printf("��ʱ������Ͽ�,");
            p=ListDeleteDeq(L,p,len-pasw+2,da,nu);
        }
        printf("��%d�����е�λ���ǣ�%d\n",i++,nu);
        pasw=da;
        len--;
    }
}
int main(){
    int n,m,i,dat;
    CircleList L;
    IniList(L);
    printf("��Լɪ�򻷡�\n");
    printf("������������");
    scanf("%d",&n);
    printf("�������1���˵����룺");
    scanf("%d",&dat);
    ListAppend(L,dat,1);
    for(i=2;i<=n;i++){
        printf("�������%d���˵����룺",i);
        scanf("%d",&dat);
        ListAppend(L,dat,i);
    }
    printf("\n��ǰѭ��˫�������е�����Ԫ������Ϊ��\n\n");
    ListTraverse(L);
    printf("�������ʼ���룺");
    scanf("%d",&m);
    JosephRing(L,m);
    system("pause");
    return 0;
}
