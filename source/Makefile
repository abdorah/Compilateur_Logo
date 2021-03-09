run: build

build: lex.yy.c parser.tab.c semantic.c semantic.h
	gcc lex.yy.c parser.tab.c semantic.c -o logo -lm
	
parser.tab.c: parser.y
	bison -d parser.y

lex.yy.c: scanner.l
	flex scanner.l
	
semantic: semantic.o
	gcc semantic.o -o semantic

semantic.o: semantic.c
	gcc -c semantic.c -o semantic.o

draw: build
	./logo < test/test.logo

clean:
	@rm -f *.o parser.tab.c parser.tab.h lex.yy.c
	@rm -f logo 
	@rm -f *.svg
