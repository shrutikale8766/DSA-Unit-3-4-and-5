
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

void BFS(vector<pair<int,int>> g[], int n, int s) {
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;

    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (auto e : g[u]) {
            if (!visited[e.first]) {
                visited[e.first] = true;
                q.push(e.first);
            }
        }
    }
    cout << endl;
}

void dijkstra(vector<pair<int,int>> g[], int n, int s, int d) {
    vector<int> dist(n + 1, INT_MAX), parent(n + 1, -1);
    priority_queue<pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>> pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto e : g[u]) {
            int v = e.first, w = e.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[d] == INT_MAX) {
        cout << "No route available!\n";
        return;
    }

    cout << "Shortest Distance: " << dist[d] << " km\n";
    cout << "Shortest Route: ";

    vector<int> path;
    for (int v = d; v != -1; v = parent[v])
        path.push_back(v);

    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

int main() {
    int n, m, u, v, w, s, d;

    cout << "Enter number of emergency centers: ";
    cin >> n;

    vector<pair<int,int>> g[n + 1];

    cout << "Enter number of roads: ";
    cin >> m;

    cout << "Enter roads (center1 center2 distance):\n";
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    cout << "Enter source center: ";
    cin >> s;
    cout << "Enter destination center: ";
    cin >> d;

    BFS(g, n, s);
    dijkstra(g, n, s, d);

    return 0;
}
