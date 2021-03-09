all: logo

logo: lex.yy.c logo.tab.c MyProg.c MyProg.h
	gcc lex.yy.c logo.tab.c MyProg.c -o logo -lm
	
logo.tab.c: logo.y
	bison -d logo.y

lex.yy.c: logo.l
	flex logo.l
	
MyProg: MyProg.o
	gcc MyProg.o -o MyProg

MyProg.o: MyProg.c
	gcc -c MyProg.c -o MyProg.o

svg: logo
	./logo < test.logo

clean:
	@rm -f *.o logo.tab.c logo.tab.h lex.yy.c
	@rm -f logo test 
	@rm -f *.svg
