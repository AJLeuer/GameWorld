//
//  GameState.cpp
//  World
//
//  Created by Adam James Leuer on 4/14/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include <iostream>

#include "../Output/OutputData.hpp"

#include "GameState.h"

using namespace std ;

bool GameState::dataIsInit = false ;

bool GameState::graphicsAreInit = false ;

const vector<GameObject *> * GameState::gameObjects = nullptr ;

vector<OutputData<float, int> *> GameState::additionalGraphicalOutputData = vector<OutputData<float, int> *>() ;

const GameMap<GameObject> * GameState::map ;

Window * GameState::window = nullptr ;

Renderer * GameState::renderer = nullptr ;

bool GameState::CONTINUE_FLAG = true ;
Timer * GameState::mainGameClock = new Timer() ;
std::mutex GameState::sharedMutex ;
string GameState::currentDirectory ;



void GameState::initData(vector<GameObject *> * gobs, const GameMap<GameObject> * map) {
	GameState::gameObjects = gobs ;
	GameState::map = map ;
	dataIsInit = true ;
}

void GameState::initGraphics(Window * window, Renderer * renderer) {
	GameState::window = window ;
	GameState::renderer = renderer ;
	graphicsAreInit = true ;
}


const vector<GameObject*> * GameState::getGameObjects()  {
	if (dataIsInit == false) {
		stringstream ss ;
		ss << "GameState::initData() must be called before reading any of its data members \n" ;
		cerr << ss.rdbuf() ;
		throw exception() ;
	}
	return gameObjects ;
}


const GameMap<GameObject> * GameState::getMap()  {
	if (dataIsInit == false) {
		stringstream ss ;
		ss << "GameState::initData() must be called before reading any of its data members \n" ;
		cerr << ss.rdbuf() ;
		throw exception() ;
	}
	return map ;
}

Window * GameState::getMainWindow() {
	if (graphicsAreInit == false) {
		stringstream ss ;
		ss << "GameState::initGraphics() must be called before reading GameState::getMainRenderer() \n" ;
		cerr << ss.rdbuf() ;
		throw exception() ;
	}
	return window ;
}

Renderer * GameState::getMainRenderer() {
	if (graphicsAreInit == false) {
		stringstream ss ;
		ss << "GameState::initGraphics() must be called before reading GameState::getMainRenderer() \n" ;
		cerr << ss.rdbuf() ;
		throw exception() ;
	}
	return renderer ;
}


unsigned mainGameLoopCount = 0 ;
unsigned worldLoopCount = 0 ;

mutex syncMutex ;
condition_variable conditionalWait ;




//static bool GLOBAL_CONTINUE_FLAG = true ;

