#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryClient    makes DictionaryClient
#  make DictionaryTest      makes DictionaryTest
#  make Order               makes Order
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg
#  make DictionaryCheck     runs DictionaryClient under valgrind
#  make DictionaryTestCheck runs DictionaryTest under valgrind
#  make OrderCheck          runs Order under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
ADT            = Dictionary
ORDER          = Order
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT_TEST       = $(ADT)Client
ADT_TEST_EXE   = DictionaryTest
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
ORDER_SOURCE   = $(ORDER).cpp
ORDER_OBJECT   = $(ORDER).o
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(ADT_TEST_EXE): $(ADT_TEST_EXE).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST_EXE) $(ADT_TEST_EXE).o $(ADT_OBJECT)

$(ORDER): $(ORDER_OBJECT) $(ADT_OBJECT)
	$(LINK) $(ORDER) $(ORDER_OBJECT) $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_TEST_EXE).o: $(ADT_TEST_EXE).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST_EXE).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

$(ORDER_OBJECT): $(ORDER_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ORDER_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(ADT_TEST) $(ADT_TEST_EXE) $(ORDER) $(OBJECT) $(ADT_TEST).o $(ADT_TEST_EXE).o $(ORDER_OBJECT) $(ADT_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) Gutenberg myGutenberg-out

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)

$(ADT)TestCheck: $(ADT_TEST_EXE)
	$(MEMCHECK) $(ADT_TEST_EXE)

$(ORDER)Check: $(ORDER)
	$(MEMCHECK) $(ORDER) input.txt output.txt