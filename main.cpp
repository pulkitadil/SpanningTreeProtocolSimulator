#include <iostream>
#include "bridgesim.h"
#include <bits/stdc++.h>
#include <vector>
#include <map>
#include <string>

using namespace std;

int main()
{

    int trace, no_of_bridges;
    cin>> trace>> no_of_bridges;
    map <string, vector<string>> portsConnToBridge; // The LANS to which a bridge is connected
    map <string, vector<string>> bridgesConnToLAN; // the bridges to which a LAN is connected

    for (int i=0; i < no_of_bridges; i++){
        string bridge_config;
        getline(cin>>ws, bridge_config);
        int pos;
        pos=bridge_config.find(":");
        string temp_bridge;
        temp_bridge=bridge_config.substr(0,pos);//It excludes the ":" and takes Bxxx
        string temp_ports= bridge_config.substr(pos+2);
        //cout<<bridge_config<<endl;
        for (auto j=0; j<temp_ports.size(); j+=2){
            portsConnToBridge[temp_bridge].push_back(temp_ports.substr(j,1));
            bridgesConnToLAN[temp_ports.substr(j,1)].push_back(temp_bridge);

        }

        //cout<<portsConnToBridge[temp_bridge][0]<<'\n'<<portsConnToBridge[temp_bridge][1]<<endl;
        //cout<<bridgesConnToLAN[temp_ports.substr(0,1)][0]<<endl;

    }
    //cout<<portsConnToBridge.begin()->first<<endl;



    Bridgesim sim(portsConnToBridge,bridgesConnToLAN,trace);
    sim.simulation();
    sim.print_status();

}
