#ifndef SERVER_H
#define SERVER_H

#include "Customer.h"

struct Server {
    int  id;
    bool isBusy;
    int  finishTime;
    int  totalBusyTime;

    Customer currentCustomer;

    Server() {
        id            = 0;
        isBusy        = false;
        finishTime    = 0;
        totalBusyTime = 0;
    }
};

#endif