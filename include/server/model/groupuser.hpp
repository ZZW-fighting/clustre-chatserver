#ifndef GROUPUSER_H
#define GROUPUSER_H
#include"user.hpp"

class Groupuser :public User
{
public:
    void setRole(string role){this->role = role;}
    string getRole(){return this->role;}

private:
    string  role;
};

#endif