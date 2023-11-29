#include "point.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>

namespace point_template{
    template <typename T, int8_t dim>
    Point<T, dim>::Point() {
        std::srand(std::time(0));
        for (int8_t i = 0; i < dim; ++i){
            this->coords[i] = std::rand()/RAND_MAX * 2000000.00;
        }
    }

    template <typename T, int8_t dim>
    Point<T, dim>::Point(T newCoords[dim]) {
        for(int8_t i = 0; i < dim; ++i){
            this->coords[i] = newCoords[i];
        }
    }

    template <typename T, int8_t dim>
    T Point<T, dim>::operator[](int8_t dimCoord) const{
        assert((dimCoord >= 0 && dimCoord < dim));
        return this->coords[dimCoord];
    }

    template <typename T, int8_t dim>
    T& Point<T, dim>::operator[](int8_t dimCoord) {
        assert(dimCoord >= 0 && dimCoord < dim);
        return this->coords[dimCoord];
    }

    template <typename T, int8_t dim>
    T Point<T, dim>::distanceToOrigin() const {
        T sqrSum = 0;
        for(int8_t i = 0; i < dim; ++i){
            sqrSum += this->coord[i]*this->coords[i];
        }
        return std::sqrt(static_cast<float>(sqrSum));
    }

    template <typename T, int8_t dim>
    T Point<T, dim>::distanceFromPoint(Point& next) const {
        T sqrSum = 0;
        for(int8_t i = 0; i < dim; ++i){
            sqrSum += (this->coord[i]*this->coords[i]) - (next[i]*next[i]);
        }
        return std::sqrt(static_cast<float>(sqrSum));
    }

    template <typename T, int8_t dim>
    bool Point<T, dim>::operator==(Point& p2) const {
        return (static_cast<float>(this->distanceFromPoint(p2) < 0.000001));
    }

    template <typename T, int8_t dim>
    std::ostream& operator<<(std::ostream& output, const Point<T, dim> &p) {
        output << "(";
        for(int8_t i = 0; i < dim - 1; ++i){
            output << "dim[" << i << "]" << p[i] << ", ";
        }
        output << p[dim - 1] << ")";
        return output;
    }
}

