#include "Queue.h"
#include "Stack.h"
#include <cstdio>
#include <iostream>
#include <string>
Queue Q;
SqStack S;
int price,vol;
void terminal(int tag,string code,int tim){
    if(!tag){//�˴���tag==0ʱΪ��������
        if(!StackFull(S)){
            Push(S,{tim,code});//����ͣ������ͣ
            cout<<"���ƺ�Ϊ"<<code<<"������������ͣ������"<<CarSearch_S(S,code)<<"��λ"<<endl;
        }
        else{
            EnQueue(Q,{tim,code});//���ڱ����ͣ
            cout<<"���ƺ�Ϊ"<<code<<"�����������˱����"<<CarSearch_Q(Q,code)<<"��λ"<<endl;
        }
    }
    else if(tag==1){//�˴���tag==1ʱΪͣ��ͣ��������ȥ
        int pos;
        Car temp;
        if(CarSearch_S(S,code)){
            pos=CarSearch_S(S,code);
            if(tim<S.base[pos-1].tim) cout<<"ʱ�䲻�Ծ�"<<endl;
            else{
                SqStack temp_S;
                IniStack(temp_S,vol);
                pos--;
                while(pos--){
                    Pop(S,temp);
                    Push(temp_S,temp);
                }
                Pop(S,temp);
                cout<<"���ƺ�Ϊ"<<temp.code<<"�������뿪ͣ����,�շ�"<<price*(tim-temp.tim)<<"Ԫ"<<endl;
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
            cout<<"�������ڱ�����ߵ�,���ƺ�Ϊ"<<code<<"�ĳ������շ�"<<endl;
        }
        else{
            cout<<"�㲻�Ծ��������䳵��"<<endl;
        }
    }
    else cout<<"�㲻�Ծ���������tag"<<endl;//��������tag������
}
int main(){
    int num,tag,tim;
    string code;
    cout<<"������ͣ����������:";
    cin>>vol;
    IniQueue(Q);
    IniStack(S,vol);
    cout<<"������ÿСʱ���շѶ�:";
    cin>>price;
    cout<<"�������������ն���������:";
    cin>>num;
    while(num--){
        cout<<"���������Ҫ���������tag,���ƺ�,ʱ��(tagΪ0��1,���ƺ�Ϊ�ַ���,ʱ��Ϊ����,��λΪСʱ):"<<endl;
        cin>>tag>>code>>tim;
        terminal(tag,code,tim);
    }
    return 0;
}
