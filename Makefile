COPT = -Wall -Wextra -O3 -lwiringPi -pthread
LOPT = -lm -pthread -lwiringPi

all: main.o thread.o max7219.o bh1750.o bmp280.o signal.o
	gcc main.o thread.o max7219.o bh1750.o bmp280.o signal.o $(LOPT) -o main

main.o: main.c project.h
	gcc -c $(COPT) main.c

thread.o: thread.c project.h
	gcc -c $(COPT) thread.c

max7219.o: max7219.c project.h
	gcc -c $(COPT) max7219.c

bh1750.o: bh1750.c project.h
	gcc -c $(COPT) bh1750.c

bmp280.o: bmp280.c project.h
	gcc -c $(COPT) bmp280.c

singal.o: signal.c project.h
	gcc -c $(COPT) signal.c

clean:
	rm -f *.o main