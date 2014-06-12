//
//  Configuration.h
//  GameWorld
//
//  Created by Adam James Leuer on 5/25/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __GameWorld__Configuration__
#define __GameWorld__Configuration__

#include <iostream>
#include <fstream>

#include "DefaultConfig.h"


using namespace std ;

/**
 * This class will mainly be used for overriding default settings,
 * usually based on some form of user input. 
 */
class Configuration {

private:

	static ifstream configFile ;
    
    static void doOverrides() ;

public:
    
    static void init() ;

	template <class Value>
	static Value getValue(string key) ;

	template <class Value>
	static void writeValue(string key, Value value) ;

} ;

template <class Value>
Value Configuration::getValue(string key) {
    //todo
}

template <class Value>
void Configuration::writeValue(string key, Value value) {
    //todo
}






#endif /* defined(__GameWorld__Configuration__) */
