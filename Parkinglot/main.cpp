#include "Queue.h"
#include "Stack.h"
#include <cstdio>
#include <iostream>
#include <string>
Queue Q;
SqStack S;
int price,vol;
void terminal(int tag,string code,int tim){
    if(!tag){//此处令tag==0时为车辆到达
        if(!StackFull(S)){
            Push(S,{tim,code});//车在停车场里停
            cout<<"车牌号为"<<code<<"的汽车进入了停车场第"<<CarSearch_S(S,code)<<"号位"<<endl;
        }
        else{
            EnQueue(Q,{tim,code});//车在便道里停
            cout<<"车牌号为"<<code<<"的汽车进入了便道第"<<CarSearch_Q(Q,code)<<"号位"<<endl;
        }
    }
    else if(tag==1){//此处令tag==1时为停在停车场里离去
        int pos;
        Car temp;
        if(CarSearch_S(S,code)){
            pos=CarSearch_S(S,code);
            if(tim<S.base[pos-1].tim) cout<<"时间不对劲"<<endl;
            else{
                SqStack temp_S;
                IniStack(temp_S,vol);
                pos--;
                while(pos--){
                    Pop(S,temp);
                    Push(temp_S,temp);
                }
                Pop(S,temp);
                cout<<"车牌号为"<<temp.code<<"的汽车离开停车场,收费"<<price*(tim-temp.tim)<<"元"<<endl;
                while(!StackEmpty(temp_S)){
                    Pop(temp_S,temp);
                    Push(S,temp);
                }
                if(!QueueEmpty(Q)){
                    DeQueue(Q,temp);
                    Push(S,temp);
                }
            }
        }
        else if(CarSearch_Q(Q,code)){
            pos=CarSearch_Q(Q,code);
            Queue temp_Q;
            IniQueue(temp_Q);
            pos--;
            while(pos--){
                DeQueue(Q,temp);
                EnQueue(temp_Q,temp);
            }
            DeQueue(Q,temp);
            while(!QueueEmpty(Q)){
                DeQueue(Q,temp);
                EnQueue(temp_Q,temp);
            }
            DestoryQueue(Q);
            Q=temp_Q;
            cout<<"由于是在便道开走的,车牌号为"<<code<<"的车无需收费"<<endl;
        }
        else{
            cout<<"你不对劲，别乱输车牌"<<endl;
        }
    }
    else cout<<"你不对劲，别乱输tag"<<endl;//定义其他tag不接受
}
int main(){
    int num,tag,tim;
    string code;
    cout<<"请输入停车场的容量:";
    cin>>vol;
    IniQueue(Q);
    IniStack(S,vol);
    cout<<"请输入每小时的收费额:";
    cin>>price;
    cout<<"请输入待处理的终端数据条数:";
    cin>>num;
    while(num--){
        cout<<"请输入符合要求的数据序tag,车牌号,时间(tag为0或1,车牌号为字符串,时间为整数,单位为小时):"<<endl;
        cin>>tag>>code>>tim;
        terminal(tag,code,tim);
    }
    return 0;
}
