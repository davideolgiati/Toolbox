//  Copyright Davide Olgiati 2018

#ifndef _UI_H
#define _UI_H

#include "interpreter.h"
#include "debug.h"

class UI {
 public:
    UI(bool debug);
    void Input();
    bool getState();
    
 private:
    bool populate(Interpreter* const I);
    
    Interpreter Engine;
    bool stay;
};

#endif /* ui_hpp */
