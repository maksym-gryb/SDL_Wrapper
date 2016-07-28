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
            (*it).x += m_body->getCenter().x;
        
        if((*it).y > m_body->getCenter().y)
            (*it).y -= m_body->getCenter().y;
        else
            (*it).y += m_body->getCenter().y;
        
        (*it) = (*it) + p_position;
    }
}

void Sprite::moveBy(Vec2<double> p_mov)
{
    Node::moveBy(p_mov);
    
    std::vector<Vec2<double> >::iterator it = m_body->start();
    
    for(;it != m_body->end(); it++)
        (*it) += p_mov;
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
    return this->collidesWith(that);
}