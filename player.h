#ifndef PLAYER_H_
#define PLAYER_H_
#include <memory>
#include <vector>
#include <string>
#include <iostream>
//Low coupling
//The Class is only responsible for player turns and moving
class Board;
class Player{
    std::string colour;
    public:
        Player(std::string colour);
        std::string getColour();
        virtual void move(std::istream &in, std::ostream &out, Board &mainBoard, int& curTurn) = 0;
        virtual ~Player() = default;
};
class Human : public Player{
    
    public:
    Human(std::string colour);
    void move(std::istream &in, std::ostream &out, Board &mainBoard, int& curTurn) override;
};
class Computer1 : public Player{
    
    public:
    Computer1(std::string colour);
    void move(std::istream &in, std::ostream &out, Board &mainBoard, int& curTurn) override;
};
class Computer2 : public Player{
    
    public:
    Computer2(std::string colour);
    void move(std::istream &in, std::ostream &out, Board &mainBoard, int& curTurn) override;
};
class Computer3 : public Player{
    
    public:
    Computer3(std::string colour);
    void move(std::istream &in, std::ostream &out, Board &mainBoard, int& curTurn) override;
};
#endif
