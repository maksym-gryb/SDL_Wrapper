#include "Body.h"
#include "Director.h"

Body::Body(WindowWrapper* p_render_target) : Node()
{
    m_center = Vec2<double>(0.0, 0.0);
    
    m_max_radius = 0.0;
    
    if(p_render_target == NULL)
        m_render_target = Director::getInstance()->getDefaultWW();
    else
        m_render_target = p_render_target;
}

Body::Body(Body* that) : Node(that)
{
    m_center = that->m_center;
    
    m_max_radius = that->m_max_radius;
    
    for(unsigned i = 0; i < that->m_points.size(); i++)
        m_points.push_back(that->m_points[i]);
}

Body::~Body() {}

void Body::setPosition(Vec2<double> p_position)
{
    for(unsigned i = 0; i < m_points.size(); i++)
        m_points[i] = m_points[i] - m_center + p_position;
    
    m_center = p_position;
}

void Body::moveBy(Vec2<double> p_mov)
{
    for(unsigned i = 0; i < m_points.size(); i++)
        m_points[i] += p_mov;
    
    m_center += p_mov;
}

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
    m_max_radius = 0.0;
    
    if(m_points.size() == 1)
        m_center = m_points[0];
    else if(m_points.size() > 1)
    {
        // calculate center
        for(unsigned i = 0; i < m_points.size(); i++)
            m_center += m_points[i];
        
        m_center = m_center / m_points.size();
        
        for(unsigned i = 0; i < m_points.size(); i++)
        {
            Vec2<double> temp = m_points[i];
            temp = temp - m_center;
            
            double magnitude = temp.magnitude();
            if(magnitude > m_max_radius)
                m_max_radius = magnitude;
        }
    }
}