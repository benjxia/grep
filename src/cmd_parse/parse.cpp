//
// Created by benjx on 5/8/2022.
//

#include "parse.h"
#include "../str_search/aho_corasick.h"

void grep::parse::parse_arg(int argc, char *argv[]) {
    int opt;   // Helper for parsing arguments

    // Parse option flags
    while ((opt = getopt(argc, argv, "ir")) != -1) {
        switch (opt) {
            // -i flag to search ignoring upper/lower case
            case 'i':
                opcnt++;
                case_s = false;
                break;
                // -r flag to search last argument recursively
            case 'r':
                opcnt++;
                rec = true;
                break;
        }
    }

    if (argc - opcnt != 3) {
        std::cerr << errmsg << std::endl;
        exit(EXIT_FAILURE);
    }
}

void grep::parse::parse_directory(std::string dirname) {

}

void grep::parse::parse_file(std::string filename) {

}