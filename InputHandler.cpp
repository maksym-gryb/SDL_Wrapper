/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InputHandler.cpp
 * Author: interloper
 * 
 * Created on July 4, 2016, 5:01 PM
 */

#include "InputHandler.h"

InputHandler::InputHandler()
{
    for(int i = 0; i < KEYS; i++)
    {
        m_keyPressed[i] = false;
        m_keyUsed[i]    = false;
    }
}

InputHandler::~InputHandler() {}

void InputHandler::pressKey(int p_key)
{
    m_keyPressed[p_key] = true;
}

void InputHandler::releaseKey(int p_key)
{
    m_keyPressed[p_key] = false;
    m_keyUsed[p_key]    = false;
}

bool InputHandler::getKey(int p_key)
{
    if(m_keyPressed[p_key] && !m_keyUsed[p_key])
        return (m_keyUsed[p_key] = true);
    
    return false;
}

void InputHandler::resetInput()
{
    for(int i = 0; i < KEYS; i++)
    {
        m_keyPressed[i] = false;
        m_keyUsed[i]    = false;
    }
}