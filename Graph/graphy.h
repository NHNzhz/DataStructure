#ifndef GRAPHY_H_INCLUDED
#define GRAPHY_H_INCLUDED
#define max_vexnum 30
#include <cstring>
#include <cstdio>
#include "BasicNode.h"
#include "Stack.h"
#include "Queue.h"

struct Graph{
    Vertex *vet;
    int vexnum,edgnum;
};

void IniGraph(Graph &G){
    G.vet=new Vertex[max_vexnum];
    G.vexnum=G.edgnum=0;
}

int findVex(Graph G,char *code){
    int i;
    for(i=0;i<G.vexnum;i++){
        if(!strcmp(code,G.vet[i].code)) return i;
    }
    return -1;
}

int Convert(char *num){
    int i,len=strlen(num),sum=0;
    for(i=0;i<len;i++){
        sum=sum*10+(num[i]-'0');
    }
    return sum;
}

void TopoSortAve(Graph &G,int semelimit,int gradlimit,int avegrad){
    int i,j,curgrad;
    Queue S;
    Vertex *p;
    Edge *q;
    IniQueue(S);
    for(i=0;i<G.vexnum;i++){
        if(!G.vet[i].indegree){
            G.vet[i].indegree--;
            EnQueue(S,&G.vet[i]);
        }
    }
    for(i=0;i<semelimit;i++){
        curgrad=0;
        printf("��%dѧ��:",i+1);
        while(!QueueEmpty(S)&&curgrad<avegrad){
            Front(S,p);
            if(curgrad+p->grade>gradlimit) break;
            DeQueue(S,p);
            curgrad+=p->grade;
            q=p->firstout;
            while(q){
                G.vet[q->posh].indegree--;
                q=q->edgt;
            }
            printf(" %s",p->code);
        }
        printf("\n");
        for(j=0;j<G.vexnum;j++){
            if(!G.vet[j].indegree){
                G.vet[j].indegree--;
                EnQueue(S,&G.vet[j]);
            }
        }
    }
    if(!QueueEmpty(S)) printf("���Ѿ���������,���п�û��������γ��߼�������~~\n");
}

void TopoSortHea(Graph &G,int semelimit,int gradlimit){
    int i,j,curgrad;
    Queue S;
    Vertex *p;
    Edge *q;
    IniQueue(S);
    for(i=0;i<G.vexnum;i++){
        if(!G.vet[i].indegree){
            G.vet[i].indegree--;
            EnQueue(S,&G.vet[i]);
        }
    }
    for(i=0;i<semelimit;i++){
        curgrad=0;
        printf("��%dѧ��:",i+1);
        while(!QueueEmpty(S)){
            Front(S,p);
            if(curgrad+p->grade>gradlimit) break;
            DeQueue(S,p);
            curgrad+=p->grade;
            q=p->firstout;
            while(q){
                G.vet[q->posh].indegree--;
                q=q->edgt;
            }
            printf(" %s",p->code);
        }
        printf("\n");
        for(j=0;j<G.vexnum;j++){
            if(!G.vet[j].indegree){
                G.vet[j].indegree--;
                EnQueue(S,&G.vet[j]);
            }
        }
    }
    if(!QueueEmpty(S)) printf("���Ѿ���������,���п�û��������γ��߼�������~~\n");
}

void SolveGraph(Graph &G){
    char line[100],temp[2],res[30],choice[101];
    int i,pos,flag,mainpos,semipos,curgrad,totgrad,semelimit,gradlimit,cournum;
    Edge *p;
    totgrad=0;
    printf("������ѧ������:\n");
    scanf("%d%*c",&semelimit);
    printf("������һѧ�ڵ�ѧ������:\n");
    scanf("%d%*c",&gradlimit);
    printf("������γ�����:\n");
    scanf("%d%*c",&cournum);
    printf("������γ���š�ѧ���Լ����޿γ����:\n");
    for(i=0;i<cournum;i++){
        fgets(line,100,stdin);
        pos=0;flag=-1;strcpy(res,"");
        while(line[pos]!='\0'){
            while(line[pos]==' ') pos++;
            temp[0]=line[pos];temp[1]='\0';
            strcat(res,temp);
            pos++;
            if((line[pos]==' '||line[pos]=='\n')&&strcmp(res,"")){
                if(flag==-1){
                    if(findVex(G,res)==-1){
                        strcpy(G.vet[G.vexnum].code,res);
                        G.vet[G.vexnum].firstin=G.vet[G.vexnum].firstout=NULL;
                        G.vet[G.vexnum].indegree=0;
                        mainpos=G.vexnum++;
                    }
                    else mainpos=findVex(G,res);
                    flag++;
                }
                else if(!flag){
                    if((curgrad=Convert(res))>gradlimit){
                        printf("ѧ�ֳ���ѽ����,��Ҳû������\n");
                        return ;
                    }
                    G.vet[mainpos].grade=curgrad;
                    totgrad+=curgrad;
                    flag++;
                }
                else{
                    if(findVex(G,res)==-1){
                        strcpy(G.vet[G.vexnum].code,res);
                        G.vet[G.vexnum].firstin=G.vet[G.vexnum].firstout=NULL;
                        G.vet[G.vexnum].indegree=0;
                        semipos=G.vexnum++;
                    }
                    else semipos=findVex(G,res);
                    G.vet[mainpos].indegree++;
                    p=new Edge({mainpos,semipos,NULL,NULL});
                    p->edgt=G.vet[semipos].firstout;
                    G.vet[semipos].firstout=p;
                    p->edgh=G.vet[mainpos].firstin;
                    G.vet[mainpos].firstin=p;
                    G.edgnum++;
                }
                strcpy(res,"");
            }
        }
    }
    if(totgrad>gradlimit*semelimit){
        printf("ѧ�ֳ���ѽ����,��Ҳû������\n");
        return ;
    }
    printf("��ѡ����Ҫ���ſη�ʽ,0Ϊѡ�񸺵���������,1Ϊѡ�񾡿��ܼ�����ǰ��ѧ��:\n");
    while(scanf("%s",choice)!=EOF){
        if(strcmp(choice,"0")&&strcmp(choice,"1")){
            printf("�鷳�������£���˵��ֻ��ѡ0��1��~~,����һ�ΰ�\n");
            continue;
        }
        else if(!strcmp(choice,"0")){
            TopoSortAve(G,semelimit,gradlimit,totgrad/semelimit);
            return ;
        }
        else{
            TopoSortHea(G,semelimit,gradlimit);
            return ;
        }
    }
}

#endif // GRAPHY_H_INCLUDED
