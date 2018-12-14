#include "../header/base.h"
#include "../header/Or_Connector.h"

bool Or_Connector::execute(){
    if(!left-> execute()){
        if(right-> execute()){
            return true;
        }
        else{
            return false;
        }
    }
    return true;
}