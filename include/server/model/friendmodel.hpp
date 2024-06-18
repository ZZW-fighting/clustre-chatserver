#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H
#include"db.hpp"
#include"user.hpp"
#include<iostream>
#include<vector>
using namespace std;

class friendModel
{
public:
    //存储用户的离线消息
    bool insert(int userid, int friendid);

    //删除用户的离线消息
    void remove(int userid);

    //查询用户的离线消息
    vector<User> query(int userid);

};




#endif