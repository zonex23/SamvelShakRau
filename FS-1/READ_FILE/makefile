CXX := g++
CXXFLAGS :=  -Wall -Wextra -std=c++17

TARGET := read_file
SRC := read_file.cpp


all: $(TARGET)

$(TARGET) : $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
