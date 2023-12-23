SRCMODULES = CBigNumber.cpp Exceptions.cpp
UNIQUESRCMODULES = CSetUnique.cpp Exceptions.cpp
OBJMODULES = $(SRCMODULES:.cpp=.o)
UNIQUEOBJMODULES = $(UNIQUESRCMODULES:.cpp=.o)
CFLAGS = -g -Wall

%.o: %.cpp %.hpp
	g++ -fPIE $(CFLAGS) -c $< -o $@

main: main.cpp $(OBJMODULES)
	g++ $(CFLAGS) $^ -o $@

unique_main: main.cpp $(UNIQUEOBJMODULES)
	g++ -D UNIQUE $(CFLAGS) $^ -o $@

test: test.cpp $(OBJMODULES)
	g++ -lgtest $(CFLAGS) $^ -o $@

unique_test: test.cpp $(UNIQUEOBJMODULES)
	g++ $(CFLAGS) $^ -o $@

-include deps.mk

deps.mk: $(SRCMODULES)
	g++ -MM $^ > $@

deps.mk: $(UNIQUESRCMODULES)
	g++ -MM $^ > $@