/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vec2.h
 * Author: interloper
 *
 * Created on January 31, 2016, 1:47 PM
 */

#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <cmath>

#define PI 3.14159265

template <class T> class Vec2{
public:
    /** variables */
    T x, y;

    /** Constructors */    
    Vec2()
    {
        x = 0;
        y = 0;
    }

    Vec2(T p_x, T p_y)
    {
        x = p_x;
        y = p_y;
    }

    /** Operators */
    Vec2 operator+(const Vec2& that)
    {
        Vec2 temp;
        temp.x = this->x + that.x;
        temp.y = this->y + that.y;
        return temp;
    }
    
    Vec2 operator-(const Vec2& that)
    {
        Vec2 temp;
        temp.x = this->x - that.x;
        temp.y = this->y - that.y;
        return temp;
    }

    void operator=(const Vec2& that)
    {
        this->x = that.x;
        this->y = that.y;
    }
    
    void operator+=(const Vec2& that)
    {
        this->x = this->x + that.x;
		this->y = this->y + that.y;
    }
    
    void operator-=(const Vec2& that)
    {
        this->x = this->x - that.x;
        this->y = this->y - that.y;
    }
    
    Vec2 operator*(const int mult)
    {
        Vec2 temp;
        temp.x = this->x * mult;
        temp.y = this->y * mult;
        return temp;
    }
    
    Vec2 operator/(const int div)
    {
        Vec2 temp;
        temp.x = this->x / div;
        temp.y = this->y / div;
        return temp;
    }
    
    /** Transformations */
    double magnitude()
    {
        return sqrt(pow(this->x, 2) + pow(this->y, 2));
    }
    
    Vec2 rotate(int ang)
    {
        Vec2 temp;
        double cos_d = cos(ang*PI/180);
        double sin_d = sin(ang*PI/180);
        temp.x = (this->x * cos_d) - (this->y * sin_d);
        temp.y = (this->x * sin_d) + (this->y * cos_d);
        return temp;
    }
    
    /** Get */
    int getX() { return x; }
    int getY() { return y; }
    
    //double getAngle() { return std::atan2(x, y); }
};

#endif /* VEC2_H */

