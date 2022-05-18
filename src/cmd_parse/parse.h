//
// Created by benjx on 5/8/2022.
//

#ifndef GREP_PARSE_H
#define GREP_PARSE_H

#include <unistd.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "../str_search/aho_corasick.h"

namespace grep {
    class parse {
    public:
        int opcnt;     // counter for opt flags
        bool case_s;   // True if search case-sensitive
        bool rec;      // true if to search specified directory recursively
        const std::string errmsg =
                "Usage: grep <-i> <-r> <search query> <file or directory>";

        /**
         * constructor
         */
        parse() = default;

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
         * Parse specified file
         *
         * @param filename Name of file
         */
        void parse_file(std::string filename);
    };

}

#endif //GREP_PARSE_H
