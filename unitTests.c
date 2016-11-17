#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "testLinkedList.h"
#include "testBinomialHeap.h"
#include "testVertex.h"
#include "testGraph.h"


int main (void) {
    CU_pSuite linked_list_suite = NULL;
    CU_pSuite binomial_heap_suite = NULL;
    CU_pSuite vertex_suite = NULL;
    CU_pSuite graph_suite = NULL;

   if (CUE_SUCCESS != CU_initialize_registry())
       return CU_get_error();

   linked_list_suite = CU_add_suite("list_test_suite", NULL, NULL);
   binomial_heap_suite = CU_add_suite("binomial_heap_suite", NULL, NULL);
   vertex_suite = CU_add_suite("vertex_suite", NULL, NULL);
   graph_suite = CU_add_suite("graph_suite", NULL, NULL);
   if (NULL == linked_list_suite || NULL == binomial_heap_suite || NULL == vertex_suite) {
       CU_cleanup_registry();
       return CU_get_error();
   }

   if ((-1 == fillLinkedListSuite(linked_list_suite)) ||
           (-1 == fill_binomial_heap_suite(binomial_heap_suite)) ||
           (-1 == fill_vertex_suite(vertex_suite)) ||
           (-1 == fill_graph_suite(graph_suite)))
       return CU_get_error();

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");

   CU_cleanup_registry();
   return CU_get_error();
}
