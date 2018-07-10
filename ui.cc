//  Copyright Davide Olgiati 2018

#include "Include/ui.h"

UI::UI(bool debug){
    Engine = new Interpreter(debug);
    stay = populate(&Engine);
    if (!(debug && stay)) {
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
    
    if(!stay) {
        std::cout << "\e[1;7;31mERROR OCCURED WHILE POPULATING\e[0m"
                  << std::endl << std::endl;
    }
}

void UI::Input(){
    bool res = true;
    std::string str = "";
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::fflush(stdin);
    std::getline(std::cin, str);
    if (str == ":exit"){
        stay = false;
    } else {
        res = Engine.parse(str);
        std::cout << ((res) ? ("\n" + str + " = " + Engine.getRet()) :
                      (Engine.getRet())) << std::endl << std::endl;
        std::cout << ((res) ? ("[\e[32mT\e[0m] >> ") : ("[\e[31mT\e[0m] >> "));
    }
}

bool UI::getState(){
    return stay;
}

bool UI::populate(Interpreter* const I) {
    bool ret = true;
    
    ret &= I->add("Ciao",
                  ciao,
                  "scrive Ciao <arg>");
    ret &= I->add("ReverseStr",
                  ReverseStr,
                  "scrive <arg> al contrario");
    ret &= I->add("Length",
                  length,
                  "ritorna la lunghrzza di <arg>");
    ret &= I->add("+",
                  sum,
                  "somma un numero variabile di argomenti >= 0");
    ret &= I->add("*",
                  mul,
                  "moltiplica un numero variabile di argomenti >= 0");
    ret &= I->add("OverArrayCiao",
                  OverArrayCiao,
                  "applica la funzione \"ciao\" su un array");
    ret &= I->add("ReverseArray",
                  ReverseArray,
                  "rigira l'array");
    ret &= I->add("/",
                  divide,
                  "divide un numero variabile di argomenti, eventualmente 0");
    ret &= I->add("OverArrayReverseStr",
                  OverArrayReverseStr,
                  "applica la funzione reverse su un array");
    ret &= I->add("OrderArray",
                  OrderArray,
                  "ordina un array");
    ret &= I->add("Sqrt",
                  squareroot,
                  "ritorna la radice quadrata degli argomenti, eventualmente 1");
    ret &= I->add("Binomial",
                  binomial,
                  "ritorna il binomiale degli argomenti, 2");
    // I.add("log",
    //       logarithm,
    //       "ritorna il logaritmo naturale degli argomenti, eventualmente 1");
    // I.add("log2",
    //       logarithm2,
    //       "ritorna il logaritmo base 2 degli argomenti, eventualmente 1");
    // I.add("log10",
    //       logarithm10,
    //       "ritorna il logaritmo base 10 degli argomenti, eventualmente 1");
    
    return ret;
}




