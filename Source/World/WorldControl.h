//
//  WorldControl.h
//  World
//
//  Created by Adam James Leuer on 3/11/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __SpriteFight__WorldController__
#define __SpriteFight__WorldController__

#include <unistd.h>

#include <iostream>
#include <ostream>
#include <vector>
#include <thread>
#include <mutex>     
#include <condition_variable>

#include "../Util/Debug.h"
#include "../Util/Util.hpp"
#include "../Util/Vect.hpp"
#include "../Util/Random.hpp"
#include "../Util/Timer.hpp"

#include "GameState.hpp"
#include "GameMap.hpp"
#include "GameInterface.h"
#include "GameEvent.h"
#include "Ability.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Pawn.h"
#include "NPC.h"

#include "../Control/Configuration.h"



using namespace std ;

/**
 * The class controlling the world managing all the objects within it.
 * It is generally responsible for managing everything that happens within the scope of a game. 
 * It holds all the GameObjects, mediates their interactions when neccessary (more or less, in many
 * cases they interact directly), handles output of the game state (whether that means realtime or recorded.
 * rendered or printed. etc. - it was designed to be flexible and extensible), and handles initialization and
 * clean up. It is essentially all static should be treated as a singleton object: don't try to create instances
 * of it. Rather call init() once at the beginning, and end the game program with exit().
 */
class WorldControl {
	
protected:
	
	//static vector<GameObject*> * allGameObjects ;

	static thread worldEventThread ;
	
	friend class MainControl ;
	friend class GameInterface ;
	friend class GameObject ;
	
	static void main() ;
	
	static void main_forwardTime() ;
	static void main_reverseTime() ;
	
	WorldControl() ;
	
	/* can umcomment this later if we end up needing it */
	//static void update() ;
	
public:
	
	/**
	 * Holds pointers to GameObjects like gameObjects, but is 2D and the placement of each GameObject in map
	 * corresponds to the x and y coordinate of its Vect. Is synced with GameObjects's map.
	 */
	static const GameMap<GameObject> * map ;
	
	static void init() ;
	
	static void begin_main() ;
	
	static void exit() ;
	
} ;

#endif /* defined(__SpriteFight__WorldController__) */
