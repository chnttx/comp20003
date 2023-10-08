all: dict2 dict3

dict2: dict2.c data.c array.c
	gcc -Wall -g -o dict2 dict2.c data.c array.c

dict3: dict3.c data.c array.c tree.c 
	gcc -Wall -g -o dict3 dict3.c data.c array.c tree.c

clean:
	rm -f dict2 dict3