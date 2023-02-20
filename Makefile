all:
	chmod a+x myShell.c
	gcc -o myShell myShell.c
	gcc -o execx execx.c
	gcc -o writef writef.c
	
clean:
	rm myShell
	rm execx
	rm writef
