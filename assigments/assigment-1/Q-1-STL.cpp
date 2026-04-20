#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <algorithm>   // std::reverse, std::accumulate (via numeric)
#include <numeric>     // std::accumulate
#include <iterator>    // std::ostream_iterator

// ─────────────────────────────────────────────
// Part (a): vector – store N integers, print in reverse
// ─────────────────────────────────────────────
void part_a() {
    std::cout << "=== Part (a): Vector – Reverse Output ===\n";

    int n;
    std::cout << "Enter N: ";
    std::cin >> n;

    std::vector<int> vec(n);
    std::cout << "Enter " << n << " integers: ";
    for (int& x : vec) std::cin >> x;

    // Use STL reverse iterator to print in reverse — O(N), no extra space
    std::cout << "Reversed: ";
    for (auto it = vec.rbegin(); it != vec.rend(); ++it)
        std::cout << *it << " ";
    std::cout << "\n\n";
}

// ─────────────────────────────────────────────
// Part (b): deque – push_front, push_back, pop_front operations
// ─────────────────────────────────────────────
void part_b() {
    std::cout << "=== Part (b): Deque – Operation Sequence ===\n";

    std::deque<int> dq;

    // Simulate a fixed sequence of operations
    struct Op { std::string type; int value; };
    std::vector<Op> ops = {
        {"push_back",  10},
        {"push_back",  20},
        {"push_front",  5},
        {"push_back",  30},
        {"pop_front",   0},   // removes 5
        {"push_front", 15},
        {"push_back",  40},
        {"pop_front",   0},   // removes 10
    };

    for (const auto& op : ops) {
        if (op.type == "push_back") {
            dq.push_back(op.value);
            std::cout << "push_back("  << op.value << ")\n";
        } else if (op.type == "push_front") {
            dq.push_front(op.value);
            std::cout << "push_front(" << op.value << ")\n";
        } else if (op.type == "pop_front") {
            if (!dq.empty()) {
                std::cout << "pop_front() -> removed " << dq.front() << "\n";
                dq.pop_front();
            }
        }
    }

    std::cout << "Final deque contents (front → back): ";
    for (const int& x : dq) std::cout << x << " ";
    std::cout << "\n\n";
}

// ─────────────────────────────────────────────
// Part (c): std::array – fixed-size, compute sum with std::accumulate
// ─────────────────────────────────────────────
void part_c() {
    std::cout << "=== Part (c): std::array – Sum via STL ===\n";

    constexpr std::size_t SIZE = 8;
    std::array<int, SIZE> arr = {3, 7, 1, 9, 4, 6, 2, 8};

    std::cout << "Array elements: ";
    for (const int& x : arr) std::cout << x << " ";
    std::cout << "\n";

    // std::accumulate from <numeric> – O(N)
    int total = std::accumulate(arr.begin(), arr.end(), 0);
    std::cout << "Sum (via std::accumulate): " << total << "\n\n";
}

int main() {
    part_a();
    part_b();
    part_c();
    return 0;
}