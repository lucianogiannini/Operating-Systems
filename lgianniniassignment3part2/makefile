CC = g++
CPPFLAGS = -I. -g
LDFLAGS = -Wl,--no-as-needed -lpthread
main: main.o
main.o: main.cpp SafeQueue.cpp
clean:
	rm main
	rm *.o
