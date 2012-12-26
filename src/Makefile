CC = g++
CFLAGS = -Wall -g
EXEC_NAME = map_coloring
INCLUDES = 
LIBS =
OBJ_FILES = main.o graph/graph.o game/game.o

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

main.o : main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o main.o -c main.cpp

%.o: %.cpp %.h
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.cc %.h
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.c %.h
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<
