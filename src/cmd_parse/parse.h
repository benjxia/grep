//
// Created by benjx on 5/8/2022.
//

#ifndef GREP_PARSE_H
#define GREP_PARSE_H

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <experimental/filesystem>
#include <sstream>
#include "../str_search/aho_corasick.h"

namespace grep {
    class parse {
    public:
        int opcnt;     // counter for opt flags

        bool case_s;   // True if search case-sensitive

        bool rec;      // true if to search specified directory recursively

        std::vector<std::string> queries;   // All query strings

        std::string searchloc;              // Location to search for pattern

        const std::string errmsg =
                "Usage: grep <-c> <-r> <search queries> <file or directory>\nExample: grep -c -r \"query1\" \"query2\" dirname";

        /**
         * constructor
         */
        parse();

        /**
         * destructor
         */
        ~parse() = default;

        /**
         * Parses command line arguments
         *
         * @param argc Number of arguments from main function
         * @param argv Array of arguments from main function
         */
        void parse_arg(int argc, char *argv[]);

        /**
         * Parse specified directory
         *
         * @param dirname Name of directory
         */
        void parse_directory(std::string dirname);

        /**
         * Parse specified directory
         *
         * @param dirpath path of directory
         */
        void parse_directory(std::filesystem::path dirpath);

        /**
         * Parse specified file
         *
         * @param filename Name of file
         */
        void parse_file(std::filesystem::path filepath);
    private:

        grep::aho_corasick ahc; // Aho Corasick Automaton for searching everything
    };

}

#endif //GREP_PARSE_H
