ifeq ($(OS), Windows_NT)
	INCLUDES := Includes\\
	BUILD := Build\\
	BIN := Bin\\
	EXECUTABLE := $(BIN)AssignmentC.exe
	SOURCE := Source\\
	DELETE := del
else
	INCLUDES := Includes/
	BUILD := Build/
	BIN := Bin/
	EXECUTABLE := $(BIN)/AssignmentD
	SOURCE := Source/
	DELETE := rm
endif


FLAGSO := g++ -g -c -std=c++11 -Wall -Wextra -Wpedantic
FLAGSL := g++ -g -std=c++11 -Wall -Wextra -Wpedantic

all: $(BUILD) $(BIN) $(EXECUTABLE)

$(EXECUTABLE): $(BUILD)Main.o
	$(FLAGSL) $(BUILD)Main.o -o $(EXECUTABLE)

$(BUILD):
ifeq ($(OS), Windows_NT)
	-@ if NOT EXIST $(BUILD) mkdir $(BUILD)
else
	if [! -d $(BUILD)]; then mkdir $(BUILD)
endif
$(BIN):
ifeq ($(OS), Windows_NT)
	-@ if NOT EXIST $(BIN) mkdir $(BIN)
else
	if [! -d $(BIN)]; then mkdir $(BIN)
endif

$(BUILD)Main.o: $(SOURCE)Main.cpp
	$(FLAGSO) $(SOURCE)Main.cpp -o $(BUILD)Main.o

clean:
	-$(DELETE) $(BUILD)Main.o $(EXECUTABLE)

