#ifndef _INCLUDEFILES_HPP_
#define _INCLUDEFILES_HPP_

#include <io.h> // loop for every file in the folder

#include <iostream>
#include <fstream> // file stream object
#include <exception>
#include <stdexcept>
#include <vector>
#include <string>
#include <unordered_map> // hash table implementation
#include <algorithm> // std::sort

// function prototype declaration:
bool count_compare(std::pair<std::string, int> w1, std::pair<std::string, int> w2); // word list sorter used in std::sort()

std::vector<std::pair<std::string, int>> get_word_count(); // Word Counter

std::unordered_map<std::string, std::string> word_stemmer(); // Word Stemmer

std::vector<std::pair<std::string, std::unordered_map<std::string, std::pair<int, std::vector<int>>>>>
get_index_generation(const std::unordered_map<std::string, int> &StopWordList); // Index Generator

std::vector<std::string> query_preprocessor(const std::vector<std::string>& Query, 
                                            const std::unordered_map<std::string, std::string>& WordStemmer,
                                            const std::unordered_map<std::string, int>& StopWordList); // Query Preprocessor

std::pair<std::string, std::vector<int>> query_processor (
                 std::vector<std::string> Query,
                 std::vector<std::pair<std::string, std::unordered_map<std::string, std::pair<int, std::vector<int>>>>> IndexGenerator
                );  // Query Processor

#endif