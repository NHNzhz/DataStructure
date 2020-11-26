#ifndef BASICNODE_H_INCLUDED
#define BASICNODE_H_INCLUDED

struct Edge{
    int posh,post;
    Edge *edgh,*edgt;
};

struct Vertex{
    char code[30];
    int grade,indegree;
    Edge *firstin,*firstout;
};

#endif // BASICNODE_H_INCLUDED
