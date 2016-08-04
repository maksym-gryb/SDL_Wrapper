#include "Label.h"
#include "Director.h"

Label::Label(WindowWrapper* p_render_target) : Node()
{
    m_text = "";
    m_font_size = DEFAULT_TEXT_SIZE;
    m_font = NULL;
    m_text_color = {255, 255, 255, 255};
    
    // Render Target
    if(p_render_target == NULL)
        m_render_target = Director::getInstance()->getDefaultWW();
    else
        m_render_target = p_render_target;
}

Label::~Label()
{
    //stuff
}

void Label::setText(std::string p_text)
{
    m_text = p_text;
}

std::string Label::getText()
{
    return m_text;
}

void Label::setFont(TTF_Font* p_font)
{
    m_font = p_font;
}

TTF_Font* Label::getFont()
{
    return m_font;
}

void Label::setColor(SDL_Color p_color)
{
    m_text_color = p_color;
}

SDL_Color Label::getColor()
{
    return m_text_color;
}