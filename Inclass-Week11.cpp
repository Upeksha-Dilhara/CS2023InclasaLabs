#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;
typedef vector<vector<pii>> Graph;

vector<int> primMST(const Graph& graph, int startVertex) {
    int numVertices = graph.size();
    vector<int> minWeight(numVertices, INT_MAX);    // Stores the minimum weight to connect each vertex to the MST
    vector<int> parent(numVertices, -1);            // Stores the parent of each vertex in the MST
    vector<bool> visited(numVertices, false);       // Tracks visited vertices

    // Priority queue to store vertices and their corresponding weights
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // Start with the specified vertex and set its weight to 0
    pq.push(make_pair(0, startVertex));
    minWeight[startVertex] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        visited[u] = true;

        // Traverse all neighboring vertices of u
        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            // If v is not yet visited and weight of edge (u, v) is less than the current weight of v
            if (!visited[v] && weight < minWeight[v]) {
                // Update the weight and parent of v
                minWeight[v] = weight;
                parent[v] = u;
                pq.push(make_pair(minWeight[v], v));
            }
        }
    }

    return parent;
}

// Function to add an undirected weighted edge to the graph
void addEdge(Graph& graph, int u, int v, int weight) {
    graph[u].push_back(make_pair(v, weight));
    graph[v].push_back(make_pair(u, weight));
}

// Function to print the Minimum Spanning Tree
void printMST(const vector<int>& parent, const Graph& graph) {
    int numVertices = graph.size();
    cout << "Edge \tWeight\n";
    for (int i = 1; i < numVertices; ++i) {
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]].second << "\n";
    }
}

int main() {
    int numVertices = 5;  // Number of vertices in the graph
    Graph graph(numVertices);

    // Adding edges to the graph
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 3, 4);
    addEdge(graph, 1, 2, 5);
    addEdge(graph, 1, 3, 3);
    addEdge(graph, 1, 4, 2);
    addEdge(graph, 2, 4, 1);

    int startVertex = 0;  // Starting vertex for MST

    // Running Prim's algorithm to find MST
    vector<int> parent = primMST(graph, startVertex);

    // Printing the MST
    printMST(parent, graph);

    return 0;
}
