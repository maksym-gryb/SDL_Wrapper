/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Body.h
 * Author: interloper
 *
 * Created on July 28, 2016, 8:11 AM
 */

#ifndef BODY_H
#define BODY_H

#include <vector>
#include "Vec2.h"

class Body {
public:
    /** Constructors */
    Body();
    Body(const Vec2<double> p_body...);//currently does not work
    virtual ~Body();
    
    /** Body */
    void pushPoint(Vec2<double> point);
    std::vector< Vec2<double> >::iterator start();// returns an iterator at the beginning of m_points
    std::vector< Vec2<double> >::iterator end();
    
    Vec2<double> getCenter();
    double getMaxRadius();
    
    /** Collision */
    bool inRange(Body *that);
    bool collidesWith(Body *that);
    
    /** Utilities */
    void calculateCenter();
    
private:
    /** Variables */
    std::vector< Vec2<double> > m_points;
    Vec2<double> m_center;
    double m_max_radius;
};

#endif /* BODY_H */
