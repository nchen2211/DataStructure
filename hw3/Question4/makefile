BIN_DIR = exe
CXX = g++
CPPFLAGS = -Wall -g
all: $(BIN_DIR)/hw3q4

$(BIN_DIR)/hw3q4: $(BIN_DIR)/llistint1.o $(BIN_DIR)/stackint.o
	$(CXX) $(CPPFLAGS) -Wall $(BIN_DIR)/llistint1.o $(BIN_DIR)/stackint.o main.cpp -o $(BIN_DIR)/hw3q4

$(BIN_DIR)/llistint1.o: lib/llistint1.h src/llistint1.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -Wall -c src/llistint1.cpp -o $(BIN_DIR)/llistint1.o

$(BIN_DIR)/stackint.o: lib/stackint.h src/stackint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -Wall -c src/stackint.cpp -o $(BIN_DIR)/stackint.o

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)