CC=g++
CFLAGS=-std=c++11 -Wall -g
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
all: main 
bin:
	mkdir -p bin
obj:
	mkdir -p obj

$(OBJ_DIR)/palavra.o : $(SRC_DIR)/palavra.cpp $(INCLUDE_DIR)/logradouro.hpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/palavra.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/palavra.o

$(OBJ_DIR)/minheap.o : $(SRC_DIR)/minheap.cpp $(INCLUDE_DIR)/logradouro.hpp 
	${CC} ${CFLAGS} -c $(SRC_DIR)/minheap.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/minheap.o

$(OBJ_DIR)/hash.o : $(SRC_DIR)/hash.cpp 
	${CC} ${CFLAGS} -c $(SRC_DIR)/hash.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/hash.o

$(OBJ_DIR)/main.o : $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/endereco.hpp $(INCLUDE_DIR)/logradouro.hpp $(INCLUDE_DIR)/palavra.hpp $(INCLUDE_DIR)/minheap.hpp $(INCLUDE_DIR)/hash.hpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/main.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/main.o

main: $(OBJ_DIR)/main.o $(OBJ_DIR)/palavra.o $(OBJ_DIR)/minheap.o $(OBJ_DIR)/hash.o | bin
	$(CC) $(CFLAGS) $^ -o bin/tp3.out

clean:
	rm -rf obj bin
