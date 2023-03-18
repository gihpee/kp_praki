#include <iostream>
#include <string>
using namespace std;

//вариант 2
class abstract_ballon
{
public:
    virtual double GetPressure(int t) = 0;
    virtual double AmountOfMatter() = 0;
    virtual string ToString() = 0;
    virtual ~abstract_ballon() {}
};


class ballon : public abstract_ballon
{
private:
    double* volume;
    double* mass;
    double* molar;

public:
    ballon(double* v, double* ma, double* mo) : volume(v), mass(ma), molar(mo) {}
    ~ballon() override
    {
        delete volume;
        delete mass;
        delete molar;
    }

    double GetPressure(int t) override
    {
        return ((*mass / *molar) * t * 8.31 / *volume);
    }

    double AmountOfMatter() override
    {
        return *mass / *molar;
    }

    string ToString() override
    {
        return "Ballon volume: " + to_string(*volume) + "m^3" + "\n" +
            +"Gas mass: " + to_string(*mass) + "kg" + "\n" +
            +"Gas molar mass: " + to_string(*molar) + "kg/mol";
    }
};

class adaptee_baloon
{
private:
    double* volume;
    double* mass;
    double* molar;
public:
    adaptee_baloon(double* v, double* ma, double* mo) : volume(v), mass(ma), molar(mo) {}
    ~adaptee_baloon()
    {
        delete volume;
        delete mass;
        delete molar;
    }

    virtual void ModifVolume(double dv) = 0;

    virtual double GetDp(int t0, int t1) = 0;

    virtual string Passport() = 0;
};

class adapter : public abstract_ballon, public adaptee_baloon
{
private:
    double* volume;
    double* mass;
    double* molar;
public:
    adapter(double* v, double* ma, double* mo) : adaptee_baloon(v, ma, mo) {}
    ~adapter()
    {
        delete volume;
        delete mass;
        delete molar;
    }

    double GetPressure(int t) override
    {
        return ((*mass / *molar) * t * 8.31 / *volume);
    }

    double AmountOfMatter() override
    {
        return *mass / *molar;
    }

    string ToString() override
    {
        return "Ballon volume: " + to_string(*volume) + "m^3" + "\n" +
            +"Gas mass: " + to_string(*mass) + "kg" + "\n" +
            +"Gas molar mass: " + to_string(*molar) + "kg/mol";
    }

    void ModifVolume(double dv) override
    {
        *volume = *volume + dv;
    }

    double GetDp(int t0, int t1) override
    {
        return GetPressure(t1) - GetPressure(t0);
    }

    string Passport() override
    {
        return ToString();
    }
};




int main()
{
    double v = 23.4;
    double ma = 11.1;
    double mo = 15.2;

    adaptee_baloon* adapted = new adapter(&v, &ma, &mo);

    cout << adapted->Passport() << endl;

    adapted->ModifVolume(2.2);

    cout << adapted->Passport() << endl;

    cout << "Изменение давления при переходе от t=44 к t=82" + to_string(adapted->GetDp(44, 82)) << endl;

}

