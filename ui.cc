//  Copyright Davide Olgiati 2018

#include "Include/ui.h"
#include <ncurses.h>

UI::UI(bool debug){
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    keypad(stdscr, TRUE);
    start_color();
    use_default_colors();
    
    init_pair(1, -1, COLOR_RED);
    init_pair(2, -1, COLOR_GREEN);
    
    Engine = new Interpreter();
    if (!debug) {
        printw("   _____         _ ___ \n"
               "  |_   _|__  ___| | _ ) _____ __\n"
               "    | |/ _ \\/ _ \\ | _ \\/ _ \\ \\ /\n"
               "    |_|\\___/\\___/_|___/\\___/_\\_\\\n\n"
               "\nver \e[7;32m 0.3.4.20180308.2139 - Kaio-ken \e[0m\n"
               "realizzato da THO in C++14 07/12/2017 - 22/02/2018\n"
               "run \e[7m:help\e[0m for more!\n\n");
        stay = true;
    }
}

void UI::Input(){
    bool res = true;
    std::string str = "";
    unsigned long pointer = History.size();
    unsigned long pos = History.size();
    
    int x, y;
    
//  std::ios_base::sync_with_stdio(false);
//  std::cin.tie(NULL);
//  std::fflush(stdin);
    printw("[T] >> ");
//  std::getline(std::cin, str);
    
    History.push_back("");
    int ch;
    do {
        ch = getch();
        switch(ch) {
            case KEY_UP:
                if(pos > 0) {
                    pos--;
                    getyx(stdscr, y, x);
                    for(unsigned long i = 0; i < str.size(); i++) {
                        x--;
                        move(y, x);
                        delch();
                    }
                    if( str != History[pos + 1])
                        History[pointer] = str;
                    str = History[pos];
                    printw(str.c_str());
                } else {
                    flash();
                }
                break;
            case KEY_DOWN:
                if(pos < History.size() - 1) {
                    pos++;
                    getyx(stdscr, y, x);
                    for(unsigned long i = 0; i < str.size(); i++) {
                        x--;
                        move(y, x);
                        delch();
                    }
                    if( str != History[pos - 1])
                        History[pointer] = str;
                    str = History[pos];
                    printw(str.c_str());
                } else {
                    flash();
                }
                break;
            case 127:
                if(str.size() > 0){
                    getyx(stdscr, y, x);
                    move(y, x-1);
                    delch();
                    str.pop_back();
                }
                break;
            case '\n':
                break;
            default:
                if((ch < 255 && ch > 32) && ch != 127)
                    addch(ch);
                    str += ch;
                break;
        }
        refresh();
    }while(ch != '\n');
    
    History[pointer] = str;
    
    if (str == ":exit"){
        stay = false;
    } else if (str == ":memusage") {
        double memusage = Engine->getMemUsage();
        
        if (1000 > memusage)
            std::cout << "Total Memeory usage: " <<  memusage << " Bytes\n";
        else if (1000000 > memusage)
            std::cout << "Total Memeory usage: " << std::setprecision(2) <<  memusage/1000 << " KBytes\n";
        else
            std::cout << "Total Memeory usage: " << std::setprecision(2) <<  memusage/1000000 << " MBytes\n";
    } else {
        res = Engine->parse(str);
        std::size_t found = str.find(" = ");
        if(found != std::string::npos)
        str.erase(found, str.size());
        Return ret = Engine->getRet();
        str = ((res) ? ("\n" + str + " = " + ret.arg) : "");
        printw(str.c_str());
        if(ret.success){
            attron(A_BOLD);
            attron(COLOR_PAIR(2));
            printw(" true ");
            attroff(COLOR_PAIR(2));
            attroff(A_BOLD);
        } else {
            attron(A_BOLD);
            attron(COLOR_PAIR(1));
            printw(" false ");
            attroff(COLOR_PAIR(1));
            attroff(A_BOLD);
        }
        printw("\n");
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
    endwin();
}
