BIN_DIR = exe
CXX = g++
CPPFLAGS = -Wall -g
all: $(BIN_DIR)/zipf

$(BIN_DIR)/zipf: main.cpp $(BIN_DIR)/hash_table.o $(BIN_DIR)/splaybst.o
	$(CXX) $(CPPFLAGS) -Wall $(BIN_DIR)/hash_table.o $(BIN_DIR)/splaybst.o main.cpp -o $(BIN_DIR)/zipf

$(BIN_DIR)/splaybst.o: splaybst.h splaybst.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -Wall -c splaybst.cpp -o $(BIN_DIR)/splaybst.o

$(BIN_DIR)/hash_table.o: hashtable.h hashtable.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -Wall -c hashtable.cpp -o $(BIN_DIR)/hash_table.o

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)