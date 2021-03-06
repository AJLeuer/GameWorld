//
//  Util.h
//  World
//
//  Created by Adam James Leuer on 3/20/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef SpriteFight_Util_h
#define SpriteFight_Util_h


#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
#include <cstddef>
#include <codecvt>
#include <optional>

#include <SDL2/SDL_rect.h>

using namespace std ;

namespace Util {

typedef uint8_t byte ;

static constexpr long double 𝜋 = 3.14159265358979323846L;

/**
 * Used to avoid ambiguity when calling various constructors
 * with integral values that might be confused for boolean
 */
enum class SafeBoolean : bool {
	t = true,
	f = false
};

template<typename N>
constexpr static bool checkIfFloatingPointType() {
	if (typeid(N) == typeid(long double)) {
		return true ;
	}
	if (typeid(N) == typeid(double)) {
		return true ;
	}
	if (typeid(N) == typeid(float)) {
		return true ;
	}
	else {
		return false ;
	}
}

static constexpr const double huge = 1.0e300 ;

template <typename N>
inline constexpr N computeFloor(N x) {
	if (x >= 0.0f)
	{
		auto ret = (N)((int)x) ;
		return ret ;
	}
	else
	{
		auto ret = (N)((int)x - 1);
		return ret ;
	}
}


/*
 * Code partial credit stackoverflow: http://stackoverflow.com/questions/4633177/c-how-to-wrap-a-float-to-the-interval-pi-pi
 * todo: reimplement
 */
template<typename M, typename N>
constexpr double Mod(M x_in, N y_in) {
	
	double x = static_cast<double>(x_in) ; /* x is ok */
	
	double y = static_cast<double>(y_in) ;

	static_assert(!std::numeric_limits<M>::is_exact , "Mod: floating-point type expected");
	static_assert(!std::numeric_limits<N>::is_exact , "Mod: floating-point type expected");
	
	if (0. == y)
		return x;
	
	double m = x - (y * computeFloor<double>(x/y)) ;
	
	// handle boundary cases resulted from floating-point cut off:
	
	if (y > 0)              // modulo range: [0..y)
	{
		if (m>=y)           // Mod(-1e-16             , 360.    ): m= 360.
			return 0;
		
		if (m<0 )
		{
			if (y+m == y)
				return 0  ; // just in case...
			else
				return y+m; // Mod(106.81415022205296 , _TWO_PI ): m= -1.421e-14
		}
	}
	else                    // modulo range: (y..0]
	{
		if (m<=y)           // Mod(1e-16              , -360.   ): m= -360.
			return 0;
		
		if (m>0 )
		{
			if (y+m == y)
				return 0  ; // just in case...
			else
				return y+m; // Mod(-106.81415022205296, -_TWO_PI): m= 1.421e-14
		}
	}
	
	return m;
}

/**
 * @param first The first value to average
 * @param second The second value to average
 *
 * @return The average of the two values
 */
template<typename N>
N average(N first, N second) {
	N sum = (first + second) ;
	double result = (static_cast<double>(sum) / static_cast<double>(2)) ;
	return static_cast<N>(result) ;
}

template<typename N>
N average(const vector<N> & numbers) {
	unsigned i = 0 ;
	N sum = 0 ;
	while(i < numbers.size()) {
		sum += numbers.at(i) ;
		i++ ;
	}
	N result = sum/i ;
	return result ;
}

template<typename T, template <typename, typename = std::allocator<T>> class Container>
T sumElements(const Container<T, std::allocator<T>> & cont) {
    
    T sum ;
    auto i = cont.begin() ;
    sum = *i ;
    
    for (i++ ; i != cont.end() ; i++) {
        sum += *i ;
    }
    
    return sum ;
}


template<typename N>
N setUnsigned(N n) {
	if (n < 0) {
		n = (n * -1) ;
	}
	return n ;
}

template<typename N>
N difference(N n0, N n1) {
	N saveSign = n1 / (setUnsigned(n1)) ;
	n1 = setUnsigned(n1) ;
}


template<typename T>
T pythag(T a, T b) {
	return sqrt((pow(a,2)) + (pow(b,2))) ;
}

inline float sinNeg(float n) {
	return (-1 * (sin(n))) ;
}
    
template <typename T, typename _Allocator, template<typename, typename> typename Container>
bool contains(Container<T, _Allocator> & container, T object) {
	if(container.size() == 0) {
		return false;
	}
	
    for (auto element : container) {
        if (element == object) {
            return true;
        }
    }
	
    return false;
}
	
template <typename T, typename Container>
bool contains(Container & container, T object) {
	if(container.size() == 0) {
		return false;
	}
	
    auto result = std::find(container.begin(), container.end(), object);

    if (result == (std::end(container))) {
        return false;
    }
	
    return true;
}

template<typename T>
T findSmallest_helper(unsigned long currSmallest, vector<T> cont) {
	//vector<T*> smallerElem = vector<T*>() ;
	auto size = cont.size() ;
	
	for (auto i = 0 ; i != cont.size() ; i++) {
		
		if (size == 1) {
			return cont.at(currSmallest) ;
		}
		if (cont.at(i) < cont.at(currSmallest)) {
			currSmallest = i ;
			size-- ;
		}
	}
	return cont.at(currSmallest) ;
}

template<typename T>
T findSmallest(vector<T> cont) {
	return findSmallest_helper(0, cont) ;
}

template<typename T>
T findLargest_helper(unsigned long currLargest, vector<T> cont) {
	auto size = cont.size() ;
	
	for (auto i = 0 ; i != cont.size() ; i++) {
		
		if (size == 1) {
			return cont.at(currLargest) ;
		}
		if (cont.at(i) > cont.at(currLargest)) {
			currLargest = i ;
			size-- ;
		}
	}
	return cont.at(currLargest) ;
}

template<typename T>
T findLargest(vector<T> cont) {
	return findLargest_helper(0, cont) ;
}

template<typename N>
N ceilling(N n1, N n2) {
	if (n1 >= n2) {
		return n1 ;
	}
	else {
		return n2 ;
	}
}

template<typename N>
N floor(N n1, N n2) {
	if (n1 <= n2) {
		return n1 ;
	}
	else {
		return n2 ;
	}
}


/**
 * Rounds a float or double to an int or long
 */
template<typename F = float, typename I = int> // F = some float or double, I = some unsigned, int, long, etc
I roundF(F value) {
    if ((typeid(F) == typeid(unsigned)) || (typeid(F) == typeid(int)) || (typeid(F) == typeid(long)))  {
        return value ;
    }
    else {
        F temp = (value >= 0.0f) ? (std::floor(value + 0.5f)) : (std::ceil(value - 0.5f)) ;
        I round = static_cast<I>(temp) ;

		/* catch a weird problem where this was returning a negative value from a posititive input */
		if ((value >= 0) && (round < 0)) {
			round = (round * -1) ;
		}
		
        return round ;
    }
}

template<typename I = int, class FloatPosition>
FloatPosition roundF(FloatPosition & pos) {
    if ((typeid(pos.x) == typeid(unsigned)) || (typeid(pos.x) == typeid(int)) || (typeid(pos.x) == typeid(long)))  {
        return pos ;
    }
    else {
        I tempX = roundFI(pos.getX()) ;
        I tempY = roundFI(pos.getY()) ;
        I tempZ = roundFI(pos.getZ()) ;
        return FloatPosition(tempX, tempY, tempZ) ;
    }
}



template<typename I = int, class FloatPosition>
FloatPosition roundF(FloatPosition * pos) {
    if ((typeid(pos->x) == typeid(unsigned)) || (typeid(pos->x) == typeid(int)) || (typeid(pos->x) == typeid(long)))  {
        return pos ;
    }
    else {
        I tempX = roundFI(pos->getX()) ;
        I tempY = roundFI(pos->getY()) ;
        I tempZ = roundFI(pos->getZ()) ;
        return FloatPosition(tempX, tempY, tempZ) ;
    }
}

template<typename I = int, class FloatPosition>
FloatPosition * roundF(FloatPosition * pos) {
    if ((typeid(pos->x) == typeid(unsigned)) || (typeid(pos->x) == typeid(int)) || (typeid(pos->x) == typeid(long)))  {
        return pos ;
    }
    else {
        I tempX = roundFI(pos->getX()) ;
        I tempY = roundFI(pos->getY()) ;
        I tempZ = roundFI(pos->getZ()) ;
        return new FloatPosition(tempX, tempY, tempZ) ;
    }
}

template<typename N>
SDL_Rect & operator*(N n, SDL_Rect & rhs) {
	rhs.w = n * rhs.w ;
	rhs.h = n * rhs.h ;
	return rhs ;
}

template<class vec3, class vec2>
SDL_Rect convertToSDL_Rect(const vec3 position, const vec2 size) {

	SDL_Rect shape ;
	shape.x = roundF(position.getX()) ;
	shape.y = roundF(position.getY()) ;

	shape.w = roundF(size.getWidth()) ;
	shape.h = roundF(size.getHeight()) ;

	return shape ;
}

template<typename Radians = double>
double convertToDegrees(const Radians angle_rad) {
	double angle_in_radians = static_cast<double>(angle_rad) ;
	double angle_in_degrees = angle_in_radians * (180.0L / 𝜋) ;
	return angle_in_degrees ;
}

template<typename Degrees = double>
double convertToRadians(const Degrees angle_deg) {
	double angle_in_degrees = static_cast<double>(angle_deg) ;
	double angle_in_radians = angle_in_degrees / (180.0L / 𝜋) ;
	return angle_in_radians ;
}




inline unsigned termWidth() {
	unsigned r = atoi(getenv("COLUMNS")) ;
	return r ;
}

inline unsigned termHeight() {
	unsigned r = atoi(getenv("LINES")) ;
	return r ;
}

/**
 * Overloads operator + for std::string to allow
 * appending any type T
 *
 * @param rhs The text to append
 */
template<class T>
string operator+(const string & str, const T & rhs) {
	string app = to_string(rhs) ;
	string ret = str ;
	ret += app ;
	return ret ;
}

inline string operator +(const string & str, const char * rhs) {
	string app(rhs) ;
	string ret = str ;
	ret += app ;
	return ret ;
}

/**
 * Code credit StackOverflow
 *
 * @see <a href="https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string">StackOverflow</a>
 */
static optional<wstring> convertToWideString(const string & str) {
	try
	{
		std::wstring wstr = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(str);
		return wstr;
	}
	catch (std::exception & exception)
	{
		return std::nullopt;
	}
}
	
/**
 * Code credit StackOverflow
 *
 * @see <a href="https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string">StackOverflow</a>
 */
static optional<string> convertToString(const wstring & wideString) {
	try
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
		std::string str = converter.to_bytes(wideString);
		return str;
	}
	catch (std::exception & exception)
	{
		return std::nullopt;
	}
}

/**
 * Takes a container holding pointer values as an argument, and an 
 * additional new container (ideally empty), and copies values from old to new, only it
 * ignores all null pointer values in the old container
 *
 * @param oldContainer A container holding pointer values
 *
 * @ return New container with all the non-null values from old
 */
template <template <typename, typename> class Container,
typename Pointer,
typename Allocator = std::allocator<Pointer> >

Container<Pointer, Allocator> * copyWithoutNullValues(Container<Pointer, Allocator> * oldContainer, Container<Pointer, Allocator> * newContainer) {

	for (auto iterator = oldContainer->begin() ; iterator != oldContainer->end() ; iterator++) {
		
		if ((* iterator) != nullptr) {
			newContainer->push_back( * iterator) ;
		}
	}
	
	return newContainer ;
}


/* powerup. other */
extern char * basicAlphabet ;

const string generateName(unsigned int length) ;


}


#endif
