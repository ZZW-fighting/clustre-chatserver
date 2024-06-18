#ifndef USERMODEL_H
#define USERMODEL_H
#include<user.hpp>
class Usermodel
{
public:
    bool insert(User &user);

    User query(int id);

    bool updateState(User &user);

    void resetstate();
};

#endif