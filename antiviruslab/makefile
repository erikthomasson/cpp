
all: Build/ Antivirus 

Antivirus: Build/main.o Build/Functions.o
	g++ -g -std=c++11 Build/main.o Build/Functions.o -o Antivirus

Build/main.o: Source/main.cpp
	g++ -g -c -std=c++11 Source/main.cpp -o Build/main.o

Build/Functions.o: Source/Functions.cpp
	g++ -g -c -std=c++11 Source/Functions.cpp -o Build/Functions.o

clean:
	-rm Build/Functions.o Build/main.o Antivirus