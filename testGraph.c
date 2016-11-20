#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "testGraph.h"
#include "graph.h"
#include "edge.h"

static void test_new_graph(void)
{
    Graph *graph = newGraph(10);
    CU_ASSERT_PTR_NOT_EQUAL(graph -> vertices, NULL);
    CU_ASSERT_PTR_EQUAL(graph -> vertices[10], NULL);
    CU_ASSERT_PTR_NOT_EQUAL(graph -> edges, NULL);
    CU_ASSERT_EQUAL(graph -> edges[1][2], 0);
}

static void test_set_graph_undir_edge(void) {
    Graph *graph = newGraph(10);
    Edge *edge = newEdge(1, 4, 10);
    setGraphUndirEdge(graph, edge);
    CU_ASSERT_PTR_NOT_EQUAL(graph -> vertices[4], NULL);
    CU_ASSERT_EQUAL(graph -> edges[1][4], 10);
    CU_ASSERT_EQUAL(graph -> edges[4][1], 10);
    edge = newEdge(1, 4, 7);
    setGraphUndirEdge(graph, edge);
    CU_ASSERT_EQUAL(graph -> edges[1][4], 10);
}

int fill_graph_suite(CU_pSuite suite)
{
    if ((NULL == CU_add_test(suite, "test_new_graph", test_new_graph)) ||
            (NULL == CU_add_test(suite, "test_set_graph_undir_edge", test_set_graph_undir_edge))) {
        CU_cleanup_registry();
        return -1;
    }
    return 0;
}
