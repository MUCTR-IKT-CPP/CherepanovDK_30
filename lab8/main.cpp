#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>

// Definition of visitor type
enum class VisitorType { Child, Adult, Senior };

// Class Visitor
class Visitor {
public:
    VisitorType type;
    int serviceTime;
    bool isElectronicQueue;

    // Constructor with generation of type, service time, and queue type
    Visitor() {
        int typeProbability = rand() % 100;
        if (typeProbability < 5)
            type = VisitorType::Child;
        else if (typeProbability < 45)
            type = VisitorType::Adult;
        else
            type = VisitorType::Senior;

        // Set service time based on visitor type
        switch (type) {
            case VisitorType::Child:
                serviceTime = 5 + rand() % 6;
                break;
            case VisitorType::Adult:
                serviceTime = 2 + rand() % 4;
                break;
            case VisitorType::Senior:
                serviceTime = 7 + rand() % 3;
                break;
        }

        // Determine queue (electronic or physical)
        int queueProbability = rand() % 100;
        if ((type == VisitorType::Child && queueProbability < 20) ||
            (type == VisitorType::Adult && queueProbability < 70) ||
            (type == VisitorType::Senior && queueProbability < 5)) {
            isElectronicQueue = true;
        } else {
            isElectronicQueue = false;
        }
    }
};

// Class Window
class Window {
public:
    bool occupied;
    int remainingServiceTime;
    int processedChild = 0, processedAdult = 0, processedSenior = 0;

    Window() : occupied(false), remainingServiceTime(0) {}

    // Process a visitor
    void startProcessing(Visitor &visitor) {
        occupied = true;
        remainingServiceTime = visitor.serviceTime;
        if (visitor.type == VisitorType::Child)
            processedChild++;
        else if (visitor.type == VisitorType::Adult)
            processedAdult++;
        else if (visitor.type == VisitorType::Senior)
            processedSenior++;
    }

    // Update window state (decrease time)
    void update() {
        if (occupied) {
            remainingServiceTime--;
            if (remainingServiceTime <= 0) {
                occupied = false;
            }
        }
    }
};

// Class Institution
class Institution {
private:
    std::queue<Visitor> physicalQueue;
    std::queue<Visitor> electronicQueue;
    std::vector<Window> windows;
    int processedChild = 0, processedAdult = 0, processedSenior = 0;

public:
    Institution(int numWindows) {
        windows.resize(numWindows);
        srand(static_cast<unsigned>(time(0)));
    }

    // Generate initial state
    void initialize() {
        for (int i = 0; i < 10; i++) {
            Visitor visitor;
            if (visitor.isElectronicQueue)
                electronicQueue.push(visitor);
            else
                physicalQueue.push(visitor);
        }
    }

    // Add new visitors every 5 minutes
    void addNewVisitors() {
        int numVisitors = rand() % 10;
        for (int i = 0; i < numVisitors; i++) {
            Visitor visitor;
            if (visitor.isElectronicQueue)
                electronicQueue.push(visitor);
            else
                physicalQueue.push(visitor);
        }
    }

    // Model one step of the institution's work
    void workStep(int time) {
        if (time % 5 == 0) {
            addNewVisitors();
        }

        // Process windows
        for (auto &window : windows) {
            window.update();

            if (!window.occupied) {
                if (!electronicQueue.empty()) {
                    window.startProcessing(electronicQueue.front());
                    electronicQueue.pop();
                } else if (!physicalQueue.empty()) {
                    window.startProcessing(physicalQueue.front());
                    physicalQueue.pop();
                }
            }
        }
    }

    // Show statistics after the institution closes
    void showStatistics() {
        std::cout << "Number of processed visitors:\n";
        for (size_t i = 0; i < windows.size(); ++i) {
            std::cout << "Window " << i + 1 << " - Child: " << windows[i].processedChild
                      << ", Adult: " << windows[i].processedAdult
                      << ", Senior: " << windows[i].processedSenior << "\n";
        }
        std::cout << "Not processed: " << physicalQueue.size() + electronicQueue.size() << "\n";
    }

    // Main work cycle of the institution
    void simulate() {
        initialize();
        for (int time = 0; time < 480; ++time) {
            if (time < 240 || time >= 300) { // From 9:00 to 13:00 and from 14:00 to 18:00
                workStep(time);
            }
        }
        showStatistics();
    }
};

int main() {
    Institution institution(3);
    institution.simulate();
    return 0;
}
