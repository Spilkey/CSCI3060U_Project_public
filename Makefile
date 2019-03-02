CC=g++

all: user.o fileio.o admin.o helper_func.o main.o
	$(CC) main.o user.o fileio.o admin.o helper_func.o -o ticket-seller
