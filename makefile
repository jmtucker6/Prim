OBJS = prim.o linkedlist.o node.o vertex.o binomialheap.o scanner.o edge.o
OPTS = -std=c99 -g -Wall
TEST_OBJS = unitTests.o testLinkedList.o testBinomialHeap.o linkedlist.o node.o vertex.o binomialheap.o

prim : $(OBJS)
	gcc $(OPTS) $(OBJS) -o prim -lm
linkedlist.o : linkedlist.c linkedlist.h node.h
	gcc $(OPTS) -c linkedlist.c
node.o : node.c node.h linkedlist.h vertex.h
	gcc $(OPTS) -c node.c
vertex.o : vertex.c vertex.h node.h
	gcc $(OPTS) -c vertex.c
binomialheap.o: binomialheap.c binomialheap.h vertex.h node.h linkedlist.h
	gcc $(OPTS) -c binomialheap.c -lm
edge.o : edge.h edge.c
	gcc $(OPTS) -c edge.c
scanner.o : scanner.h scanner.c
	gcc $(OPTS) -c scanner.c
testLinkedList.o : testLinkedList.c vertex.h node.h linkedlist.h
	gcc $(OPTS) -c testLinkedList.c
testBinomialHeap.o : testBinomialHeap.c testBinomialHeap.h binomialheap.h vertex.h
	gcc $(OPTS) -c testBinomialHeap.c
unitTests.o : unitTests.c testLinkedList.h
	gcc $(OPTS) -c unitTests.c
unitTests: $(TEST_OBJS)
	gcc $(OPTS) $(TEST_OBJS) -o unitTests -lcunit -lm
	./unitTests
clean :
	rm -rf $(OBJS) prim
