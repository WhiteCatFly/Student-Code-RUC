#include "HMM.h"
#include <fstream>

HMM::HMM(){
	word_total = 0;
	lang_source.clear();
	word_freq.clear();	
	part_trans.clear();
	part_total.clear();
	word_part_list.clear();
	out_flag = 1;
	sentence = dived_sen = "";
}

void HMM::pre_treatment(){
	ifstream lang_in;
	lang_in.open("language_source");
	
	string sentence;
	while (getline(lang_in, sentence)){
		int word_end = sentence.find(' '), word_begin = sentence.find_first_not_of(' ');
		string last_part = NWORD;
		++part_total[last_part];
		while (word_end != -1){
			int slash_pos = sentence.find('/', word_begin);
			string Word = sentence.substr(word_begin, slash_pos - word_begin);
			string part_of_speech = sentence.substr(slash_pos + 1, word_end - slash_pos - 1);
			++word_total;
			++word_freq[Word];
			++part_trans[make_pair(part_of_speech, last_part)];
			++part_total[part_of_speech];
			++word_part_trans[make_pair(Word, part_of_speech)];
			if (word_part_trans[make_pair(Word, part_of_speech)] == 1)
				word_part_list[Word].push_back(part_of_speech);
			word_begin = sentence.find_first_not_of(' ', word_end);
			word_end = sentence.find(' ', word_begin);
			last_part = part_of_speech;
		}
	}
}
