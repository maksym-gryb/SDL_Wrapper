#include "Cursor.h"

Cursor* Cursor::instance = NULL;

Cursor::Cursor() : Sprite("resources/cursor.png")
{
    // Status
    m_show = true;
    
    // Arrangement
    m_anchor = Vec2<double>(0.0, 0.0);
    
    // Texture
    m_texture_dst = new SDL_Rect;
    m_texture_dst->x = -m_size.x;
    m_texture_dst->y = -m_size.y;
    m_texture_dst->w = m_size.x;
    m_texture_dst->h = m_size.y;
}

Cursor* Cursor::getInstance()
{
	if (instance == NULL)
		instance = new Cursor;

	return instance;
}


Cursor::~Cursor() {}

void Cursor::update()
{
    
}