CC=g++
CFLAGS=-c -Wall -O3
LIBFLAGS=-lboost_program_options

TARGET=fcryptor

SOURCES=main.cpp \
		src/shell.cpp \
		src/random_key_gen.cpp \
		src/file_ec_dc.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o src/*.o
	rm -rf $(TARGET)
