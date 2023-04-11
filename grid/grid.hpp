#include "Point/point.hpp"

#ifndef GRID_H
#define GRID_H

class Node{
  public:
    Node(Point pt, Node* t): p{pt}, next{t}{
    }
    Point p;
    Node* next;
};
typedef Node* link;

class Grid{
  public:
    Grid(float dist);
    ~Grid();
    void gridInsert(Point& p);
    unsigned int generateRandomPoints(unsigned int N);

  private:
    template <typename Q, typename R>
    Q** malloc2D(R r, R c);

    template <typename S, typename T>
    void delete2D(S** g, T r, T c);

    void setDistance(float dist);

    unsigned int cnt;
    unsigned int d;
    static link** grid;
    unsigned int gSize;
};


//2D array malloc allocation 
template <typename Q, typename R>
Q** Grid::malloc2D(R r, R c){
  Q** a = new Q*[r];
  for(R i = 0; i < r; ++i)
    a[i] = new Q[c];
  return a;
}

//2D array malloc allocation 
template <typename S, typename T>
void Grid::delete2D(S** grid, T r, T c){
  S** a = grid;
  for(T i = 0; i < r; ++i){
    delete [] a[i];
    a[i] = nullptr;
  }
  delete [] a;
  a = grid = nullptr;
}

#endif