import itertools

nodes = ['u', 'v', 'w', 'x', 'y', 'z']

edges = {
    ('u', 'x'): 60, 
    ('u', 'w'): 56, 
    ('u', 'v'): 51, 
    ('u', 'z'): 35, 
    ('u', 'y'): 2,
    ('x', 'w'): 70, 
    ('x', 'v'): 13, 
    ('x', 'z'): 68, 
    ('x', 'y'): 61,
    ('v', 'y'): 51, 
    ('v', 'z'): 68, 
    ('v', 'w'): 78,
    ('w', 'z'): 21, 
    ('w', 'y'): 57,
    ('y', 'z'): 36
}

graph = {node: {} for node in nodes}

for (n1, n2), weight in edges.items():
    graph[n1][n2] = weight
    graph[n2][n1] = weight

min_weight = float('inf')
best_tour = None

for p in itertools.permutations(nodes):
    weight = 0
    for i in range(len(p) - 1):
        weight += graph[p[i]][p[i+1]]
    weight += graph[p[-1]][p[0]]
    
    if weight < min_weight:
        min_weight = weight
        best_tour = p

print("Nearest Neighbour")
print(best_tour)
print(min_weight)
