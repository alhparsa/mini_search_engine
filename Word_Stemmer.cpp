#include "IncludeFiles.hpp"

// return value explaination:
// the original files have been dealt ( word stemming and eliminate the punctuation ) in the "File Processor.py"
// the content of query should be input and dealt by cpp, this file build a word stemmer map to deal the input
// every word which was stemmed was stored in "stem.txt"
// the input query will be stemmed by this wordstemmer and search later 
std::unordered_map<std::string, std::string> word_stemmer() // Word Stemmer
{
    std::fstream Fin("./stem.txt", std::ios::in);  // band the fsrteam object with the file, to read from the file
    std::unordered_map<std::string, std::string> WordStemmer; // the WordStemmer to return
    std::string origin_word, stem_word;  // used to input each word pair

    while(Fin >> origin_word >> stem_word) // read every original word and its result after word stemming
    {
        WordStemmer[origin_word] = stem_word; // build the map between them 
    }

    return WordStemmer;
}