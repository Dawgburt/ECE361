CC = gcc
CFLAGS = -std=c99 -Wall
SOURCES = TempHumidBST.c bst.c iom361_r2.c float_rndm.c
OBJECTS = $(SOURCES:.c=.o)  # Object files corresponding to source files
EXECUTABLE = TempHumidBST_App

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(EXECUTABLE)