#include "Cursor.h"

Cursor* Cursor::instance = NULL;

Cursor::Cursor() : Sprite()
{
    // Status
    m_show = true;
    
    // Arrangement
    m_anchor = Vec2<double>(0.0, 0.0);
    
    m_texture_dst = new SDL_Rect;
    m_texture_dst->x = -m_size.x;
    m_texture_dst->y = -m_size.y;
    m_texture_dst->w = m_size.x;
    m_texture_dst->h = m_size.y;

    // Image
    m_sprite_path = "resources/cursor.png";
    m_sprite_path = "resources/potato.jpg";
}

Cursor* Cursor::getInstance()
{
	if (instance == NULL)
		instance = new Cursor;

	return instance;
}


Cursor::~Cursor() {}