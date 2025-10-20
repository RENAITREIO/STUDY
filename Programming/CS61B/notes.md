# CS61B notes

### tree traversals
- pre-order traversal  
use: for printing directary listing

- in-order traversal

- post-order traversal  
use: for gathering file sizes

- level order(BFS)

### graph
simple graph  
no "length 1 loops"  
no "parallel edges"  

s-t connectivity  
connected(s, t)  

depth-first search(DFS)  

graph traversals
- dfs preorder(dfs calls)
- dfs postorder(dfs returns)

graph representations
- adjacency matrix
- edge sets
- adjacency lists(recommanded)

breadth-first search  
implement with queue

### Dijkstra's algorithm
construct a shortest-path tree

### A* algorithm
`d(initial, v) + h(v, goal)`  
need to choose good heuristics
```
OPEN = priority queue containing START
CLOSED = empty set
while lowest rank in OPEN is not the GOAL:
  current = remove lowest rank item from OPEN
  add current to CLOSED
  for neighbors of current:
    cost = g(current) + movementcost(current, neighbor)
    if neighbor in OPEN and cost less than g(neighbor):
      remove neighbor from OPEN, because new path is better
    if neighbor in CLOSED and cost less than g(neighbor):
      remove neighbor from CLOSED
    if neighbor not in OPEN and neighbor not in CLOSED:
      set g(neighbor) to cost
      add neighbor to OPEN
      set priority queue rank to g(neighbor) + h(neighbor)
      set neighbor's parent to current

reconstruct reverse path from goal to start
by following parent pointers
```

## minimum spanning trees
Cycle Property and Cut Property  
Prim's algorithm(use cut property)  
Kruskal's algorithm

directed acyclic graphs  
topological sort  
DAG shortest paths(can find path with negative edges)  
DAG longest paths: flip all the weights and use shortest path algorithm

### Tries
a digit-by-digit set representation  
the hash-table based trie  
the BST-based trie  

## Sorting
- selection sort
- heapsort(naive, in-place(without priority queue, max-heap is better))
- mergesort
- insertion sort(does very little work if nearly sorted)
- quicksort/partition sort(BST sort)  
Hoare partitioning(a partition algorithm make quicksort faster)  
(quick select: use partition algorithm to find the median)
- sleep sort
- counting sort
- radix sort(LSD, MSD)

### theoretical bounds
comparison sorts: heapsort, mergesort, quicksort, insertion sort, selection sort, bubble sort  
non-comparison sorts: radix sort, sleepsort, gravity sort, BOGOsort  
log(N!) = N log N








## Reflection
- sentinel may be useful
- set with comparator is better than list with sort
