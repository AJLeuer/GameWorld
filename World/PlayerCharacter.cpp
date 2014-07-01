//
//  PlayerCharacter.cpp
//  SpriteFight
//
//  Created by aleuer2 on 6/30/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "PlayerCharacter.h"

/**
 * Constructs a default PlayerCharacter.
 */
PlayerCharacter::PlayerCharacter() :
    Character() {}


/**
 * Copy constructor for PlayerCharacter
 *
 * @param The PlayerCharacter to be copied
 */
PlayerCharacter::PlayerCharacter(const PlayerCharacter & other) :
    Character(other) {}

/**
 * Move constructor for PlayerCharacter
 *
 * @param The PlayerCharacter to be moved
 */
PlayerCharacter::PlayerCharacter(PlayerCharacter && other) :
    Character(other) {}

/**
 * Constructs a PlayerCharacter based on the arguments given
 *
 * @param name The name of this PlayerCharacter
 * @param alive Whether this PlayerCharacter is dead or alive
 * @param state The CharacterState of this PlayerCharacter
 * @param health The Health of this PlayerCharacter
 * @param damage The Damage capability of this PlayerCharacter
 */
PlayerCharacter(AssetType type, const string & imageFilename, float size, const Pos2<float> & loc, string name, Reaction reaction, DoA alive, CharacterState state, unsigned health, unsigned damage) :
    Character(type, imageFilename, size, loc, name, reaction, alive, state, health, damage) {}


/**
 * Constructs a randomized PlayerCharacter. The client has to option to simply leave the argument randSeed as
 * 0, in which case the constructor will generate its own random number.
 *
 * @param randSeed A seed to initialize the random number generator
 */
PlayerCharacter(FastRand<int> rand) :
    Character(rand) {}


/**
 * Destructor for PlayerCharacter
 */
~PlayerCharacter() {}


/**
 * Assignment operator overload (copy)
 *
 * @param rhs The right hand side argument (which will be copied)
 */
PlayerCharacter & operator=(const PlayerCharacter & rhs) {
    if (this != &rhs) {
        this->Character::operator=(other) ;
    }
    return *this ;
    
}

/**
 * Assignment operator overload (move)
 *
 * @param rhs The right hand side argument (which will be moved)
 */
PlayerCharacter & operator=(PlayerCharacter && rhs) {
    if (this != &rhs) {
        this->Character::operator=(std::move(other)) ;
    }
    return *this ;
}


/**
 * Overloads operator() for PlayerCharacter. Possibly will be used to
 * call notify(). TBD.
 */
void operator()() {
    //todo
}


/**
 * Overloads the overload of operator(). The actual implementation
 * and uses for this are still undecided.
 *
 * @param otherCharacter A reference to another PlayerCharacter
 */
void operator()(GameObject * other) {
    //todo
}


/**
 * Writes a formatted text description of this PlayerCharacter into the desired output stream
 */
void textDescription(ostream * writeTo) const {
    this->Character::textDescription(writeTo) ;
}

//using GameObject's implementation for now, may change later
void defaultBehaviors() {
    //todo
}

/**
 * Attacks a hostile PlayerCharacter
 *
 * @param enemy The enemy to attack
 */
void attack(PlayerCharacter * enemy) {
    //todo
}
