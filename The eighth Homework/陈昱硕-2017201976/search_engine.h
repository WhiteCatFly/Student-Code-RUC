#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>

#include "filter.h"
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
    Filter filter_;

    static void LoadFile(const size_t idx, const std::string &file_name, Index &index,
                         const Filter &filter);
    static PostingList BasicAccurateSearch(const std::vector<Words> &query,
                                           const Index &idx);
    static void BasicRankedSearch(const std::vector<std::string> &words,
                                  const std::vector<double> &term_frequency,
                                  const Index &idx,
                                  std::vector<double> &final_scores, const double rate);

    PostingList AccurateSearch(const std::vector<Words> &query);
    PostingList RankedSearch(const std::vector<Words> &query);

public:
    SearchEngine(const std::string &file_list = "file_list.txt",
                 const std::string &stop_word = "stop_words.txt");

    SearchResult Search(const Query &query, const size_t limits = 10);
    void Run();

    ~SearchEngine() = default;
};

#endif
