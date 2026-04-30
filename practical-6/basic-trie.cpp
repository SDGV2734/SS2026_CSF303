#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Trie {
private:
    struct Node {
        bool isEnd = false;
        map<char, Node *> children;
    };

    Node *root;

    bool remove(Node *node, const string &word, int depth) {
        if (depth == (int)word.size()) {
            if (!node->isEnd) {
                return false;
            }
            node->isEnd = false;
            return node->children.empty();
        }

        char ch = word[depth];
        auto it = node->children.find(ch);
        if (it == node->children.end()) {
            return false;
        }

        bool shouldDeleteChild = remove(it->second, word, depth + 1);
        if (shouldDeleteChild) {
            delete it->second;
            node->children.erase(it);
        }

        return !node->isEnd && node->children.empty();
    }

    void display(Node *node, string &current) const {
        if (node->isEnd) {
            cout << current << " ";
        }

        for (auto &[ch, child] : node->children) {
            current.push_back(ch);
            display(child, current);
            current.pop_back();
        }
    }

    void clear(Node *node) {
        for (auto &[_, child] : node->children) {
            clear(child);
        }
        delete node;
    }

public:
    Trie() {
        root = new Node();
    }

    ~Trie() {
        clear(root);
    }

    void insert(const string &word) {
        Node *current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new Node();
            }
            current = current->children[ch];
        }
        current->isEnd = true;
    }

    bool search(const string &word) const {
        Node *current = root;
        for (char ch : word) {
            auto it = current->children.find(ch);
            if (it == current->children.end()) {
                return false;
            }
            current = it->second;
        }
        return current->isEnd;
    }

    void remove(const string &word) {
        remove(root, word, 0);
    }

    void display() const {
        string current;
        display(root, current);
        cout << '\n';
    }
};

int main() {
    Trie trie;
    vector<string> words = {"apple", "app", "apply", "bat", "ball"};

    cout << "Basic Trie Algorithm\n";
    cout << "Inserting words: ";
    for (const string &word : words) {
        cout << word << " ";
        trie.insert(word);
    }

    cout << "\nWords in trie: ";
    trie.display();

    cout << "\nSearch operations\n";
    cout << "app: " << (trie.search("app") ? "Found" : "Not found") << '\n';
    cout << "bat: " << (trie.search("bat") ? "Found" : "Not found") << '\n';
    cout << "bad: " << (trie.search("bad") ? "Found" : "Not found") << '\n';

    cout << "\nDeleting app and bat...\n";
    trie.remove("app");
    trie.remove("bat");

    cout << "Words after deletion: ";
    trie.display();

    cout << "\nSearch after deletion\n";
    cout << "app: " << (trie.search("app") ? "Found" : "Not found") << '\n';
    cout << "apple: " << (trie.search("apple") ? "Found" : "Not found") << '\n';
    cout << "bat: " << (trie.search("bat") ? "Found" : "Not found") << '\n';

    return 0;
}
