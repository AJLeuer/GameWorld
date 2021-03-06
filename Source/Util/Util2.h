//
//  Util2.h
//  World
//
//  Created by Adam James Leuer on 5/23/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __SpriteFight__Util2__
#define __SpriteFight__Util2__

#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <cmath>

#include "Util.hpp"
#include "Vect.hpp"
#include "Size.hpp"

#include "../World/GameState.hpp"

#include "../Control/Configuration.h"

/* Creating a second header for utility functions since we ran into some trouble 
   with includes */
template<typename M, typename N>
Size<N> & operator * (M m, Size<N> & rhs) {
	rhs.setW((m * rhs.getW())) ;
	rhs.setH((m * rhs.getH())) ;
	return rhs ;
}

template<typename M, typename N>
Vect<N> * convert(const Vect<M> * converted) {
    return new Vect<N>(Util::roundF<M, N>(converted->getX()), Util::roundF<M, N>(converted->getY()), Util::roundF<M, N>(converted->getZ())) ;
}

/**
 * This function translates between coordinate systems.
 */
template<typename N>
Vect<N> translateToWindowCoords(const Vect<N> & worldCoords) {
	
	Vect<N> origin = getWindowOriginAsWorldCoord<N>() ;
	
	auto windowCoords = translateCoords(worldCoords, {0, 0}, origin) ;
	
	return windowCoords ;
}

/**
 * Translates the Vect coords from a source coordinate system to coordinates
 * in the destination coordinate system. To work properly, this function an additonal
 * pair of coordinates: first coordinates from the source coordinate system, followed by
 * equivalent coordinates from the destination coordinate system. "Equivalent" implies that if these two
 * coordinate systems were overlaid one on top of the other, then these two coordinates would be
 * in the same spot. The simplest way to do this is to simply give the origin ({0, 0, 0}) from the source
 * coordinate system, and its equivalent from the destination coordinate system.
 *
 * @param coords The coordinate to translate
 * @param sourceCoords Sample coordinates from the source coordinate system
 * @param equivalentDestinationCoords Coordinates from the destination coordinate system that are equivalent to sourceCoords
 */
template<typename N>
Vect<N> translateCoords(const Vect<N> & coords, const Vect<N> & sourceCoords, const Vect<N> & equivalentDestinationCoords) {
	
	/* using a position to store, not an actual position, but the difference between a position from the source coordinate system and
	 a position from the destination coordinate system (i.e. a vector) */
	auto differential = sourceCoords - equivalentDestinationCoords ;
	
	auto coordsAsDestCoordSystemCoords = (coords + differential) ;
	
	return coordsAsDestCoordSystemCoords ;
}

/**
 * An implementation of the formula for finding the distance between two points
 * in Euclidian space, as given at http://en.wikipedia.org/wiki/Euclidean_distance
 *
 * @param p The first point
 * @param q The second point
 */
template<typename N>
N calcEuclidianDistance(const Vect<N> & p, const Vect<N> & q) {
    auto sum = pow<N>((q.getX() - p.getX()), 2) + pow<N>((q.getY() - p.getY()), 2) ;
    auto sqRoot = sqrt(sum) ;
    return sqRoot ;
}









#endif /* defined(__SpriteFight__Util2__) */
