#include "bridge.h"
using namespace std;

struct Bridgesim{

    map <string, vector<string>> portsConnToBridge; // The LANS to which a bridge is connected
    map <string, vector<string>> bridgesConnToLAN; // the bridges to which a LAN is connected
    map <string, Bridge> bridgemap;//maps a bridge to the corresponding Bridge class
    int trace;

    Bridgesim(map <string, vector<string>> portsConnToBridge, // The LANS to which a bridge is connected
    map <string, vector<string>> bridgesConnToLAN, // the bridges to which a LAN is connected
    int trace){
        this->portsConnToBridge=portsConnToBridge;
        this->bridgesConnToLAN=bridgesConnToLAN;
        this->trace=trace;

        for(auto it=portsConnToBridge.begin(); it!=portsConnToBridge.end(); it++){
            this->bridgemap[it->first]= Bridge(it->first, it->second);
        }

    }

    void simulation();
    void print_msg(msg m);
    void print_status();

};
