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
	
tar:
	tar -cvf TPLogo.tar Makefile MyProg.c MyProg.h exemple1Logo logo.l logo.y 
	
svg: logo
	./logo < test.logo
	inkscape dessin.svg

test: Test.c MyProg.o
	gcc Test.c MyProg.h MyProg.o -o test -lm
	./test

clean:
	@rm -f *.o logo.tab.c logo.tab.h lex.yy.c
	@rm -f logo test 
	@rm -f *.svg
