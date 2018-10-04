CC=gcc
CFLAGS=-c -Wall 
EXECUTE=newton

$(EXECUTE): $(EXECUTE).o
	$(CC) -o $(EXECUTE) $(EXECUTE).o -lm

$(EXECUTE).o: $(EXECUTE).c
	$(CC)  $(CFLAGS) $(EXECUTE).c -lm
