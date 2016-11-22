#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "testGraph.h"
#include "graph.h"
#include "edge.h"

static void test_new_graph(void)
{
    Graph *graph = newGraph(10);
    CU_ASSERT_EQUAL(graph -> maxIndex, 10);
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

static void test_set_graph_vertex(void) {
    Graph *graph = newGraph(10);
    Vertex *vertex = newKnownVertex(1, 20);
    setGraphVertex(graph, vertex);
    CU_ASSERT_PTR_EQUAL(graph -> vertices[1], vertex);
    CU_ASSERT_EQUAL(graph -> vertices[1] -> key, 20);
    vertex = newKnownVertex(1, 10);
    setGraphVertex(graph, vertex);
    CU_ASSERT_EQUAL(graph -> vertices[1] -> key, 20);
}

static void test_prim_min_span_tree(void) {
    Graph *graph = newGraph(6);
    setGraphUndirEdge(graph, newEdge(1, 2, 4));
    setGraphUndirEdge(graph, newEdge(1, 4, 7));
    setGraphUndirEdge(graph, newEdge(1, 5, 21));
    setGraphUndirEdge(graph, newEdge(2, 5, 1));
    setGraphUndirEdge(graph, newEdge(2, 6, 18));
    setGraphUndirEdge(graph, newEdge(3, 5, 5));
    setGraphUndirEdge(graph, newEdge(3, 6, 10));
    setGraphUndirEdge(graph, newEdge(4, 6, 9));

    int edges[7][7] = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 4, 0, 7, 0, 0},
        {0, 4, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 5, 0},
        {0, 7, 0, 0, 0, 0, 9},
        {0, 0, 1, 5, 0, 0, 0},
        {0, 0, 0, 0, 9, 0, 0}
    };

    Graph *minTree = primMinSpanTree(graph);
    for (int sourceId = 0; sourceId <= 6; sourceId++)
        for (int sinkId = 0; sinkId <= 6; sinkId++)
            CU_ASSERT_EQUAL(minTree -> edges[sourceId][sinkId],
                    edges[sourceId][sinkId]);

}

static void test_prim_min_span_tree_disconnected(void) {
    Graph *graph = newGraph(6);
    setGraphUndirEdge(graph, newEdge(1, 2, 2));
    setGraphUndirEdge(graph, newEdge(1, 4, 3));
    setGraphUndirEdge(graph, newEdge(1, 5, 6));
    setGraphUndirEdge(graph, newEdge(2, 4, 9));
    setGraphUndirEdge(graph, newEdge(3, 6, 7));
    setGraphUndirEdge(graph, newEdge(4, 5, 8));

    int edges[7][7] = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 3, 6, 0},
        {0, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 7},
        {0, 3, 0, 0, 0, 0, 0},
        {0, 6, 0, 0, 0, 0, 0},
        {0, 0, 0, 7, 0, 0, 0},
    };

    Graph *minTree = primMinSpanTree(graph);
    for (int sourceId = 0; sourceId <= 3; sourceId++)
        for (int sinkId = 0; sinkId <= 6; sinkId++)
            CU_ASSERT_EQUAL(minTree -> edges[sourceId][sinkId],
                    edges[sourceId][sinkId]);
}

int fill_graph_suite(CU_pSuite suite)
{
    if ((NULL == CU_add_test(suite, "test_new_graph", test_new_graph)) ||
            (NULL == CU_add_test(suite, "test_set_graph_undir_edge", test_set_graph_undir_edge)) ||
            (NULL == CU_add_test(suite, "test_set_graph_vertex", test_set_graph_vertex)) ||
            (NULL == CU_add_test(suite, "test_prim_min_span_tree", test_prim_min_span_tree)) ||
            (NULL == CU_add_test(suite, "test_prim_min_span_tree_disconnected", test_prim_min_span_tree_disconnected))) {
        CU_cleanup_registry();
        return -1;
    }
    return 0;
}
