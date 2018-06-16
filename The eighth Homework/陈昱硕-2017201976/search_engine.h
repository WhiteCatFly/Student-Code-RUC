#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>

#include "document.h"
#include "index.h"
#include "query.h"
#include "search_result.h"

class SearchEngine{
private:
    enum FlagStatus{
        none = 000,
        plus_flag = 001,
        minus_flag = 002,
        and_flag = 004,
        or_flag = 010,
        xor_flag = 020
    };
    const std::string file_list_;
    Document doc_list_;
    Index title_index_, body_index_;
    void *segmentor_;

    static void LoadFile(const size_t idx, const std::string &file_name, Index &index);
    static PostingList BaseSearch(const std::vector<Words> &query, const Index &idx);

    PostingList AccurateSearch(const std::vector<Words> &query);
    PostingList RankedSearch(const std::vector<Words> &query);

public:
    SearchEngine(const std::string &file_list = "file_list.txt");

    SearchResult Search(const Query &query, const size_t limits = 10);
    void Run();

    ~SearchEngine() = default;
};

#endif