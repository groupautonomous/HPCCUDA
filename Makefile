CC=gcc
CFLAGS=-c -Ofast -g 
EXECUTE=newton

.PHONY : clean

all : $(EXECUTE)

$(EXECUTE): $(EXECUTE).o
	$(CC) -o $(EXECUTE) $(EXECUTE).o -lm -pthread

$(EXECUTE).o: $(EXECUTE).c
	$(CC) $(CFLAGS) $(EXECUTE).c -lm -pthread


clean : 
	rm -f $(EXECUTE).o $(EXECUTE)
