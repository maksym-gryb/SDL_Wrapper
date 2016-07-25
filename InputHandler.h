/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InputHandler.h
 * Author: interloper
 *
 * Created on July 4, 2016, 5:01 PM
 */

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "Keys.h"

class InputHandler {
public:
    /**Constructors */
    InputHandler();
    ~InputHandler();
    
    /**Set */
    void pressKey(int p_key);
    void releaseKey(int p_keys);
    
    /**Get */
    bool getKey(int p_key);
    
    /**Utilities */
    void resetInput();
    
private:
    bool m_keyPressed[KEYS];
    bool m_keyUsed[KEYS];
};

#endif /* INPUTHANDLER_H */

