#ifndef USER_H
#define USER_H


class User
{
public:
    User();
    User(bool is_admin) : is_admin(is_admin) {}
    bool isAdmin() { return is_admin; }

private:
    bool is_admin = false;
};

#endif // USER_H
