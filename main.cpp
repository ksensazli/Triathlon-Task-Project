#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <time.h>

using namespace std;

//I define the constants I will use here to avoid confusion in the code.
const int NUM_TEAMS = 300;
const int NUM_ATHLETES_PER_TEAM = 3;
const int SWIM_DISTANCE = 50;
const int BIKE_DISTANCE = 400;
const int RUN_DISTANCE = 100;

// Athlete class to represent individual athletes
class Athlete {
public:
    int teamID;             // Team ID of the athlete
    int athleteID;          // Unique ID of the athlete within the team
    float swimSpeed;        // Speed of the athlete during swimming
    float bikeSpeed;        // Speed of the athlete during biking
    float runSpeed;         // Speed of the athlete during running
    int position;           // Current position of the athlete in the race

    // Constructor to initialize an athlete with given parameters
    Athlete(int teamID, int athleteID, float swimSpeed, float bikeSpeed, float runSpeed) {
        this->teamID = teamID;
        this->athleteID = athleteID;
        this->swimSpeed = swimSpeed;       // random[1,5]
        this->bikeSpeed = bikeSpeed;       // swimSpeed * 3
        this->runSpeed = runSpeed;         // swimSpeed / 3
        position = 0;                      // Initialize position to start of the race
    }
};

mutex mtx; //mutex for synchronization
int selectedTeam = 0;       // Team ID selected for tracking
int selectedAthlete = 0;    // Athlete ID selected for tracking

// Function to calculate position of an athlete during a specific segment (swim, bike, run)
void calculatePosition(Athlete& athlete, int distance, int speedMultiplier) {
    // Swim
    while (athlete.position < SWIM_DISTANCE) {
        // Calculate new position based on speed
        athlete.position += athlete.swimSpeed * speedMultiplier;

        // Simulate transition time between segments
        this_thread::sleep_for(chrono::seconds(1));

        // Output athlete's current position if it belongs to the specified team
        if (athlete.teamID == selectedTeam) {
            if (athlete.athleteID == selectedAthlete)
            {
                mtx.lock(); // Lock mutex before accessing shared resources
                if (athlete.position > SWIM_DISTANCE)
                {
                    athlete.position = SWIM_DISTANCE; // Ensure the position doesn't exceed the swim distance
                }
                cout << "Team " << athlete.teamID << " - Athlete " << athlete.athleteID << " - " << "Swim" << " - Position: " << athlete.position << " meters\n";
                mtx.unlock(); // Unlock mutex after accessing shared resources
            }
        }
    }

    // Transition from swim to bike
    this_thread::sleep_for(chrono::seconds(10));

    // Bike
    while (athlete.position < SWIM_DISTANCE  + BIKE_DISTANCE) {
        // Calculate new position based on speed
        athlete.position += athlete.bikeSpeed * speedMultiplier;

        // Simulate transition time between segments
        this_thread::sleep_for(chrono::seconds(1));

        // Output athlete's current position if it belongs to the specified team
        if (athlete.teamID == selectedTeam) {
            if (athlete.athleteID == selectedAthlete)
            {
                mtx.lock(); // Lock mutex before accessing shared resources
                if (athlete.position > SWIM_DISTANCE + BIKE_DISTANCE)
                {
                    athlete.position = SWIM_DISTANCE + BIKE_DISTANCE; // Ensure the position doesn't exceed the swim + bike distance
                }
                cout << "Team " << athlete.teamID << " - Athlete " << athlete.athleteID << " - " << "Bike" << " - Position: " << athlete.position << " meters\n";
                mtx.unlock(); // Unlock mutex after accessing shared resources
            }
        }
    }

    // Transition from bike to run
    this_thread::sleep_for(chrono::seconds(10));

    // Run
    while (athlete.position < SWIM_DISTANCE + BIKE_DISTANCE + RUN_DISTANCE) {
        // Calculate new position based on speed
        athlete.position += athlete.runSpeed * speedMultiplier;

        // Simulate transition time between segments
        this_thread::sleep_for(chrono::seconds(1));

        // Output athlete's current position if it belongs to the specified team
        if (athlete.teamID == selectedTeam) {
            if (athlete.athleteID == selectedAthlete)
            {
                mtx.lock(); // Lock mutex before accessing shared resources
                if (athlete.position > SWIM_DISTANCE + BIKE_DISTANCE + RUN_DISTANCE)
                {
                    athlete.position = SWIM_DISTANCE + BIKE_DISTANCE + RUN_DISTANCE; // Ensure the position doesn't exceed the swim + bike + run distance
                }
                cout << "Team " << athlete.teamID << " - Athlete " << athlete.athleteID << " - " << "Run" << " - Position: " << athlete.position << " meters\n";
                mtx.unlock(); // Unlock mutex after accessing shared resources
            }
        }
    }

    // Check if the athlete has finished the race
    if (athlete.position >= SWIM_DISTANCE + BIKE_DISTANCE + RUN_DISTANCE)
    {
        return;
    }
}

// Function to simulate the entire race for all athletes
void simulateRace(vector<Athlete>& athletes) {
    // Create threads to calculate positions for each athlete in each segment
    vector<thread> threads;
    for (Athlete& athlete : athletes) {
        threads.emplace_back(calculatePosition, ref(athlete), SWIM_DISTANCE, 1);
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }
}

// Main function
int main() {
    // Create random number generator
    srand(time(NULL));
    int speed = rand()%5 + 1; // Generate random speed for the athletes

    // Create athletes
    vector<Athlete> athletes;
    for (int i = 0; i < NUM_TEAMS; ++i) {
        for (int j = 0; j < NUM_ATHLETES_PER_TEAM; ++j) {
            athletes.emplace_back(i, j, speed, speed * 3, speed / 3); // Create athletes with random speeds
        }
    }

    // Select team and athlete for real-time tracking
    cout << "Enter the team ID you want to track (0 - " << NUM_TEAMS - 1 << "): ";
    cin >> selectedTeam;
    if (selectedTeam > NUM_TEAMS - 1)
    {
        cout << "Please enter the valid team ID";
        return 0;
    }

    cout << "Enter the athlete ID you want to track (0 - " << NUM_ATHLETES_PER_TEAM - 1 << "): ";
    cin >> selectedAthlete;
    if (selectedAthlete > NUM_ATHLETES_PER_TEAM - 1)
    {
        cout << "Please enter the valid athlete ID";
        return 0;
    }

    // Simulate the race
    simulateRace(athletes);

    // Output positions of all athletes when the first one finishes
    cout << "************ RESULTS ************" << endl;
    for (const Athlete& athlete : athletes) {
        cout << "Team " << athlete.teamID << " - Athlete " << athlete.athleteID << " - Final Position: " << athlete.position << " meters\n";
    }

    return 0;
}
