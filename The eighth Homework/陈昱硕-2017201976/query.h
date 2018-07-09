#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

#include "filter.h"

typedef std::vector<std::string> Words;

class Query{
private:
    bool accurate_;
    std::vector<Words> query_;

public:
    Query(void *segmentor, Filter filter);

    bool accurate() const{return accurate_;}
    const std::vector<Words> & query() const{return query_;}

    ~Query() = default;
};

#endif
