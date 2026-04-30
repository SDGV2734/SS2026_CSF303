#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class PatriciaTrie {
private:
    struct Node;

    struct Edge {
        string label;
        Node *child;
    };

    struct Node {
        bool isEnd = false;
        map<char, Edge> edges;
    };

    Node *root;

    int commonPrefixLength(const string &a, const string &b) const {
        int i = 0;
        while (i < (int)a.size() && i < (int)b.size() && a[i] == b[i]) {
            i++;
        }
        return i;
    }

    void insert(Node *node, const string &word) {
        if (word.empty()) {
            node->isEnd = true;
            return;
        }

        char first = word[0];
        auto it = node->edges.find(first);

        if (it == node->edges.end()) {
            Node *child = new Node();
            child->isEnd = true;
            node->edges[first] = {word, child};
            return;
        }

        Edge oldEdge = it->second;
        int lcp = commonPrefixLength(word, oldEdge.label);

        if (lcp == (int)oldEdge.label.size()) {
            insert(oldEdge.child, word.substr(lcp));
            return;
        }

        Node *middle = new Node();
        string oldSuffix = oldEdge.label.substr(lcp);
        middle->edges[oldSuffix[0]] = {oldSuffix, oldEdge.child};

        string newSuffix = word.substr(lcp);
        if (newSuffix.empty()) {
            middle->isEnd = true;
        } else {
            Node *newChild = new Node();
            newChild->isEnd = true;
            middle->edges[newSuffix[0]] = {newSuffix, newChild};
        }

        it->second = {oldEdge.label.substr(0, lcp), middle};
    }

    bool search(Node *node, const string &word) const {
        if (word.empty()) {
            return node->isEnd;
        }

        auto it = node->edges.find(word[0]);
        if (it == node->edges.end()) {
            return false;
        }

        const Edge &edge = it->second;
        if (word.rfind(edge.label, 0) != 0) {
            return false;
        }

        return search(edge.child, word.substr(edge.label.size()));
    }

    bool remove(Node *node, const string &word) {
        if (word.empty()) {
            if (!node->isEnd) {
                return false;
            }
            node->isEnd = false;
            return true;
        }

        auto it = node->edges.find(word[0]);
        if (it == node->edges.end()) {
            return false;
        }

        Edge &edge = it->second;
        if (word.rfind(edge.label, 0) != 0) {
            return false;
        }

        bool deleted = remove(edge.child, word.substr(edge.label.size()));
        if (!deleted) {
            return false;
        }

        Node *child = edge.child;
        if (!child->isEnd && child->edges.empty()) {
            delete child;
            node->edges.erase(it);
        } else if (!child->isEnd && child->edges.size() == 1) {
            auto only = child->edges.begin();
            edge.label += only->second.label;
            edge.child = only->second.child;
            child->edges.clear();
            delete child;
        }

        return true;
    }

    void display(Node *node, string current) const {
        if (node->isEnd) {
            cout << current << " ";
        }

        for (auto &[_, edge] : node->edges) {
            display(edge.child, current + edge.label);
        }
    }

    void printStructure(Node *node, const string &indent) const {
        for (auto &[_, edge] : node->edges) {
            cout << indent << "- " << edge.label;
            if (edge.child->isEnd) {
                cout << " (word)";
            }
            cout << '\n';
            printStructure(edge.child, indent + "  ");
        }
    }

    void clear(Node *node) {
        for (auto &[_, edge] : node->edges) {
            clear(edge.child);
        }
        delete node;
    }

public:
    PatriciaTrie() {
        root = new Node();
    }

    ~PatriciaTrie() {
        clear(root);
    }

    void insert(const string &word) {
        insert(root, word);
    }

    bool search(const string &word) const {
        return search(root, word);
    }

    void remove(const string &word) {
        remove(root, word);
    }

    void display() const {
        display(root, "");
        cout << '\n';
    }

    void printStructure() const {
        printStructure(root, "");
    }
};

int main() {
    PatriciaTrie trie;
    vector<string> words = {"romane", "romanus", "rubens", "ruber", "rubicon", "rubicundus"};

    cout << "PATRICIA / Compressed Trie Algorithm\n";
    cout << "Inserting words: ";
    for (const string &word : words) {
        cout << word << " ";
        trie.insert(word);
    }

    cout << "\n\nCompressed structure:\n";
    trie.printStructure();

    cout << "\nWords in trie: ";
    trie.display();

    cout << "\nSearch operations\n";
    cout << "romanus: " << (trie.search("romanus") ? "Found" : "Not found") << '\n';
    cout << "rubicon: " << (trie.search("rubicon") ? "Found" : "Not found") << '\n';
    cout << "ruby: " << (trie.search("ruby") ? "Found" : "Not found") << '\n';

    cout << "\nDeleting ruber and romanus...\n";
    trie.remove("ruber");
    trie.remove("romanus");

    cout << "Words after deletion: ";
    trie.display();

    cout << "\nCompressed structure after deletion:\n";
    trie.printStructure();

    cout << "\nSearch after deletion\n";
    cout << "ruber: " << (trie.search("ruber") ? "Found" : "Not found") << '\n';
    cout << "romane: " << (trie.search("romane") ? "Found" : "Not found") << '\n';

    return 0;
}
