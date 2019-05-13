//
// Created by ECEM on 20.11.2017.
//

#ifndef PROJE2YEDEK_CUSTOMER_H
#define PROJE2YEDEK_CUSTOMER_H


class Customer {
public:
    double currentTime;
    double arrivalTime;
    double price;
    double orderTime;
    double brewTime;
    int index;
    int position;//positions 0:arrived 1:onCashierQueue 2:ordering 3:baristaQueue 4:brewing
    double finishTime;
    int cashier;
    int barista;
    Customer();
    Customer(double arrival, double price, double order, double brew);
    Customer(const Customer& x);
    Customer& operator=(const Customer& x);
    ~Customer();
};


#endif //PROJE2YEDEK_CUSTOMER_H
