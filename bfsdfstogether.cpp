#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>

using namespace std;

// Graph class representing an undirected graph using adjacency list representation
class Graph {
    int V; // Number of vertices

    // Array of vectors to represent adjacency list
    vector<int>* adj;

public:
    Graph(int V) {
        this->V = V;
        adj = new vector<int>[V];
    }

    // Function to add an edge to the graph
    void addEdge(int v, int w) {
        adj[v].push_back(w); // Add w to v’s list
        adj[w].push_back(v); // Add v to w’s list
    }

    // Function to perform Breadth First Search traversal
    void BFS(int startVertex) {
        // Mark all vertices as not visited
        vector<bool> visited(V, false);

        // Create a queue for BFS
        queue<int> queue;

        // Mark the current node as visited and enqueue it
        visited[startVertex] = true;
        queue.push(startVertex);

        while (!queue.empty()) {
            // Dequeue a vertex from queue and print it
            int currentVertex = queue.front();
            cout << currentVertex << " ";
            queue.pop();

            // Get all adjacent vertices of the dequeued vertex currentVertex.
            // If an adjacent has not been visited, then mark it visited and enqueue it
            for (int neighbor : adj[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
    }

    // Function to perform Depth First Search traversal
    void DFS(int startVertex) {
        // Mark all vertices as not visited
        vector<bool> visited(V, false);

        // Create a stack for DFS
        stack<int> stack;

        // Push the current startVertex onto the stack
        stack.push(startVertex);

        while (!stack.empty()) {
            // Pop a vertex from stack and print it
            int currentVertex = stack.top();
            stack.pop();

            // Stack may contain same vertex twice. So we need to print the popped item only if it's not visited.
            if (!visited[currentVertex]) {
                cout << currentVertex << " ";
                visited[currentVertex] = true;
            }

            // Get all adjacent vertices of the popped vertex currentVertex.
            // If an adjacent has not been visited, then push it onto the stack
            for (int neighbor : adj[currentVertex]) {
                if (!visited[neighbor]) {
                    stack.push(neighbor);
                }
            }
        }
    }
};

int main() {
    // Create a graph given in the example
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    cout << "BFS traversal starting from vertex 0: ";
    g.BFS(0);
    cout << endl;

    cout << "DFS traversal starting from vertex 0: ";
    g.DFS(0);
    cout << endl;

    return 0;
}
