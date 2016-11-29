#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "testBinomialHeap.h"
#include "binheap.h"
#include "vertex.h"
#include "linkedlist.h"

static void test_heap_create(void) {
    BinomialHeap *heap = newBinHeap(&vertexMinComparator);
    CU_ASSERT_PTR_EQUAL(heap -> min, NULL);
    CU_ASSERT(isEmptyList(heap -> rootList));
    CU_ASSERT_EQUAL(heap -> size, 0);
}

static void test_insert_into_heap(void) {
    BinomialHeap *heap = newBinHeap(&vertexMinComparator);
    Vertex *vertex = newKnownVertex(1, 20);
    insertBinHeap(heap, vertex);
    CU_ASSERT_EQUAL(heap -> size, 1);
    CU_ASSERT_EQUAL(heap -> rootList -> size, 1);
    CU_ASSERT_PTR_NOT_EQUAL(heap -> min, NULL);
    vertex = newKnownVertex(2, 10);
    insertBinHeap(heap, vertex);
    CU_ASSERT_EQUAL(heap -> size, 2);
    CU_ASSERT_EQUAL(heap -> rootList -> size, 1);
    vertex = newKnownVertex(3, 5);
    insertBinHeap(heap, vertex);
    CU_ASSERT_EQUAL(heap -> size, 3);
    CU_ASSERT_EQUAL(heap -> rootList -> size, 2);
    CU_ASSERT_PTR_EQUAL((Vertex *) heap -> min -> vertex, vertex);
}

static void test_decrease_key(void) {
    BinomialHeap *heap = newBinHeap(&vertexMinComparator);
    insertBinHeap(heap, newKnownVertex(1, 20));
    insertBinHeap(heap, newKnownVertex(2, 15));
    insertBinHeap(heap, newKnownVertex(3, 27));
    Node * node = insertBinHeap(heap, newKnownVertex(4, 31));
    insertBinHeap(heap, newKnownVertex(5, 7));
    insertBinHeap(heap, newKnownVertex(6, 22));
    insertBinHeap(heap, newKnownVertex(7, 13));
    Vertex *tempMin = (Vertex *) heap -> min -> vertex;
    CU_ASSERT_EQUAL(tempMin -> id, 5);
    decreaseKeyBinHeap(heap, node, newKnownVertex(4, 3));
    tempMin = (Vertex *) heap -> min -> vertex;
    CU_ASSERT_EQUAL(tempMin -> id, 4);
}

static void test_extract_min(void) {
    BinomialHeap *heap = newBinHeap(&vertexMinComparator);
    insertBinHeap(heap, newKnownVertex(1, 20));
    insertBinHeap(heap, newKnownVertex(2, 15));
    insertBinHeap(heap, newKnownVertex(3, 27));
    insertBinHeap(heap, newKnownVertex(4, 31));
    insertBinHeap(heap, newKnownVertex(5, 7));
    insertBinHeap(heap, newKnownVertex(6, 22));
    insertBinHeap(heap, newKnownVertex(7, 13));
    Vertex *min = (Vertex *) extractBinHeap(heap);
    CU_ASSERT_EQUAL(min -> id, 5);
    int heapMinVertexId = ((Vertex *) heap -> min -> vertex ) -> id;
    CU_ASSERT_EQUAL(heapMinVertexId, 7);
    CU_ASSERT_EQUAL(heap -> size, 6);
    min = (Vertex *) extractBinHeap(heap);
    CU_ASSERT_EQUAL(min -> id, 7);
    CU_ASSERT_EQUAL(heap -> size, 5);
    min = (Vertex *) extractBinHeap(heap);
    CU_ASSERT_EQUAL(min -> id, 2);
    CU_ASSERT_EQUAL(heap -> size, 4);
}

static void test_delete_from_heap(void) {
    BinomialHeap *heap = newBinHeap(&vertexMinComparator);
    Vertex *vertex = newKnownVertex(1, 20);
    insertBinHeap(heap, vertex);
    deleteFromHeap(heap, vertex -> owner);
    CU_ASSERT_EQUAL(heap -> min, NULL);
    CU_ASSERT_EQUAL(heap -> size, 0);

    vertex = newKnownVertex(1, 20);
    insertBinHeap(heap, vertex);
    vertex = newKnownVertex(2, 15);
    insertBinHeap(heap, vertex);
    deleteFromHeap(heap, vertex -> owner);
    CU_ASSERT_EQUAL(heap -> size, 1);
    CU_ASSERT_PTR_NOT_EQUAL(heap -> rootList -> head, NULL);
    
    vertex = newKnownVertex(3, 27);
    insertBinHeap(heap, vertex);
    insertBinHeap(heap, newKnownVertex(4, 31));
    insertBinHeap(heap, newKnownVertex(5, 7));
    insertBinHeap(heap, newKnownVertex(6, 22));
    insertBinHeap(heap, newKnownVertex(7, 13));
    Node *minNode = heap -> min;
    deleteFromHeap(heap, minNode);
    CU_ASSERT_PTR_NOT_EQUAL(heap -> min, minNode);
    CU_ASSERT_EQUAL(heap -> size, 5);
    deleteFromHeap(heap, vertex -> owner);
    CU_ASSERT_EQUAL(heap -> size, 4);
}

static void test_combine_binomial_heaps(void) {
    BinomialHeap *left = newBinHeap(&vertexMinComparator);
    BinomialHeap *right = newBinHeap(&vertexMinComparator);
    insertBinHeap(left, newKnownVertex(1, 20));
    insertBinHeap(left, newKnownVertex(2, 15));
    insertBinHeap(left, newKnownVertex(3, 27));
    insertBinHeap(right, newKnownVertex(4, 31));
    insertBinHeap(right, newKnownVertex(5, 7));
    insertBinHeap(right, newKnownVertex(6, 22));
    insertBinHeap(right, newKnownVertex(7, 13));
    CU_ASSERT_EQUAL(left -> size, 3);
    int minId = ((Vertex *) left -> min -> vertex) -> id;
    CU_ASSERT_EQUAL(minId, 2);
    CU_ASSERT_EQUAL(right -> size, 4);
    minId = ((Vertex *) right -> min -> vertex) -> id;
    CU_ASSERT_EQUAL(minId, 5);

    combineBinomialHeaps(left, right);
    CU_ASSERT_EQUAL(left -> size, 7);
    CU_ASSERT_EQUAL(left -> rootList -> size, 3);
    minId = ((Vertex *) left -> min -> vertex) -> id;
    CU_ASSERT_EQUAL(minId, 5);
}

int fill_binomial_heap_suite(CU_pSuite suite) {
    if ((NULL == CU_add_test(suite, "test_heap_create", test_heap_create)) ||
            (NULL == CU_add_test(suite, "test_insert_into_heap", test_insert_into_heap)) ||
            (NULL == CU_add_test(suite, "test_decrease_key", test_decrease_key)) ||
            (NULL == CU_add_test(suite, "test_extract_min", test_extract_min)) ||
            (NULL == CU_add_test(suite, "test_delete_from_heap", test_delete_from_heap)) ||
            (NULL == CU_add_test(suite, "test_combine_binomial_heaps", test_combine_binomial_heaps))) {
        CU_cleanup_registry();
        return -1;
    }
    return 0;
}
