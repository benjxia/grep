//
// Created by benjx on 5/7/2022.
//

#ifndef GREP_AHO_CORASICK_H
#define GREP_AHO_CORASICK_H

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
namespace grep {

    /**
     * Class containing Aho Corasick Automaton for quicker string search
     */
    class aho_corasick {
    public:

        /**
         * Default constructor for Aho Corasick Automaton
         */
        aho_corasick();

        /**
         * Default destructor for Aho Corasick Automaton
         */
        ~aho_corasick();

        /**
         * Builds Aho Corasick Automaton given stream to file containing all words
         *
         * @param query list of strings to search for
         */
        void build_ahc(const std::vector<std::string> &query);

        /**
         * Returns current size of Aho Corasick automaton
         *
         * @return # of words in Aho Corasick automaton
         */
        size_t size();

        /**
         * Searches the query string for the entries in the automaton
         *
         * @param query string to search
         */
        void search(const std::string &query);

    private:

        /**
         * Class containing trie nodes for aho corasick automata
         */
        class ahc_node {
        public:

            bool is_word;       // True if current node is word node

            ahc_node *parent;   // Parent to current node, nullptr if root

            std::unordered_map<char, ahc_node *> children; // map of child edges

            ahc_node *suf_link; // Node's suffix link

            ahc_node *dict_link;// Node's dictionary link

            const char edge;    // Label of edge going into current node

            /**)
             * Default constructor for ahc_node
             *
             * @param p Pointer to parent node
             *
             * @param _edge edge label going into node
             */
            ahc_node(ahc_node *p, char _edge);

            /**
             * Default destructor for ahc_node
             */
            ~ahc_node() = default;
        };

        /**
         * Clears Aho Corasick Automaton
         */
        void clear();

        /**
         * Recursively delete all nodes in Aho Corasick automaton
         *
         * @param node Node and children to delete
         */
        void delete_nodes(ahc_node *node);

        /**
         * Returns the word represented by node in trie
         *
         * @param base Word node to find complete word from
         *
         * @return string that base word node represents
         */
        std::string find_word(ahc_node *base);

        /**
         * Inserts query string into Automaton used for building trie
         *
         * @param query String to add to Aho Corasick Automaton
         */
        void insert(const std::string &query);

        /**
         * Returns true if string in Aho Corasick Automaton
         *
         * @param query String to search for
         *
         * @return True if exists, false otherwise
         */
        bool contains(const std::string &query);

        ahc_node *root; // Root of Aho Corasick Automaton

        size_t words;   // Number of words in Aho Corasick Automaton

    };

}
#endif //GREP_AHO_CORASICK_H
