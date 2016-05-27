BIN_DIR = exe
CXX = g++
CPPFLAGS = -Wall -g
all: $(BIN_DIR)/hw4

$(BIN_DIR)/hw4: Facile.cpp $(BIN_DIR)/llistint.o $(BIN_DIR)/stackint.o $(BIN_DIR)/ProgramState.o $(BIN_DIR)/LetStatement.o $(BIN_DIR)/PrintStatement.o $(BIN_DIR)/PrintAllStatement.o $(BIN_DIR)/GotoStatement.o $(BIN_DIR)/EndStatement.o $(BIN_DIR)/AddStatement.o $(BIN_DIR)/SubStatement.o $(BIN_DIR)/MultStatement.o $(BIN_DIR)/DivStatement.o $(BIN_DIR)/IfStatement.o $(BIN_DIR)/GosubStatement.o $(BIN_DIR)/ReturnStatement.o $(BIN_DIR)/EndStatement.o
	$(CXX) $(CPPFLAGS) -Wall $(BIN_DIR)/llistint.o $(BIN_DIR)/stackint.o $(BIN_DIR)/ProgramState.o $(BIN_DIR)/LetStatement.o $(BIN_DIR)/PrintStatement.o $(BIN_DIR)/PrintAllStatement.o $(BIN_DIR)/GotoStatement.o $(BIN_DIR)/EndStatement.o $(BIN_DIR)/AddStatement.o $(BIN_DIR)/SubStatement.o $(BIN_DIR)/MultStatement.o $(BIN_DIR)/DivStatement.o $(BIN_DIR)/IfStatement.o $(BIN_DIR)/GosubStatement.o $(BIN_DIR)/ReturnStatement.o Facile.cpp -o $(BIN_DIR)/hw4

$(BIN_DIR)/ReturnStatement.o: lib/ReturnStatement.h src/ReturnStatement.cpp 
	$(CXX) $(CPPFLAGS) -Wall -c src/ReturnStatement.cpp -o $(BIN_DIR)/ReturnStatement.o

$(BIN_DIR)/GosubStatement.o: lib/GosubStatement.h src/GosubStatement.cpp 
	$(CXX) $(CPPFLAGS) -Wall -c src/GosubStatement.cpp -o $(BIN_DIR)/GosubStatement.o

$(BIN_DIR)/IfStatement.o: lib/IfStatement.h src/IfStatement.cpp 
	$(CXX) $(CPPFLAGS) -Wall -c src/IfStatement.cpp -o $(BIN_DIR)/IfStatement.o

$(BIN_DIR)/DivStatement.o: lib/DivStatement.h src/DivStatement.cpp 
	$(CXX) $(CPPFLAGS) -Wall -c src/DivStatement.cpp -o $(BIN_DIR)/DivStatement.o

$(BIN_DIR)/MultStatement.o: lib/MultStatement.h src/MultStatement.cpp 
	$(CXX) $(CPPFLAGS) -Wall -c src/MultStatement.cpp -o $(BIN_DIR)/MultStatement.o

$(BIN_DIR)/SubStatement.o: lib/SubStatement.h src/SubStatement.cpp 
	$(CXX) $(CPPFLAGS) -Wall -c src/SubStatement.cpp -o $(BIN_DIR)/SubStatement.o

$(BIN_DIR)/AddStatement.o: lib/AddStatement.h src/AddStatement.cpp 
	$(CXX) $(CPPFLAGS) -Wall -c src/AddStatement.cpp -o $(BIN_DIR)/AddStatement.o

$(BIN_DIR)/EndStatement.o: lib/EndStatement.h src/EndStatement.cpp 
	$(CXX) $(CPPFLAGS) -Wall -c src/EndStatement.cpp -o $(BIN_DIR)/EndStatement.o

$(BIN_DIR)/GotoStatement.o: lib/GotoStatement.h src/GotoStatement.cpp 
	$(CXX) $(CPPFLAGS) -Wall -c src/GotoStatement.cpp -o $(BIN_DIR)/GotoStatement.o

$(BIN_DIR)/PrintAllStatement.o: lib/PrintAllStatement.h src/PrintAllStatement.cpp 
	$(CXX) $(CPPFLAGS) -Wall -c src/PrintAllStatement.cpp -o $(BIN_DIR)/PrintAllStatement.o

$(BIN_DIR)/PrintStatement.o: lib/PrintStatement.h src/PrintStatement.cpp 
	$(CXX) $(CPPFLAGS) -Wall -c src/PrintStatement.cpp -o $(BIN_DIR)/PrintStatement.o

$(BIN_DIR)/LetStatement.o: lib/LetStatement.h src/LetStatement.cpp 
	$(CXX) $(CPPFLAGS) -Wall -c src/LetStatement.cpp -o $(BIN_DIR)/LetStatement.o

$(BIN_DIR)/ProgramState.o: lib/ProgramState.h src/ProgramState.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -Wall -c src/ProgramState.cpp -o $(BIN_DIR)/ProgramState.o

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