#include <iostream>
#include <vector>
#include "postag_dll.h"

int main(int argc, char * argv[]) {
    if (argc < 1) {
        return -1;
    }

    void * engine = postagger_create_postagger(argv[1]);
    if (!engine) {
        return -1;
    }

    std::vector<std::string> words;

    words.push_back("这");
    words.push_back("是");
    words.push_back("词性");
    words.push_back("标注");
    words.push_back("程序");

    std::vector<std::string> tags;

    postagger_postag(engine, words, tags);

    for (int i = 0; i < tags.size(); ++ i) {
        std::cout << words[i] << "/" << tags[i];
        if (i == tags.size() - 1) std::cout << std::endl;
        else std::cout << " ";

    }

    postagger_release_postagger(engine);
    return 0;
}
