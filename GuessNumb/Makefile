all: program executable

program:
	gcc -o guessnumb -I ./include ./src/game.c ./src/main.c

executable:
	chmod u+x ./guessnumb

clean:
	rm -f ./guessnumb
