//#include <builtins.h>
#include"../calc.X/calc.h"


Calculator_t calc;
int main(){
    app_initialize();
    while(1)
    {
        calculator_mode(&calc);    
        infixToPostfix(&calc);
    }
    return EXIT_SUCCESS;
}
void app_initialize()
{
    ecu_layer_initialize(); 
    calc_init(&calc);
}

