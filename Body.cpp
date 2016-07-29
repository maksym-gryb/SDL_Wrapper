#include "Body.h"

Body::Body()
{
    m_center = Vec2<double>(0.0, 0.0);
    
    m_max_radius = 0.0;
}

Body::Body(const Vec2<double> p_body...) : Body()
{
    /*va_list args;
    va_start(args, p_body);
    
    do{
        m_body.push_back(va_arg(args, Vec2<double>));
    }while();*/
    
    calculateCenter();
}

Body::~Body() {}

void Body::pushPoint(Vec2<double> point)
{
    m_points.push_back(point);
    calculateCenter();
}

std::vector< Vec2<double> >::iterator Body::start()
{
    return m_points.begin();
}

std::vector< Vec2<double> >::iterator Body::end()
{
    return m_points.end();
}

Vec2<double> Body::getCenter()
{
    return m_center;
}

double Body::getMaxRadius()
{
    return m_max_radius;
}

bool Body::inRangeWith(Body* that)
{
    double delta_x = this->getCenter().x - that->getCenter().x;
    double delta_y = this->getCenter().y - that->getCenter().y;
    
    double distance = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    double limit    = this->getMaxRadius() + that->getMaxRadius();
    
    if(distance < limit)
        return true;
    
    return false;
}

bool Body::collidesWith(Body* that)
{
    /*
    double angle = 0.0;
    std::vector< Vec2<double> >::iterator it = that->start();
    
    for(;it != that->end(); it++)
        for(int i = 0; i < m_points.size(); i++)
        {
            if(i < m_points.size() - 1)
                ;//angle += atan((*it).y - m_points);
            else
                ;//calculate angle between this point and the last
        }
    
    if(angle >= 360.0)
        return true;
    
    return false;
    */
    return true;
}

void Body::calculateCenter()
{
    m_center = Vec2<double>(0.0, 0.0);
    
    if(m_points.size() == 1)
        m_center = m_points[0];
    else if(m_points.size() > 1)
    {
        // calculate center
        for(unsigned i = 0; i < m_points.size(); i++)
            m_center += m_points[i];
        
        m_center = m_center / m_points.size();
        
        // calculate max radius
        if(m_max_radius == 0.0)
            m_max_radius = 0.0;
        
        for(unsigned i = 0; i < m_points.size(); i++)
        {
            double magnitude = m_points[i].magnitude();
            if(magnitude > m_max_radius)
                m_max_radius = magnitude;
        }
    }
}