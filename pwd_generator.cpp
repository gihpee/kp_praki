#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class password_generator {
public:
    
    virtual string generate() = 0;
    virtual size_t length() = 0;
    virtual string allowed_chars() = 0;
    virtual void add(password_generator* ptr) = 0;

};

class basic_password_generator : public password_generator
{
public:
    size_t len;
    size_t length() override {
        return len;
    }
    string generate() override { throw exception(); }
    string allowed_chars() override { throw exception(); }
    void add(password_generator* ptr) override { throw exception(); }

};

class digit_generator : public basic_password_generator //в этом и в следующих подобных классах метод allowed_chars() возвращает рандомную строку длины len (которую задает пользователь) соответствующих символов
{
public:
    string allowed_chars() override {
        string a = "1234567890";
        string res = "";
        for (int i = 0; i < len; i++)
        {
            res += a[rand() % (size(a) + 1)];
        }
        return res;
    }
};

class symbol_generator : public basic_password_generator
{
public:
    string allowed_chars() override {
        string a = "!@#$%^&*(){}:>?<";
        string res = "";
        for (int i = 0; i < len; i++)
        {
            res += a[rand() % (size(a) + 1)];
        }
        return res;
    }
};

class upper_letter_generator : public basic_password_generator
{
public:
    string allowed_chars() override {
        string a = "QWERTYUIOPASDFGHJKLZXCVBNM";
        string res = "";
        for (int i = 0; i < len; i++)
        {
            res += a[rand() % (size(a) + 1)];
        }
        return res;
    }
};

class lower_letter_generator : public basic_password_generator
{
public:
    string allowed_chars() override {
        string a = "qwertyuiopasdfghjklzxcvbnm";;
        string res = "";
        for (int i = 0; i < len; i++)
        {
            res += a[rand() % (size(a) + 1)];
        }
        return res;
    }
};

class composite_password_generator : public password_generator
{
private:
    vector<password_generator*> generators;
public:
    string allowed_chars() override { throw exception(); }
    size_t length() override { throw exception(); }

    void add(password_generator* ptr) override {
        generators.push_back(ptr);
    }
    string generate() override { //тут я получаю все рандомные строки различных типов символов из allowed_chars а затем еще и дополнительно их перемешиваю
        string pwd = "";
        for (const auto& g : generators)
        {
            pwd += g->allowed_chars();
        }
        random_shuffle(pwd.begin(), pwd.end());
        return pwd;
    }
};

int main()
{   
    password_generator* cpg = new composite_password_generator;

    basic_password_generator* dg = new digit_generator;
    dg->len = 2;
    basic_password_generator* sg = new symbol_generator;
    sg->len = 3;
    basic_password_generator* ulg = new upper_letter_generator;
    ulg->len = 8;
    basic_password_generator* llg = new lower_letter_generator;
    llg->len = 5;

    cpg->add(dg);
    cpg->add(sg);
    cpg->add(ulg);
    cpg->add(llg);

    cout << cpg->generate() << endl;
}

