#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "BasicNode.h"

struct SqStack{
    Vertex **base;
    int top,ssize;
};

void IniStack(SqStack &S,int siz){
    S.top=0;S.base=new Vertex*[siz];S.ssize=siz;
}

void DestroyStack(SqStack &S){
    delete []S.base;
    S.ssize=S.top=0;
}

void ClearStack(SqStack &S){
    S.top=0;
}

bool StackEmpty(SqStack &S){
    return !S.top;
}

bool StackFull(SqStack &S){
    return S.top==S.ssize;
}

void Push(SqStack &S,Vertex* e){
    S.base[S.top++]=e;
}

bool Pop(SqStack &S,Vertex* &e){
    if(!StackEmpty(S)){
        e=S.base[--S.top];
        return true;
    }
    return false;
}

bool Top(SqStack S,Vertex* &e){
    if(!StackEmpty(S)){
        e=S.base[S.top-1];
        return true;
    }
    return false;
}

#endif // STACK_H_INCLUDED
