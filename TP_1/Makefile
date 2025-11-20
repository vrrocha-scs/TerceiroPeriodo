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


$(OBJ_DIR)/cena.o : $(INCLUDE_DIR)/cena.hpp $(INCLUDE_DIR)/insertion.hpp $(INCLUDE_DIR)/objeto.hpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/cena.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/cena.o

$(OBJ_DIR)/insertion.o : $(INCLUDE_DIR)/objeto.hpp $(INCLUDE_DIR)/insertion.hpp $(INCLUDE_DIR)/cena.hpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/insertion.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/insertion.o

$(OBJ_DIR)/minheap.o : $(INCLUDE_DIR)/minheap.hpp $(INCLUDE_DIR)/objeto.hpp 
	${CC} ${CFLAGS} -c $(SRC_DIR)/minheap.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/minheap.o

$(OBJ_DIR)/objeto.o : $(INCLUDE_DIR)/objeto.hpp $(INCLUDE_DIR)/insertion.hpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/objeto.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/objeto.o

$(OBJ_DIR)/main.o : $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/cena.hpp $(INCLUDE_DIR)/objeto.hpp $(INCLUDE_DIR)/insertion.hpp $(INCLUDE_DIR)/minheap.hpp 
	${CC} ${CFLAGS} -c $(SRC_DIR)/main.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/main.o

main: $(OBJ_DIR)/main.o $(OBJ_DIR)/objeto.o $(OBJ_DIR)/insertion.o $(OBJ_DIR)/cena.o $(OBJ_DIR)/minheap.o | bin
	$(CC) $(CFLAGS) $^ -o bin/tp1.out

clean:
	rm -rf obj bin
