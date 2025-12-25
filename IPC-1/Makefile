CC = g++

CFLAGS = -std=c++11 -Wall


TARGET = signal-echo

all: $(TARGET)


$(TARGET): signal-echo.cpp
	$(CC) $(CFLAGS) signal-echo.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
