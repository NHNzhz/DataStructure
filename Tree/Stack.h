#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "BasicNode.h"

//顺序栈结构定义
struct SqStack{
    TNode **base;
    int top,ssize; //栈顶和栈的容量
};

//初始化栈
void IniStack(SqStack &S,int siz){
    S.top=0;S.base=new TNode*[siz];S.ssize=siz;
}

//销毁栈
void DestroyStack(SqStack &S){
    delete []S.base;
    S.ssize=S.top=0;
}

//清空栈
void ClearStack(SqStack &S){
    S.top=0;
}

//判断栈是否为空栈
bool StackEmpty(SqStack &S){
    return !S.top;
}

//判断栈是否已满
bool StackFull(SqStack &S){
    return S.top==S.ssize;
}

//将e压入栈中
void Push(SqStack &S,TNode* e){
    S.base[S.top++]=e;
}

//将栈顶元素出栈，并用e保存
bool Pop(SqStack &S,TNode* &e){
    if(!StackEmpty(S)){
        e=S.base[--S.top];
        return true;
    }
    return false;
}

//用e保存栈顶元素
bool Top(SqStack S,TNode* &e){
    if(!StackEmpty(S)){
        e=S.base[S.top-1];
        return true;
    }
    return false;
}

#endif // STACK_H_INCLUDED
