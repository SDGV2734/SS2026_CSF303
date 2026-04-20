#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// ═══════════════════════════════════════════════
// Part (a): KMP – Longest Prefix Suffix (LPS)
// ═══════════════════════════════════════════════

/**
 * Builds the LPS (failure function) array for a pattern.
 *
 * lps[i] = length of the longest proper prefix of pattern[0..i]
 *          that is also a suffix of pattern[0..i].
 *
 * Complexity: O(M) where M = pattern length
 */
std::vector<int> compute_lps(const std::string& pattern) {
    int m = pattern.size();
    std::vector<int> lps(m, 0);

    int len = 0;   // length of previous longest prefix-suffix
    int i   = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else {
            if (len != 0)
                len = lps[len - 1];  // fall back – don't increment i
            else
                lps[i++] = 0;
        }
    }
    return lps;
}

void kmp_demo() {
    std::string pattern = "ABABCABAB";
    std::vector<int> lps = compute_lps(pattern);

    std::cout << "=== Part (a): KMP LPS Array ===\n";
    std::cout << "Pattern : ";
    for (char c : pattern) std::cout << c << "  ";
    std::cout << "\n";

    std::cout << "Index   : ";
    for (int i = 0; i < (int)pattern.size(); ++i)
        std::cout << i << "  ";
    std::cout << "\n";

    std::cout << "LPS     : ";
    for (int v : lps) std::cout << v << "  ";
    std::cout << "\n";

    // Step-by-step explanation
    std::cout << "\nStep-by-step construction:\n";
    std::cout << "Index 0 (A)       : lps[0] = 0  (by definition, empty prefix)\n";
    std::cout << "Index 1 (B)       : 'A'!='B'         -> lps[1] = 0\n";
    std::cout << "Index 2 (A)       : 'A'=='A'          -> lps[2] = 1\n";
    std::cout << "Index 3 (B)       : 'B'=='B'          -> lps[3] = 2\n";
    std::cout << "Index 4 (C)       : 'C'!='A', fall -> lps[4] = 0\n";
    std::cout << "Index 5 (A)       : 'A'=='A'          -> lps[5] = 1\n";
    std::cout << "Index 6 (B)       : 'B'=='B'          -> lps[6] = 2\n";
    std::cout << "Index 7 (A)       : 'A'=='A'          -> lps[7] = 3\n";
    std::cout << "Index 8 (B)       : 'B'=='B'          -> lps[8] = 4\n";
    std::cout << "\n";
}

// ═══════════════════════════════════════════════
// Part (b): Rabin-Karp String Matching
// ═══════════════════════════════════════════════

/**
 * Rabin-Karp algorithm using polynomial rolling hash.
 *
 * Hash of s[i..i+m-1] = (s[i]*BASE^(m-1) + ... + s[i+m-1]) mod MOD
 *
 * Rolling hash update (slide window by one):
 *   hash_new = (BASE * (hash_old - s[i]*BASE^(m-1)) + s[i+m]) mod MOD
 *
 * Collision Handling:
 *   When hash(window) == hash(pattern), we do an explicit character-by-
 *   character comparison (verification step). This avoids false positives
 *   from hash collisions while keeping the average case O(N+M).
 *
 * Average case : O(N + M)   – very few spurious hash matches
 * Worst  case  : O(N * M)   – all windows hash-match (e.g. "aaa…a" / "aa")
 */

constexpr long long BASE = 31;
constexpr long long MOD  = 1000000007LL;   // large prime reduces collisions

std::vector<int> rabin_karp(const std::string& text, const std::string& pattern) {
    int n = text.size(), m = pattern.size();
    std::vector<int> matches;

    if (m > n) return matches;

    // Precompute BASE^(m-1) mod MOD
    long long h = 1;
    for (int i = 0; i < m - 1; ++i) h = (h * BASE) % MOD;

    // Compute initial hashes for pattern and first window
    long long pat_hash = 0, win_hash = 0;
    for (int i = 0; i < m; ++i) {
        pat_hash = (pat_hash * BASE + (pattern[i] - 'a' + 1)) % MOD;
        win_hash = (win_hash * BASE + (text[i]    - 'a' + 1)) % MOD;
    }

    for (int i = 0; i <= n - m; ++i) {
        if (win_hash == pat_hash) {
            // Hash match → verify character by character (handle collisions)
            if (text.substr(i, m) == pattern)
                matches.push_back(i);
            // else: hash collision (spurious match) – skipped
        }
        // Roll the hash to the next window
        if (i < n - m) {
            win_hash = (BASE * (win_hash - (text[i] - 'a' + 1) * h % MOD + MOD) +
                        (text[i + m] - 'a' + 1)) % MOD;
        }
    }
    return matches;
}

void rabin_karp_demo() {
    std::cout << "=== Part (b): Rabin-Karp Demo ===\n";
    std::string text    = "ababcababcabab";
    std::string pattern = "abab";

    std::vector<int> pos = rabin_karp(text, pattern);

    std::cout << "Text   : " << text    << "\n";
    std::cout << "Pattern: " << pattern << "\n";
    std::cout << "Matches at index(es): ";
    for (int i : pos) std::cout << i << " ";
    std::cout << "\n\n";

    std::cout << "Collision handling: When two windows share the same hash value\n"
                 "  but differ in content (a spurious match), the algorithm falls\n"
                 "  back to an O(M) character-by-character comparison before\n"
                 "  reporting a match. With a large prime modulus this is rare.\n\n";

    std::cout << "Time complexity:\n";
    std::cout << "  Average case : O(N + M)  — few hash collisions\n";
    std::cout << "  Worst  case  : O(N * M)  — every window causes a spurious match\n";
}

int main() {
    kmp_demo();
    rabin_karp_demo();
    return 0;
}