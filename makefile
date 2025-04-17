all:
	gcc -Iinclude -r src/io.c src/track_utils.c src/adv_utils.c -o wavekit.o

clean:
	rm -f wavekit.o
