/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Sprite.h
 * Author: interloper
 *
 * Created on January 31, 2016, 1:42 PM
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Vec2.h"
#include "Node.h"
#include "Director.h"

class Sprite : public Node{
public:
    /** Constructors */
    Sprite();
    Sprite(std::string p_sprite_path);
    virtual ~Sprite();

    /** Image */
    std::string getSpritePath();
    
    /** Sprite */
    virtual void update() = 0;

protected:
    /** Image */
    std::string m_sprite_path;
};

#endif /* SPRITE_H */
