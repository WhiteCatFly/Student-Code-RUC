#include <cstring>
#include <cmath>
#include <sstream>
#include <map>
#include <vector>
#include "sent_processor.h"	
#include "corpus.h"

extern std::map< std::string, std::vector<std::string> > words;
extern std::map< std::pair<std::string, std::string>, double > freq;
extern std::map< std::pair<std::string, std::string>, double > p_matrix;
extern std::map< std::string, double > word_freq;
extern int word_count;

using namespace std;

string word_split(const vector<string> & ws) {
	int length = ws.size();
	double * possibility = new double[length + 1];
	int * last = new int [length + 1];
	bool * new_word = new bool [length + 1];
	possibility[0] = 0;
	for (int i = 0; i < length; ++i) {
		possibility[i + 1] = -inf;
		last[i + 1] = 0;
		new_word[i] = true;
		for (int j = 0; j <= i ; ++j) {
			string word = "";
			double poss = -inf;
			for (int k = j; k <= i; ++k)
				word = word + ws[k];
			if (word_freq.find(word) != word_freq.end()) {
				poss = log(word_freq[word]);
				new_word[i] = false;
			}
			if (possibility[i + 1] < possibility[j] + poss) {
				possibility[i + 1] = possibility[j] + poss;
				last[i + 1] = j;
			}
		}
		if (new_word[i] == true) {
			int plc = -1;
			for (int j = i - 1; j > 0; --j)
				if (new_word[j] == false) {
					plc = j;
					break;
				}
			possibility[i + 1] = possibility[plc + 1];
			last[i + 1] = plc + 1;
		}
	}
	string sent = "";
	int plc = length;
	while (plc) {
		int end = plc;
		plc = last[end];
		sent = " " + sent;
		for (int k = end - 1; k >= plc; --k)
			sent = ws[k] + sent;
	}
	delete[] possibility;
	delete[] last;
	return sent;
}

void tag(string sentence, ostream & os) {
	istringstream ifs(sentence);
	string word;
	int last_size = 1,count = 0;
	double * possibility = new double [last_size];
	string * part = new string[last_size];
	double * new_possibility;
	string * new_part;
	map<string, string> best[maxl];
	
	possibility[0] = 0;
	part[0] = start;
	while (ifs>>word) {
		if (words.find(word) == words.end()) {
			words[word].push_back(other);
		}
		int size = words[word].size();
		new_possibility = new double[size];
		new_part = new string[size];
		for (int i = 0; i < size; ++i) {
			new_part[i] = words[word][i];
			new_possibility[i] = -inf;
		}
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < last_size; ++j) {
				pair<string, string> pr = make_pair(part[j], new_part[i]);
				if (part[j] == other || new_part[i] == other)
					p_matrix[pr] = 1;
				if (possibility[j] + log(p_matrix[pr]) > new_possibility[i]) { 
					new_possibility[i] = possibility[j] + log(p_matrix[pr]);
					best[count][new_part[i]] =  part[j];
				}
			}
			pair<string, string> pr = make_pair(new_part[i], word);
			if (new_part[i] == other) freq[pr]  = 1;
			new_possibility[i] += log(freq[pr]);
		}
		delete[] possibility;
		delete[] part;
		last_size = size;
		possibility = new double [size];
		part = new string [size];
		for (int i = 0; i < size; ++i) {
			possibility[i] = new_possibility[i];
			part[i] = new_part[i];
		}
		delete[] new_possibility;
		delete[] new_part;
		count++;
	}
	
	string * part_of_sentence = new string[count];
	int maxn = -inf;
	string maxi;
	for (int i = 0; i < last_size; ++i)
		if (possibility[i] > maxn) {
			maxn = possibility[i];
			maxi = part[i];
		}
	for (int i = count - 1; i >= 0; --i) {
		part_of_sentence[i] = maxi;
		maxi = best[i][maxi];
	}
	
	istringstream fin(sentence);
	count = 0;
	while (fin>>word) {
		os<<word<<seperate_sign<<part_of_sentence[count]<<' ';
		count++;
	}
	os<<endl;
}
