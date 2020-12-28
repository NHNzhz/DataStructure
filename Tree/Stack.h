#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "BasicNode.h"

//˳��ջ�ṹ����
struct SqStack{
    TNode **base;
    int top,ssize; //ջ����ջ������
};

//��ʼ��ջ
void IniStack(SqStack &S,int siz){
    S.top=0;S.base=new TNode*[siz];S.ssize=siz;
}

//����ջ
void DestroyStack(SqStack &S){
    delete []S.base;
    S.ssize=S.top=0;
}

//���ջ
void ClearStack(SqStack &S){
    S.top=0;
}

//�ж�ջ�Ƿ�Ϊ��ջ
bool StackEmpty(SqStack &S){
    return !S.top;
}

//�ж�ջ�Ƿ�����
bool StackFull(SqStack &S){
    return S.top==S.ssize;
}

//��eѹ��ջ��
void Push(SqStack &S,TNode* e){
    S.base[S.top++]=e;
}

//��ջ��Ԫ�س�ջ������e����
bool Pop(SqStack &S,TNode* &e){
    if(!StackEmpty(S)){
        e=S.base[--S.top];
        return true;
    }
    return false;
}

//��e����ջ��Ԫ��
bool Top(SqStack S,TNode* &e){
    if(!StackEmpty(S)){
        e=S.base[S.top-1];
        return true;
    }
    return false;
}

#endif // STACK_H_INCLUDED
