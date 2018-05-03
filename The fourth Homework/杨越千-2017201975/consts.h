#ifndef CONSTS_H_
#define CONSTS_H_

#include <regex>
#include <string>

const std::string def_path = "", def_file = "links.txt";
const int def_mode = 0;
const std::string nul_str = "";

const std::regex link_re("(\"|\')?(http://|https://)?([^{}\\s]+/)*[^{}\\.]+(\\.(cn|com|net|org|ac|io|php|html|htm|jsp|do))?[^{}\\s\\.]*");
const std::regex image_re("(\"|\')?(http://|https://)?([^{}\\s]+/)*[^{}\\.]+\\.(png|jpg|jpeg|gif|bmp)[^{}\\s\\.]*");
const std::regex sound_re("(\"|\')?(http://|https://)?([^{}\\s]+/)*[^{}\\.]+\\.(cda|ogg|mp3|MP3|asf|wma|wav|mp3pro|ape|midi|vqf|mpg|m4a)[^{}\\s\\.]*");
const std::regex word_re("(\"|\')?(http://|https://)?([^{}\\s]+/)*[^{}\\.]+\\.(doc|docx|xls|xlsx|ppt|pptx|pdf)[^{}\\s\\.]*");
const std::regex end_re("[^{}/]+/");

const std::regex tag_re("<\\w.*?>"), str_re("[^<>\\s]+"), s_re("[\\t\\s]*");

#endif
