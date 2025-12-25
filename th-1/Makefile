CXX = g++

CXXFLAGS = -std=c++11 -pthread -Wall -O2


TARGET = sum_arr

SRC = sum_arr.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
