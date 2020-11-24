#include <cstdio>
#include <cstring>
#include <cmath>
#include "tree.h"
#define maxparm 20
using namespace std;
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
    if(T_flag&&F_flag) printf("这是可满足式\n");
    else if(T_flag) printf("这是永真式\n");
    else printf("这是永假式\n");
}
int main(){
    int i,j,len,cnt,num;
    char s[101],parm[31];
    bool flag,toomuch;
    printf("(注意：支持的运算符为&,|,~,=,其中=为结束符;变量区分大小写,个数限制在30个以内)\n请输入要判别的语句的个数:\n");
    scanf("%d%*c",&num);
    while(num--){
        cnt=0;toomuch=false;
        printf("输入要判别的语句:\n");
        fgets(s,101,stdin);
        memset(parm,0,sizeof(parm));
        for(i=0;i<strlen(s);i++){
            if((s[i]>='A'&&s[i]<='Z')||(s[i]>='a'&&s[i]<='z')){
                if(!cnt) parm[cnt++]=s[i];
                else{
                    flag=true;
                    for(j=0;j<strlen(parm);j++){
                        if(parm[j]==s[i]){
                            flag=false;
                            break;
                        }
                    }
                    if(flag&&cnt==30){
                        toomuch=true;
                        break;
                    }
                    if(flag) parm[cnt++]=s[i];
                }
            }
        }
        if(toomuch){
            printf("变量个数太多啦\n");
            continue;
        }
        len=strlen(parm);
        TNode *T;
        IniTree(T);
        if(CreateTree(T,s)&&IsValid(s)) Judgement(T,parm,len);
        else printf("请不要乱输式子\n");
        DestroyTree(T);
    }
    return 0;
}
