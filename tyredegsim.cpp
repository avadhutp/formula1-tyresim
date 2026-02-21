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
    // 1. THE PHYSICS FORCES
    // The "Cliff": Exponential increase as we hit the lifeLimit
    double thermalCliff = std::pow((i / lifeLimit), 12);
    
    // The "Fuel Gain": Car gets 0.07s faster every lap as it gets lighter
    double fuelGain = i * 0.07; 

    // The "Warm-up Penalty": Lap 1 is very cold, Lap 2 is getting there, Lap 3+ is optimal
    double warmUpPenalty = 0.0;
    if (i == 1) {
        warmUpPenalty = 1.1; // 1.2s penalty for cold tires
    } else if (i == 2) {
        warmUpPenalty = 0.2; // 0.4s penalty as they bleed heat in
    }

    // 2. THE CALCULATION
    // Base Time + Penalty (Slows you down) - Fuel Gain (Speeds you up) + Cliff (Slows you down)
    Laptime = baseLaptime + warmUpPenalty - fuelGain + thermalCliff;

    // 3. BENCHMARKING & WARNINGS
    if (i == 1) firstLaptime = Laptime;

    std::cout << "Lap " << i << ": ";
    timeFormat(Laptime);
    
    // 3-SECOND WARNING SYSTEM 
    // Triggers when the cliff makes the car 3s slower than the initial Lap 1 pace
    if (Laptime > (firstLaptime + 1.0)) {
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