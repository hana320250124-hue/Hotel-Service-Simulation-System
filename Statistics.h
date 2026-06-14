#ifndef STATISTICS_H
#define STATISTICS_H

#include <iostream>
#include <iomanip>
#include "Config.h"
#include "Department.h"

using namespace std;

static const char* DEPT_NAMES[] = { "Front Desk", "Concierge", "Restaurant" };

void printStats(Department depts[]) {

    cout << "\n";
    cout << "========================================\n";
    cout << "         HOTEL SIMULATION REPORT        \n";
    cout << "========================================\n";
    cout << "  Simulation Duration : " << SIM_TIME       << " ticks\n";
    cout << "  Hotel Capacity      : " << HOTEL_CAPACITY << " guests\n";
    cout << "========================================\n";

    int grandServed    = 0;
    int grandAbandoned = 0;

    for (int i = 0; i < 3; i++) {

        grandServed    += depts[i].totalServed;
        grandAbandoned += depts[i].totalAbandoned;

        double avgRating = (depts[i].totalServed > 0)
            ? (double)depts[i].totalRatingSum / depts[i].totalServed
            : 0.0;

        cout << "\n--- " << DEPT_NAMES[i] << " ---\n";
        cout << fixed << setprecision(2);
        cout << "  Customers Served   : " << depts[i].totalServed    << "\n";
        cout << "  Customers Abandoned: " << depts[i].totalAbandoned << "\n";
        cout << "  Avg Satisfaction   : " << avgRating << " / 5.00\n";

        for (int s = 0; s < depts[i].numServers; s++) {
            double util = (double)depts[i].servers[s].totalBusyTime
                          / SIM_TIME * 100.0;

            cout << "  Server " << (s + 1)
                 << " Utilization : " << util << "%"
                 << "  (busy " << depts[i].servers[s].totalBusyTime
                 << " / " << SIM_TIME << " ticks)\n";
        }
    }

    cout << "\n========================================\n";
    cout << "  TOTALS\n";
    cout << "  Total Served   : " << grandServed    << "\n";
    cout << "  Total Abandoned: " << grandAbandoned << "\n";
    cout << "========================================\n\n";
}

#endif