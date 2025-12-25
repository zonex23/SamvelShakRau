CXX = g++
CXXFLAGS = -std=c++11 -Wall


FIRST = first
SECOND = second
SHARED_ARRAY = shared_array.o


all: $(FIRST) $(SECOND)


$(FIRST): first.cpp $(SHARED_ARRAY)
	$(CXX) $(CXXFLAGS) -o $(FIRST) first.cpp $(SHARED_ARRAY)


$(SECOND): second.cpp $(SHARED_ARRAY)
	$(CXX) $(CXXFLAGS) -o $(SECOND) second.cpp $(SHARED_ARRAY)


$(SHARED_ARRAY): shared_array.cpp shared_array.h
	$(CXX) $(CXXFLAGS) -c shared_array.cpp

clean:
	rm -f $(FIRST) $(SECOND) $(SHARED_ARRAY)


rebuild: clean all
