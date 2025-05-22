CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = dumsum
SRC = dumsum.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

