# Health and Fitness Tracker

A simple C++ project to help users manage and track their fitness goals and daily workouts. This system uses a circular linked list to track daily workouts over the course of a week and a priority queue (heap) to manage fitness goals based on their importance.

## Features

- **Track Workouts**: Add, view, and cycle through workouts for the week.
- **Set Fitness Goals**: Prioritize fitness goals using a priority queue.
- **File Persistence**: Saves and loads workouts and goals from text files for continued use across sessions.

## How It Works

- **Circular Linked List**: Tracks daily workouts for an entire week, rolling over at the end.
- **Priority Queue (Heap)**: Prioritizes fitness goals, ensuring the most important goals are at the top.
- **File Handling**: All workouts and goals are saved in `workouts.txt` and `goals.txt`, respectively, for future use.

## How to Run

1. Compile the project:
   ```bash
   g++ -o health_fitness_tracker main.cpp
   ```
2. Run the program:
   ```bash
   ./health_fitness_tracker
   ```
