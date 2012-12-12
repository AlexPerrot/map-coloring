CC = g++
CFLAGS = -Wall -O3
EXEC_NAME = map_coloring
INCLUDES = 
LIBS =
OBJ_FILES = main.o graph/graph.o

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp %.h
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.cc %.h
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.c %.h
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<
