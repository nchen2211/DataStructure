CXX = g++
CPPFLAGS = -Wall -g
BIN_DIR = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/llistint.o
	-@echo "--- All Built!---"

$(BIN_DIR)/llistint.o: lib/llistint.h src/llistint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -Wall -c src/llistint.cpp -o $(BIN_DIR)/llistint.o

$(BIN_DIR)/listtest: test.cpp $(BIN_DIR)/llistint.o
	$(CXX) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/.dirstamp:
	-mkdir -p $(BIN_DIR)
	-touch $@

.PHONY: clean llisttest

llisttest: $(BIN_DIR)/listtest
	-@$(BIN_DIR)/listtest
	-@echo "--- All Tested!---"

clean:
	-rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"
	