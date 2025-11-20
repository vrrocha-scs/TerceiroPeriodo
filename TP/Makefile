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

$(OBJ_DIR)/utilitarios.o : $(SRC_DIR)/utilitarios.cpp $(INCLUDE_DIR)/utilitarios.hpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/utilitarios.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/utilitarios.o

$(OBJ_DIR)/corrida.o : $(SRC_DIR)/corrida.cpp $(INCLUDE_DIR)/corrida.hpp $(INCLUDE_DIR)/demanda.hpp $(INCLUDE_DIR)/trecho.hpp $(INCLUDE_DIR)/parada.hpp $(INCLUDE_DIR)/utilitarios.hpp $(INCLUDE_DIR)/evento.hpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/corrida.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/corrida.o

$(OBJ_DIR)/minheap.o : $(SRC_DIR)/minheap.cpp $(INCLUDE_DIR)/minheap.hpp $(INCLUDE_DIR)/evento.hpp 
	${CC} ${CFLAGS} -c $(SRC_DIR)/minheap.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/minheap.o

$(OBJ_DIR)/evento.o : $(INCLUDE_DIR)/evento.hpp $(INCLUDE_DIR)/parada.hpp 
	${CC} ${CFLAGS} -c $(SRC_DIR)/evento.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/evento.o

$(OBJ_DIR)/main.o : $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/demanda.hpp $(INCLUDE_DIR)/trecho.hpp $(INCLUDE_DIR)/corrida.hpp $(INCLUDE_DIR)/minheap.hpp 
	${CC} ${CFLAGS} -c $(SRC_DIR)/main.cpp ${LIBS} -I$(INCLUDE_DIR) -o $(OBJ_DIR)/main.o

main: $(OBJ_DIR)/main.o $(OBJ_DIR)/corrida.o $(OBJ_DIR)/demanda.o $(OBJ_DIR)/minheap.o $(OBJ_DIR)/utilitarios.o | bin
	$(CC) $(CFLAGS) $^ -o bin/tp1.out

clean:
	rm -rf obj bin
