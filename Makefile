#CC=
#LD=
#LIB=
#LIBDIR=-L/
#INCDIR=-I/
#CFLGAS=-Wall -O2 -fPIC
#LDFLGAS=-shared
TARGET=dept
SRCS=*.c
OBJS=$(SRCS:.c=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $^

.c.o:
	$(CC) $(CFLAGS) -c $< $(INCDIR) $(LIBDIR) $(LIB)

.PHONY: clean
clean:
	$(RM) $(TERGET) $(OBJS)

subsystem:
	$(MAKE) -C subdir
