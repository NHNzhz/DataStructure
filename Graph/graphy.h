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
        printf("第%d学期:",i+1);
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
    if(!QueueEmpty(S)) printf("我已经尽力排了,还有课没排上是你课程逻辑有问题~~\n");
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
        printf("第%d学期:",i+1);
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
    if(!QueueEmpty(S)) printf("我已经尽力排了,还有课没排上是你课程逻辑有问题~~\n");
}

void SolveGraph(Graph &G){
    char line[100],temp[2],res[30],choice[101];
    int i,pos,flag,mainpos,semipos,curgrad,totgrad,semelimit,gradlimit,cournum;
    Edge *p;
    totgrad=0;
    printf("请输入学期总数:\n");
    scanf("%d%*c",&semelimit);
    printf("请输入一学期的学分上限:\n");
    scanf("%d%*c",&gradlimit);
    printf("请输入课程总数:\n");
    scanf("%d%*c",&cournum);
    printf("请输入课程序号、学分以及先修课程序号:\n");
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
                        printf("学分超了呀朋友,我也没法安排\n");
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
        printf("学分超了呀朋友,我也没法安排\n");
        return ;
    }
    printf("请选择你要的排课方式,0为选择负担尽量均匀,1为选择尽可能集中于前几学期:\n");
    while(scanf("%s",choice)!=EOF){
        if(strcmp(choice,"0")&&strcmp(choice,"1")){
            printf("麻烦读个题呗，都说了只能选0和1了~~,再输一次吧\n");
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
