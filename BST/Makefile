#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryClient     makes DictionaryClient
#  make Order                makes Order
#  make DictionaryTest       makes DictionaryTest
#  make clean                removes all binaries
#  make WordFrequencyCheck   runs WordFrequency under valgrind on Gutenberg
#  make DictionaryCheck      runs DictionaryClient under valgrind
#  make OrderCheck           runs Order under valgrind
#  make DictionaryTestCheck  runs DictionaryTest under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
ADT            = Dictionary
ORDER          = Order
DICT_TEST      = DictionaryTest   # Added DictionaryTest target
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT_TEST       = $(ADT)Client
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
ORDER_SOURCE   = $(ORDER).cpp
ORDER_OBJECT   = $(ORDER).o
DICT_TEST_SRC  = DictionaryTest.cpp  # Added DictionaryTest source file
DICT_TEST_OBJ  = DictionaryTest.o    # Added DictionaryTest object file
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(ORDER): $(ORDER_OBJECT) $(ADT_OBJECT)
	$(LINK) $(ORDER) $(ORDER_OBJECT) $(ADT_OBJECT)

# Ensure DictionaryTest is correctly compiled and linked
$(DICT_TEST): $(DICT_TEST_OBJ) $(ADT_OBJECT)
	$(LINK) $(DICT_TEST) $(DICT_TEST_OBJ) $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(DICT_TEST_OBJ): $(DICT_TEST_SRC) $(ADT_HEADER)  # Added DictionaryTest object compilation
	$(COMPILE) $(DICT_TEST_SRC)

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

$(ORDER_OBJECT): $(ORDER_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ORDER_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(ADT_TEST) $(ORDER) $(DICT_TEST) $(OBJECT) $(ADT_TEST).o $(ORDER_OBJECT) $(ADT_OBJECT) $(DICT_TEST_OBJ)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) Gutenberg myGutenberg-out

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)

$(ORDER)Check: $(ORDER)
	$(MEMCHECK) $(ORDER) input.txt output.txt

# Fixed target for DictionaryTestCheck under Valgrind
$(DICT_TEST)Check: $(DICT_TEST)
	$(MEMCHECK) ./$(DICT_TEST)
