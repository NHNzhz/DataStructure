#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "BasicNode.h"

struct LNode{
    Vertex *data;
    LNode *next;
};

struct Queue{
    LNode *Front,*Rear;
    int length;
};

void IniQueue(Queue &Q){
    Q.Front=Q.Rear=new LNode;
    Q.Front->next=NULL;
    Q.length=0;
}

void DestoryQueue(Queue &Q){
    LNode *p;
    while(Q.Front->next){
        p=Q.Front->next;
        Q.Front->next=Q.Front->next->next;
        delete p;
    }
    delete Q.Front;
    Q.Front=Q.Rear=NULL;
    Q.length=0;
}

bool QueueEmpty(Queue &Q){
    return Q.length==0;
}

void EnQueue(Queue &Q,Vertex *e){
    LNode *p=new LNode;
    p->data=e;
    p->next=NULL;
    Q.Rear->next=p;
    Q.Rear=p;
    Q.length++;
}

bool DeQueue(Queue &Q,Vertex* &e){
    if(QueueEmpty(Q)) return false;
    LNode *p=Q.Front->next;
    e=p->data;
    Q.Front->next=p->next;
    if(p==Q.Rear) Q.Rear=Q.Front;
    delete p;
    Q.length--;
    return true;
}

bool Front(Queue Q,Vertex* &e){
    if(QueueEmpty(Q)) return false;
    LNode *p=Q.Front->next;
    e=p->data;
    return true;
}

#endif // QUEUE_H_INCLUDED
