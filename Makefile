CC=g++

all: user.o fileio.o admin.o main.o
	$(CC) main.o user.o fileio.o admin.o -o ticket-seller
