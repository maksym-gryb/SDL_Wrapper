/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Scene.h
 * Author: interloper
 *
 * Created on May 29, 2016, 4:51 PM
 */

#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
    /** Constructor */
    Scene();
    virtual ~Scene();
    
    /** Scene */
    virtual void setup() = 0;
    virtual int run() = 0;
};

#endif /* SCENE_H */

