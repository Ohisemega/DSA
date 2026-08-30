#include <cstring>
#include <string>
#include "tree.hpp"

struct Trie_ascii {
    struct Node_ascii {
        Node_ascii* alph[26];
        bool is_leaf;
        Node_ascii(): is_leaf{false} {
            memset(alph, NULL, 26*(sizeof(Node_ascii*)));
        }
    };
    Node_ascii head;
    Node_ascii buffer[30001];
    void insert_r(Node_ascii* node, const std::string& key) {
        auto curr_node = node;
        for (char c: key){
            if (!curr_node->alph[c - 'a']) {
                auto new_n = new Node_ascii();
                node->alph[c - 'a'] = new_n;

            }
            curr_node = curr_node->alph[c - 'a'];
        }
        curr_node->is_leaf = true;
    }

    bool search_r(Node_ascii* node, const std::string& key) {
        auto curr_node = node;
        for (char c: key) {
            if (!curr_node->alph[c - 'a']) {
                return false;
            }
            curr_node = curr_node->alph[c - 'a'];
        }
        return curr_node->is_leaf;
    }

    public:
        Trie_ascii() : head{} {
            // sizeof(buffer);
        }
        void insert(const std::string& key) {
            insert_r(&head, key);
        }
        
        bool search(const std::string& key) {
            return search_r(&head, key);
        }
}