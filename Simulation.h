#ifndef SIMULATION_H
#define SIMULATION_H

#include "Department.h"
#include "Config.h"
#include <cstdlib>

const int MAX_WAIT = 10;

void runSimulation(Department depts[]) {

    int customerID = 1;

    for (int t = 1; t <= SIM_TIME; t++) {

        // ── Generate customers (70% chance each tick) ──
        if (rand() % 100 < 70) {
            Customer c;
            c.id          = customerID++;
            c.department  = (DeptType)(rand() % 3);
            c.isVIP       = (rand() % 100 < 20);
            c.arrivalTime = t;
            c.serviceTime = rand() % 5 + 1;   // 1..5 ticks

            if (c.isVIP)
                depts[c.department].vipQueue.enqueue(c);
            else
                depts[c.department].normalQueue.enqueue(c);
        }

        // ── Process each department ────────────────────
        for (int d = 0; d < 3; d++) {

            // ── Abandonment: remove normal customers who waited too long ──
            //
            // FIX: 'temp' is a local Queue on the stack.
            // Its destructor (now fixed in Queue.h) will correctly
            // delete all remaining nodes when this block exits.
            // No leak here as long as Queue::~Queue() is correct.
            //
            {
                Queue temp;
                while (!depts[d].normalQueue.isEmpty()) {
                    Customer c = depts[d].normalQueue.dequeue();

                    if (t - c.arrivalTime > MAX_WAIT) {
                        c.abandoned = true;
                        depts[d].totalAbandoned++;
                        // c goes out of scope here – no heap involved, no leak
                    } else {
                        temp.enqueue(c);
                    }
                }
                // Move survivors back
                while (!temp.isEmpty())
                    depts[d].normalQueue.enqueue(temp.dequeue());
            }   // ← temp destroyed here, its destructor frees all nodes

            // ── Servers ───────────────────────────────
            for (int s = 0; s < depts[d].numServers; s++) {

                Server& srv = depts[d].servers[s];

                // 1) Finish service FIRST before assigning anyone new
                if (srv.isBusy && t >= srv.finishTime) {

                    Customer& c = srv.currentCustomer;

                    if      (c.waitingTime < 3)  c.rating = 5;
                    else if (c.waitingTime < 6)  c.rating = 4;
                    else if (c.waitingTime < 10) c.rating = 3;
                    else                          c.rating = 2;

                    srv.totalBusyTime      += c.serviceTime;
                    depts[d].totalServed++;
                    depts[d].totalRatingSum += c.rating;

                    srv.isBusy = false;
                }

                // 2) Assign next customer only if server is now free
                if (!srv.isBusy) {

                    Customer c;
                    bool found = false;

                    if (!depts[d].vipQueue.isEmpty()) {
                        c     = depts[d].vipQueue.dequeue();
                        found = true;
                    } else if (!depts[d].normalQueue.isEmpty()) {
                        c     = depts[d].normalQueue.dequeue();
                        found = true;
                    }

                    if (!found) continue;

                    c.startTime   = t;
                    c.waitingTime = t - c.arrivalTime;

                    srv.currentCustomer = c;
                    srv.isBusy          = true;
                    srv.finishTime      = t + c.serviceTime;
                }
            }
        }
    }
}

#endif