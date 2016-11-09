OBJS = prim.o linkedlist.o node.o vertex.o binomialheap.o
OPTS = -std=c99 -g -Wall

prim : $(OBJS)
	gcc $(OPTS) $(OBJS) -o prim
linkedlist.o : linkedlist.c linkedlist.h node.h
	gcc $(OPTS) -c linkedlist.c
node.o : node.c node.h linkedlist.h vertex.h
	gcc $(OPTS) -c node.c
vertex.o : vertex.c vertex.h node.h
	gcc $(OPTS) -c vertex.c
binomialheap.o: binomialheap.c binomialheap.h vertex.h node.h linkedlist.h
	gcc $(OPTS) -c binomialheap.c
clean :
	rm -rf $(OBJS) prim
