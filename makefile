OBJS = prim.o linkedlist.o node.o vertex.o binomialheap.o scanner.o edge.o graph.o queue.o
OPTS = -std=c99 -g -Wall
TEST_OBJS = unitTests.o testGraph.o testVertex.o testLinkedList.o testBinomialHeap.o linkedlist.o node.o vertex.o binomialheap.o graph.o edge.o queue.o

prim : $(OBJS)
	gcc $(OPTS) $(OBJS) -o prim -lm
prim.o : prim.c scanner.h vertex.h node.h linkedlist.h binomialheap.h graph.h edge.h
	gcc $(OPTS) -c prim.c
queue.o : queue.h queue.c node.h vertex.h
	gcc $(OPTS) -c queue.c
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
graph.o : graph.h graph.c vertex.h
	gcc $(OPTS) -c graph.c
scanner.o : scanner.h scanner.c
	gcc $(OPTS) -c scanner.c
testGraph.o : testGraph.h testGraph.c graph.h edge.h
	gcc $(OPTS) -c testGraph.c
testVertex.o : testVertex.c testVertex.h vertex.h
	gcc $(OPTS) -c testVertex.c
testLinkedList.o : testLinkedList.c testLinkedList.h vertex.h node.h linkedlist.h
	gcc $(OPTS) -c testLinkedList.c
testBinomialHeap.o : testBinomialHeap.c testBinomialHeap.h binomialheap.h vertex.h
	gcc $(OPTS) -c testBinomialHeap.c
unitTests.o : unitTests.c testLinkedList.h testBinomialHeap.h testVertex.h
	gcc $(OPTS) -c unitTests.c
unitTests: $(TEST_OBJS)
	gcc $(OPTS) $(TEST_OBJS) -o unitTests -lcunit -lm
test : unitTests
	./unitTests
clean :
	rm -rf $(OBJS) prim unitTests
