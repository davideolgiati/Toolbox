//  Copyright Davide Olgiati 2018

#include "Include/ui.h"

ui::ui(bool debug){
    Engine = new Interpreter(debug);
    if (!debug) {
        std::cout << "   _____         _ ___                        _"
        << "_______ ______ "
        << std::endl
        << "  |_   _|__  ___| | _ ) _____ __"
        << "     ____    /_  __/ // / __ \\"
        << std::endl
        << "    | |/ _ \\/ _ \\ | _ \\/ _ \\ \\ /"
        << "    /___/     / / / _  / /_/ / "
        << std::endl
        << "    |_|\\___/\\___/_|___/\\___/_\\_\\"
        << "             /_/ /_//_/\\____/ \n"
        << "                                  \n"
        << "\nver \e[7;32m 0.3.4.20180308.2139 - Kaio-ken \e[0m\n"
        << "realizzato da THO in C++14 07/12/2017 - 22/02/2018\n"
        << "run \e[7m:help\e[0m for more!\n\n";
    }
}
