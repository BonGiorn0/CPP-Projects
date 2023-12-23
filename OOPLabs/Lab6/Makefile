SRCMODULES = Deposit.cpp
OBJMODULES = $(SRCMODULES:.cpp=.o)
CFLAGS = -g -Wall

%.o: %.cpp %.hpp
	g++ $(CFLAGS) -c $< -o $@

main: main.cpp $(OBJMODULES)
	g++ $(CFLAGS) $^ -o $@

-include deps.mk

deps.mk: $(SRCMODULES)
	g++ -MM $^ > $@