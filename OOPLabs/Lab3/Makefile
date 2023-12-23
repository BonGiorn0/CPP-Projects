SRCMODULES = BigNumber.cpp                                        
OBJMODULES = $(SRCMODULES:.cpp=.o)
CFLAGS = -g -Wall
 
%.o: %.cpp %.h
	g++ $(CFLAGS) -c $< -o $@

main: main.cpp $(OBJMODULES)
	g++ $(CFLAGS) $^ -o $@

test: test.cpp $(OBJMODULES)
	g++ $(CFLAGS) -lgtest $^ -o $@
 
-include deps.mk
 
deps.mk: $(SRCMODULES)
	g++ -MM $^ > $@
