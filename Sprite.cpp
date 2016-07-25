#include "Sprite.h"

Sprite::Sprite() : Node()
{
    // Image
    m_sprite_path = "";
}

Sprite::Sprite(std::string p_sprite_path) : Sprite()
{
    m_sprite_path = p_sprite_path;
}

Sprite::~Sprite() {}

std::string Sprite::getSpritePath()
{
    return m_sprite_path;
}