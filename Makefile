all: rahhid

rahhid: rahhid.o
	$(CC) -Wall -Werror -Wextra -Os -o rahhid rahhid.o -lm -lhidapi-hidraw

rahhid.o: rahhid.c
	$(CC) -Wall -Werror -Wextra -Os -o rahhid.o -c rahhid.c

clean:
	$(RM) -f rahhid rahhid.o
