OBJ_DIR = output

OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/lexer.o $(OBJ_DIR)/symbole.o $(OBJ_DIR)/automate.o $(OBJ_DIR)/state.o
TEST_OBJS = $(OBJ_DIR)/lexer.o $(OBJ_DIR)/symbole.o $(OBJ_DIR)/automate.o $(OBJ_DIR)/state.o

main: $(OBJS)
	g++ -std=c++17 -Wall -o main $(OBJS)

tests: $(TEST_OBJS) tests.cpp
	g++ -std=c++17 -Wall -o tests $(TEST_OBJS) tests.cpp

$(OBJ_DIR)/main.o: main.cpp lexer.h automate.h state.h symbole.h | $(OBJ_DIR)
	g++ -std=c++17 -Wall -c main.cpp -o $@

$(OBJ_DIR)/lexer.o: lexer.cpp lexer.h | $(OBJ_DIR)
	g++ -std=c++17 -Wall -c lexer.cpp -o $@

$(OBJ_DIR)/symbole.o: symbole.cpp symbole.h | $(OBJ_DIR)
	g++ -std=c++17 -Wall -c symbole.cpp -o $@

$(OBJ_DIR)/automate.o: automate.cpp automate.h | $(OBJ_DIR)
	g++ -std=c++17 -Wall -c automate.cpp -o $@

$(OBJ_DIR)/state.o: state.cpp state.h | $(OBJ_DIR)
	g++ -std=c++17 -Wall -c state.cpp -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf main tests $(OBJ_DIR)