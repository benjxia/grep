//
// Created by benjx on 5/7/2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "aho_corasick.h"

grep::aho_corasick::aho_corasick() {
    case_s = false;
    if ((root = new ahc_node(nullptr, '\0')) == nullptr) {
        std::cerr << "out of heap space" << std::endl;
        exit(EXIT_FAILURE);
    }
    words = 0;
}

grep::aho_corasick::~aho_corasick() {
    clear();
}

void grep::aho_corasick::insert(const std::string &query) {
    ahc_node *curr = root; // Current node for traversal

    // For each character in query, traverse to correct node
    for (char c : query) {
        if (!case_s) {
            // Handle case sensitivity
            c = std::tolower(c);
        }
        // Create new node if needed
        if (!curr->children.count(c)) {
            if ((curr->children[c] = new ahc_node(curr, c)) == nullptr) {
                // Handle case of out of memory
                std::cerr << "out of memory" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        // Traverse to node
        curr = curr->children[c];
    }

    // Increment word count if needed
    if (!curr->is_word) {
        words++;
    }
    curr->is_word = true;
}

bool grep::aho_corasick::contains(const std::string &query) {
    ahc_node *curr = root; // Current node for traversal

    // For each character in query, traverse to correct node
    for (char c : query) {
        // Corresponding node not found
        if (!curr->children.count(c)) {
            return false;
        }

        // Traverse down correct child
        curr = curr->children[c];
    }
    return curr->is_word;
}

void grep::aho_corasick::build_ahc(const std::vector<std::string> &query, bool _case) {
    case_s = _case;
    // Build MWT for automota
    for (std::string i : query) {
        insert(i);
    }

    // BFS to add suffix links
    std::queue<ahc_node *> bfs;
    bfs.push(root);
    ahc_node *curr;

    // Generate suffix links
    while (!bfs.empty()) {
        curr = bfs.front();
        bfs.pop();

        // Push children into queue
        for (auto i : curr->children) {
            bfs.push(i.second);
        }

        if (curr == root || curr->parent == root) {
            curr->suf_link = root; // Set suffix link to root in specific cases
        } else {
            ahc_node *p = curr->parent; // Parent of current node
            char c = curr->edge;        // Label of edge going into curr
            ahc_node *x = p->suf_link;  // Parent's suffix link

            // Set suffix link of curr
            while (true) {
                if (x->children.count(c)) {
                    curr->suf_link = x->children[c];
                    break;
                } else if (x == root) {
                    curr->suf_link = root;
                    break;
                } else {
                    x = x->suf_link;
                }
            }
        }
    }

    curr = nullptr;
    bfs = std::queue<ahc_node *>(); // clear bfs queue

    // Generate dictionary links
    bfs.push(root);
    ahc_node *dict_search;

    while (!bfs.empty()) {
        curr = bfs.front();
        bfs.pop();
        // Push children into queue
        for (auto i : curr->children) {
            bfs.push(i.second);
        }
        dict_search = curr->suf_link;
        while (dict_search != root) {
            if (dict_search->is_word) {
                curr->dict_link = dict_search;
                break;
            }
            dict_search = dict_search->suf_link;
        }
    }

}

size_t grep::aho_corasick::size() {
    return this->words;
}

std::vector<std::string> grep::aho_corasick::search(const std::string &query) {
    ahc_node *curr = root;  // Node pointer for automaton traversal
    std::string output_str; // String represented by word nodes
    unsigned long idx = 0;  // Keep track of current string index
    ahc_node *dict_search;  // Pointer used to traverse dictionary chain

    std::vector<std::string> out; // Output vector
    for (char c : query) {

        while (!curr->children.count(c)) {
            if (curr == root) {
                break;
            }
            curr = curr->suf_link;
        }

        if (curr->children.count(c)) {
            curr = curr->children[c];
        }

        if (curr->is_word) {
            output_str = find_word(curr);
            out.push_back(output_str);
        }

        // Traverse dictionary chain
        dict_search = curr->dict_link;
        while (dict_search != nullptr) {
            output_str = find_word(dict_search);
            out.push_back(output_str);
            dict_search = dict_search->dict_link;
        }
        idx++;
    }
    return out;
}

void grep::aho_corasick::clear() {
    delete_nodes(root);
}

void grep::aho_corasick::delete_nodes(ahc_node *node) {
    // Avoid seg fault
    if (node == nullptr) {
        return;
    }
    // Delete each child recursively
    for (auto i : node->children) {
        delete_nodes(i.second);
    }
    // Delete in postorder
    delete node;
}

std::string grep::aho_corasick::find_word(ahc_node *base) {
    // Traverse up trie to find word represented at base
    std::string out;
    while (base != root) {
        out = base->edge + out;
        base = base->parent;
    }
    return out;
}

grep::aho_corasick::ahc_node::ahc_node(ahc_node *p, char _edge) :
        parent(p),
        is_word(false),
        children(),
        suf_link{nullptr},
        dict_link(nullptr),
        edge(_edge) {};
