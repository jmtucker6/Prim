#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "testBinomialHeap.h"
#include "binomialheap.h"
#include "vertex.h"

static void test_heap_create(void) {
    BinomialHeap *heap = newBinomialHeap(&vertexMinComparator);
    CU_ASSERT_PTR_EQUAL(heap -> min, NULL);
    CU_ASSERT(isEmptyList(heap -> rootList));
    CU_ASSERT_EQUAL(heap -> size, 0);
}

static void test_insert_into_heap(void) {
    BinomialHeap *heap = newBinomialHeap(&vertexMinComparator);
    Vertex *vertex = newKnownVertex(1, 20);
    insertIntoHeap(heap, vertex);
    CU_ASSERT_EQUAL(heap -> size, 1);
    CU_ASSERT_EQUAL(heap -> rootList -> size, 1);
    CU_ASSERT_PTR_NOT_EQUAL(heap -> min, NULL);
    vertex = newKnownVertex(2, 10);
    insertIntoHeap(heap, vertex);
    CU_ASSERT_EQUAL(heap -> size, 2);
    CU_ASSERT_EQUAL(heap -> rootList -> size, 1);
}

int fill_binomial_heap_suite(CU_pSuite suite) {
    if ((NULL == CU_add_test(suite, "test_heap_create", test_heap_create)) ||
            (NULL == CU_add_test(suite, "test_insert_into_heap", test_insert_into_heap))) {
        CU_cleanup_registry();
        return -1;
    }
    return 0;
}
