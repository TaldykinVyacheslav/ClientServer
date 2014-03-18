CC := $(CROSS_COMPILE)gcc
LIBS := -lpthread

all:
	mkdir -p clientFiles
	mkdir -p serverFiles
	$(CC) -o client client.c $(LIBS)
	$(CC) -o server server.c $(LIBS)
	mv client clientFiles
	mv server serverFiles
	cp -p ServerDoc.in serverFiles
clean:
	rm -r ./clientFiles
	rm -r ./serverFiles
