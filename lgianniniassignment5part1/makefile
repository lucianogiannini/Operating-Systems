CC = g++
CPPFLAGS = -I.
LDFLAGS = -Wl,--no-as-needed -lpthread
main: main.o Item.o Resource.o
main.o: main.cpp main.h
Item.o: Item.cpp Item.h
Resource.o: Resource.cpp Resource.h
clean:
	rm *.o
	rm main
