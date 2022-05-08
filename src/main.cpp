#include <iostream>
#include <cstdio>
#include "./str_search/aho_corasick.h"

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
    grep::aho_corasick a;
    std::vector<std::string> in;
    in.push_back("a");
    in.push_back("g");
    in.push_back("gag");
    in.push_back("gc");
    in.push_back("gca");
    in.push_back("c");
    in.push_back("caa");
    a.build_ahc(in);
    a.search("gcaa");

    return EXIT_SUCCESS;
}
