#include <cstdio>
#include <cstring>
#include <cmath>
#include "tree.h"
#define maxparm 30
using namespace std;
//判断输入的逻辑表达式是否含不合法字符
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

//判断并输出逻辑表达式的类型
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

//打印注意事项
void printCautious(){
    int col_num=120,gap1=19,gap2=22,i;
    for(i=0;i<col_num;i++) printf("-");
    for(i=0;i<col_num;i++) printf("*");
    printf("*");
    for(i=0;i<gap1;i++) printf(" ");
    printf("(注意：支持的运算符为&,|,~,=,其中=为结束符;变量区分大小写,个数限制在30个以内)");
    for(i=0;i<gap2;i++) printf(" ");
    printf("*");
    for(i=0;i<col_num;i++) printf("*");
    for(i=0;i<col_num;i++) printf("-");
}

int main(){
    int i,j,len,cnt,num;
    char s[101],parm[32];
    bool flag,toomuch;
    printCautious();//输出提示语
    printf("\n请输入要判别的语句的个数:\n");
    scanf("%d%*c",&num); //输入需要处理的逻辑表达式的个数
    while(num--){
        cnt=0;toomuch=false;
        printf("输入要判别的语句:\n");
        fgets(s,101,stdin); //按行读入需要判别的逻辑表达式
        memset(parm,0,sizeof(parm)); //初始化变量列表
        for(i=0;i<(int)strlen(s);i++){ //判断变量是否在变量列表中，若不在，则插入变量列表，同时判断变量总数是否大于30个
            if((s[i]>='A'&&s[i]<='Z')||(s[i]>='a'&&s[i]<='z')){
                if(!cnt) parm[cnt++]=s[i];
                else{
                    flag=true; //flag用于标记当前变量是否可以插入变量表中
                    for(j=0;j<(int)strlen(parm);j++){
                        if(parm[j]==s[i]){
                            flag=false;
                            break;
                        }
                    }
                    if(flag&&cnt==maxparm){ //变量个数过多
                        toomuch=true;
                        break;
                    }
                    if(flag) parm[cnt++]=s[i];
                }
            }
        }
        if(toomuch){ //表达式在变量个数上不合法
            printf("变量个数太多啦\n");
            continue;
        }
        len=strlen(parm);
        TNode *T;
        IniTree(T); //初始化二叉逻辑表达式树
        if(CreateTree(T,s)&&IsValid(s)) //建树成功，判断并输出表达式类型
            Judgement(T,parm,len);
        else //建树不成功，说明表达式不合法
            printf("请不要乱输式子\n");
        DestroyTree(T); //销毁二叉逻辑表达式树
    }
    return 0;
}
