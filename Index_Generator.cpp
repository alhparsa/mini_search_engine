#include "IncludeFiles.hpp"

extern std::string Path; // define in "Word_Counter.cpp"
extern std::string FilePath; // define in "Word_Counter.cpp"

// return value explaination:
// the first component of std::pair is a file's filename
// the second componentis the word index of this file
    // the first component std::string of the map is a word
    // the second component std::string is its total appear time in the passage and its appear place (stored in vector)
// the target of this search engine is to find the most possible file
// so build the index of every file will make it easy for us to find the target file by calculating the total appear frequency of query  
std::vector<std::pair<std::string, std::unordered_map<std::string, std::pair<int, std::vector<int>>>>> 
get_index_generation(const std::unordered_map<std::string, int>& StopWordList)  // Index Generator
{
    // the IndexGenerator to return
    std::vector<std::pair<std::string, std::unordered_map<std::string, std::pair<int, std::vector<int>>>>> IndexGenerator;
    // used to input each word
    std::string TempWord;

    _finddata_t FileInfo; // struct _finddata_t is defined in "corecrt_io.h", store a file's information
    long handle = _findfirst(FilePath.c_str(), &FileInfo);  // handle of the file, FileInfo will store this file's information
    int file_order = 0;  // note the total file amount which is dealt 

    do 
    {
        std::fstream Fin(Path + FileInfo.name, std::ios::in);  // band the fsrteam object with the file, to read from the file
        // insert a new object into IndexGenerator
        IndexGenerator.emplace_back(FileInfo.name, std::unordered_map<std::string, std::pair<int, std::vector<int>>>() );
        int word_order = 1; // note the appear place of the word in the file
        while(Fin >> TempWord)
        {
            if( 0 == StopWordList.count(TempWord) ) // if we are dealing with a stop word, it should be ignored
            {
                if( 0 == IndexGenerator[file_order].second.count(TempWord) ) // if this word hasn't appeared in this file yet
                {
                    IndexGenerator[file_order].second[TempWord].first = 1; // initialize this word into the map
                }

                else
                {
                    ++IndexGenerator[file_order].second[TempWord].first; // increment the word's appear frequency
                }

                IndexGenerator[file_order].second[TempWord].second.emplace_back(word_order); // note the appear place in the vector 
            }
            word_order++; // increment the word order
        }

        ++file_order; // increment the file order
    } while (_findnext(handle, &FileInfo) == 0); // if not all files have been dealt

    return IndexGenerator;
}