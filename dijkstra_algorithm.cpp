// Program to find Dijkstra's shortest path using
// priority_queue in STL
#include <vector>
#include <functional>
#include <queue>

# define INF 0x3f3f3f3f

// iPair ==> Integer Pair
typedef std::pair<int, int> iPair;

// To add an edge
void addEdge(std::vector <std::pair<int, int> > adj[], int u,
             int v, int wt)
{
    adj[u].push_back(std::make_pair(v, wt));
    adj[v].push_back(std::make_pair(u, wt));
}


// Prints shortest paths from src to all other vertices
void shortestPath(std::vector<std::pair<int,int> > adj[], int V, int src)
{
    // Create a priority queue to store vertices that
    // are being preprocessed. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
    std::priority_queue< iPair, std::vector <iPair> , std::greater<iPair> > pq;

    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    std::vector<int> dist(V, INF);

    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push(std::make_pair(0, src));
    dist[src] = 0;

    /* Looping till priority queue becomes empty (or all
    distances are not finalized) */
    while (!pq.empty())
    {
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();

        // Get all adjacent of u.
        for (auto x : adj[u])
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = x.first;
            int weight = x.second;

            // If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }

    // Print shortest distances stored in dist[]
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Driver program to test methods of graph class
int shortest_path(int source, int dest, int distance, int z){
    std::vector<iPair> adj[z];

    // making above shown graph
    for (int i = 0; i<z; i++) {
        addEdge(adj, source, i, distance);
    }
    shortestPath(adj, z, 0);

    return 0;
}
