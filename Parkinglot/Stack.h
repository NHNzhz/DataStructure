#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "Car.h"

struct SqStack{
    Car *base;
    int top,ssize;
};

void IniStack(SqStack &S,int siz){
    S.top=0;S.base=new Car[siz];S.ssize=siz;
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

void Push(SqStack &S,Car e){
    S.base[S.top++]=e;
}

void Pop(SqStack &S,Car &e){
    e=S.base[--S.top];
}

int CarSearch_S(SqStack S,string code){
    int i;
    for(i=0;i<S.top;i++){
        if(S.base[i].code==code) return i+1;
    }
    return 0;
}

#endif // STACK_H_INCLUDED
