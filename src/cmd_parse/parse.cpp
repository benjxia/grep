//
// Created by benjx on 5/8/2022.
//

#include "parse.h"
#include "../str_search/aho_corasick.h"

grep::parse::parse() {
    opcnt = 0;
    case_s = false;
    rec = false;
}

void grep::parse::parse_arg(int argc, char *argv[]) {
    int opt;   // Helper for parsing arguments

    // Parse option flags
    while ((opt = getopt(argc, argv, "CcRr")) != -1) {
        switch (opt) {
            // -i flag to be upper/lower case-sensitive
            case 'C':
            case 'c':
                if (!case_s) {
                    opcnt++;
                    case_s = true;
                }
                break;
            // -r flag to search last argument recursively
            case 'R':
            case 'r':
                if (!rec) {
                    opcnt++;
                    rec = true;
                }
                break;
        }
    }

    // Handle invalid arg count
    if (argc - opcnt < 3) {
        std::cerr << errmsg << std::endl;
        exit(EXIT_FAILURE);
    }

    // Add queries to query vector
    for (int i = optind; i < argc - 1; i++) {
        queries.push_back(argv[i]);
    }

    // Last argument is search location
    searchloc = argv[argc - 1];

    ahc.build_ahc(queries, case_s);
}

void grep::parse::parse_directory(std::string dirname) {
    std::filesystem::path cur(dirname);
    if (std::filesystem::is_directory(cur)) {
        // Parse each element in directory
        for (const auto &entry : std::filesystem::directory_iterator(dirname)) {
            // Parse file if needed
            if (!entry.is_directory()) {
                parse_file(entry.path());
            } else if (rec) {
                // Parse directories recursively if needed
                parse_directory(entry.path());
            }
        }
    } else {
        parse_file(cur);
    }
}

void grep::parse::parse_directory(std::filesystem::path dirpath) {
    // Parse each element in directory
    for (const auto &entry : std::filesystem::directory_iterator(dirpath)) {
        // Parse file if needed
        if (!entry.is_directory()) {
            parse_file(entry.path());
        } else if (rec) {
            // Parse directories recursively if needed
            parse_directory(entry.path());
        }
    }
}

void grep::parse::parse_file(std::filesystem::path filepath) {
    std::ifstream file(filepath);
    std::string curr_line;
    // Parse each line of file
    while (std::getline(file, curr_line)) {
        // Search current line for queries
        std::vector<std::string> found = ahc.search(curr_line);

        // If queries found, print matches and current line
        if (found.size() > 0) {
            std::cout << filepath << ": ";
            for (auto &i : found) {
                std::cout << i << " ";
            }
            std::cout << std::endl << curr_line << std::endl;
        }
    }
}
