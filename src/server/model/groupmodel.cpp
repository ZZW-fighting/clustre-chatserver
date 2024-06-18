#include"groupmodel.hpp"

//创建群组
bool GroupModel::createGroup(Group &group)
{
    // 1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into allgroup(groupname, groupdesc) values('%s', '%s')", group.getName().c_str(), group.getDesc().c_str());
    MySQL mysql;
    if (mysql.connect())
    {
        if(mysql.update(sql))
        {
            group.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
        
    }
    return false;

}

//加入群组
void GroupModel::addGroup(int userid, int groupid, string role)
{
    // 1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into groupuser(userid, groupid, role) values(%d, %d, '%s')", userid, groupid, role.c_str());
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

//查询用户所在群组的信息
vector<Group> GroupModel::qureyGroups(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "select a.id,a.groupname,a.groupdesc b.grouprole from allgroup a inner join groupuser b on b.groupid = a.id where b.userid = %d", userid); //多表查询，查询friend的id,name,state
    MySQL mysql;
    vector<Group> vec;
    if(mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if(res != nullptr)
        {
            MYSQL_ROW row;
            while((row=mysql_fetch_row(res)) != nullptr) //依次调用 mysql_fetch_row() 将返回结果集中的下一行，如果没有更多行则返回 FALSE。
            {
                Group group;
                group.setId(atoi(row[0]));
                group.setName(row[1]);
                group.setDesc(row[2]);
                vec.push_back(group);
            }
            mysql_free_result(res);
        }

        //查询群组的用户信息
        for(Group& group : vec)
        {
            bzero(sql, sizeof(sql));
            sprintf(sql, "select a.id,a.name,a.state b.grouprole from user a inner join groupuser b on b.userid = a.id where b.groupid = %d", group.getId()); //多表查询，查询friend的id,name,state
            MYSQL_RES *res = mysql.query(sql);
            if(res != nullptr)
            {
                MYSQL_ROW row;
                while((row=mysql_fetch_row(res)) != nullptr) //依次调用 mysql_fetch_row() 将返回结果集中的下一行，如果没有更多行则返回 FALSE。
                {
                    Groupuser groupuser;
                    groupuser.setId(atoi(row[0]));
                    groupuser.setName(row[1]);
                    groupuser.setState(row[2]);
                    groupuser.setRole(row[3]);
                    group.getUsers().push_back(groupuser);
                }
                mysql_free_result(res);
                return vec;
            }

        }
    }
    return vec;
}

//根据指定的groupid查询群组用户id列表，用于群聊
vector<int> GroupModel::qureyGroupUsers(int userid, int groupid)
{
    char sql[1024] = {0};
    sprintf(sql, "select userid from groupuser where groupid = %d and userid != %d", groupid, userid); //多表查询，查询friend的id,name,state
    MySQL mysql;
    vector<int> vec;
    if(mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if(res != nullptr)
        {
            MYSQL_ROW row;
            while((row=mysql_fetch_row(res)) != nullptr) //依次调用 mysql_fetch_row() 将返回结果集中的下一行，如果没有更多行则返回 FALSE。
            {
                vec.push_back(atoi(row[0]));  
            }
            mysql_free_result(res);
            return vec;
        }
    }
    return vec;
}