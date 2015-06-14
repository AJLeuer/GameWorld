//
//  MainControl.cpp
//  World
//
//  Created by Adam James Leuer on 4/16/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//



#include "MainControl.h"

using namespace std ;

/* not safe to initialize this yet */
Player * MainControl::player0 = nullptr ;
Player * MainControl::player1 = nullptr ;

const unsigned * MainControl::loopCount = &mainGameLoopCount ; //Debug symbol, delete

void MainControl::begin_exit() {
	GLOBAL_CONTINUE_FLAG = false ;
}

void MainControl::setupMainContrExit() {
	
	/* Signal handling */
	signal(SIGQUIT, &MainControl::exitmc) ;
	signal(SIGABRT, &MainControl::exitmc) ;
	signal(SIGTERM, &MainControl::exitmc) ;
	
	/* Register for MainControl::exit() to be called if a quit event is initiated (i.e. user clicks
	  window close button, presses ⌘Q, etc */
	EventRegister * quitEvent = new EventRegister(&MainControl::begin_exit, EventType::SDL_QUIT) ;
	InputControl::registerForEvent(quitEvent) ;
}

auto reverseTimeFlow = [] () -> void {
	if (timeFlow == TimeFlow::forward) {
		timeFlow = TimeFlow::reverse ;
	}
	else { //if (timeFlow == TimeFlow::reverse)
		timeFlow = TimeFlow::forward ;
	}
} ;

void MainControl::setupCallbacks() {
	KeyInputRegister * onKeypressReverseTime = new KeyInputRegister(reverseTimeFlow, {TIME_REVERSE_KEY}, KeypressEvaluationMethod::any) ;
	InputControl::registerForKeypress(onKeypressReverseTime) ;
}

void MainControl::init() {
	
	GameState::mainGameClock->startTimer() ;
	GLOBAL_CONTINUE_FLAG = true ;
	mainThreadID = this_thread::get_id() ;
	
	//do initializations
    Configuration::init() ;
	Debug::init() ;
	
	int sdlinit_error = SDL_Init(0) ;
	
	if (sdlinit_error != 0) {
		stringstream ss ;
		ss << "SDL_Init() failed." << '\n' ;
		ss << SDL_GetError() << '\n' ;
		cerr << ss.rdbuf() ;
		throw exception() ;
	}
	
	GraphicalOutput::init() ;
    TextOutput<float, int>::init() ;
	InputControl::init() ;
	MainControl::setupCallbacks() ;
	WorldControl::init() ;    //must be last, will init GameState as well
	Weapon::init() ;
	
	Player::initDefaultPlayers() ; //players (i.e. of class Player) will set up callbacks from actual player (i.e. live human) input
	
	player0 = Player::defaultPlayer0 ;
	player1 = Player::defaultPlayer1 ;
	
	player0->displayVelocity( { static_cast<float>((globalMaxX() * 0.70)), static_cast<float>((globalMaxY() * 0.85))},
						     {142, 255, 8, 0}, {0, 0, 0, 0}) ;
	
	player1->displayVelocity( { static_cast<float>((globalMaxX() * 0.15)), static_cast<float>((globalMaxY() * 0.85))},
							 {251, 0, 107, 0}, {0, 0, 0, 0}) ;
	
	//setup MainControl to exit() later (typically with a callback assigned to a keypress)
	setupMainContrExit() ;
}

void MainControl::main() {
    
	/* Start main functions for all controller classes. WorldControl manages the world on its own thread, and input and output
	 switch off on the main thread */
	WorldControl::begin_main() ;
	
	GraphicalOutput::drawFPS() ;
	
	auto rt = refreshTime ; //debug symbol
	
	while (GLOBAL_CONTINUE_FLAG) {
		
		auto * mloop = &mainGameLoopCount ; //debug var, delete this
		auto * wloop = &worldLoopCount ; //debug var, delete
		
		/* Will need to lock the mutex when shutting down */
		
		auto startTime = GameState::mainGameClock->checkTimeElapsed() ;
		
		GraphicalOutput::update() ;
		GraphicsData<float, int>::checkForCollisions() ;
		InputControl::update() ;
		
		if (GLOBAL_CONTINUE_FLAG == false) { /* we check here because setting false will have been done by callback during InputControl::update() */
			break ;
		}
		
		auto time2 = GameState::mainGameClock->checkTimeElapsed() ;
		auto timeElapsed = time2 - startTime ;
		auto sleepTime = (refreshTime - timeElapsed) ;
		
		mainGameLoopCount++ ;
		
		this_thread::sleep_for(sleepTime) ;
		
		if (mainGameLoopCount > worldLoopCount) {
			unique_lock<mutex> locked(mainThreadsSync) ;
			
			shared_conditional.wait(locked) ;
		}

		shared_conditional.notify_all() ;
	}

	/* exit signaled GLOBAL_CONTINUE_FLAG. We're outta here! Handing off to MainControl::exit() */
}

void MainControl::exitmc(int sig) {
	
    GLOBAL_CONTINUE_FLAG = false ;
    /* other signals to define false here? */
        
    TextOutput<float, int>::exit() ; /* quits() sdl_ttf */
    GraphicalOutput::exit() ;
    WorldControl::exit() ;
    InputControl::exit() ;
	
		
    SDL_Quit() ; /* Call this only making all calls to SDL_QuitSubSystem() */
	
    GameState::mainGameClock->stopTimer() ;

	
	exit(sig) ;
	
	/* And we're done! Returning now... */
}



