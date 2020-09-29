SOURCES = gtrace.c exam.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = exam

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

clean:
	rm -rf *.o
	rm -f $(EXECUTABLE)
	rm -f $(EXECUTABLE).exe
