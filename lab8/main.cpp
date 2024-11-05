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

    
    Visitor() {
        int typeProbability = rand() % 100;
        if (typeProbability < 5)
            type = VisitorType::Child;
        else if (typeProbability < 45)
            type = VisitorType::Adult;
        else
            type = VisitorType::Senior;

        // Determine service time
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

    
    /**
     * Starts processing a visitor in the window.
     * 
     * Sets the window as occupied and sets the remaining service time to the visitor's service time.
     * Increments the processed counter for the visitor's type.
     *
     * @param visitor the visitor to start processing
     */
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

    
    /**
     * Updates the window status.
     * 
     * If the window is occupied, decrements the remaining service time.
     * If the remaining service time is zero or negative, sets the window as unoccupied.
     */
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

    
    /**
     * Initializes the institution by creating a set of visitors.
     * 
     * For each visitor, determines whether they belong to the electronic or physical queue
     * based on their isElectronicQueue attribute and adds them to the appropriate queue.
     * This simulates the initial state of the queues with a predefined number of visitors.
     */
    void initialize() {
        for (int i = 0; i < 10; i++) {
            Visitor visitor;
            if (visitor.isElectronicQueue)
                electronicQueue.push(visitor);
            else
                physicalQueue.push(visitor);
        }
    }

    
    /**
     * Simulates the arrival of new visitors.
     * 
     * A random number of visitors between 0 and 9 is generated.
     * For each visitor, their isElectronicQueue attribute is used to determine
     * whether they are added to the electronic or physical queue.
     * This simulates the continuous flow of visitors entering the institution.
     */
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

    
    /**
     * Simulates one step of the institution's work.
     * 
     * If the time is divisible by 5, adds new visitors to the queues.
     * For each window, updates its status and if it is unoccupied, starts processing
     * a visitor from the electronic queue if it is not empty, or from the physical queue if it is not empty.
     * This simulates the continuous processing of visitors by the institution.
     * 
     * @param time the current time
     */
    void workStep(int time) {
        if (time % 5 == 0) {
            addNewVisitors();
        }

        
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

    
    /**
     * Shows the statistics of the simulation.
     * 
     * Prints the number of visitors of each type processed by each window and the number of visitors not processed.
     */
    void showStatistics() {
        std::cout << "Number of processed visitors:\n";
        for (size_t i = 0; i < windows.size(); ++i) {
            std::cout << "Window " << i + 1 << " - Child: " << windows[i].processedChild
                      << ", Adult: " << windows[i].processedAdult
                      << ", Senior: " << windows[i].processedSenior << "\n";
        }
        std::cout << "Not processed: " << physicalQueue.size() + electronicQueue.size() << "\n";
    }

    
    /**
     * Simulates the work of the bank.
     * 
     * Calls initialize(), then calls workStep() for each minute from 9:00 to 13:00 and from 14:00 to 18:00.
     * Finally, calls showStatistics() to show the statistics of the simulation.
     */
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
