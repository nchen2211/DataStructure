BIN_DIR = exe
CXX = g++
CPPFLAGS = -Wall -g
all: $(BIN_DIR)/hw3q5

$(BIN_DIR)/hw3q5: $(BIN_DIR)/llistint.o $(BIN_DIR)/stackint.o
	$(CXX) $(CPPFLAGS) -Wall $(BIN_DIR)/llistint.o $(BIN_DIR)/stackint.o hw3q5_main.cpp -o $(BIN_DIR)/hw3q5

$(BIN_DIR)/llistint.o: lib/llistint.h src/llistint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -Wall -c src/llistint.cpp -o $(BIN_DIR)/llistint.o

$(BIN_DIR)/stackint.o: lib/stackint.h src/stackint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -Wall -c src/stackint.cpp -o $(BIN_DIR)/stackint.o

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)