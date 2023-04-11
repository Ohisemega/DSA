#include "grid.hpp"
#include <stdexcept>
#include <iostream>

link** Grid::grid = nullptr;

void Grid::setDistance(float dist){
	if(dist < 1 && dist >= 0){
		this->d = dist;
		this->gSize = (1.0/dist) + 1;
	}else{
		throw std::invalid_argument("Distance is either not positive or greater than 1!");
	}
}

Grid::Grid(float dist){
	setDistance(dist);
	this->gSize = (1.0/dist) + 1.0;
	grid = Grid::malloc2D<Node*>(gSize + 2, gSize + 2);
}

Grid::~Grid(){
	Grid::delete2D<Node*>(this->grid, gSize + 2, gSize + 2);
}

void Grid::gridInsert(Point& p){
	std::cout << "This is the value of x and y: " << p.getXcord() << ", " << p.getYcord() << "\n";
  	int X = (p.getXcord()*static_cast<float>(gSize)) + 1.0;
  	int Y = (p.getYcord()*static_cast<float>(gSize)) + 1.0;
  	std::cout << "This is the value of X and Y: " << X << ", " << Y << "\n";
  	Node* s;
  	Node* t = new Node(p, grid[X][Y]);
  	for(int i = X - 1; i <= X+1; ++i){
    	for(int j = Y - 1; j <= Y+1; ++j){
      		std::cout << "the link is: " << i << ", " << j << ": ";
      		for(s = grid[i][j]; s != nullptr; s = s->next){
        		std::cout << (s->p).getXcord() << ", " << (s->p).getYcord() << "-->";
        		if(Point::distance(s->p, t->p) < d) ++cnt;
      		}
      	std::cout << "nullptr\n";
    	}
  	}
  	grid[X][Y] = t;
}

unsigned int Grid::generateRandomPoints(unsigned int N){
	this->cnt = 0;
	for(int i = 0; i < N; ++i){
		Point p = Point();
		gridInsert(p);
	}
	return this->cnt;
}


