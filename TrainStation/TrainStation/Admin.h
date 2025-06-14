#pragma once
#include "MyString.h"

class Admin
{
    MyString username;
    MyString password;

public:
    Admin(const MyString& username, const MyString& password);

    const MyString& getUsername() const;
    bool checkPassword(const MyString& pwd) const;
};

