#ifndef NODE_H
#define NODE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Vec2.h"

class Node{
public:
    /**Constructor */
    Node();
    virtual ~Node();

    /**Node Status */
    int getId();
    void show(bool p_show);
    bool show();

    /**Arrangement */
    // position
    void setPosition(Vec2<double> p_position);
    void moveBy(Vec2<double> p_movement);
    Vec2<double> getPosition();

    // anchor
    void setAnchor(Vec2<double> p_anchor);

    // size
    void setSize(Vec2<double> p_size);
    Vec2<double> getSize();

    /**Texture */
    void setTexture(SDL_Texture* p_texture);
    SDL_Texture* getTexture();
    SDL_Rect* getTextureSrc();
    SDL_Rect* getTextureDst();

protected:
    // Static Varaibles
    static int s_current_id;
    
    // Node Status
    int  m_id;
    bool m_show;

    // Arrangement
    Vec2<double> m_position;
    Vec2<double> m_anchor;
    Vec2<double> m_size;

    // Texture
    SDL_Texture* m_texture;
    SDL_Rect* m_texture_src;
    SDL_Rect* m_texture_dst;
};

#endif /* NODE_H */
