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

        //setupPauseMenu();

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

    while(isRunning())
    {
        m_timer_now = Director::getInstance()->getTimer();

        update();

        render();

        animation();

        handleEvents();

        handleUserInput();
    }

    cleanUp();
    return 0;
}

void Game::quit()
{
    Director::getInstance()->quit();
}

void Game::cleanUp()
{
    Director::getInstance()->cleanUp();
}

/*void Game::setupPauseMenu()
{
    //Sprite* pMenuItem;

    //pMenuItem = Director::getInstance()->createMenuItem("GAME PAUSED", WINDOW_WIDTH/2 - 32*5, WINDOW_HEIGHT/2 - 32, 32);
    //pMenuItem->showSprite(false);
    //pause_menu.push_back(pMenuItem);
}*/

bool Game::isRunning()
{
    return Director::getInstance()->isRunning();
}

/*bool Game::isPaused()
{
    return Director::getInstance()->isPaused();
}*/

void Game::setScene(Scene* pScene)
{
    m_scene = pScene;
}

Scene* Game::getScene()
{
    return m_scene;
}

long Game::getTimer()
{
    return m_timer_now;
}

/*void Game::pause()
{
    Director::getInstance()->pause();
    showPauseMenu();
}

void Game::unpause()
{
    Director::getInstance()->unpause();
    hidePauseMenu();
    settleTimers();
}*/

void Game::update()
{
    if (m_timer_now < m_timer_next[UPDATE_TIMER] || getScene() == 0)
        return;

    // reset timer
    m_timer_next[UPDATE_TIMER] = m_timer_now + GAME_SPEED;

    // When game is paused
    /*if(isPaused())
        return;*/

    // Run scene
    if(m_scene != NULL)
        m_scene->run();
}

void Game::handleEvents()
{
    Director::getInstance()->handleEvents();
}

void Game::handleUserInput()
{
    if(Director::getInstance()->getKey(/*KEY_ENTER*/0))
    {
        /*if(isPaused())
            unpause();
        else
            pause();*/
    }
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

/*void Game::showPauseMenu()
{
    //for(std::vector<Sprite*>::iterator it = pause_menu.begin(); it != pause_menu.end(); it++)
        //(*it)->showSprite(true);
}

void Game::hidePauseMenu()
{
    //for(std::vector<Sprite*>::iterator it = pause_menu.begin(); it != pause_menu.end(); it++)
        //(*it)->showSprite(false);
}*/

void Game::settleTimers()
{
    m_timer_now = Director::getInstance()->getTimer();

    m_timer_next[UPDATE_TIMER] = m_timer_now + GAME_SPEED;
    m_timer_next[RENDER_TIMER] = m_timer_now + FPS;
    m_timer_next[INPUT_TIMER]  = m_timer_now + INPUT_SPEED;
}
