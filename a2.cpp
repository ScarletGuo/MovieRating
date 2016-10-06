////////////////////////////////////////////////////////////////////////////////
// File Name:      a2.cpp
//
// Author:         Zhihan Guo
// CS email:       zhihan@cs.wisc.edu
//
// Description:    The source file for a2.
//
// IMPORTANT NOTE: THIS IS THE ONLY FILE THAT YOU SHOULD MODIFY FOR A2.
//                 You SHOULD NOT MODIFY any of the following:
//                   1. Name of the functions/methods.
//                   2. The number and type of parameters of the functions.
//                   3. Return type of the functions.
////////////////////////////////////////////////////////////////////////////////

#include "a2.hpp"
#include "trim.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>


void cleanData(std::ifstream &inFile, std::ofstream &outFile,
               std::unordered_set<std::string> &stopwords) {
    // TODO: Implement this method.
    // # of lines of code in Gerald's implementation: 13
    // Do the following operations on each review before
    
    // read lines from file
	std::string line;
	while (getline(inFile, line)) {
		std::vector<std::string> words;
		std::vector<std::string> outTokens;
	    //   1. Replace hyphens with spaces.
		replaceHyphensWithSpaces(&line);
	    //   2. Split the line of text into individual words.
		splitLine(&line, &words);
	    //   3. Remove the punctuation marks from the words.
		removePunctuation(&words,&outTokens);
	    //   4. Remove the trailing and the leading whitespaces in each word.
		removeWhiteSpaces(&outTokens);
	    //   5. Remove the empty words.
		removeEmptyWords(&outTokens);
	    //   6. Remove words with just one character in them. You should NOT remove
	    //      numbers in this step because if you do so, you'll lose the ratings.
		removeSingleLetterWords(&outTokens);
	    //   7. Remove stopwords.	
		removeStopWords(&outTokens, &stopwords);
	    // storing it to the output file:	
		for (std::string s : outTokens) {
			outFile << s << ' ';
		}
		outFile << endl;
	}

}

void fillDictionary(std::ifstream &newInFile,
                    std::unordered_map<std::string, std::pair<long, long>> &dict) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 20
	std::string line;
	while (getline(newInFile, line)) {
		std::vector<std::string> words;
		splitLine(&line, &words);
		std::long rating = words[0];
		std::long COUNTER = 1;
		for (int i = 1; i < words.size(); i++) {
			if (dict.find(word[i]) == dict.end()) { // not exist 
				dict.emplace(words[i],make_pair(rating, COUNTER));
			} else { // already exist
				std::long rate, count;
				rate = dict[word[i]].first + rating;
				count = dict[word[i]].second + COUNTER;
				dict[word[i]] = make_pair(rate, count);
			}	
		}	
	}
}


void fillStopWords(std::ifstream &inFile,
                   std::unordered_set<std::string> &stopwords) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
	std::string line;
	while (getline(inFile, line)) {
		stopwords.insert(line);
	}
}

void rateReviews(std::ifstream &testFile,
                 std::unordered_map<std::string, std::pair<long, long>> &dict,
                 std::ofstream &ratingsFile) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 20
	while (getline(testFile, line)) {
		std::vector<std::string> words;
		splitLine(&line, &words);
		long rateLine = 0;
		for (int i = 1; i < words.size(); i++) {
			if (dict.find(word[i]) == dict.end()) { // not exist 
				 rateLine += 2;
			} else { // already exist
				rateLine += dict[word[i]].first / dict[word[i]].second;
			}	
		}	
		ratingsFile << rateLine / words.size << endl;
	}
}

void removeEmptyWords(std::vector<std::string> &tokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    tokens.erase(remove_if(tokens.begin(), tokens.end(),
                           [](const std::string& s){ return s.size() == 0;
                           }), tokens.end());
}

void removePunctuation(std::vector<std::string> &inTokens,
                       std::vector<std::string> &outTokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 10
    std:: string item;
    for (int i = 0; i < inTokens.size(); i++) {
        remove_copy_if(inTokens[i].begin(),inTokens[i].end(),
                       item.begin(), std::ptr_fun<int, int>(&std::ispunct));
        outTokens.push_back(item);
    }
}

void removeSingleLetterWords(std::vector<std::string> &tokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    tokens.erase(remove_if(tokens.begin() + 1, tokens.end(),
                           [](const std::string& s){ return s.size() == 1;
                           }), tokens.end());
}

void removeStopWords(std::vector<std::string> &tokens,
                     std::unordered_set<std::string> &stopwords) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    tokens.erase(remove_if(tokens.begin(), tokens.end(),
                           [](const std::string& s,
                              std::unordered_set<std::string> stopwords){
                               return stopwords.find(s) != stopwords.end();
                           }), tokens.end());
}

void removeWhiteSpaces(std::vector<std::string> &tokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    // You may want to use the trim() method from the trim.*pp files in a2.
    std:: string temp;
    for (int i = 0; i < tokens.size(); i++) {
        temp = trim(tokens[i]);
        tokens[i] = temp;
    }
}

void replaceHyphensWithSpaces(std::string &line) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    std:: replace(line.begin(), line.end(), '-', ' ');
    
}

void splitLine(std::string &line, std::vector<std::string> &words) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 10
    std:: stringstream ss;
    ss.str(line);
    std::string item;
    while (std::getline(ss, item, ' ')) {
        words.push_back(item);
    }

}

