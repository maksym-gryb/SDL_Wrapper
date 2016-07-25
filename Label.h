#ifndef LABEL_HPP
#define LABEL_HPP

#include "Node.h"

#include <string>

const int DEFAULT_TEXT_SIZE = 18;
const SDL_Color DEFAULT_TEXT_COLOR = { 255, 255, 255, 255 };

const std::string DEFAULT_FONT = "resources/Mops.ttf";

class Label: public Node{
public:
    /**Constructor */
    Label();
    ~Label();

    /**Text */
    void setText(std::string p_text);
    std::string getText();

    /**Texture */
    // font
    void setFont(TTF_Font* p_font);
    TTF_Font* getFont();

    // color
    void setColor(SDL_Color p_color);
    SDL_Color getColor();

private:
    // Text
    std::string m_text;
    int m_font_size;
    TTF_Font* m_font;
    SDL_Color m_text_color;
};

#endif /* LABEL_HPP */