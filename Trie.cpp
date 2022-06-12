# include <bits/stdc++.h>

using namespace std;

struct TrieNode {
    bool wordEnd;
    TrieNode *children[26];

    TrieNode() {
        wordEnd = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

class Trie {
    TrieNode *root;
public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string &word) {
        TrieNode *itr = root;
        for (char ch: word) {
            int idx = ch - 'a';
            if (!itr->children[idx])
                itr->children[idx] = new TrieNode();
            itr = itr->children[idx];
        }
        itr->wordEnd = true;
    }

    bool search(const string &word) {
        TrieNode *itr = root;
        for (char ch: word) {
            int idx = ch - 'a';
            if (!itr->children[idx])
                return false;
            itr = itr->children[idx];
        }
        return itr->wordEnd;
    }
};

int main() {
    Trie trie;
    trie.insert("anshul");
    trie.insert("tripathi");
    trie.insert("sneha");
    trie.insert("kapoor");

    cout << trie.search("anshul") << endl;
    cout << trie.search("asdlkjf") << endl;
    cout << trie.search("sneha") << endl;

    cout << "size of trie: " << sizeof(TrieNode) << endl;

    return 0;
}