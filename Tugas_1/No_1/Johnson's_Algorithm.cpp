#include <bits/stdc++.h>
using namespace std;
#define INF 9999999

struct Edge {
    long u, v, w;
};

bool bellmanFord(long vertexCount, const vector<Edge>& edges, vector<long>& h) {
    h.assign(vertexCount + 1, 0); 
    
    for (long i = 0; i <= vertexCount; i++) {
        for (const auto& edge : edges) {
            if (h[edge.u] != INF && h[edge.u] + edge.w < h[edge.v]) {
                h[edge.v] = h[edge.u] + edge.w;
            }
        }
    }

    for (const auto& edge : edges) {
        if (h[edge.u] != INF && h[edge.u] + edge.w < h[edge.v]) {
            return false;
        }
    }

    return true;
}

void dijkstra(long start, long end, long vertexCount, const vector<vector<pair<long, long>>>& adj, const vector<long>& h) {
    priority_queue<pair<long, long>, vector<pair<long, long>>, greater<pair<long, long>>> pq;
    vector<long> dist_hat(vertexCount + 1, INF);
    vector<long> parent(vertexCount + 1, -1);
    
    dist_hat[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        long d = pq.top().first;
        long u = pq.top().second;
        pq.pop();
        
        if (d > dist_hat[u]) continue;
        
        for (const auto& neighbor : adj[u]) {
            long v = neighbor.first;
            long weight = neighbor.second; 
            
            if (dist_hat[u] + weight < dist_hat[v]) {
                dist_hat[v] = dist_hat[u] + weight;
                parent[v] = u;
                pq.push({dist_hat[v], v});
            }
        }
    }

    cout << "\n=== Algoritma Johnson ===\n";
    cout << endl;

    if (dist_hat[end] >= INF) {
        cout << "Tidak ada rute dari v-" << start << " ke v-" << end << "\n";
    } else {
        long real_dist = dist_hat[end] + h[end] - h[start];
        cout << "Jarak terpendek v-" << start << " ke v-" << end << " = " << real_dist << "\n";
        
        vector<long> path;
        for (long at = end; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        
        cout << "Rute yang ditempuh: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << "v-" << path[i];
            if (i + 1 < path.size()) cout << " -> ";
        }
        cout << "\n";
    }
}

int main(void) {
    long vertexCount, edgeCount;
    if (!(cin >> vertexCount >> edgeCount)) return 0;
    
    vector<Edge> originalEdges;
    vector<Edge> bellmanEdges;
    
    for (long i = 1; i <= vertexCount; i++) {
        bellmanEdges.push_back({0, i, 0});
    }
    
    for (long i = 0; i < edgeCount; i++) {
        long u, v, w;
        cin >> u >> v >> w;
        originalEdges.push_back({u, v, w});
        originalEdges.push_back({v, u, w});
        bellmanEdges.push_back({u, v, w});
        bellmanEdges.push_back({v, u, w});
    }
    
    long start, end;
    cin >> start >> end;
    
    vector<long> h;
    if (!bellmanFord(vertexCount, bellmanEdges, h)) {
        cout << "\n=== Algoritma Johnson ===\n";
        cout << "Graf mengandung siklus bernilai negatif (negative-weight cycle)!\n";
        return 0;
    }
    
    vector<vector<pair<long, long>>> adj(vertexCount + 1);
    for (const auto& edge : originalEdges) {
        long reweighted = edge.w + h[edge.u] - h[edge.v];
        adj[edge.u].push_back({edge.v, reweighted});
    }
    
    dijkstra(start, end, vertexCount, adj, h);
    
    return 0;
}
