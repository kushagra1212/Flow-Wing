#include "fw_gc.h"
#include "test_harness.h"

/* A dummy descriptor; contents don't matter for packing. */
static const FWTypeDescriptor g_dummy = { .name = "dummy", .kind = FW_KIND_BLOB };

static void test_word_packing(void) {
  uintptr_t w = fw_word_pack(&g_dummy);
  CHECK(fw_word_desc(w) == &g_dummy);   /* descriptor recovered */
  CHECK(fw_word_marked(w) == 0);        /* starts unmarked */

  w = fw_word_set_mark(w);
  CHECK(fw_word_marked(w) == 1);
  CHECK(fw_word_desc(w) == &g_dummy);   /* mark did not corrupt descriptor */

  w = fw_word_clear_mark(w);
  CHECK(fw_word_marked(w) == 0);
  CHECK(fw_word_desc(w) == &g_dummy);
}

int main(void) {
  RUN_TEST(test_word_packing);
  return TEST_SUMMARY();
}
