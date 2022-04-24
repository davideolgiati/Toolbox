//  Copyright Davide Olgiati 2018

#include "ui.h"
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
               "\nver 0.3.5.20180730.1108 - Senzu Bean\n"
               "realizzato da THO in C++14 07/12/2017 - 30/07/2018\n"
               "run :help for more!\n\n");
        stay = true;
    }
}

void UI::Input(){
    bool res = true;
    std::string str = "";
    unsigned long pointer = 0;
    unsigned long pos = History.size();
    
    int x, y;
    
    printw("[T] >> ");
    
    History.push_back("");
    int ch;
    do {
        ch = getch();
        switch(ch) {
            case KEY_LEFT:
                if(pointer > 0) {
                    getyx(stdscr, y, x);
                    move(y, x-1);
                    pointer--;
                } else {
                    flash();
                }
                break;
            case KEY_RIGHT:
                if(pointer < str.size()) {
                    getyx(stdscr, y, x);
                    move(y, x+1);
                    pointer++;
                } else {
                    flash();
                }
                break;
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
                    pointer = str.size() - 1;
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
                    pointer = str.size() - 1;
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
                    pointer--;
                }
                break;
            case '\n':
                break;
            default:
                if(ch < 127 && ch > 31) {
                    addch(ch);
                    str += ch;
                    pointer++;
                }
                break;
        }
        refresh();
    }while(ch != '\n');
    
    printw("\n\n");
    History[History.size() - 1] = str;
    
    std::size_t comment = str.find("//");
    if(pos != std::string::npos)
        str = str.substr(0, comment);
    
    if(str != "") {
        if (str == ":exit"){
            stay = false;
        } else if (str == ":memusage") {
            double memusage = Engine->getMemUsage();
            
            if (1000 > memusage)
                printw("Total Memeory usage: %.2f Bytes\n", memusage);
            else if (1000000 > memusage)
                printw("Total Memeory usage: %.2f KBytes\n", memusage/1000);
            else
                printw("Total Memeory usage: %.2f MBytes\n", memusage/1000000);
        } else {
            res = Engine->parse(str);
            std::size_t found = str.find(" = ");
            if(found != std::string::npos)
                str.erase(found, str.size());
            Return ret = Engine->getRet();
            if(str[0] != ':')
                str = ((res) ? (str + " = " + ret.arg) : (str + " = "));
            else
                str = ret.arg;
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
            printw("\n\n");
        }
    }
}

bool UI::getState(){
    return stay;
}

void UI::debug() {
    // runTests();
    // getch();
}

UI::~UI() {
    delete Engine;
    endwin();
}
