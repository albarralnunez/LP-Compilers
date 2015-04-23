all:
	antlr -gt example1.g
	dlg -ci parser.dlg scan.c
	g++ -o example1 example1.c scan.c err.c
	
clean:
	rm -f *.o example1.c scan.c err.c parser.dlg tokens.h mode.h