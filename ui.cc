//  Copyright Davide Olgiati 2018

#include "Include/ui.h"

UI::UI(bool debug){
    Engine = new Interpreter(debug);
    if (!debug) {
        std::cout << "   _____         _ ___ \n"
                  << "  |_   _|__  ___| | _ ) _____ __\n"
                  << "    | |/ _ \\/ _ \\ | _ \\/ _ \\ \\ /\n"
                  << "    |_|\\___/\\___/_|___/\\___/_\\_\\\n\n"
                  << "\nver \e[7;32m 0.3.4.20180308.2139 - Kaio-ken \e[0m\n"
                  << "realizzato da THO in C++14 07/12/2017 - 22/02/2018\n"
                  << "run \e[7m:help\e[0m for more!\n\n";
        stay = true;
    }
}

void UI::Input(){
    bool res = true;
    std::string str = "";
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::fflush(stdin);
    std::cout << ((res) ? ("[\e[32mT\e[0m] >> ") : ("[\e[31mT\e[0m] >> "));
    std::getline(std::cin, str);
    if (str == ":exit"){
        stay = false;
    } else {
        res = Engine->parse(str);
        std::cout << ((res) ? ("\n" + str + " = " + Engine->getRet()) :
                      (Engine->getRet())) << std::endl << std::endl;
    }
}

bool UI::getState(){
    return stay;
}

void UI::debug() {
    runTests();
}

UI::~UI() {
    delete Engine;
}
