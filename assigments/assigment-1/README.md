# Assignment 1

**Module: Competitive Programming**

**Module Code: CSF303**

**Student Name: Sonam Dorji Ghalley**

**Student ID: 022320299**

## **Topics: STL Containers, Bellman-Ford Algorithm, Floyd-Warshall Algorithm**

### **Question 1: STL Usage in C++**

This question demonstrates efficient use of three core STL containers: vector, deque, and std::array. The first part of the project uses STL iterators and utilities to create its loops which run through all elements of the data.

#### **Part (a) — std::vector: Reverse Output**

The program first fills a std::vector<int> with N integers before it displays the contents in reverse order. The method displays all elements without changing the actual container. The operation requires O(N) time for processing while using O(1) additional memory space.

```cpp
std::vector<int> vec(n);
for (int& x : vec) std::cin >> x;

// Reverse iteration — O(N), O(1) extra space
for (auto it = vec.rbegin(); it != vec.rend(); ++it)
    std::cout << *it << " ";
```
- [source code](./Q-1-STL.cpp)
___

The design decision depends on the implementation of reverse iterators which use `rbegin` and `rend` as their standard C++ functions. The system provides an alternative method of using std::reverse together with forward iteration which leads to container modification. The system offers reverse iterators as the preferred method for non-destructive operations.

#### **Part (b) — std::deque: Operation Sequence**

The deque (double-ended queue) system allows for insertion and removal operations to be performed on both ends of the system at constant time O(1) efficiency. The subsequent operations will be demonstrated through their execution which will display the resulting state of the system.

| **Operation**  | **Value** | **Deque State (front→back)** | **Notes**         |
| -------------- | --------- | ---------------------------- | ----------------- |
| push_back(10)  | 10        | [10]                         | Initial insertion |
| push_back(20)  | 20        | [10, 20]                     | Append to rear    |
| push_front(5)  | 5         | [5, 10, 20]                  | Prepend to front  |
| push_back(30)  | 30        | [5, 10, 20, 30]              | Append to rear    |
| pop_front()    | —         | [10, 20, 30]                 | Removes 5         |
| push_front(15) | 15        | [15, 10, 20, 30]             | Prepend to front  |
| push_back(40)  | 40        | [15, 10, 20, 30, 40]         | Append to rear    |
| pop_front()    | —         | [10, 20, 30, 40]             | Final state       |

#### **Part (c) — std::array: Fixed-Size Sum**

The std::array<int, N> serves as a container that requires stack memory for its fixed-size storage. The container operates with a fixed size determined at compile time, which makes it more efficient than std::vector for collections of small size with known dimensions. The function uses std::accumulate from <numeric> to calculate the total sum.

```cpp
constexpr std::size_t SIZE = 8;
std::array<int, SIZE> arr = {3, 7, 1, 9, 4, 6, 2, 8};

// std::accumulate: O(N), no manual loop required
int total = std::accumulate(arr.begin(), arr.end(), 0);
// Result: 40

```
- [source code](./Q-1-STL.cpp)

**Complexity Summary:**

1. **Part (a) - O(N) time, O(1) space (reverse iteration).**
2. **Part (b) - O(1) per operation.**
3. **Part (c) - O(N) for accumulate, O(1) space.**
___

### **Question 2: Bellman-Ford Algorithm**

#### **Algorithm Overview**

The Bellman-Ford algorithm computes single-source shortest paths in a weighted directed graph, correctly handling negative edge weights. The algorithm operates with a time complexity of O(V × E) and requires O(V) space to store the distance array.

#### **Core Logic**

**The relaxation phase:** It requires V−1 iterations during which edge (u, v, w) processing occurs. The distance to vertex v gets updated when the distance from u plus weight w becomes less than the existing distance to v. After V−1 iterations all shortest paths become optimal because any simple path can only use V−1 edges at most.

**The detection of cycles:** It requires one more round of relaxation to be completed. The existence of a negative-weight cycle which connects to the starting point becomes obvious when any existing distance still requires relaxation.

```cpp
// Initialise
dist[src] = 0; all others = INF;

// Phase 1: Relax V-1 times
for (int iter = 0; iter < V - 1; ++iter) {
    for (const Edge& e : edges) {
        if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v])
            dist[e.v] = dist[e.u] + e.w;
    }
}

// Phase 2: Detect negative cycle
for (const Edge& e : edges)
    if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v])
        negative_cycle = true;

```
- [source code](./Q-2-bellmanford.cpp)


**Example:**

![image.png](Assignment%201/image.png)

**Graph: V=5, E=8, edges: (0,1,−1), (0,2,4), (1,2,3), (1,3,2), (1,4,2), (3,2,5), (3,1,1), (4,3,−3). Source = 0.**

| **Vertex** | **Distance** | **Reachable?** | **Notes**          |
| ---------- | ------------ | -------------- | ------------------ |
| 0          | 0            | Yes (source)   | Start vertex       |
| 1          | −1           | Yes            | Via edge (0→1: −1) |
| 2          | 2            | Yes            | 0→1→2: −1+3=2      |
| 3          | −2           | Yes            | 0→1→4→3: −1+2+(−3) |
| 4          | 1            | Yes            | 0→1→4: −1+2=1      |

The time Complexity O(V × E) and space Complexity O(V) The early-termination optimisation exits as soon as no update occurs in an iteration, which helps to improve average-case performance of the algorithm.
___

### **Question 3: Floyd-Warshall Algorithm**

#### **Algorithm Overview**

The Floyd-Warshall algorithm uses dynamic programming(DP) to find the shortest paths between all pairs of vertices. The algorithm requires O(V³) time to complete its execution and needs O(V²) memory space for its operations. The key DP recurrence is:

```cpp
dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

for each intermediate vertex k from 0 to V-1
    for each source      i from 0 to V-1
        for each target   j from 0 to V-1
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

```
- [source code](./Q-3-floydwarshall.cpp)

#### **Negative Cycle Detection**

After the algorithm completes, we need to examine the principal diagonal of the matrix. Any vertex `i` that has a `dist[i][i]` value less than 0, there exists on a negative-weight cycle. Any path that passes through such a vertex becomes undefined with a value of effectively negative infinity.

```cpp
for (int i = 0; i < V; ++i)
    if (dist[i][i] < 0) { neg_cycle = true; break; }

```

 **Example:**

![image.png](Assignment%201/image%201.png)

**Graph: V=4, Edges: (0,1,3),(0,3,7),(1,2,2),(2,0,−5),(3,0,2),(1,3,4). Resulting distance matrix:**

|        | **v0** | **v1** | **v2** | **v3** |
| ------ | ------ | ------ | ------ | ------ |
| **v0** | 0      | 3      | 5      | 7      |
| **v1** | −3     | 0      | 2      | 4      |
| **v2** | −5     | −2     | 0      | 2      |
| **v3** | 2      | 5      | 7      | 0      |

#### **Theoretical Explanation**

Why Floyd-Warshall works with negative edge weights ?

The Floyd-Warshall algorithm uses dynamic programming to evaluate all vertices as possible intermediate points on paths between two vertices. The algorithm uses distance relaxation by checking the sum of dist[i][k] and dist[k][j] because it can process negative values through its design which permits edge weights to have negative values. The shortest path between any two vertices can be broken down into optimal sub-paths as long as no negative cycle exists which meets the criteria for optimal substructure.

Why Floyd-Warshall fails with negative-weight cycles ?

The existence of a reachable negative cycle between vertices i and j prevents the determination of a shortest path because infinite cycle repetitions lead to cost reductions which reach minus infinity. The algorithm will not reach any specific numerical solution for this situation. The condition dist[i][i] < 0 indicates that vertex i can reach itself with negative total cost which creates a logical contradiction because simple paths cannot exist under this condition, thereby breaking the DP algorithm's fundamental rule of optimal substructure.

---

## **References**

### **STL Containers and C++ Standard Library**

1. Stroustrup, B. (2013). _The C++ Programming Language_ (4th ed.). Addison-Wesley Professional.
   - Comprehensive coverage of STL containers including vector, deque, and array.

2. Josuttis, N. M. (2012). _The C++ Standard Library: A Tutorial and Reference_ (2nd ed.). Addison-Wesley Professional.
   - Detailed reference for C++ STL including iterators and container operations.

3. cppreference.com. _C++ Reference: Containers_. https://en.cppreference.com/w/cpp/container
   - Online reference documentation for all STL containers and their methods.

4. cppreference.com. _C++ Reference: Algorithms_. https://en.cppreference.com/w/cpp/algorithm
   - Documentation for std::accumulate and other algorithm utilities.

### **Graph Algorithms**

5. Bellman, R. (1958). "On a Routing Problem." _Quarterly of Applied Mathematics_, 16(1), 87-90.
   - Original paper introducing the Bellman-Ford algorithm for shortest path computation.

6. Floyd, R. W. (1962). "Algorithm 97: Shortest Path." _Communications of the ACM_, 5(6), 345.
   - Original paper on the Floyd-Warshall algorithm for all-pairs shortest paths.

7. Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). _Introduction to Algorithms_ (3rd ed.). MIT Press.
   - Standard textbook covering Bellman-Ford (p. 643-662), Floyd-Warshall (p. 690-701), and graph theory fundamentals.

8. Sedgewick, R., & Wayne, K. (2011). _Algorithms_ (4th ed.). Addison-Wesley Professional.
   - Comprehensive treatment of shortest path algorithms with detailed implementations.

### **Competitive Programming**

9. Halim, S., & Halim, F. (2013). _Competitive Programming 3: The New Lower Bound of Programming Contests_. Lulu.
   - Practical guide for competitive programming with algorithm implementations and problem-solving strategies.

10. GeeksforGeeks. _Graph Algorithms_. https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/
    - Online tutorials and implementations for graph algorithms including shortest paths.

### **Negative Cycles and Weight Detection**

11. Wikipedia. _Bellman-Ford Algorithm_. https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
    - Overview of the algorithm with focus on negative cycle detection.

12. Wikipedia. _Floyd-Warshall Algorithm_. https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
    - Comprehensive explanation of the all-pairs shortest path algorithm.
