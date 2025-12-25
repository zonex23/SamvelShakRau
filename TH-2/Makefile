CC = g++
CFLAGS = -std=c++11 -pthread -Wall -fPIC
LDFLAGS = -pthread
LIBNAME = libparallel_scheduler.so
DEMO = demo-application
all: $(LIBNAME) $(DEMO)

$(LIBNAME): parallel_scheduler.o
	$(CC) -shared -o $@ $^ $(LDFLAGS)

parallel_scheduler.o: parallel_scheduler.cpp parallel_scheduler.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(DEMO): demo-application.o $(LIBNAME)
	$(CC) $< -L. -lparallel_scheduler -o $@ $(LDFLAGS)

demo-application.o: demo-application.cpp parallel_scheduler.hpp
	$(CC) $(CFLAGS) -c $< -o $@

run: $(DEMO)
	LD_LIBRARY_PATH=. ./$(DEMO)


clean:
	rm -f *.o *.so $(DEMO)

.PHONY: all clean run
