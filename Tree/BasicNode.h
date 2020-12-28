#ifndef BASICNODE_H_INCLUDED
#define BASICNODE_H_INCLUDED

//二叉逻辑表达式树基本节点定义
struct TNode{
    char data; //数据域
    int val; //赋值域
    TNode *lc,*rc; //指向左右子节点的指针
};

#endif // BASICNODE_H_INCLUDED
