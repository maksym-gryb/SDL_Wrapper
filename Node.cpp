#include "Node.h"

int Node::s_current_id = 0;

Node::Node()
{
    // Status
    m_id   = ++s_current_id;
    m_show = false;

    // Arrangement
    m_position = Vec2<double>(0.0,   0.0);
    m_velocity = Vec2<double>(0.0,   0.0);
    m_anchor   = Vec2<double>(0.5,   0.5);
    m_size     = Vec2<double>(30.0, 30.0);
    
    // Texture
    m_texture     = NULL;
    m_texture_src = NULL;
    m_texture_dst = NULL;
}

Node::Node(Node *that)
{
    // Status
    m_id   = ++s_current_id;
    m_show = false;

    // Arrangement
    m_position = that->m_position;
    m_velocity = that->m_velocity;
    m_anchor   = that->m_anchor;
    m_size     = that->m_size;
    
    // Texture
    m_texture     = that->m_texture;
    m_texture_src = that->m_texture_src;
    m_texture_dst = that->m_texture_dst;
    
    // Render Target
    m_render_target = that->m_render_target;
}

Node::~Node()
{
    //SDL_DestroyTexture(m_texture);
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

void Node::setVeclocity(Vec2<double> p_velocity)
{
    m_velocity = p_velocity;
}

void Node::moveBy(Vec2<double> p_movement)
{
    m_position += p_movement;

    if(m_texture_dst != NULL)
    {
        m_texture_dst->x = m_position.x;
        m_texture_dst->y = m_position.y;
    }
}

Vec2<double> Node::getPosition()
{
    return m_position;
}

Vec2<double> Node::getVelocity()
{
    return m_velocity;
}

void Node::setSize(Vec2<double> p_size)
{
    // Arrangement
    m_size = p_size;
    
    // Texture
    m_texture_dst->w = m_size.x;
    m_texture_dst->h = m_size.y;
}

Vec2<double> Node::getSize()
{
    return m_size;
}

void Node::setAnchor(Vec2<double> p_anchor)
{
    m_anchor = p_anchor;
}

Vec2<double> Node::getAnchor()
{
    return m_anchor;
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

WindowWrapper* Node::getRenderTarget()
{
    return m_render_target;
}