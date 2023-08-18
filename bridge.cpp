#include "bridge.h"
using namespace std;

Bridge::Bridge(){};

void Bridge::leaf_node_check(){
    int nDP=0;
    int nNP=0;
    int nRP=0;
    string RP_key;
    for(auto it=port_status.begin(); it!=port_status.end(); it++){
            if(it->second=="DP") nDP++;
            if(it->second=="NP") nNP++;
            if(it->second=="RP") {
                    nRP++;
                    RP_key= it->first;//as such may not required as the RP is stored in root_port already
            }
        }
    if(nDP==0 && nRP!=0) {
        port_status[RP_key]="NP";
        root_port="-1"; //there exists no root port
    }
}

bool Bridge::better_msg_received(msg m){
    bool isChanged=false;


    //Rule 1,2,3

    {
        if ((m.Bi< root_brige_id)|| (m.Bi==root_brige_id && m.d+1<dis_to_root)||(m.Bi==root_brige_id && m.d+1==dis_to_root && m.Bj<sending_bridge_id))

        {

            for(auto it=port_status.begin(); it!=port_status.end(); it++){
                it->second="DP"; //Changing all ports to DP as the root bridge has changed
            }
            root_brige_id=m.Bi;
            dis_to_root=m.d+1; //the distance to root gets added by 1
            isRoot=false;
            sending_bridge_id=m.Bj;
            root_port=m.port; //the root port is set to the port on which the message is recd
            port_status[m.port]="RP";
            leaf_node_check();
            isChanged=true;
            //return isChanged;
    }
    //Rule 5
    else if(m.Bi==root_brige_id && port_status[m.port]!="RP" && port_status[m.port]!="NP"&& (m.d<dis_to_root || (m.d==dis_to_root && m.Bj<bridge_id)))
    {   //only DP is changed to NP

        port_status[m.port]= "NP";
        leaf_node_check();
        isChanged=true;
        //return isChanged;
    }

    else{
        leaf_node_check();
        isChanged=false;
        //return isChanged;
    }
    }

    return isChanged;

}

void Bridge::show_port_status(){
    cout<<"B"<<bridge_id<<": ";
    for(auto it=port_status.begin(); it!=port_status.end(); it++){
        cout<<it->first<<"-"<<it->second<<" ";
    }
}

