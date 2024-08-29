#ifndef SQUARE_HPP
#define SQUARE_HPP

class Square {
private:
    int x; 
    int y; 

public:
    Square(int x, int y); 
    void changePosition(int newX, int newY);
    Square();
};

#endif 