#include "IncludeFiles.hpp"

std::string Path = "./shakespeare_dealt/"; // the parent path of the text file
std::string FilePath = "./shakespeare_dealt/*.txt"; // file path format for loop every file
std::string OriginPath = "./shakespeare/"; // the origin files without preprocess

bool count_compare(std::pair<std::string, int> w1, std::pair<std::string, int> w2) // word list sorter used in std::sort()
{
    return w1.second > w2.second;
}

// return value explaination:
// the first component of std::pair is a word appear in the text files after word stemming
// the second component of std::pair is the total time this word appear in exery file
std::vector<std::pair<std::string, int>> get_word_count() // Word Counter
{
    std::vector<std::pair<std::string, int>> SortList; // used to sort words, ordered by its appear frequency
    std::unordered_map<std::string, int> WordCount; // map the word to its its appear frequency
    std::string TempWord; // used to input each word

    _finddata_t FileInfo; // struct _finddata_t is defined in "corecrt_io.h", store a file's information
    long handle = _findfirst(FilePath.c_str(), &FileInfo); // handle of the file, FileInfo will store this file's information

    do 
    {
        std::fstream Fin(Path + FileInfo.name, std::ios::in); // band the fsrteam object with the file, to read from the file 
        while(Fin >> TempWord)
        {
            if( 0 == WordCount.count(TempWord) ) // if the word has not appeared in the counting word's hash table
            {
                WordCount[TempWord] = 1;  //the appear frequency of this word is initialized to be 1
            }

            else  // increment the appear frequency of this word
            {
                ++WordCount[TempWord];
            }
        }

    } while (_findnext(handle, &FileInfo) == 0);  // if all files haven't been dealt yet

    for(auto& word : WordCount) // insert every pair into a vector to sort them
    {
        SortList.emplace_back(std::make_pair(word.first, word.second));
    }

    std::sort(SortList.begin(), SortList.end(), count_compare); // <algorithm>

    return SortList;
}