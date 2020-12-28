#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include "BasicNode.h"
#include "Stack.h"
#include <cstring>
#define maxsize 5000000

//初始化二叉逻辑表达式树
void IniTree(TNode* &T){
    T=NULL;
}

//销毁二叉逻辑表达式树
void DestroyTree(TNode *T){
    if(T){
        DestroyTree(T->lc);
        DestroyTree(T->rc);
        delete T;
    }
    T=NULL;
}

//判断是否为表达式（包括0,1）
bool IsParameter(char &c){
    return ((c>='A'&&c<='Z')||(c>='a'&&c<='z')||c=='0'||c=='1');
}

//判断是否为运算符
bool IsOperator(char &c){
    return (c=='|')||(c=='&')||(c=='~')||(c=='(')||(c==')')||(c=='\n');
}

//运算符优先级比较
int Compare(char t1,char t2){
    int res;
    switch(t2){
        case '|':
            if(t1=='(') res=1;
            else res=-1;
            break;
        case '&':
            if(t1=='&'||t1==')') res=-1;
            else res=1;
            break;
        case '(': res=1;break;
        case ')':
            if(t1=='(') res=0;
            else res=-1;
            break;
        case '\n': res=-1;
    }
    return res;
}

//根据表达式构建二叉逻辑表达式树
bool CreateTree(TNode* &root,char *exp){
    SqStack snode,soper;
    IniStack(snode,maxsize);IniStack(soper,maxsize);
    TNode *p,*q,*s;
    int cnt=0;
    char opera;
    while(!StackEmpty(soper)||exp[cnt]!='\n'){
        if(exp[cnt]==' ') cnt++;
        else if(IsParameter(exp[cnt])){
            p=new TNode;
            p->data=exp[cnt++];
            if(p->data=='1'||p->data=='0') p->val=p->data-'0';
            p->lc=p->rc=NULL;
            Push(snode,p);
        }
        else if(IsOperator(exp[cnt])){
            if(exp[cnt]=='~'){
                p=new TNode;
                q=new TNode;
                p->data=exp[cnt++];
                q->data=exp[cnt++];
                p->lc=q;p->rc=NULL;
                q->lc=q->rc=NULL;
                Push(snode,p);
            }
            if(StackEmpty(soper)&&cnt<(int)strlen(exp)-1){
                p=new TNode;
                p->data=exp[cnt++];
                p->lc=p->rc=NULL;
                Push(soper,p);
            }
            else if(Top(soper,p)){
                opera=p->data;
                switch(Compare(opera,exp[cnt])){
                case 1:
                    p=new TNode;
                    p->data=exp[cnt++];
                    p->lc=p->rc=NULL;
                    Push(soper,p);
                    break;
                case 0:
                    Pop(soper,s);
                    delete s;
                    cnt++;
                    break;
                case -1:
                    Pop(soper,s);
                    if(StackEmpty(snode)) return false;
                    Pop(snode,p);
                    if(StackEmpty(snode)) return false;
                    Pop(snode,q);
                    s->lc=p;s->rc=q;
                    Push(snode,s);
                }
            }
        }
        else return false;
    }
    if(Pop(snode,root)&&StackEmpty(snode)){
        DestroyStack(snode);
        DestroyStack(soper);
        return true;
    }
    else{
        while(StackEmpty(snode)){
            delete root;
            Pop(snode,root);
        }
        delete root;
        DestroyStack(snode);
        DestroyStack(soper);
        root=NULL;
        return false;
    }
}

//将数据域与tar值相等的结点的赋值域赋为val
void ValueAssign(TNode *T,char tar,int val){
    if(T){
        if(T->data==tar) T->val=val;
        else if(T->data=='1') T->val=1;
        else if(T->data=='0') T->val=0;
        ValueAssign(T->lc,tar,val);
        ValueAssign(T->rc,tar,val);
    }
}

//令二叉树中所有结点的赋值域均被赋值，且根结点的赋值域即为当前赋值下表达式的值
void Operation(TNode* &T){
    if(T){
        Operation(T->lc);
        Operation(T->rc);
        if(T->data=='&') T->val=T->lc->val&T->rc->val;
        else if(T->data=='|') T->val=T->lc->val|T->rc->val;
        else if(T->data=='~') T->val=!T->lc->val;
    }
}

#endif // TREE_H_INCLUDED
