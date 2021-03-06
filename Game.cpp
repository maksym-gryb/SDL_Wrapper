/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Game.cpp
 * Author: interloper
 *
 * Created on February 1, 2016, 10:27 PM
 */

#include "Game.h"

Game* Game::instance = NULL;

Game::Game()
{
    if(Director::getInstance()->init())
    {
        m_critical_error = false;

        m_scene = 0;

        settleTimers();
    }
    else
        m_critical_error = true;
}

Game::~Game() {}

Game* Game::getInstance()
{
    if(instance == NULL)
        instance = new Game;

    return instance;
}

int Game::run(Scene* p_starting_scene)
{
    if(m_critical_error)
        return -1;
    
    setScene(p_starting_scene);
    
    Director::getInstance()->setupCursor();
    
    Director::getInstance()->setupDefaultFont();

    while(isRunning())
    {
        m_timer_now = Director::getInstance()->getTimer();

        update();

        render();

        animation();

        handleEvents();
    }

    cleanUp();
    return 0;
}

int Game::run()
{
    if(m_critical_error)
        return -1;
    
    //loadXML();
    
    Director::getInstance()->setupCursor();
    
    Director::getInstance()->setupDefaultFont();

    while(isRunning())
    {
        m_timer_now = Director::getInstance()->getTimer();

        update();

        render();

        animation();

        handleEvents();
    }
}

int Game::loadXML()
{
    TiXmlDocument doc;
    
    // Load XML
    if(!doc.LoadFile("config.xml"))
    {
        std::cerr << "Error loading file";
        return -1;
    }
    
    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL)
    {
        std::cerr << "Failed to load file! No Root Element.";
        return -1;
    }
    
    depthFirstSearch(root);
    
    delete root;
    
    return 0;
}

void Game::depthFirstSearch(TiXmlElement* node, std::string depth)
{
    // error handling
    if(node == NULL)
    {
        std::cerr << "void depthFirstSearch(TiXmlElement*, std::string) FAILED! ";
        std::cerr << "First function parameter cannot be NULL!";
        return;
    }
    
    // print root and it's attributes
    std::cout << depth << node->Value() << " :";
    for(TiXmlAttribute* attr = node->FirstAttribute(); attr != NULL; attr = attr->Next())
        std::cout << " " << attr->Name() << "=" << attr->Value();
        //std::cout << attr->Name() << "=" << attr->Value() << "\t";// A Spacing Solution
    std::cout << std::endl;
    
    // print root's children
    for(TiXmlElement* sub_e = node->FirstChildElement(); sub_e != NULL; sub_e = sub_e->NextSiblingElement())
        depthFirstSearch(sub_e, depth + "\t");
}

void Game::quit()
{
    Director::getInstance()->quit();
}

void Game::cleanUp()
{
    Director::getInstance()->cleanUp();
}

bool Game::isRunning()
{
    return Director::getInstance()->isRunning();
}

void Game::setScene(Scene* pScene)
{
    m_scene = pScene;
    
    m_scene->setup();
}

Scene* Game::getScene()
{
    return m_scene;
}

long Game::getTimer()
{
    return m_timer_now;
}

void Game::update()
{
    if (m_timer_now < m_timer_next[UPDATE_TIMER] || getScene() == 0)
        return;

    // reset timer
    m_timer_next[UPDATE_TIMER] = m_timer_now + GAME_SPEED;

    // Run scene
    if(m_scene != NULL)
        m_scene->run();
}

void Game::handleEvents()
{
    Director::getInstance()->handleEvents();
}

void Game::resetInput()
{
    // reset timer
    m_timer_next[INPUT_TIMER] = m_timer_now + INPUT_SPEED;

    // resetInput
    Director::getInstance()->resetInput();
}

void Game::render()
{
    if (m_timer_now < m_timer_next[RENDER_TIMER])
        return;

    // reset timer
    m_timer_next[RENDER_TIMER] = m_timer_now + FPS;

    // render
    Director::getInstance()->render();
}

void Game::animation()
{
    if (m_timer_now < m_timer_next[ANIMATION_TIMER])
        return;

    //reset timer
    m_timer_next[ANIMATION_TIMER] = m_timer_now + ANIMATION_SPEED;

    // animation
    Director::getInstance()->animation();
}

void Game::settleTimers()
{
    m_timer_now = Director::getInstance()->getTimer();

    m_timer_next[UPDATE_TIMER] = m_timer_now + GAME_SPEED;
    m_timer_next[RENDER_TIMER] = m_timer_now + FPS;
    m_timer_next[INPUT_TIMER]  = m_timer_now + INPUT_SPEED;
}
