#ifndef POINT_HPP
#define POINT_HPP

template <typename dataT>
class Point{
    public:
        Point();
        Point(dataT x_, dataT y_);
        dataT distanceToOrigin() const;
        dataT distanceFromPoint(Point& p2) const;

    private:
        dataT _x, _y;
};

#endif