#include <iostream>
#include "time.h"
#include <sqlite3.h>
using namespace std;
#include <cmath> 

int Loopingcount(double track_temp) {
    double Laptime, firstLaptime, totalStintTime = 0;
    int totalLaps;
    double baseLaptime = 120.0; 

    // Base: Assuming 18 laps at 30°C. 
    // Sens: Lapses 1 lap of life for every 4 degrees extra.
    double lifeLimit = 18.0 - ((track_temp - 30.0) / 4.0);
    if (lifeLimit < 8) lifeLimit = 8; // Safety net to avoid crashing my pow function :(

    // 2. THE BRIEFING (Must be here to see it before input)
    cout << "\n--- TRACK DATA ---" << std::endl;
    cout << "Track Temp: " << track_temp << "C" << std::endl;
    cout << "Estimated Tyre Life: " << lifeLimit << " Laps" << std::endl;
    cout << "----------------------------" << std::endl;

    cout << "Enter laps for this stint: ";
    cin >> totalLaps;
    cout << "Enter base laptime (e.g., 120): ";
    cin >> baseLaptime;

    for (int i = 1; i <= totalLaps; i++) {
        double warmUpGain = 1.5 * std::sqrt(i);
        double thermalCliff = std::pow((i / lifeLimit), 12);

        Laptime = baseLaptime - warmUpGain + thermalCliff;

        // Capture Lap 1 benchmark
        if (i == 1) firstLaptime = Laptime;

        std::cout << "Lap " << i << ": ";
        timeFormat(Laptime);
        
        // 3-SECOND WARNING SYSTEM 
        if (Laptime > (firstLaptime + 3.0)) {
            cout << " [!]";
        }
        
        std::cout << std::endl;
        totalStintTime += Laptime;
    }

    return 0;
}

int main()
{
    sqlite3* db;
    sqlite3_stmt* stmt;
    double track_temp = 25.0; // Default fallback

    // 1. PULL DATA FROM THE BRIDGE FIRST
    if (sqlite3_open("f1_sim.db", &db) == SQLITE_OK) {
        const char* query = "SELECT track_temp FROM race_weather ORDER BY id DESC LIMIT 1;";
        
        if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK) {
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                track_temp = sqlite3_column_double(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    // 2. RUN SIMULATION WITH THE LIVE DATA
    Loopingcount(track_temp);

    return 0;
}