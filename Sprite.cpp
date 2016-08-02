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
    // Set Node Position
    Node::setPosition(p_position);
    
    // Set Collision Body's Position
    m_body->setPosition(p_position);
}

void Sprite::setVelocity(Vec2<double> p_velocity)
{
    m_velocity = p_velocity;
}

void Sprite::moveBy(Vec2<double> p_mov)
{
    // Move Node Position
    Node::moveBy(p_mov);
    
    // Move Collision Body Position
    m_body->moveBy(p_mov);
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