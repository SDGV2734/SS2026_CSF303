# Assignment 2

**Module: Competitive Programming**

**Module Code: CSF303**

**Student Name: Sonam Dorji Ghalley**

**Student ID: 022320299**

## **Topics: Bitmasking, Johnson's Algorithm, Arbitrage Detection, Edmonds' Algorithm, KMP, Rabin-Karp**

### **Question 1: Bitmasking**

#### **Subset Enumeration via Bitmasking**

The `N` integers which have N values that do not exceed 20 create all their possible subsets through their association with unique bitmask values which exist between 0 and $2^N − 1$. The bit `i` of the mask shows that element `i` has been included to form that specific subset:

```cpp
int total_subsets = 1 << N;   // 2^N

for (int mask = 0; mask < total_subsets; ++mask) {
    long long sum = 0;
    for (int i = 0; i < N; ++i)
        if (mask & (1 << i))   // bit i set → include a[i]
            sum += a[i];

    if (sum % K == 0) ++count;
}
```

- [source code](./bitmasking.cpp)

---

 **Example:**

Input: N=4, elements={1, 2, 3, 4}, K=3. Total subsets = 16

| **Mask (binary)** | **Subset**     | **Sum** | **Div by 3?** |
| ----------------- | -------------- | ------- | ------------- |
| 0000              | { }            | 0       | **Yes**       |
| 0001              | { 1 }          | 1       | No            |
| 0010              | { 2 }          | 2       | No            |
| 0011              | { 1, 2 }       | 3       | **Yes**       |
| 0100              | { 3 }          | 3       | **Yes**       |
| 0101              | { 1, 3 }       | 4       | No            |
| 0110              | { 2, 3 }       | 5       | No            |
| 0111              | { 1, 2, 3 }    | 6       | **Yes**       |
| 1000              | { 4 }          | 4       | No            |
| 1001              | { 1, 4 }       | 5       | No            |
| 1010              | { 2, 4 }       | 6       | **Yes**       |
| 1011              | { 1, 2, 4 }    | 7       | No            |
| 1100              | { 3, 4 }       | 7       | No            |
| 1101              | { 1, 3, 4 }    | 8       | No            |
| 1110              | { 2, 3, 4 }    | 9       | **Yes**       |
| 1111              | { 1, 2, 3, 4 } | 10      | No            |

**Result:** 6 subsets have a sum divisible by 3.

**Complexity:** O($2^N × N$) time - practical for N ≤ 20 (at most ~20 million iterations).

### **Question 2: Johnson's Algorithm**

#### **Part (a) - Efficiency vs. Floyd-Warshall for Sparse Graphs**

| **Metric**       | **Floyd-Warshall**      | **Johnson's Algorithm**                         |
| ---------------- | ----------------------- | ----------------------------------------------- |
| Time complexity  | O(V³)                   | O($V² log V + V·E$) — Dijkstra with binary heap |
| Space complexity | O(V²)                   | O($V²$) for output, O(V+E) working space        |
| Best suited for  | Dense graphs ($E ≈ V²$) | Sparse graphs (E << $V²$)                       |
| Negative weights | Handled directly        | Handled via Bellman-Ford reweighting            |

The comparison of Johnson's $(V* E log V)$ to Floyd-Warshall's $(V³)$ shows that Johnson's term grows at a slower rate for dispersed graphs which have `E` values that are considerably less than $V²$. The sparse graph with `V=1000` and `E=2000` demonstrates that Johnson's algorithm performs at around $2×10⁷$ operations while Floyd-Warshall requires approximately $10⁹$ operations which results in a speed advantage of 50 times.

#### **Part (b) — Edge Reweighting & Bellman-Ford's Role**

Dijkstra algorithm needs edges to have non-negative weights which prevents Johnson algorithm from using it directly. The method of edge reweighting achieves its goal by maintaining the original shortest-path structure.

- **Step 1** - Add a new source vertex `q`: The graph receives a new vertex q which connects to all other vertices through a zero-weight edge. This change does not impact the already established shortest paths.
- **Step 2** - Run Bellman-Ford from `q`: The function $h[v]$ determines the shortest route from `q` to every vertex `v`. The algorithm processes negative weight conditions while it identifies negative cycles which result in a detection of algorithm failure.
- **Step 3** - The process of reweighting all edges begins with the replacement of each edge weight `w(u,v)` through the use of `w'(u,v)` which equals `w(u,v) + h[u] - h[v]`. The method ensures that all reweighted edges remain non-negative because the triangle inequality states that `h[v]` must be less than or equal to `h[u] + w(u,v)` .
- **step 4** - Dijkstra algorithm needs to be executed for every starting point of the graph. Dijkstra algorithm now works correctly with non-negative reweighted edges. The process starts with distance calculations of `d'(u,v)` followed by path reconstruction through `d(u,v)` which equals `d'(u,v) - h[u] + h[v].`

**Key insight:** 

The reweighting process keeps the paths in their original order because path P remains shorter than path Q according to the original graph distances. The Bellman-Ford algorithm is selected because it can process negative weight situations while requiring only a single distance measurement from point q to complete the distance calculation.

### **Question 3: Arbitrage Detection in Currency Exchange**

**The currency exchange network is modelled as a weighted directed graph $G = (V, E$):**

- **vertex(V):** Each vertex represents one currency (e.g., USD, EUR, GBP, JPY)
- **Edges(E):** A directed edge from currency `i` to currency `j` represents the availability of an exchange rate `r(i,j)`. The edge exists for every pair where direct exchange is possible.
- **Edge weights:** The exchange rate `r(i,j)` defines the adhesive aspect on part of travel between $i → j$, in the sense that 1 unit of `i` is exchangeable for `r(i,j)` units of `j`.

The existence of an arbitrage opportunity becomes clear through the discovery of a graph cycle which demonstrates that its exchange rate products surpass the value of 1.0. This means that any currency in the cycle will produce more than 1 unit output through the exchange process which starts with 1 unit of any currency and ends with the same currency.

#### **Part (b) — Logarithmic Transformation**

The method for detecting cycles uses a product value which exceeds 1 through a process that requires multiplication and requires a different approach from standard graph algorithms. The process of logarithmic transformation allows multiplication operations to be transformed into addition operations:

```cpp
// Transform: replace each edge weight w(i,j) = r(i,j) with:
w'(i,j) = -log(r(i,j))

// A cycle i → j → k → i has product > 1 iff:
r(i,j) × r(j,k) × r(k,i) > 1

// Taking log of both sides:
log(r(i,j)) + log(r(j,k)) + log(r(k,i)) > 0

// Negating (to convert maximisation to minimisation):
-log(r(i,j)) + -log(r(j,k)) + -log(r(k,i)) < 0

// Therefore: a negative cycle in the transformed graph
// ↔ an arbitrage opportunity in the original graph
```

#### **Part (c) — Algorithm Choice & Justification**

**Algorithm: Bellman-Ford is the correct algorithm for arbitrage detection.**

- **Handles negative weights:** The log transformation process transforms edge weights into real-number values which permit negative values when `r` exceeds 1. Dijkstra algorithm fails to process negative weights but Bellman-Ford algorithm can handle them correctly.
- **Detects negative cycles:** Bellman-Ford's `V-th` relaxation pass directly identifies negative-weight cycles, which correspond exactly to arbitrage opportunities.
- **Reports affected paths:**The Bellman-Ford algorithm enables the identification of vertices that exist on negative cycles or can be accessed from negative cycles which helps in determining the specific currencies that participate in arbitrage trading.
- **Complexity:** O($V × E$) — acceptable for the relatively small number of traded currencies (typically V < 200).

### **Question 4: Edmonds' Algorithm**

**Problem Statement**

**Edmonds' algorithm (also known as Edmonds' Branching Algorithm or Chu-Liu/Edmonds' algorithm) solves the following precisely-stated problem:**

_Given a weighted directed graph G = (V, E) with a designated root vertex $r ∈ V$, find a minimum-weight spanning arborescence rooted at r — that is, a spanning subgraph in which r has in-degree 0, every other vertex $v ≠ r$ has in-degree exactly 1, and the unique directed path from r to each vertex v follows the tree edges, all while minimising the total sum of edge weights._

**Formal Definition:**

- **Phase 1 — Greedy selection:** The procedure requires selection of the least weight incoming edge for every non-root vertex v. The algorithm shows an growth when these selected edges create an arborescence structure.
- **Phase 2 — Cycle contraction:** The directed cycle C should be contracted into a single super-vertex while all incoming edge weights need adjustment which requires subtracting the minimum incoming edge weight of each original vertex in C from their respective edge weights.
- **Phase 3 — Recursion & expansion:** You should first apply recursion to the contracted graph and then you need to restore the original graph through solution expansion which starts by breaking the cycle at the vertex whose incoming edge was replaced.
- **Complexity:** $O(E log V)$ with a Fibonacci heap, or $O(V·E)$ with simpler implementations.

**Contrast with MST:** Edmonds' algorithm solves the directed equivalent of Kruskal's/Prim's minimum spanning tree problem. The directed constraint requires all non-root vertices to select exactly one incoming edge but the process also needs to avoid cycles through contraction and expansion operations.

### **Question 5: String Matching Algorithms**

#### **Part (a) — KMP: LPS Array for "ABABCABAB"**

The KMP algorithm uses the Longest Prefix Suffix (LPS) array which people also refer to as the failure function. The LPS array element LPS[i] shows the length of the longest proper prefix which serves as a suffix for the substring pattern`[0..i]`.

**Pattern: ABABCABAB:**

| **Index** | 0     | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     |
| --------- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |
| **Char**  | **A** | **B** | **A** | **B** | **C** | **A** | **B** | **A** | **B** |
| **LPS**   | 0     | 0     | 1     | 2     | 0     | 1     | 2     | 3     | 4     |

**Step-by-step construction:**

| **i** | **Char** | **LPS[i]** | **Comparison**                                           | **Reasoning**                                  |
| ----- | -------- | ---------- | -------------------------------------------------------- | ---------------------------------------------- |
| 0     | A        | **0**      | (base case)                                              | LPS[0] is always 0 — no proper prefix possible |
| 1     | B        | **0**      | $pattern[0]='A' ≠ pattern[1]='B'$                        | No matching prefix-suffix; LPS[1]=0            |
| 2     | A        | **1**      | $pattern[0]='A' = pattern[2]='A'$                        | 'A' matches; LPS[2]=1                          |
| 3     | B        | **2**      | $pattern[1]='B' = pattern[3]='B'$                        | 'AB' matches; LPS[3]=2                         |
| 4     | C        | **0**      | $pattern[2]='A' ≠ pattern[4]='C'; fallback→''; no match$ | LPS[4]=0                                       |
| 5     | A        | **1**      | $pattern[0]='A' = pattern[5]='A'$                        | 'A' matches; LPS[5]=1                          |
| 6     | B        | **2**      | $pattern[1]='B' = pattern[6]='B'$                        | 'AB' matches; LPS[6]=2                         |
| 7     | A        | **3**      | $pattern[2]='A' = pattern[7]='A'$                        | 'ABA' matches; LPS[7]=3                        |
| 8     | B        | **4**      | $pattern[3]='B' = pattern[8]='B'$                        | 'ABAB' matches; LPS[8]=4                       |

The LPS array enables KMP to avoid redundant comparisons. Upon detecting a mismatch at index `i` in the pattern KMP directly uses `LPS[i−1]` to skip to that index after using knowledge from earlier partial matches. The process reaches an overall matching complexity of $O(N+M)$ through this technique.

#### **Part (b) — Rabin-Karp: Collision Handling & Complexity**

**Hash Collision Handling**

The Rabin-Karp algorithm employs a rolling polynomial hash function to perform efficient text window movement. A hash collision (spurious hit) occurs when the hash value of a text window equals the pattern hash, but the actual characters differ. The situation is managed through these particular methods:

- **Hash match detected:** When hash`(text[i..i+m−1]) == hash(pattern)`, a character-by-character verification is performed in O(M) time before reporting a match.
- **False positive:** The system establishes character matching requirements to verify proper processing of the data. The window keeps moving forward because no matching result has been established.
- **Minimising collisions:** The use of a major prime modulus which equals `10⁹+7` creates a substantial decrease in the likelihood of hash function collisions. The implementation of double-hashing through two distinct hash functions creates a system which results in almost no false positive detections.

```cpp
// Rolling hash update — O(1) per slide
win_hash = (BASE * (win_hash - text[i]*h) + text[i+m]) % MOD;

// On hash match: verify explicitly
if (win_hash == pat_hash && text.substr(i,m) == pattern)
    matches.push_back(i);  // confirmed match
// else: spurious hash collision, continue sliding
```

- [source code](./string-matching.cpp)

---

**Time Complexity**

| **Case**      | **Complexity** | **Explanation**                                                                                                                                                                                      |
| ------------- | -------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Average case  | **$O(N + M)$** | Good hash functions create extremely rare occurrences of hash collisions. The assessment of each window requires constant time O(1) while the verification process occurs only in exceptional cases. |
| Worst case    | **$O(N × M)$** | Every window's hash matches the pattern hash (spurious hits), triggering O(M) verification for each of O(N) windows. Example: text="aaa…a", pattern="aa".                                            |
| Preprocessing | $O(M)$         | Computing the initial hash for the pattern and the first window.                                                                                                                                     |

**The KMP algorithm achieves its worst-case runtime of $O(N + M)$ because it employs LPS array to eliminate unnecessary pattern matching operations. Rabin-Karp provides its strongest performance through its ability to conduct simultaneous searches for multiple patterns by using a hash set which operates at an average time cost of $O(N)$.**

---

## **References**

### **Bitmasking and Bit Manipulation**

1. Kernighan, B. W., & Ritchie, D. M. (1988). _The C Programming Language_ (2nd ed.). Prentice Hall.
   - Classic reference on bitwise operations and low-level programming techniques.

2. Halim, S., & Halim, F. (2013). _Competitive Programming 3: The New Lower Bound of Programming Contests_. Lulu.
   - Practical guide including bitmask enumeration for subset generation and dynamic programming.

3. GeeksforGeeks. _Bitmasking and Dynamic Programming_. https://www.geeksforgeeks.org/tag/bitmasking/
   - Tutorials on bitmask techniques and common problem patterns.

### **Graph Algorithms - Johnson's Algorithm**

4. Johnson, D. B. (1977). "Efficient All-Pairs Shortest Paths Computation." _SIAM Journal on Computing_, 6(2), 268-279.
   - Original paper introducing Johnson's algorithm for all-pairs shortest paths.

5. Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). _Introduction to Algorithms_ (3rd ed.). MIT Press.
   - Comprehensive treatment of Johnson's algorithm (p. 685-695) with detailed complexity analysis.

6. Dijkstra, E. W. (1959). "A Note on Two Problems in Connexion with Graphs." _Numerische Mathematik_, 1(1), 269-271.
   - Original paper on Dijkstra's algorithm, fundamental to Johnson's approach.

### **Arbitrage Detection and Currency Exchange**

7. Sedgewick, R., & Wayne, K. (2011). _Algorithms_ (4th ed.). Addison-Wesley Professional.
   - Section on negative weight cycles and arbitrage detection in currency exchange networks.

8. Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). _Introduction to Algorithms_ (3rd ed.). MIT Press.
   - Bellman-Ford algorithm and negative cycle detection (p. 643-662).

9. Logarithmic transformation for graph problems. _Algorithm Archives_. https://www.algorithms.org/
   - Detailed explanation of converting multiplicative constraints to additive ones via logarithms.

### **Edmonds' Algorithm - Directed Minimum Spanning Arborescence**

10. Edmonds, J. (1967). "Optimum Branchings." _Journal of Research of the National Bureau of Standards_, 71B(4), 233-240.
    - Seminal paper introducing the algorithm for finding minimum-weight spanning arborescences.

11. Chu, Y. J., & Liu, T. H. (1965). "On the Shortest Arborescence of a Directed Graph." _Scientia Sinica_, 14(10), 1396-1400.
    - Early work on the directed spanning tree problem, leading to Edmonds' algorithm.

12. Tarjan, R. E. (1977). "Finding Optimum Branchings." _Networks_, 7(1), 25-35.
    - Efficient implementation techniques for Edmonds' algorithm.

13. Wikipedia. _Edmonds' Algorithm_. https://en.wikipedia.org/wiki/Edmonds%27_algorithm
    - Overview and implementation guidance for minimum spanning arborescence.

### **String Matching - KMP Algorithm**

14. Knuth, D. E., Morris Jr., J. H., & Pratt, V. R. (1977). "Fast Pattern Matching in Strings." _SIAM Journal on Computing_, 6(2), 323-350.
    - Original paper introducing the Knuth-Morris-Pratt algorithm with failure function (LPS array).

15. Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). _Introduction to Algorithms_ (3rd ed.). MIT Press.
    - KMP algorithm explanation with pseudocode and complexity analysis (p. 1003-1013).

16. GeeksforGeeks. _KMP Algorithm_. https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-matching/
    - Step-by-step KMP implementation with LPS array construction examples.

### **String Matching - Rabin-Karp Algorithm**

17. Rabin, M. O., & Karp, R. M. (1987). "Efficient Randomized Pattern-Matching Algorithms." _IBM Journal of Research and Development_, 31(2), 249-260.
    - Original paper presenting the Rabin-Karp rolling hash algorithm for pattern matching.

18. Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). _Introduction to Algorithms_ (3rd ed.). MIT Press.
    - Rabin-Karp algorithm and hash collision handling (p. 1015-1021).

19. Wikipedia. _Rabin-Karp Algorithm_. https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm
    - Overview of rolling hash computation and multiple pattern matching applications.


