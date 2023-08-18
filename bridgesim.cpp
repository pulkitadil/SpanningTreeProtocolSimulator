#include "bridgesim.h"
using namespace std;

void Bridgesim::print_msg(msg m) {
    cout<<m.t<< " " <<m.c<< " B" <<m.Bk<< " (B" <<m.Bi<< ", "<<m.d<< ", B"<<m.Bj<<")"<<endl;
}

void Bridgesim::simulation(){
    int t=0;
    bool isChanged=true; //to stop a simulation

    while(isChanged){

        vector<msg> sent_msgs; // stores messages which are sent
        vector<msg> recd_msgs;// stores messages which are recd
        isChanged=false; // changing to false by default; if any change happens, it will be set to true again

        for(auto it=bridgemap.begin(); it!= bridgemap.end(); it++){

            Bridge currBridge= it->second;
            vector<string> currPortsvec = currBridge.ports;

            for (int i=0; i<currPortsvec.size(); i++){
                string currPort = currPortsvec[i];
                if(currBridge.port_status[currPort]=="DP")//msgs are sent through DP and the msgs which are recd are hence sent through DP of neighboring bridges
                {
                    //sending messages
                    msg msg_to_be_sent=msg(t, 's' , currBridge.bridge_id, currBridge.root_brige_id, currBridge.dis_to_root, currBridge.bridge_id, currPortsvec[i]);
                    //Bk= currBridgeId as event is happening on the curr bridge
                    sent_msgs.push_back(msg_to_be_sent);

                    //receiving messages
                    for(int j=0; j< bridgesConnToLAN[currPort].size(); j++){
                        int dest_bridge_id= stoi(bridgesConnToLAN[currPort][j].substr(1));
                        if(dest_bridge_id!=currBridge.bridge_id){
                            msg msg_to_be_recd=msg(t+1, 'r' , dest_bridge_id , currBridge.root_brige_id, currBridge.dis_to_root, currBridge.bridge_id, currPortsvec[i]);
                            recd_msgs.push_back(msg_to_be_recd);
                        }
                    }
                }
            }
        }


        for(int i=0; i<recd_msgs.size(); i++){
               msg currmsg=recd_msgs[i];
               int msg_dest_id=currmsg.Bk;
               string dest_bridge_str= "B" + to_string(msg_dest_id);
               Bridge* dest_bridge = &(this->bridgemap[dest_bridge_str]);
               bool isChanged1= dest_bridge->better_msg_received(currmsg);
               //cout<<isChanged1<<" "<<isChanged<<endl;
               isChanged = isChanged | isChanged1;
               //taking OR to take into account if any change happened in prev for iterations
        }
        //cout<<"IS" << isChanged<<endl;

        if(trace==1) { //To print the msgs

            for(int i=0; i<sent_msgs.size(); i++){
                print_msg(sent_msgs[i]);
            }

            for(int i=0; i<recd_msgs.size(); i++){
                print_msg(recd_msgs[i]);
            }
        }
    t++;
    } //end while
} //end simulation

void Bridgesim::print_status(){
    vector<int> ids;
    for(auto it=bridgemap.begin(); it!=bridgemap.end(); it++){
        ids.push_back(stoi(it->first.substr(1)));
    }

    // To print the bridges in increasing order of their id
    sort (ids.begin(), ids.end());
    vector <string> bridges;
    for(auto x: ids) {
        bridges.push_back("B" + to_string(x));
    }

    for (auto it: bridges){
        bridgemap[it].show_port_status();
        cout<<endl;
    }
}

