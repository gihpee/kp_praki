#include <iostream>
#include <vector>
using namespace std;

class order {
public:
    order(int quant, int price) : quant_(quant), price_(price) {}

    int get_quantity() const { return quant_; }
    int get_price() const { return price_; }
    int get_total_price() const { return quant_ * price_; }

private:
    int quant_;
    int price_;
};


class discount_type {
public:
    virtual int get_discount(const order& order) const = 0;
};

class fixed_discount : public discount_type {
public:
    fixed_discount(int discount) : discount_(discount) {}

    int get_discount(const order& order) const override {
        return order.get_total_price() * discount_ / 100;
    }

private:
    int discount_;
};

class volume_discount : public discount_type {
public:
    volume_discount(int discount, int quanth) : discount_(discount), quanth_(quanth) {}

    int get_discount(const order& order) const override {
        return order.get_quantity() >= quanth_ ? order.get_total_price() * discount_ / 100 : 0;
    }

private:
    int discount_;
    int quanth_;
};

class price_discount : public discount_type {
public:
    price_discount(int discount, int totalpriceth) : discount_(discount), totalpriceth_(totalpriceth) {}

    int get_discount(const order& order) const override {
        return order.get_total_price() >= totalpriceth_ ? order.get_total_price() * discount_ / 100 : 0;
    }

private:
    int discount_;
    int totalpriceth_;
};


int main() {
    vector<order> orders = {
            order(30, 5000),
    };

    vector<discount_type*> strategies = {
            new fixed_discount(5),
            new volume_discount(10, 50),
            new price_discount(15, 100000),
    };

    int totaldis = 0;
    for (const auto& order : orders) {
        for (const auto& strategy : strategies) {
            totaldis += strategy->get_discount(order);
        }
    }

    int totalprice = orders[0].get_total_price() - totaldis;
    cout << totalprice << endl;

    return 0;
}




