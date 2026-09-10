#include <bits/stdc++.h>
using namespace std;
#define INF 9999999

int main(void) {
    long vertexCount, edgeCount;
    if (!(cin >> vertexCount >> edgeCount)) return 0;
    
    vector<vector<long>> dist(vertexCount + 1, vector<long>(vertexCount + 1, INF));
    vector<vector<long>> next_node(vertexCount + 1, vector<long>(vertexCount + 1, -1));
    
    for (long i = 1; i <= vertexCount; i++) {
        dist[i][i] = 0;
        next_node[i][i] = i;
    }
    
    for (long i = 0; i < edgeCount; i++) {
        long u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = w;
        dist[v][u] = w;
        next_node[u][v] = v;
        next_node[v][u] = u;
    }
    
    long start, end;
    cin >> start >> end;

    for (long k = 1; k <= vertexCount; k++) {
        for (long i = 1; i <= vertexCount; i++) {
            for (long j = 1; j <= vertexCount; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next_node[i][j] = next_node[i][k];
                    }
                }
            }
        }
    }
    
    cout << "\n=== Algoritma Floyd-Warshall ===\n";
    cout << endl;

    if (dist[start][end] >= INF) {
        cout << "Tidak ada rute dari v-" << start << " ke v-" << end << "\n";
    } else {
        cout << "Jarak terpendek v-" << start << " ke v-" << end << " = " << dist[start][end] << "\n";
        
        cout << "Rute yang ditempuh: ";
        long curr = start;
        cout << "v-" << curr;
        while (curr != end) {
            curr = next_node[curr][end];
            cout << " -> v-" << curr;
        }
        cout << "\n";
    }
    
    return 0;
}