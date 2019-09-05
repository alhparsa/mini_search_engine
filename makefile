all: SearchEngine.exe

SearchEngine.exe: IncludeFiles.hpp Word_Counter.cpp Word_Stemmer.cpp Index_Generator.cpp Query_Preprocessor.cpp Query_Processor.cpp main.cpp
	g++ -o SearchEngine.exe Word_Counter.cpp Word_Stemmer.cpp Index_Generator.cpp Query_Preprocessor.cpp Query_Processor.cpp main.cpp

clean:
	del *.exe