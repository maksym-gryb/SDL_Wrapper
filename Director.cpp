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
    
    m_windows = NULL;
    
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
    delete m_windows;
    
    delete m_input_handler;

    IMG_Quit();
    
    //TTF_Quit():?????

    SDL_Quit();
}

bool Director::initSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)// error initializing SDL
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_windows = new WindowWrapper("RPG Battle",
                                  WINDOW_X, WINDOW_Y,
                                  WINDOW_W, WINDOW_H,
                                  SDL_WINDOW_SHOWN
                                 );

    if(m_windows->errorsExist())
        return false;

    int img_flags = IMG_INIT_PNG;
    if(IMG_Init(img_flags) & img_flags)
         m_surface = SDL_GetWindowSurface(m_windows->getWindow());
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

bool Director::init()
{
    if(!initSDL())
    return (m_running = false);

    m_input_handler = new InputHandler;

    setupDefaultFont();

    setupCursor();
    
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

/*TTF_Font* Director::getDefaultFont()
{
    return m_default_font;
}*/

void Director::addNode(Sprite* pSprite)
{
    p_nodes.push_back(pSprite);

    // Create textures if needed
    if(pSprite->getSpritePath() != "")
        Director::getInstance()->assignTexture(pSprite);
}

void Director::deleteNode(Sprite* pSprite)
{
    int id = pSprite->getId();
    for(std::vector<Node*>::iterator it = p_nodes.begin(); it != p_nodes.end(); it++)
    {
        if((*it)->getId() == id)
        {
            delete (*it);
            it = p_nodes.erase(it);
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
    SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(m_windows->getRenderer(), temp_surface);

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
    SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(m_windows->getRenderer(), temp_surface);

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
    SDL_SetRenderDrawColor(m_windows->getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(m_windows->getRenderer());

    SDL_SetRenderDrawColor(m_windows->getRenderer(), 255, 255, 255, 255);
    draw();

    SDL_RenderPresent(m_windows->getRenderer());
}

void Director::draw()
{
    // Draw Sprites
    for (std::vector<Node*>::iterator it = p_nodes.begin(); it != p_nodes.end();)
    {
        if ((*it) == NULL)
            it = p_nodes.erase(it);
        else
        {
            draw(*it);
            it++;
        }
    }
}

void Director::draw(Node* p_node)
{
    SDL_RenderCopy(m_windows->getRenderer(), p_node->getTexture(), p_node->getTextureSrc(), p_node->getTextureDst());
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
