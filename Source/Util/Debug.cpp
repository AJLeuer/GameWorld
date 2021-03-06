//
//  Debug.cpp
//  World
//
//  Created by Adam James Leuer on 4/6/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Debug.h"

using namespace std ;


unsigned Debug::debugCounter = 0 ;

Debug * Debug::debugOutput = nullptr ;

void Debug::init() {
	if (debugToSTDOutput) {
		debugOutput = new Debug(&cout) ;
	}
	else {
		debugOutput = new Debug(new ofstream("Debug.txt")) ;
	}
}