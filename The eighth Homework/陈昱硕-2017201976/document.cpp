#include "document.h"

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

size_t Document::find(const string &doc) const{
    auto iter = doc_map_.find(doc);
    return (iter == doc_map_.end() ? npos : iter -> second);
}

size_t Document::append(const string &doc){
    auto iter = doc_map_.find(doc);
    if (iter == doc_map_.end()){
        doc_map_.insert(make_pair(doc, doc_number_));
        doc_number_ ++;
        doc_name_.push_back(doc);
        return doc_number_ - 1;
    }
    return iter -> second;
}

string Document::operator [] (size_t idx) const{
    if (idx < doc_number_)
        return doc_name_[idx];
    return string();
}