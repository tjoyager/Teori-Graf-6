#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<long,long>>> adjList;

void addEdge(long u, long v, long w){
    adjList[u].push_back({v, w});
    adjList[v].push_back({u, w});
}

void dijkstra(vector<long> &result, long start, long vertexCount){
    vector<bool> visited(vertexCount + 1, false);
    priority_queue <pair<long, long>,
                    vector <pair<long, long>>,
                    greater <pair<long, long>> > pq;
    result = vector<long>(vertexCount + 1, LONG_MAX);


    pq.push(make_pair(0, start));
    result[start] = 0;


    while(!pq.empty()){
        auto temp = pq.top();
        pq.pop();
        if(visited[temp.second]) continue;
        visited[temp.second] = true;


        for(auto vertex : adjList[temp.second]){
            long nextVertex = vertex.first;
            long weight = vertex.second;


            if(temp.first + weight < result[nextVertex]) {
                result[nextVertex] = temp.first + weight;
                pq.push(make_pair(result[nextVertex], nextVertex));
            }
        }
    }
}


int main(void){
    long vertexCount, edgeCount;
    cin >> vertexCount >> edgeCount;

    adjList.assign(vertexCount + 1, {});

    for(long i = 0; i < edgeCount; i++){
        long u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }

    long start, end;
    cin >> start >> end;

    vector<long> result;
    dijkstra(result, start, vertexCount);

    cout << "\nJarak terpendek v-" << start << " ke v-" << end << " = " << result[end] << "\n";

    return 0;
}
