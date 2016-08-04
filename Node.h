#ifndef NODE_H
#define NODE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Vec2.h"
#include "WindowWrapper.h"

class Node{
public:
    /**Constructor */
    Node();
    Node(Node *that);
    virtual ~Node();

    /**Node Status */
    int getId();
    void show(bool p_show);
    bool show();

    /**Arrangement */
    // position
    virtual void setPosition(Vec2<double> p_position);
    virtual void setVeclocity(Vec2<double> p_velocity);
    virtual void moveBy(Vec2<double> p_movement);
    Vec2<double> getPosition();
    Vec2<double> getVelocity();

    // anchor
    void setAnchor(Vec2<double> p_anchor);
    Vec2<double> getAnchor();

    // size
    void setSize(Vec2<double> p_size);
    Vec2<double> getSize();

    /**Texture */
    void setTexture(SDL_Texture* p_texture);
    SDL_Texture* getTexture();
    SDL_Rect* getTextureSrc();
    SDL_Rect* getTextureDst();
    
    /** Render Target */
    WindowWrapper* getRenderTarget();

protected:
    // Static Varaibles
    static int s_current_id;
    
    // Node Status
    int  m_id;
    bool m_show;

    // Arrangement
    Vec2<double> m_position;
    Vec2<double> m_velocity;
    Vec2<double> m_anchor;
    Vec2<double> m_size;

    // Texture
    SDL_Texture* m_texture;
    SDL_Rect* m_texture_src;
    SDL_Rect* m_texture_dst;
    
    // Render Target
    WindowWrapper* m_render_target;
};

#endif /* NODE_H */
