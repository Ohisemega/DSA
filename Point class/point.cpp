#include "point.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

template <typename T>
Point<T>::Point(){
    std::srand(std::time(0));
    this->_x = std::rand()/RAND_MAX * 20000;
    this->_y = std::rand()/RAND_MAX * 20000;
}

template <typename T>
Point<T>::Point(T x, T y){
    this->_x{x};
    this->_y{y};
}

template <typename T>
T Point<T>::distanceToOrigin() const{
    return std::sqrt(std::pow(this->_x, 2) + std::pow(this->y, 2));
}

template <typename T>
T Point<T>::distanceFromPoint(Point& next) const{
    return std::sqrt(std::pow(this->_x - next._x, 2) + std::pow(this->y - next._y, 2));
}