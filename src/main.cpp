#include <iostream>
#include <cctype>
#include <algorithm>
#include "./str_search/aho_corasick.h"
#include "./cmd_parse/parse.h"

int main(int argc, char *argv[]) {

    std::vector<std::string> search;// vector of strings to search
    std::vector<std::string> files; // vector of filenames/directories to search
    grep::parse parser;

    // Parse program arguments, handles bad calls
    parser.parse_arg(argc, argv);

    parser.parse_file(parser.searchloc);

    return EXIT_SUCCESS;
}
