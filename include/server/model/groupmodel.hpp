#ifndef GROUPMODEL_H
#define GROUPMODEL_H
#include"group.hpp"
#include"db.hpp"
#include<string>
#include<string.h>
#include<vector>
using namespace std;

class GroupModel
{
public:
    //创建群组
    bool createGroup(Group &group);

    //加入群组
    void addGroup(int userid, int groupid, string role);

    //查询用户所在群组的信息
    vector<Group> qureyGroups(int userid);

    //根据指定的groupid查询群组用户id列表，用于群聊
    vector<int> qureyGroupUsers(int userid, int groupid);
};

#endif