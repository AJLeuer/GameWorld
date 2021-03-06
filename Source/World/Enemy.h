//
//  Enemy.h
//  World
//
//  Created by aleuer2 on 6/3/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __SpriteFight__Enemy__
#define __SpriteFight__Enemy__

#include <iostream>

#include "NPC.h"

class Enemy : public NPC {
  

public:
    
    
    Enemy() : NPC() {}
	
	Enemy(const AssetFile & imageFile, float size, const Vect<float> & loc, const Angle rotation, string name,
		  unsigned health, unsigned damage, Util::SafeBoolean monitorVelocity, bool boundsChecking) :
	
		  NPC(imageFile, size, loc, rotation, name, health, damage, monitorVelocity, boundsChecking) {}
    
    virtual void doDefaultBehavior(bool initialCall = false) override ;
    
    
    
} ;

#endif /* defined(__SpriteFight__Enemy__) */
