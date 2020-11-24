#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include "BasicNode.h"
#include "Stack.h"
#include <cstring>
#define maxsize 100

void IniTree(TNode *T){
    T=NULL;
}

void DestroyTree(TNode *T){
    if(T){
        DestroyTree(T->lc);
        DestroyTree(T->rc);
        delete T;
    }
    T=NULL;
}

bool IsParameter(char &c){
    return ((c>='A'&&c<='Z')||(c>='a'&&c<='z')||c=='0'||c=='1');
}

bool IsOperator(char &c){
    return (c=='|')||(c=='&')||(c=='~')||(c=='(')||(c==')')||(c=='\n');
}

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
            if(StackEmpty(soper)&&cnt<strlen(exp)-1){
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
    if(Pop(snode,root)&&StackEmpty(snode)) return true;
    else return false;
}

void ValueAssign(TNode *T,char tar,int val){
    if(T){
        if(T->data==tar) T->val=val;
        else if(T->data=='1') T->val=1;
        else if(T->data=='0') T->val=0;
        ValueAssign(T->lc,tar,val);
        ValueAssign(T->rc,tar,val);
    }
}

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
