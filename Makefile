EXENAME = main
OBJS = main.o map.o point.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread -lm

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

map.o : map.cpp map.hpp
	$(CXX) $(CXXFLAGS) map.cpp

point.o : point.cpp point.hpp
	$(CXX) $(CXXFLAGS) point.cpp

clean:
	-rm -f *.o $(EXENAME)
