#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Shuffle
#  make ListClient     makes ListClient
#  make ListTest       makes ListTest (for testing the List class)
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

# Targets for building the main programs
Shuffle : Shuffle.o List.o
	g++ -std=c++17 -Wall -o Shuffle Shuffle.o List.o 

ListClient : ListClient.o List.o
	g++ -std=c++17 -Wall -o ListClient ListClient.o List.o 

# Add target for testing
ListTest : ListTest.o List.o
	g++ -std=c++17 -Wall -o ListTest ListTest.o List.o

# Object file dependencies
Shuffle.o : List.h Shuffle.cpp
	g++ -std=c++17 -Wall -c Shuffle.cpp

ListClient.o : List.h ListClient.cpp
	g++ -std=c++17 -Wall -c ListClient.cpp

ListTest.o : List.h ListTest.cpp
	g++ -std=c++17 -Wall -c ListTest.cpp

List.o : List.h List.cpp
	g++ -std=c++17 -Wall -c List.cpp

# Clean up binary files
clean :
	rm -f Shuffle Shuffle.o ListClient ListClient.o ListTest ListTest.o List.o

# Run memory leak checks using valgrind
check1 : ListClient
	valgrind --leak-check=full ListClient

check2 : Shuffle
	valgrind --leak-check=full Shuffle 35
