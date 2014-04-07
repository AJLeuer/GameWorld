//
//  TestAdapter.cpp
//  GameWorld
//
//  Created by Adam James Leuer on 3/19/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "TestAdapter.h"

void TestAdapter::init() {
	this->AdapterInterface::init() ;
	
	//local initializations:
}

void TestAdapter::show() {
	 aiThread = new std::thread(&TestAdapter::show_threaded, std::move(this)) ;
}

void TestAdapter::show_threaded() {
	while (World::isRunning()) {
		GameObject * temp  = nullptr ;
		for (auto i = 0 ; i < (*WorldObjects)->size() ; i++) {
			if (World::isRunning()) {
				World::runningMtx.lock() ;
				if (*WorldObjects != nullptr) {
					temp = (*WorldObjects)->at(i) ;
					cout << "Current GameObject: " ;
					cout << *temp ;
					Location trans = AdapterUtil::transLocation(*(temp->getLocation())) ;
					cout << "Tranlated location: " ;
					cout << trans.toString() << endl ;
					cout << temp->getIcon().c_str() << endl << endl ;
					temp = nullptr ;
				}
				World::runningMtx.unlock() ;
			}
		}
	}
}

void TestAdapter::operator()() {
	this->show() ;
}

void TestAdapter::close() {
	this->AdapterInterface::close() ;
	
	//local cleanup:
	
}
