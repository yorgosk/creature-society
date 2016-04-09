CC = g++
CFLAGS = -Wall
OBJECTS = main.o functions.o

society: $(OBJECTS)
	$(CC) $(CFLAGS) -o society $(OBJECTS)

main.o: main.cc
	$(CC) $(CFLAGS) -c main.cc

functions.o: functions.cc
	$(CC) $(CFLAGS) -c functions.cc

.PHONY: clean

clean:
	rm -f society $(OBJECTS)
