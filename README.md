# Triathlon Race Simulation

This program simulates a triathlon race. Each team consists of 3 athletes, and each athlete competes in three different segments: swimming, biking, and running. The program calculates the position of each athlete based on their speed and allows real-time tracking of a selected team and athlete.

## Features

- **Swim Distance:** 5000 meters
- **Bike Distance:** 40000 meters
- **Run Distance:** 10000 meters
- **Total Distance:** 55000 meters
- **Three Segments per Athlete:**
  - **Swim:** Speed ranges from 1 to 5 meters per second
  - **Bike:** Speed is three times the swim speed
  - **Run:** Speed is one-third of the swim speed

## How It Works

1. **Initialization:**
   - Random speeds for athletes are generated.
   - Athletes are created with a speed for swimming, biking, and running.

2. **Simulation:**
   - Threads are created for each athlete to calculate their position in each segment.
   - Positions are updated in real-time, and transition times between segments are simulated.

3. **Real-Time Tracking:**
   - Users can track the progress of a specific athlete from a selected team.
   - The program outputs the athlete's position in the swim, bike, and run segments.

4. **Final Results:**
   - After all athletes complete the race, their final positions are displayed.

## Compilation and Execution

To compile and run the program, use the following commands:

```bash
g++ -o triathlon_simulation triathlon_simulation.cpp -pthread
./triathlon_simulation
```

## Input

1. **Team ID:** Enter the team ID you want to track (0 - 299).
2. **Athlete ID:** Enter the athlete ID you want to track within the team (0 - 2).

## Example
```java
Enter the team ID you want to track (0 - 299): 1
Enter the athlete ID you want to track (0 - 2): 2
```
