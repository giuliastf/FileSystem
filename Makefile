all : build
build :
	gcc -g -Wall arb.c dir_file.c tema3.c -o tema3
run :
	./tema3
clean :
	rm -rf tema3