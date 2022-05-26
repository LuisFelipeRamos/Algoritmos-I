#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: Compilar o Trabalho Prático 1 - Disciplina de Algoritmos I
# Autor		: Luís Felipe Ramos Ferreira - Matrícula: 2019022553
#---------------------------------------------------------------------
# Opções	: make - compila tudo e gera o 'target' executável
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = g++
CFLAGS = -Wall -c
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/PreferenceList.o $(OBJ)/GaleShapley.o
HDRS = $(INC)/PreferenceList.hpp $(INC)/GaleShapley.hpp
CFLAGS = -Wall -c -I$(INC) -std=c++17

EXE = $(BIN)/tp01

$(BIN)/tp01: $(OBJS)
	$(CC) -o $(BIN)/tp01 $(OBJS) $(LIBS)

$(OBJ)/PreferenceList.o: $(HDRS) $(SRC)/PreferenceList.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/PreferenceList.o $(SRC)/PreferenceList.cpp


$(OBJ)/GaleShapley.o: $(HDRS) $(SRC)/GaleShapley.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/GaleShapley.o $(SRC)/GaleShapley.cpp

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

clean:
	rm  $(EXE) $(OBJS)