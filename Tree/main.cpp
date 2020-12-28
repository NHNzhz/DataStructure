#include <cstdio>
#include <cstring>
#include <cmath>
#include "tree.h"
#define maxparm 30
using namespace std;
//�ж�������߼����ʽ�Ƿ񺬲��Ϸ��ַ�
bool IsValid(char *exp){
    int i,l,r,num,cntl,cntr;
    num=strlen(exp);
    cntl=cntr=0;
    l=r=0;
    for(i=0;i<num;i++){
        if(exp[i]=='(') cntl++;
        else if(exp[i]==')') cntr++;
        if(cntl<cntr) return false;
        if(exp[i]==' '||exp[i]=='\n') continue;
        else if(exp[i]=='|'||exp[i]=='&'){
            l=i-1;
            r=i+1;
            while(exp[l]==' '){
                l--;
                if(l<0) return false;
            }
            while(exp[r]==' '){
                r++;
                if(r>=num) return false;
            }
            if(!IsParameter(exp[l])&&exp[l]!=')') return false;
            if(!IsParameter(exp[r])&&exp[r]!='~'&&exp[r]!='(') return false;
        }
        else if(exp[i]=='~'){
            r=i+1;
            while(exp[r]==' '){
                r++;
                if(r>=num) return false;
                if(!IsParameter(exp[r])&&exp[r]!='(') return false;
            }
        }
        else if(!IsParameter(exp[i])&&!IsOperator(exp[i])) return false;
    }
    return true;
}

//�жϲ�����߼����ʽ������
void Judgement(TNode *T,char *tar,int num){
    int i,j,val[30],cnt;
    bool T_flag=false,F_flag=false;
    cnt=(int)pow(2.0,(double)num);
    for(i=0;i<cnt;i++){
        for(j=0;j<num;j++){
            val[j]=(i>>j)%2;
            ValueAssign(T,tar[j],val[j]);
        }
        Operation(T);
        if(T->val) T_flag=true;
        else F_flag=true;
    }
    if(T_flag&&F_flag) printf("���ǿ�����ʽ\n");
    else if(T_flag) printf("��������ʽ\n");
    else printf("��������ʽ\n");
}

//��ӡע������
void printCautious(){
    int col_num=120,gap1=19,gap2=22,i;
    for(i=0;i<col_num;i++) printf("-");
    for(i=0;i<col_num;i++) printf("*");
    printf("*");
    for(i=0;i<gap1;i++) printf(" ");
    printf("(ע�⣺֧�ֵ������Ϊ&,|,~,=,����=Ϊ������;�������ִ�Сд,����������30������)");
    for(i=0;i<gap2;i++) printf(" ");
    printf("*");
    for(i=0;i<col_num;i++) printf("*");
    for(i=0;i<col_num;i++) printf("-");
}

int main(){
    int i,j,len,cnt,num;
    char s[101],parm[32];
    bool flag,toomuch;
    printCautious();//�����ʾ��
    printf("\n������Ҫ�б�����ĸ���:\n");
    scanf("%d%*c",&num); //������Ҫ������߼����ʽ�ĸ���
    while(num--){
        cnt=0;toomuch=false;
        printf("����Ҫ�б�����:\n");
        fgets(s,101,stdin); //���ж�����Ҫ�б���߼����ʽ
        memset(parm,0,sizeof(parm)); //��ʼ�������б�
        for(i=0;i<(int)strlen(s);i++){ //�жϱ����Ƿ��ڱ����б��У������ڣ����������б�ͬʱ�жϱ��������Ƿ����30��
            if((s[i]>='A'&&s[i]<='Z')||(s[i]>='a'&&s[i]<='z')){
                if(!cnt) parm[cnt++]=s[i];
                else{
                    flag=true; //flag���ڱ�ǵ�ǰ�����Ƿ���Բ����������
                    for(j=0;j<(int)strlen(parm);j++){
                        if(parm[j]==s[i]){
                            flag=false;
                            break;
                        }
                    }
                    if(flag&&cnt==maxparm){ //������������
                        toomuch=true;
                        break;
                    }
                    if(flag) parm[cnt++]=s[i];
                }
            }
        }
        if(toomuch){ //���ʽ�ڱ��������ϲ��Ϸ�
            printf("��������̫����\n");
            continue;
        }
        len=strlen(parm);
        TNode *T;
        IniTree(T); //��ʼ�������߼����ʽ��
        if(CreateTree(T,s)&&IsValid(s)) //�����ɹ����жϲ�������ʽ����
            Judgement(T,parm,len);
        else //�������ɹ���˵�����ʽ���Ϸ�
            printf("�벻Ҫ����ʽ��\n");
        DestroyTree(T); //���ٶ����߼����ʽ��
    }
    return 0;
}
