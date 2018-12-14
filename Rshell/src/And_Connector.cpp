#include "../header/base.h"
#include "../header/And_Connector.h"

bool And_Connector::execute(){
    if(left-> execute()){
        if(right->execute()){
            return true;
        }
        else{
            return false;
        }
        
    }
    return false;
}
