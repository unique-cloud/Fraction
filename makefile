src = $(wildcard *.cc)
obj = $(src:.cc=.o)

CC = g++
LDFLAGS =

main: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(obj) main