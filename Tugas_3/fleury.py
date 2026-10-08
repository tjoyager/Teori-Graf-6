import copy

edges = [
    ('u', 'x', 1), ('u', 'y', 4), ('u', 'w', 5),
    ('x', 'y', 2), ('x', 'z', 3), ('x', 'v', 6),
    ('y', 'w', 1), ('y', 'z', 2),
    ('w', 'z', 2), ('w', 'v', 2),
    ('z', 'v', 3)
]

graph = {node: [] for node in 'uxywzv'}
weights = {}

for u, v, w in edges:
    graph[u].append(v)
    graph[v].append(u)
    weights[(u, v)] = w
    weights[(v, u)] = w

def is_bridge(g, u, v):
    if g[u].count(v) > 1:
        return False
    
    def dfs(node, visited):
        count = 1
        visited.add(node)
        for neighbor in set(g[node]):
            if neighbor not in visited:
                count += dfs(neighbor, visited)
        return count

    count1 = dfs(u, set())

    g[u].remove(v)
    g[v].remove(u)

    count2 = dfs(u, set())

    g[u].append(v)
    g[v].append(u)

    return count1 > count2

def fleury(start, g):
    g_copy = copy.deepcopy(g)
    path = [start]
    curr = start

    while g_copy[curr]:
        next_node = None
        if len(set(g_copy[curr])) == 1:
            next_node = g_copy[curr][0]
        else:
            for neighbor in sorted(g_copy[curr], key=lambda n: weights[(curr, n)]):
                if not is_bridge(g_copy, curr, neighbor):
                    next_node = neighbor
                    break
            if not next_node:
                next_node = g_copy[curr][0]
        
        g_copy[curr].remove(next_node)
        g_copy[next_node].remove(curr)
        path.append(next_node)
        curr = next_node

    return path

optimal_tour = fleury('u', graph)
total_weight = sum(weights[(optimal_tour[i], optimal_tour[i+1])] for i in range(len(optimal_tour)-1))

print(optimal_tour)
print(total_weight)
