#include "../header/base.h"
#include "../header/Semi_Connector.h"

bool Semi_Connector::execute(){
    left-> execute();	
    if(right-> execute()){
        return true;
    }
    return false;
}
