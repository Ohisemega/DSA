#include "point.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

template <typename T>
Point<T>::Point(){
    std::srand(std::time(0));
    this->_x = std::rand()/RAND_MAX * 2000000000.00;
    this->_y = std::rand()/RAND_MAX * 2000000000.00;
}

template <typename T>
Point<T>::Point(T x, T y) : _x{x}, _y{y}{

}

template <typename T>
T Point<T>::getX() const{
    return this->_x;
}

template <typename T>
T Point<T>::getY() const{
    return this->_y;
}

template <typename T>
T Point<T>::distanceToOrigin() const{
    return std::sqrt(std::pow(this->_x, 2) + std::pow(this->y, 2));
}

template <typename T>
T Point<T>::distanceFromPoint(Point& next) const{
    return std::sqrt(std::pow(this->_x - next._x, 2) + std::pow(this->y - next._y, 2));
}

template <typename T>
bool Point<T>::operator==(Point& p2) const{
    return (this->distanceFromPoint(p2) < 0.000001);
}
template <typename T>
std::ostream& operator<<(std::ostream& output, const Point<T> &p) {
    output << "x: " << p._x << "y: " << p._y << "\n";

    return output;
}