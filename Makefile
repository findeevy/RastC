CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = src/main.c src/framebuffer.c src/tools.c
OBJS = $(SRCS:.c=.o)

TARGET = RastC

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
