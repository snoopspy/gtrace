SOURCES = gtrace.c exam.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = exam
#LDFLAGS += -lws2_32 // for win32
 
all: $(SOURCES) $(EXECUTABLE)
 
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)
 
clean:
	rm -rf *.o
	rm -rf $(EXECUTABLE)
