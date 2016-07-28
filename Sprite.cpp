#include "Sprite.h"

Sprite::Sprite() : Node()
{
    // Image
    m_sprite_path = "";
}

Sprite::Sprite(std::string p_sprite_path) : Node()
{
    // Image
    m_sprite_path = p_sprite_path;
}

Sprite::~Sprite() {}

std::string Sprite::getSpritePath()
{
    return m_sprite_path;
}

void Sprite::setCollisionBody(Body* p_body)
{
    m_body = p_body;
}

bool Sprite::collidesWith(Sprite* that)
{
    return this->collidesWith(that);
}