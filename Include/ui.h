//  Copyright Davide Olgiati 2018

#ifndef _UI_H
#define _UI_H

#include "interpreter.h"

class ui {
 public:
    ui(bool debug);
    
 private:
    Interpreter Engine;
};

#endif /* ui_hpp */
