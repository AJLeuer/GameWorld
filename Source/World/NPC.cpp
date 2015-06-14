//
//  NPC.cpp
//  World
//
//  Created by Adam James Leuer on 3/11/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//


#include "NPC.h"

NPC::NPC() :
	Character() {}

NPC::NPC(const NPC & other) :
	Character(other) {}

NPC::NPC(NPC && other) :
	Character(std::move(other)) {}

NPC::NPC(const AssetFile & imageFile, float size, const Vect<float> & loc, const Angle rotation,
		 string name, DoA alive, CharacterState state, unsigned health, unsigned damage, SafeBoolean monitorVelocity, bool boundsChecking,
		 Reaction reaction) :

	Character(imageFile, size, loc, rotation, name, reaction, alive, state, health, damage, monitorVelocity, boundsChecking) {}

NPC::NPC(Randm<int> rand, AssetType type) :
	Character(rand, type)
{
	this->reaction = Reaction(rand() % 5) ;
	//todo finish
}

NPC::~NPC() {
	//todo
}

void NPC::operator()() {
	//todo
}

void NPC::operator()(Character & other) {
	*(Debug::debugOutput) << "" << endl ;//todo
}

void NPC::notify() {
	//todo
}

void NPC::passMessage(Message * message, GameObject & recipient) {
	//todo
}

void NPC::textDescription(ostream * writeTo) const {
	stringstream ss ;
	this->Character::textDescription(&ss) ;
	ss << "Reaction to player: " << this->reaction << endl ;
	*writeTo << ss.rdbuf() ;
}

void NPC::attack(GameObject * enemy) {
	//todo
}




