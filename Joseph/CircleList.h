#ifndef CIRCLELIST_H_INCLUDED
#define CIRCLELIST_H_INCLUDED

struct LNode{
    int data,num;
    LNode *prior,*next;
};

struct CircleList{
    LNode *head,*tail;
    int len;
};

void IniList(CircleList &L){
    L.head=L.tail=NULL;
    L.len=0;
}

bool ListEmpty(CircleList &L){
    return !L.head;
}

void ClearList(CircleList &L){
    if(L.head){
        LNode *p,*q;
        p=L.head;
        while(p!=L.tail){
            q=p->next;
            delete p;
            p=q;
        }
        delete L.tail;
        L.head=L.tail=NULL;
        L.len=0;
    }
}

void ListAppend(CircleList &L,int da,int nu){
    LNode *p=new LNode;
    p->data=da;p->num=nu;
    if(!L.head){
        L.head=L.tail=p;
    }
    else{
        L.tail->next=p;
        p->prior=L.tail;
        L.tail=p;
    }
    L.tail->next=L.head;
    L.head->prior=L.tail;
    L.len++;
}

LNode *ListDeleteSeq(CircleList &L,LNode *pos,int tar,int &da,int &nu){
    LNode *p,*nex;
    if(tar<1||!L.head) return NULL;
    else if(L.len==1){
        da=pos->data;nu=pos->num;
        delete pos;
        L.head=L.tail=NULL;
        L.len=0;
        nex=NULL;
    }
    else{
        p=pos;
        int cnt=1;
        while(cnt!=tar){
            p=p->next;
            cnt++;
        }
        p->next->prior=p->prior;
        p->prior->next=p->next;
        da=p->data;nu=p->num;
        nex=p->next;
        delete p;
        L.len--;
    }
    return nex;
}

LNode *ListDeleteDeq(CircleList &L,LNode *pos,int tar,int &da,int &nu){
    LNode *p,*pre;
    if(tar<1||!L.head) return NULL;
    else if(L.len==1){
        da=pos->data;nu=pos->num;
        delete pos;
        L.head=L.tail=NULL;
        L.len=0;
        pre=NULL;
    }
    else{
        p=pos;
        int cnt=1;
        while(cnt!=tar){
            p=p->prior;
            cnt++;
        }
        p->next->prior=p->prior;
        p->prior->next=p->next;
        da=p->data;nu=p->num;
        pre=p->next;
        delete p;
        L.len--;
    }
    return pre;
}

void ListTraverse(CircleList &L){
    LNode *p=L.head;
    if(p){
        while(p!=L.tail){
            printf("Î»ÖÃ£º%d ÃÜÂë£º%d\n",p->num,p->data);
            p=p->next;
        }
        printf("Î»ÖÃ£º%d ÃÜÂë£º%d\n",p->num,p->data);
    }
}

#endif // CIRCLELIST_H_INCLUDED
