#include "IncludeFiles.hpp"

extern std::string Path; // define in "IncludeFiles.hpp"
extern std::string FilePath; // define in "IncludeFiles.hpp"
extern std::string OriginPath; // define in "IncludeFiles.hpp"

int main(int argc, const char* argv[])
{
    // counting word frequency
    std::cout << "Word Counter running..." << std::endl;
    auto SortList = get_word_count(); // get the counting result
    std::fstream fout("WordCount.txt", std::ios::out); // write the result into the text file
    std::unordered_map<std::string, int> StopWordList; // get the list of stop word
    for(auto i : SortList) // write the result into the text file
    {
        fout << " (" << i.first << ", " << i.second << ") ";
        if( i.second >= 2000 || i.first.length() <= 2 ) // too common or too short word should be stop word
        {
            StopWordList[i.first] = 1;
        }
    }
    std::cout << "Word counting complete. You can see the result in the \"WordCount.txt\"." << std::endl;

    // initialize word stemming table
    std::cout << "Word Stemmer running..." << std::endl;
    auto WordStemmer = word_stemmer(); // build the word stemmer with "stem.txt"
    std::cout << "Word Stemmer complete." << std::endl;

    // get the index generation
    std::cout << "Index Generator running..." << std::endl;
    auto IndexGenerator = get_index_generation(StopWordList);  // build the index generator
    std::fstream iout("Index.txt", std::ios::out); // band the fsrteam object with the file, to read from the file
    for(auto& z : IndexGenerator)  // write the file index into the "Index.txt"
    {
        iout << std::endl << z.first << std::endl << std::endl; // first write the file's name into the text
        for(auto& i : z.second) // ippo among every word ever appear in this file
        {
            iout << i.first << "  " << i.second.first << "  " << std::endl; // write the word and its total appear time
            for(auto &j : i.second.second)
            {
                iout << j << " "; // write the word's every appear place
            }
            iout << std::endl;
        }
    }
    std::cout << "Index Generation complete. You can see the result in the \"Index.txt\"." << std::endl << std::endl;

    // query process
    std::cout << "Do you want to try to query over our shakespeare's work set? Input 'y' to query, and others to exit: ";
    char mode; // the state mode, note if countinue query
    std::cin >> mode;
    while( 'y' == mode )
    {
        try
        {
            std::vector<std::string> Query;
            std::string SingleWord;
            int QueryNum; // the size of original query
            std::cout << "Please input the amount of query words: ";
            std::cin >> QueryNum; // input the size of original query
            for (int iter = 0; iter < QueryNum; ++iter) // input the content of original query
            {
                std::cin >> SingleWord;
                Query.emplace_back(SingleWord);
            }

            auto NewQuery = query_preprocessor(Query, WordStemmer, StopWordList);  // query preprocess
            auto QueryResult = query_processor(NewQuery, IndexGenerator); // query process

            std::cout << "Query Result: " << QueryResult.first << std::endl;
            std::cout << "Appear place of the original passage:" << std::endl;
            for(auto& p : QueryResult.second) // output every keyword's passage content nearby
            {
                std::cout << "...";
                std::fstream Fin(Path + QueryResult.first, std::ios::in);  // band the fsrteam object with the file, to read from the file
                std::string TempWord;  // read from the file
                int place = 1;  // the word order while processing 
                while(Fin >> TempWord)
                {
                    if( place - p >= -5 && place - p <= 5 )  // this means if we'll meet the keyword
                    {
                        std::cout << TempWord << " "; // output the content
                    }
                    ++place;
                }
                std::cout << "..." << std::endl;
            }
        }
        catch(std::runtime_error e)
        {
            std::cout << "Sorry, but we cannot find anything about your query." << std::endl;
        }

        std::cout << "Countinue to query? Input 'y' to query, and others to exit: ";
        std::cin >> mode; // if continue to query
    }

    std::cout << "Search system log out." << std::endl;
    system("pause");
    return 0;
}