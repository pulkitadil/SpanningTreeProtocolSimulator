#include <vector>
#include<iostream>
#include <bits/stdc++.h>
#include <map>
using namespace std;

struct msg{

    int Bi; // the root bridge the sender thinks
    int Bj; // the sender bridge
    int Bk; //receiving bridge
    int d; //distance to root bridge as thought by Bj
    char c; //sent/received
    int t; //time at which msg is received
    string port; //port on which sent/recd

    //msg();

    msg(int t, char c, int Bk, int Bi, int d, int Bj, string port){

        this->t=t;
        this->c=c;
        this->Bk=Bk;
        this->Bi=Bi;
        this->d=d;
        this->Bj=Bj;
        this->port=port;

    }

};

struct Bridge{

    int bridge_id; //Trim the B from bridge id
    vector<string> ports; //A,B,C,D.... strings cannot be compared directly...but ports[0] will be a char and can be compared directly
    map <string, string> port_status;
    int root_brige_id; //root bridge according to the current bridge
    int dis_to_root;
    int sending_bridge_id;
    bool isRoot;
    string root_port;// the current root port...may not be reqd

    Bridge();//dummy constructor

    Bridge(string bridge, vector<string> ports){
        bridge_id= stoi(bridge.substr(1)); //trimming the B from B_i //stoi => string to int // substr(1) -> 1st index to end of string
        this->ports=ports;
        root_brige_id=bridge_id;
        dis_to_root=0;
        sending_bridge_id=-1; //No bridge has yet sent the message
        isRoot=true; //bridge thinks itself as the root
        root_port="-1"; //No RP exists

        for(int i=0; i<ports.size(); i++){
            port_status[ports[i]] = "DP"; //initially all the ports are thought of as DP
        }

    }

    bool better_msg_received(msg m);
    void leaf_node_check();
    void show_port_status();
};


