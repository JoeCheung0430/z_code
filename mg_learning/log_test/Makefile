OBJS=main.o zlog.o myfile.o
CC=g++
CFLAGS=-c -Wall -g

log:$(OBJS)
	$(CC) $^ -o log
%.o:%.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) *.o log