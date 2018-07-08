#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H

#include <iostream>
#include <vector>
#include <string>

#include "index.h"
#include "document.h"
#include "query.h"

class SearchResult{
private:
    enum FlagState{none, highlight};
    size_t saved_number_;
    size_t total_number_;
    const size_t kDisplayLimits_ = 0;
    std::vector<std::string> doc_;
    std::vector<std::vector<std::string> > title_;
    std::vector<std::vector<std::string> > snippets_;
    std::vector<std::vector<int> > title_flag_;
    std::vector<std::vector<int> > snippets_flag_;

    static void Read(const std::string &file_name, const Query &query,
                     std::vector<std::vector<std::string> > &str_vec,
                     std::vector<std::vector<int> > &flag_vec, bool inital);
    static void Write(std::ostream &os, const std::string &type,
                      const std::vector<std::string> &str_vec,
                      const std::vector<int> &flag_vec);

public:
    SearchResult() = default;
    SearchResult(const PostingList &post, const Query &query,
                 const Document &doc_list, size_t limits = 10);

    friend std::ostream & operator << (std::ostream &os, const SearchResult &result);
    // friend const SearchResult & Search

    ~SearchResult() = default;
};
#endif