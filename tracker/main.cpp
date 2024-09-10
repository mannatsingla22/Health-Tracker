#include <iostream>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

// workout tracking
class WorkoutNode {
public:
    string workout;
    WorkoutNode* next;
    WorkoutNode(const string& wkout) : workout(wkout), next(nullptr) {}
};

class WorkoutTracker {
private:
    WorkoutNode* head;
    WorkoutNode* tail;
    WorkoutNode* current;
    string fileName = "workouts.txt";

public:
    WorkoutTracker();
    ~WorkoutTracker();
    void addWorkout(const string& workout);
    void nextWorkout();
    void displayWorkouts() const;
    void saveWorkouts() const;
    void loadWorkouts();
};

WorkoutTracker::WorkoutTracker() : head(nullptr), tail(nullptr), current(nullptr) {
    loadWorkouts();
}

WorkoutTracker::~WorkoutTracker() {
    if (head) {
        WorkoutNode* temp = head;
        do {
            WorkoutNode* next = temp->next;
            delete temp;
            temp = next;
        } while (temp != head);
    }
}

void WorkoutTracker::addWorkout(const string& workout) {
    WorkoutNode* newNode = new WorkoutNode(workout);
    if (!head) {
        head = tail = current = newNode;
        tail->next = head;
    } else {
        tail->next = newNode;
        tail = newNode;
        tail->next = head;
    }
    saveWorkouts();
}

void WorkoutTracker::nextWorkout() {
    if (current) {
        current = current->next;
    }
}

void WorkoutTracker::displayWorkouts() const {
    if (head) {
        WorkoutNode* temp = head;
        do {
            cout << temp->workout << endl;
            temp = temp->next;
        } while (temp != head);
    } else {
        cout << "No workouts available.\n";
    }
}

void WorkoutTracker::saveWorkouts() const {
    ofstream outFile(fileName);
    if (outFile.is_open()) {
        WorkoutNode* temp = head;
        if (temp) {
            do {
                outFile << temp->workout << endl;
                temp = temp->next;
            } while (temp != head);
        }
        outFile.close();
    } else {
        cout << "Unable to open file to save workouts.\n";
    }
}

void WorkoutTracker::loadWorkouts() {
    ifstream inFile(fileName);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            addWorkout(line); 
        }
        inFile.close();
    }
}

// workout goals
class Goal {
public:
    string goalDescription;
    int priority;
    Goal(const string& desc, int prio) : goalDescription(desc), priority(prio) {}
    bool operator<(const Goal& other) const {
        return priority < other.priority;
    }
};

class GoalManager {
private:
    priority_queue<Goal> goals;
    string fileName = "goals.txt"; 

public:
    void addGoal(const string& description, int priority);
    void displayGoals() const;
    void saveGoals() const;
    void loadGoals();
    
    GoalManager() {
        loadGoals();
    }
};

void GoalManager::addGoal(const string& description, int priority) {
    goals.emplace(description, priority);
    saveGoals();
}

void GoalManager::displayGoals() const {
    if (goals.empty()) {
        cout << "No goals set.\n";
        return;
    }
    priority_queue<Goal> tempGoals = goals;
    while (!tempGoals.empty()) {
        Goal top = tempGoals.top();
        cout << "Goal: " << top.goalDescription << ", Priority: " << top.priority << endl;
        tempGoals.pop();
    }
}

void GoalManager::saveGoals() const {
    ofstream outFile(fileName);
    if (outFile.is_open()) {
        priority_queue<Goal> tempGoals = goals;
        while (!tempGoals.empty()) {
            Goal top = tempGoals.top();
            outFile << top.goalDescription << ";" << top.priority << endl;
            tempGoals.pop();
        }
        outFile.close();
    } else {
        cout << "Unable to open file to save goals.\n";
    }
}

void GoalManager::loadGoals() {
    ifstream inFile(fileName);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            size_t delimiterPos = line.find(';');
            if (delimiterPos != string::npos) {
                string description = line.substr(0, delimiterPos);
                int priority = stoi(line.substr(delimiterPos + 1));
                addGoal(description, priority);
            }
        }
        inFile.close();
    }
}

int main() {
    WorkoutTracker tracker;
    GoalManager manager;

    // sample Data
    tracker.addWorkout("Run 5km");
    tracker.addWorkout("Yoga Session");
    tracker.addWorkout("Strength Training");

    manager.addGoal("Lose 5kg", 2);
    manager.addGoal("Run a marathon", 1);

    // display data
    cout << "Workouts for the Week:\n";
    tracker.displayWorkouts();

    cout << "\nFitness Goals:\n";
    manager.displayGoals();

    return 0;
}