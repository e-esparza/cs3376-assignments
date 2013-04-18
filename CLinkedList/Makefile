all: clean program executable

program:
	gcc -o linkedlist -I ./include ./src/main.c ./src/linkedlist.c

executable:
	chmod u+x ./linkedlist

clean:
	rm -f ./linkedlist
