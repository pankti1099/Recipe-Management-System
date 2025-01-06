
Pt2.2: Pt2.2Main.o Pt2.2Functions.o
	gcc -o Pt2.2 Pt2.2Main.o Pt2.2Functions.o

# To obtain object files
Pt2.2Main.o: Pt2.2Main.c Pt2.h
	gcc -c Pt2.2Main.c

Pt2.2Functions.o: Pt2.2Functions.c Pt2.h
	gcc -c Pt2.2Functions.c

# To remove generated files
clean:
	rm -f Pt2.2 Pt2.2Main.o Pt2.2Functions.o
