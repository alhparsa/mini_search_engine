#include "IncludeFiles.hpp"

// this function will do the word stemming job for the original input query
std::vector<std::string> query_preprocessor(const std::vector<std::string>& Query, 
                                            const std::unordered_map<std::string, std::string>& WordStemmer,
                                            const std::unordered_map<std::string, int>& StopWordList)
{
    std::vector<std::string> NewQuery;
    
    for(auto s : Query)
    {
        auto temp_s = s;
        std::transform(temp_s.begin(), temp_s.end(), temp_s.begin(), ::tolower); // tramsforn a word to its lowercase form
        if( 0 == StopWordList.count(temp_s) ) // if this word is not a stop word
        {
            if( 0 != WordStemmer.count(temp_s) ) // if this word really ever appear in all files
            {
                NewQuery.emplace_back(WordStemmer.at(temp_s));  // insert the word stemmed form of this word
            }
        }
    }

    return NewQuery;
}