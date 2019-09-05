#include "IncludeFiles.hpp"

extern std::string Path; // define in "Word_Counter.cpp"
extern std::string FilePath; // define in "Word_Counter.cpp"

// return value explaination:
// the first component of the pair is the most possible file's name
// the second component of the pair is every keyword's first appear place
std::pair<std::string, std::vector<int>> query_processor (
                 std::vector<std::string> Query,
                 std::vector<std::pair<std::string, std::unordered_map<std::string, std::pair<int, std::vector<int>>>>> IndexGenerator
                ) // Query Preprocessor
{
    if( Query.size() == 0 )
    {
        throw std::runtime_error("ERROR");
    }

    std::pair<std::string, std::vector<int>> query_result; // the Query process result to return
    int max_frequency = -1; // the most possible file's frequency
    int temp_frequency = 0;

    for(auto& file: IndexGenerator) // search among every file
    {
        std::vector<int> page_index; // the keyword's appear place

        for(auto& word : Query) // loop amoung every key word
        {
            if(0 != file.second.count(word)) // if this key word ever appear in this file
            {
                temp_frequency += file.second.at(word).first; // add the word's frequency
                page_index.emplace_back(file.second.at(word).second[0]); // add its appear place
            }
        }

        if(temp_frequency > max_frequency) // if this file is more possible
        {
            max_frequency = temp_frequency; // update the max frequency
            query_result.first = file.first; // update the file's name
            query_result.second = page_index; // convey these word's first index
        }
        temp_frequency = 0; // initlalize the frequency
    }

    return query_result;
}