ifeq ($(OS), Windows_NT)
	INCLUDES := Includes\\
	BUILD := Build\\
	BIN := Bin\\
	EXECUTABLE := $(BIN)dijkstra.exe
	SOURCE := Source\\
	DELETE := del
else
	INCLUDES := Includes/
	BUILD := Build/
	BIN := Bin/
	EXECUTABLE := $(BIN)dijkstra
	SOURCE := Source/
	DELETE := rm
endif

CPP := g++
CPPFLAGS := -std=c++17 

all: $(EXECUTABLE)

$(EXECUTABLE): $(BUILD)main.o
	$(CPP) $(CPPFLAGS) $(BUILD)main.o -o $(EXECUTABLE)

$(BUILD)main.o: $(SOURCE)main.cpp $(INCLUDES)PriorityQ.hpp
	$(CPP) $(CPPFLAGS) -c $(SOURCE)main.cpp -I$(INCLUDES) -o $(BUILD)main.o

clean:
	-$(DELETE) $(EXECUTABLE) $(BUILD)main.o