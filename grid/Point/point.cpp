#include "point.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

//2D array malloc allocation 
template <typename Q, typename R>
Q** malloc2D(R r, R c){
	Q** a = new Q*[r];
  	for(int i = 0; i < r; ++i)
    	a[i] = new Q[c];
  	return a;
}


Point::Point() {
	std::srand(std::time(0));
	x = randFloatCord();
	y = randFloatCord();
}

Point::Point(float xp, float yp) : x{xp}, y{yp}{ //empty
}

Point::~Point(){
}

float Point::distance(const Point& a, const Point& b){
	return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

float Point::distFrmOrg() const{
	return std::sqrt(std::pow(this->x - 0, 2) + std::pow(this->y - 0, 2));
}

float Point::getXcord() const{
	return this->x;
}

float Point::getYcord() const{
	return this->y;
}

float Point::randFloatCord() const{
	return static_cast<float>(1.0 * rand())/RAND_MAX;
}
