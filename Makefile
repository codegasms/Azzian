CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lraylib

SRCS = main.c screen_game.c
OBJS = $(SRCS:.c=.o)
EXEC = Azzian

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
