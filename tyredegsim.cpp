#include <iostream>
#include "time.h"
#include <sqlite3.h>
using namespace std;
#include <cmath> 

int Loopingcount(double track_temp) {
    double Laptime, firstLaptime, totalStintTime = 0;
    int totalLaps;
    double baseLaptime = 120.0; 

    // 1. Calculate the Strategy 
    double lifeLimit = 12.0 - ((track_temp - 25.0) / 2.0);
    if (lifeLimit < 5) lifeLimit = 5;

    // 2. THE BRIEFING (Must be here to see it before input)
    std::cout << "\n--- BRIDGE DATA RECEIVED ---" << std::endl;
    std::cout << "Track Temp: " << track_temp << "C" << std::endl;
    std::cout << "Estimated Tyre Life: " << lifeLimit << " Laps" << std::endl;
    std::cout << "----------------------------" << std::endl;

    std::cout << "Enter laps for this stint: ";
    std::cin >> totalLaps;
    std::cout << "Enter base laptime (e.g., 120): ";
    std::cin >> baseLaptime;

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
            std::cout << " [!]";
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