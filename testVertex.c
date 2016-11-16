#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "vertex.h"

static void test_new_vertex(void) {
    Vertex *vertex = newVertex();
    CU_ASSERT(vertex != NULL);
    CU_ASSERT_EQUAL(vertex -> id, 0);
    CU_ASSERT_EQUAL(vertex -> key, 0);
}

static void test_new_known_vertex(void) {
    Vertex *vertex = newKnownVertex(1, 20);
    CU_ASSERT(vertex != NULL);
    CU_ASSERT_EQUAL(vertex -> id, 1);
    CU_ASSERT_EQUAL(vertex -> key, 20);
}

static void test_vertex_min_comparator(void) {
    CU_ASSERT_EQUAL(vertexMinComparator(NULL, NULL), 0);
    CU_ASSERT_EQUAL(vertexMinComparator(NULL, newKnownVertex(0, 0)), -1);
    CU_ASSERT_EQUAL(vertexMinComparator(newKnownVertex(0, 0), NULL), 1);
    CU_ASSERT_EQUAL(vertexMinComparator(newKnownVertex(1, 20), newKnownVertex(2, 9)), 1);
    CU_ASSERT_EQUAL(vertexMinComparator(newKnownVertex(1, 9), newKnownVertex(2, 20)), -1);
    CU_ASSERT_EQUAL(vertexMinComparator(newKnownVertex(1, 9), newKnownVertex(2, 9)), -1);
    CU_ASSERT_EQUAL(vertexMinComparator(newKnownVertex(2, 9), newKnownVertex(1, 9)), 1);
    CU_ASSERT_EQUAL(vertexMinComparator(newKnownVertex(1, 20), newKnownVertex(1, 20)), 0);
}


int fill_vertex_suite(CU_pSuite suite) {
    if((NULL == CU_add_test(suite, "test_new_vertex", test_new_vertex)) ||
            (NULL == CU_add_test(suite, "test_new_known_vertex", test_new_known_vertex)) ||
            (NULL == CU_add_test(suite, "test_vertex_min_comparator", test_vertex_min_comparator))) {
        CU_cleanup_registry();
        return -1;
    }
    return 0;
}
