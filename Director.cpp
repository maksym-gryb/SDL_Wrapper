/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Director.cpp
 * Author: interloper
 *
 * Created on May 29, 2016, 4:11 PM
 */

#include "Director.h"

Director* Director::instance = NULL;

Director::Director()
{
    m_running = false;
    
    m_windows.push_back(NULL);
    
    m_default_font = NULL;
    
    m_input_handler = NULL;
}

Director::~Director()
{
    //stuff
}

Director* Director::getInstance()
{
    if(instance == NULL)
        instance = new Director;

    return instance;
}

void Director::quit()
{
    m_running = false;
}

bool Director::isRunning()
{
    return m_running;
}

void Director::cleanUp()
{
    for(unsigned i = m_windows.size() - 1; i > 0; i++)
    {
        if(m_windows[i] != NULL)
            delete m_windows[i];
        
        m_windows.pop_back();
    }
    
    delete m_input_handler;

    IMG_Quit();
    
    TTF_Quit();

    SDL_Quit();
}

bool Director::initSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)// error initializing SDL
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    int img_flags = IMG_INIT_PNG;
    if(IMG_Init(img_flags) & img_flags)
         ;//m_surface = SDL_GetWindowSurface(m_windows->getWindow());// not currently viable with multi-windows
    else
    {
        std::cerr << "IMG_Init error: " << SDL_GetError() << std::endl;
        return false;
    }

    if(TTF_Init() == -1)
    {
        std::cerr << "TTF_Init error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

WindowWrapper* Director::createWindow(std::string p_title)
{
    WindowWrapper* temp_ww = new WindowWrapper(p_title.c_str(),
                                               WINDOW_X, WINDOW_Y,
                                               WINDOW_W, WINDOW_H,
                                               SDL_WINDOW_SHOWN
                                              );

    if(temp_ww->errorsExist())
    {
        delete temp_ww;
        return NULL;
    }
    
    if(m_windows.size() == 1 && m_windows[0] == NULL)
        m_windows[0] = temp_ww;
    else
        m_windows.push_back(temp_ww);
    
    return temp_ww;
}

bool Director::init()
{
    if(!initSDL())
        return (m_running = false);

    m_input_handler = new InputHandler;
    
    return (m_running = true);
}

void Director::setupDefaultFont()
{
    m_default_font = TTF_OpenFont(DEFAULT_FONT.c_str(), 90);
}

void Director::setupCursor()
{
    SDL_ShowCursor(SDL_DISABLE);

    addNode(Cursor::getInstance());
}

void Director::handleEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
            quit();
        else if (e.type == SDL_MOUSEMOTION)
        {
            int x = e.motion.x;
            int y = e.motion.y;
            Cursor::getInstance()->setPosition(Vec2<double>(x, y));
        }
        else if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_UP:     m_input_handler->pressKey(KEY_UP);    break;
                case SDLK_RIGHT:  m_input_handler->pressKey(KEY_RIGHT); break;
                case SDLK_DOWN:   m_input_handler->pressKey(KEY_DOWN);  break;
                case SDLK_LEFT:   m_input_handler->pressKey(KEY_LEFT);  break;
                case SDLK_SPACE:  m_input_handler->pressKey(KEY_SPACE); break;
                //case SDLK_RETURN: m_input_handler->pressKey(KEY_ENTER); break;
                //case SDLK_z:      m_input_handler->pressKey(KEY_z);     break;
                //case SDLK_x:      m_input_handler->pressKey(KEY_x);     break;
            }
        }
        else if(e.type == SDL_KEYUP)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_UP:     m_input_handler->releaseKey(KEY_UP);    break;
                case SDLK_RIGHT:  m_input_handler->releaseKey(KEY_RIGHT); break;
                case SDLK_DOWN:   m_input_handler->releaseKey(KEY_DOWN);  break;
                case SDLK_LEFT:   m_input_handler->releaseKey(KEY_LEFT);  break;
                case SDLK_SPACE:  m_input_handler->releaseKey(KEY_SPACE); break;
                //case SDLK_RETURN: m_input_handler->releaseKey(KEY_ENTER); break;
                //case SDLK_z:      m_input_handler->releaseKey(KEY_z);     break;
                //case SDLK_x:      m_input_handler->releaseKey(KEY_x);     break;
            }
        }
    }
}

void Director::resetInput()
{
    m_input_handler->resetInput();
}

bool Director::getKey(int p_key)
{
    return m_input_handler->getKey(p_key);
}

void Director::resetKey(int p_key)
{
    m_input_handler->resetKey(p_key);
}

/*TTF_Font* Director::getDefaultFont()
{
    return m_default_font;
}*/

void Director::addNode(Sprite* p_sprite)
{
    m_sprites.push_back(p_sprite);

    // Create textures if needed
    if(p_sprite->getSpritePath() != "")
        Director::getInstance()->assignTexture(p_sprite);
}

void Director::deleteNode(Sprite* p_sprite)
{
    int id = p_sprite->getId();
    for(std::vector<Sprite*>::iterator it = m_sprites.begin(); it != m_sprites.end(); it++)
    {
        if((*it)->getId() == id)
        {
            delete (*it);
            it = m_sprites.erase(it);
            break;
        }
    }
}

void Director::addNode(Label* p_label)
{
    m_labels.push_back(p_label);

    // Create textures if needed
    Director::getInstance()->assignTexture(p_label);
}

void Director::deleteNode(Label* p_label)
{
    int id = p_label->getId();
    for(std::vector<Label*>::iterator it = m_labels.begin(); it != m_labels.end(); it++)
    {
        if((*it)->getId() == id)
        {
            delete (*it);
            it = m_labels.erase(it);
            break;
        }
    }
}

SDL_Texture* Director::createTexture(Sprite* p_sprite)
{
    // find loaded texture
    std::map<std::string, SDL_Texture*>::iterator it = m_loaded_textures.find(p_sprite->getSpritePath());
    if (it != m_loaded_textures.end())
        return it->second;

    //load new texture
    SDL_Surface* temp_surface = IMG_Load(p_sprite->getSpritePath().c_str());
    SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(p_sprite->getRenderTarget()->getRenderer(), temp_surface);

    // free surface
    SDL_FreeSurface(temp_surface);

    // store new texture
    m_loaded_textures[p_sprite->getSpritePath()] = temp_texture;

    return temp_texture;
}

void Director::assignTexture(Sprite* pSprite)
{
    pSprite->setTexture(createTexture(pSprite));
}

SDL_Texture* Director::createTexture(Label* p_label)
{
    SDL_Surface* temp_surface = TTF_RenderText_Blended(p_label->getFont(), p_label->getText().c_str(), p_label->getColor());
    SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(p_label->getRenderTarget()->getRenderer(), temp_surface);

    SDL_QueryTexture(temp_texture, NULL, NULL, NULL, NULL);

    SDL_FreeSurface(temp_surface);

    return temp_texture;
}

void Director::assignTexture(Label* p_label)
{
    p_label->setTexture(createTexture(p_label));
}

void Director::render()
{
    for(unsigned i = 0; i < m_windows.size(); i++)
    {
        if(m_windows[i] == NULL)
            continue;
        SDL_SetRenderDrawColor(m_windows[i]->getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(m_windows[i]->getRenderer());
    }

    for(unsigned i = 0; i < m_windows.size(); i++)
    {
        if(m_windows[i] == NULL)
            continue;
        SDL_SetRenderDrawColor(m_windows[i]->getRenderer(), 255, 255, 255, 255);
    }
    
    draw();

    for(unsigned i = 0; i < m_windows.size(); i++)
    {
        if(m_windows[i] == NULL)
            continue;
        SDL_RenderPresent(m_windows[i]->getRenderer());
    }
}

void Director::draw()
{
    // Draw Sprites
    for (std::vector<Sprite*>::iterator it = m_sprites.begin(); it != m_sprites.end();)
    {
        if ((*it) == NULL)
            it = m_sprites.erase(it);
        else
        {
            draw(*it);
            #ifndef PRODUCTION_MODE
            draw((*it)->getCollisionBody());
            #endif
            it++;
        }
    }
    
    // Draw Labels
    for (std::vector<Label*>::iterator it = m_labels.begin(); it != m_labels.end();)
    {
        if ((*it) == NULL)
            it = m_labels.erase(it);
        else
        {
            draw(*it);
            it++;
        }
    }
}

void Director::draw(Node* p_node)
{
    SDL_RenderCopy(p_node->getRenderTarget()->getRenderer(), p_node->getTexture(), p_node->getTextureSrc(), p_node->getTextureDst());
}

#ifndef PRODUCTION_MODE
void Director::draw(Body* p_body)
{
    std::vector<Vec2<double> >::iterator it = p_body->start();
    if(it == p_body->end())
        return;
    
    std::vector<Vec2<double> >::iterator next = p_body->start();
    next++;
    
    // draw collision body center
    SDL_Rect rect = {(int)p_body->getCenter().x - 5, (int)p_body->getCenter().y - 5, 10, 10};
    SDL_RenderFillRect(p_body->getRenderTarget()->getRenderer(), &rect);
    
    // draw collision body
    while(it != p_body->end() && next != p_body->end())
    {
        SDL_RenderDrawLine(p_body->getRenderTarget()->getRenderer(), (*it).x, (*it).y, (*next).x, (*next).y);
        
        it++;
        next++;
        
        if(next == p_body->end())
            next = p_body->start();
    }
}
#endif

WindowWrapper* Director::getDefaultWW()
{
    if(m_windows.size() > 0)
        return m_windows[0];
    
    m_windows.push_back(NULL);
    return m_windows[0];
}

void Director::animation()
{
    //stuff
}

void Director::passiveAnimation()
{
    //stuff
}

void Director::activeAnimation()
{
    //stuff
}

long Director::getTimer()
{
    return clock();
}

int Director::getRandomNumber()
{
    return (int)clock();
}
