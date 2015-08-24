all: rahhid

rahhid: rahhid.o
	$(CC) -Wall -Werror -Wextra -Os -o rahhid rahhid.o -lm `pkg-config --libs hidapi-libusb`

rahhid.o: rahhid.c
	$(CC) -Wall -Werror -Wextra `pkg-config --cflags hidapi-libusb` -Os -o rahhid.o -c rahhid.c

clean:
	$(RM) -f rahhid rahhid.o
