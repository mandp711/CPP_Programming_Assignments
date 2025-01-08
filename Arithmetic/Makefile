#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 6
#
#  make                     makes Arithmetic
#  make BigIntegerClient    makes BigIntegerClient
#  make ListClient          makes ListClient
#  make ListTest            makes ListTest
#  make clean               removes all binaries
#  make ArithmeticCheck     runs Arithmetic in valgrind on in4 junk4
#  make BigIntegerCheck     runs BigIntegerTest in valgrind
#  make ListCheck           runs ListTest in valgrind
#  make BigIntegerTest      compiles and runs BigIntegerTest
#------------------------------------------------------------------------------

MAIN           = Arithmetic
ADT1           = BigInteger
ADT2           = List
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT1_TEST      = $(ADT1)Client
ADT1_SOURCE    = $(ADT1).cpp
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_TEST      = $(ADT2)Client
ADT2_SOURCE    = $(ADT2).cpp
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
LIST_TEST      = ListTest
LIST_TEST_SRC  = ListTest.cpp
LIST_TEST_OBJ  = ListTest.o
LIST_CLIENT    = ListClient
LIST_CLIENT_SRC = ListClient.cpp
LIST_CLIENT_OBJ = ListClient.o
BIGINT_TEST    = BigIntegerTest
BIGINT_TEST_SRC = BigIntegerTest.cpp
BIGINT_TEST_OBJ = BigIntegerTest.o
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(ADT1_TEST): $(ADT1_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(ADT1_TEST) $(ADT1_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)

$(ADT2_TEST): $(ADT2_TEST).o $(ADT2_OBJECT)
	$(LINK) $(ADT2_TEST) $(ADT2_TEST).o $(ADT2_OBJECT)

$(LIST_TEST): $(LIST_TEST_OBJ) $(ADT2_OBJECT)
	$(LINK) $(LIST_TEST) $(LIST_TEST_OBJ) $(ADT2_OBJECT)

$(LIST_CLIENT): $(LIST_CLIENT_OBJ) $(ADT2_OBJECT)
	$(LINK) $(LIST_CLIENT) $(LIST_CLIENT_OBJ) $(ADT2_OBJECT)

$(BIGINT_TEST): $(BIGINT_TEST_OBJ) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(BIGINT_TEST) $(BIGINT_TEST_OBJ) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(OBJECT): $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_TEST).o: $(ADT1_TEST).cpp $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(ADT1_TEST).cpp

$(ADT2_TEST).o: $(ADT2_TEST).cpp $(ADT2_HEADER)
	$(COMPILE) $(ADT2_TEST).cpp

$(BIGINT_TEST_OBJ): $(BIGINT_TEST_SRC) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(BIGINT_TEST_SRC)

$(ADT1_OBJECT): $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT): $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

$(LIST_TEST_OBJ): $(LIST_TEST_SRC) $(ADT2_HEADER)
	$(COMPILE) $(LIST_TEST_SRC)

$(LIST_CLIENT_OBJ): $(LIST_CLIENT_SRC) $(ADT2_HEADER)
	$(COMPILE) $(LIST_CLIENT_SRC)

clean:
	$(REMOVE) $(MAIN) $(ADT1_TEST) $(ADT2_TEST) $(LIST_TEST) $(LIST_CLIENT) $(BIGINT_TEST)
	$(REMOVE) $(OBJECT) $(ADT1_TEST).o $(ADT2_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(REMOVE) $(LIST_TEST_OBJ) $(LIST_CLIENT_OBJ) $(BIGINT_TEST_OBJ)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) in4 junk4

$(ADT1)Check: $(ADT1_TEST)
	$(MEMCHECK) $(ADT1_TEST)

$(ADT2)Check: $(ADT2_TEST)
	$(MEMCHECK) $(ADT2_TEST)

ListCheck: $(LIST_TEST)
	$(MEMCHECK) ./$(LIST_TEST)

ArithmeticCheck: $(MAIN)
	$(MEMCHECK) $(MAIN) in4 junk4

BigIntegerCheck: $(BIGINT_TEST)
	$(MEMCHECK) $(BIGINT_TEST)
