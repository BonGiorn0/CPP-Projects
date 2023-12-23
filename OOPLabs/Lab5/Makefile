SRCMODULES = CSet.cpp
UNIQUESRCMODULES = CSetUnique.cpp
OBJMODULES = $(SRCMODULES:.cpp=.o)
UNIQUEOBJMODULES = $(UNIQUESRCMODULES:.cpp=.o)
CFLAGS = -g -Wall

%.o: %.cpp %.hpp
	g++ -fPIE $(CFLAGS) -c $< -o $@

main: main.c $(OBJMODULES)
	g++ $(CFLAGS) $^ -o $@

unique_main: main.c $(UNIQUEOBJMODULES)
	g++ -D UNIQUE $(CFLAGS) $^ -o $@

-include deps.mk

deps.mk: $(SRCMODULES)
	g++ -MM $^ > $@

deps.mk: $(UNIQUESRCMODULES)
	g++ -MM $^ > $@