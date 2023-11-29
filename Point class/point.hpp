#ifndef POINT_HPP
#define POINT_HPP
namespace point_template{
    #include <string.h>
    template <typename dataT, int8_t dim>
    class Point{
        template <typename T>
        inline friend std::ostream& operator<<(std::ostream& out, const Point<T, dim>& p);
        public:
            Point();
            Point(dataT newCoords[dim]);
            dataT operator[](int8_t coord) const;
            dataT& operator[](int8_t coord);
            dataT distanceToOrigin() const;
            dataT distanceFromPoint(Point& p2) const;
            bool operator==(Point& p2) const;

        private:
            dataT coords[dim];
    };
}
#include "point.tpp"
#endif