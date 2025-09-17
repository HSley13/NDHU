#include <iostream>
#include <vector>

class WaitForGraph {

  public:
    explicit WaitForGraph(int processes)
        : num_processes{processes}, adjacency_list(processes) {
    }

    // Add an edge to the graph
    void addDependency(int from, int to) {
        adjacency_list[from].push_back(to);
    }

    // Print the adjacency list
    void printGraph() const {
        std::cout << "Wait-For Graph:" << std::endl;
        for (int i{0}; i < num_processes; i++) {
            std::cout << "P" << i << ": ";
            for (const int &neighbor : adjacency_list[i]) {
                std::cout << "P" << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }

    // Detect cycle in the graph
    bool detectDeadlock() {
        std::vector<bool> visited(num_processes, false);
        std::vector<bool> recursion_stack(num_processes, false);

        // Check each process
        for (int process{0}; process < num_processes; process++) {
            if (!visited[process] && dfs(process, visited, recursion_stack)) {
                return true; // Deadlock detected
            }
        }
        return false; // No deadlock
    }

  private:
    // Depth-First Search for cycle detection
    bool dfs(int process, std::vector<bool> &visited, std::vector<bool> &recursion_stack) {
        visited[process] = true;
        recursion_stack[process] = true;

        // Explore neighbors
        for (int neighbor : adjacency_list[process]) {
            if (!visited[neighbor] && dfs(neighbor, visited, recursion_stack)) {
                return true; // Deadlock detected
            } else if (recursion_stack[neighbor]) {
                return true; // Deadlock detected
            }
        }

        recursion_stack[process] = false; // Backtrack
        return false;                     // No cycle found
    }

    int num_processes;
    std::vector<std::vector<int>> adjacency_list;
};

int main(void) {
    // Step 1: Create Wait-For Graph
    WaitForGraph wfg{5};

    // Step 2: Add dependencies from RAG
    wfg.addDependency(0, 1); // P0 → P1
    wfg.addDependency(1, 2); // P1 → P2
    wfg.addDependency(2, 3); // P2 → P3
    wfg.addDependency(3, 4); // P3 → P4
    wfg.addDependency(4, 0); // P3 → P4 (Cycle)

    // Step 3: Print the Wait-For Graph
    wfg.printGraph();

    // Step 4: Detect deadlock
    if (wfg.detectDeadlock()) {
        std::cout << "Deadlock detected in the system!" << std::endl;
    } else {
        std::cout << "No deadlock detected in the system." << std::endl;
    }
}
