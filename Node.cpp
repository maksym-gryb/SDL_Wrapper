#include "Node.h"

int Node::s_current_id = 0;

Node::Node()
{
    // Status
    m_id   = ++s_current_id;
    m_show = false;

    // Arrangement
    m_position = Vec2<double>(0.0,  0.0);
    m_anchor   = Vec2<double>(0.5,  0.5);
    m_size     = Vec2<double>(30.0, 30.0);
    
    // Texture
    m_texture     = NULL;
    m_texture_src = NULL;
    m_texture_dst = NULL;
}

Node::~Node()
{
    SDL_DestroyTexture(m_texture);
}

int Node::getId()
{
    return m_id;
}

void Node::show(bool p_show)
{
    m_show = p_show;
}

bool Node::show()
{
    return m_show;
}

void Node::setPosition(Vec2<double> pos)
{
    m_position = pos;

    m_position.x -= (m_size.x * m_anchor.x);
    m_position.y -= (m_size.y * m_anchor.y);

    if(m_texture_dst != NULL)
    {
        m_texture_dst->x = m_position.x;
        m_texture_dst->y = m_position.y;
    }
}

void Node::moveBy(Vec2<double> mov)
{
    setPosition(m_position + mov);
}

Vec2<double> Node::getPosition()
{
    return m_position;
}

Vec2<double> Node::getSize()
{
    return m_size;
}

void Node::setAnchor(Vec2<double> p_anchor)
{
    m_anchor = p_anchor;
}

void Node::setTexture(SDL_Texture* p_texture)
{
    m_texture = p_texture;
}

SDL_Texture* Node::getTexture()
{
    return m_texture;
}

SDL_Rect* Node::getTextureSrc()
{
    return m_texture_src;
}

SDL_Rect* Node::getTextureDst()
{
    return m_texture_dst;
}