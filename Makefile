exe:check.o csv.o display.o func.o main.o sort.o
	gcc -o exe check.o csv.o display.o func.o main.o sort.o
check.o:check.c
	gcc -c check.c
csv.o:csv.c type.h
	gcc -c csv.c
display.o:display.c type.h
	gcc -c display.c
func.o:func.c type.h
	gcc -c func.c
main.o:main.c type.h
	gcc -c main.c
sort.o:sort.c type.h
	gcc -c sort.c
clean:
	rm -f exe check.o csv.o display.o func.o main.o sort.o