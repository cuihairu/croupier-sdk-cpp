#include <iostream>
#include "croupier/sdk/croupier_client.h"

int main(){
    croupier::sdk::CroupierClient cli{"127.0.0.1:19090"};
    cli.connect();
    std::cout << "Croupier SDK C++ skeleton, agent=" << cli.agent_addr() << "\n";
    return 0;
}

