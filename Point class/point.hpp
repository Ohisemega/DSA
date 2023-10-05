#ifndef POINT_HPP
#define POINT_HPP

#include <string>
template <typename dataT>
class Point{
    template <typename T>
    friend std::ostream& operator<<(std::ostream& out, const Point<T>& p);
    public:
        Point();
        Point(dataT x_, dataT y_);
        dataT getX() const;
        dataT getY() const;
        dataT distanceToOrigin() const;
        dataT distanceFromPoint(Point& p2) const;
        bool operator==(Point& p2) const;

    private:
        dataT _x, _y;
};


#endif