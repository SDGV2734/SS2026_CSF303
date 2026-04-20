#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

int main() {
    int N;
    std::cout << "Enter N: ";
    std::cin >> N;

    std::vector<int> a(N);
    std::cout << "Enter " << N << " integers: ";
    for (int& x : a) std::cin >> x;

    int K;
    std::cout << "Enter K: ";
    std::cin >> K;

    int total_subsets = 1 << N;   // 2^N
    int count = 0;

    std::cout << "\nAll subsets:\n";

    for (int mask = 0; mask < total_subsets; ++mask) {
        long long sum = 0;
        std::string subset = "{ ";

        for (int i = 0; i < N; ++i) {
            if (mask & (1 << i)) {         // bit i is set → element i is in subset
                sum += a[i];
                subset += std::to_string(a[i]) + " ";
            }
        }
        subset += "}";

        bool divisible = (sum % K == 0);
        if (divisible) ++count;

        std::cout << "Mask " << std::string(N, ' ');
        // Print binary representation
        for (int i = N - 1; i >= 0; --i)
            std::cout << ((mask >> i) & 1);
        std::cout << " | " << std::setw(20) << std::left << subset
                  << " | sum = " << std::setw(6) << sum
                  << (divisible ? "  ← divisible by " + std::to_string(K) : "")
                  << "\n";
    }

    std::cout << "\nTotal subsets: " << total_subsets << "\n";
    std::cout << "Subsets with sum divisible by " << K << ": " << count << "\n";

    return 0;
}