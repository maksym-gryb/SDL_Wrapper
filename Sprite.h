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
#include "Body.h"

class Sprite : public Node{
public:
    /** Constructors */
    Sprite(std::string p_sprite_path, WindowWrapper* p_render_target = NULL);
    Sprite(Sprite *that);
    virtual ~Sprite();
    
    /** Arrangement */
    void setPosition(Vec2<double> p_position);
    void setVelocity(Vec2<double> p_velocity);
    void moveBy(Vec2<double>);

    /** Image */
    std::string getSpritePath();
    
    /** Sprite */
    virtual void update() = 0;
    
    /** Collision */
    void setCollisionBody(Body* p_body);
    Body* getCollisionBody();
    bool inRangeWith(Sprite *that);
    bool collidesWith(Sprite *that);

protected:
    /** Image */
    std::string m_sprite_path;
    
    /** Collision Body */
    Body* m_body;
};

#endif /* SPRITE_H */
