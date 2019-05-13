//
// Created by ECEM on 20.11.2017.
//

#ifndef PROJE2YEDEK_CASHIER_H
#define PROJE2YEDEK_CASHIER_H

#include "Customer.h"

class Cashier {
public:
    Customer* currentCustomer;
    double totalWorkTime;
    Cashier();
    Cashier(const Cashier& a);
    Cashier& operator=(const Cashier& x);
    ~Cashier();
    void takeCustomer(Customer &a);
    void giveCustomer();
};


#endif //PROJE2YEDEK_CASHİER_H
