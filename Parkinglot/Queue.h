#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "Car.h"

struct LNode{
    Car ca;
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

void EnQueue(Queue &Q,Car e){
    LNode *p=new LNode;
    p->ca=e;
    p->next=NULL;
    Q.Rear->next=p;
    Q.Rear=p;
    Q.length++;
}

bool DeQueue(Queue &Q,Car &e){
    if(QueueEmpty(Q)) return false;
    LNode *p=Q.Front->next;
    e=p->ca;
    Q.Front->next=p->next;
    if(p==Q.Rear) Q.Rear=Q.Front;
    delete p;
    Q.length--;
    return true;
}

int CarSearch_Q(Queue Q,string code){
    LNode *p=Q.Front->next;
    int i=0;
    while(p){
        if(p->ca.code==code) return i+1;
        i++;
        p=p->next;
    }
    return 0;
}

#endif // QUEUE_H_INCLUDED
