#include <iostream>
#include <cctype>
#include <algorithm>
#include "./str_search/aho_corasick.h"
#include "./cmd_parse/parse.h"

int main(int argc, char *argv[]) {

    std::vector<std::string> search;// vector of strings to search
    std::vector<std::string> files; // vector of filenames/directories to search
    grep::parse parser;
    // Protect against incorrect usage
//    if (argc - opcnt != 3) {
//        std::cerr << errmsg << std::endl;
//        return EXIT_FAILURE;
//    }

    grep::aho_corasick a(true);

    a.build_ahc(search);
    a.search("gcaa");

    return EXIT_SUCCESS;
}
