#include <iostream>
#include <string>
using namespace std;

class pwd_checker
{
public:
    virtual bool check(string& pwd) = 0;
    virtual ~pwd_checker() {}
};

class length_checker : public pwd_checker
{
public:
    virtual bool check(string& pwd) override
    {
        return pwd.length() >= 10;
    }
};

class non_alph_checker : public pwd_checker
{
private:
    pwd_checker* checker_;
public:
    non_alph_checker(pwd_checker* checker) : checker_(checker) {}
    virtual ~non_alph_checker() { delete checker_; }
    virtual bool check(string& pwd) override
    {
        if (!checker_->check(pwd))
        {
            return false;
        }

        for (char a : pwd)
        {
            if (!isalpha(a))
            {
                return true;
            }
        }
        return false;
    }
};

class num_checker : public pwd_checker
{
private:
    pwd_checker* checker_;
public:
    num_checker(pwd_checker* checker) : checker_(checker) {}
    virtual ~num_checker() { delete checker_; }
    virtual bool check(string& pwd) override
    {
        if (!checker_->check(pwd))
        {
            return false;
        }

        for (char a : pwd)
        {
            if (isdigit(a))
            {
                return true;
            }
        }
        return false;
    }
};

class low_up_checker : public pwd_checker
{
private:
    pwd_checker* checker_;
public:
    low_up_checker(pwd_checker* checker) : checker_(checker) {}
    virtual ~low_up_checker() { delete checker_; }
    virtual bool check(string& pwd) override
    {
        if (!checker_->check(pwd))
        {
            return false;
        }

        bool low = false;
        bool up = false;

        for (char a : pwd)
        {
            if (isupper(a))
            {
                up = true;
            }
            else if (islower(a))
            {
                low = true;
            }
        }
        return low && up;
    }
};

int main()
{
    pwd_checker* checker = new length_checker();
    checker = new non_alph_checker(checker);
    checker = new num_checker(checker);
    checker = new low_up_checker(checker);

    string pwd1 = "ejh34";
    string pwd2 = "iherisosiddlsvfbsiebfv";
    string pwd3 = "eirueouroeirui''''";
    string pwd4 = "ifdisivisbvis&*&^&$%uvsd2153712537";
    string pwd5 = "iUigIugOiGi&^78^86%";

    cout << checker->check(pwd1) << endl;
    cout << checker->check(pwd2) << endl;
    cout << checker->check(pwd3) << endl;
    cout << checker->check(pwd4) << endl;
    cout << checker->check(pwd5) << endl;

}

