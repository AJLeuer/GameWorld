//
//  MainController.h
//  GameWorld
//
//  Created by Adam James Leuer on 4/16/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __GameWorld__MainController__
#define __GameWorld__MainController__

#include <iostream>

#include "../Util/Debug.h"
#include "../Output/AdapterInterface.hpp"
#include "../Output/Adapter.hpp"
#include "../Output/TestAdapter.hpp"
#include "../Util/Time.h"
#include "WorldController.h"

#endif /* defined(__GameWorld__MainController__) */


class MainController {
	
private:
	static AdapterInterface<GameObject> * currentAdapter ;
	
	
public:
	
	static void start(bool * b) ;
	static void stop(bool * b) ;
} ;