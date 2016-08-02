#include "Sprite.h"

Sprite::Sprite() : Node()
{
    // Image
    m_sprite_path = "";
    
    // Collision Body
    m_body = new Body;
}

Sprite::Sprite(std::string p_sprite_path) : Sprite()
{
    // Image
    m_sprite_path = p_sprite_path;
}

Sprite::Sprite(Sprite* that) : Node(that)
{
    // Image
    m_sprite_path = that->m_sprite_path;
    
    // Collision Body
    m_body = new Body(that->m_body);
}

Sprite::~Sprite() {}

void Sprite::setPosition(Vec2<double> p_position)
{
    Node::setPosition(p_position);
    
    std::vector<Vec2<double> >::iterator it = m_body->start();
    
    for(;it != m_body->end(); it++)
    {
        if((*it).x > m_body->getCenter().x)
            (*it).x -= m_body->getCenter().x;
        else
            (*it).x = m_body->getCenter().x - (*it).x;
        
        if((*it).y > m_body->getCenter().y)
            (*it).y -= m_body->getCenter().y;
        else
            (*it).y = m_body->getCenter().y - (*it).y;
        
        (*it) = (*it) + p_position;
    }
    
    m_body->calculateCenter();
}

void Sprite::setVelocity(Vec2<double> p_velocity)
{
    m_velocity = p_velocity;
}

void Sprite::moveBy(Vec2<double> p_mov)
{
    this->Node::moveBy(p_mov);
    
    std::vector<Vec2<double> >::iterator it = m_body->start();
    
    for(;it != m_body->end(); it++)
        (*it) += p_mov;
    
    m_body->calculateCenter();
}

std::string Sprite::getSpritePath()
{
    return m_sprite_path;
}

void Sprite::setCollisionBody(Body* p_body)
{
    m_body = p_body;
}

Body* Sprite::getCollisionBody()
{
    return m_body;
}

bool Sprite::inRangeWith(Sprite* that)
{
    return m_body->inRangeWith(that->getCollisionBody());
}

bool Sprite::collidesWith(Sprite* that)
{
    return this->m_body->collidesWith(that->m_body);
}