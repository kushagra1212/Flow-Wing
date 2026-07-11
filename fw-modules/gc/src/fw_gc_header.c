#include "fw_gc.h"
#include "fw_gc_internal.h"

uintptr_t fw_word_pack(const FWTypeDescriptor *desc) {
  return (uintptr_t)desc;              /* aligned: low 3 bits already 0 */
}
const FWTypeDescriptor *fw_word_desc(uintptr_t word) {
  return (const FWTypeDescriptor *)(word & ~FW_FLAG_MASK);
}
int fw_word_marked(uintptr_t word) {
  return (word & FW_MARK_BIT) != 0;
}
uintptr_t fw_word_set_mark(uintptr_t word) {
  return word | FW_MARK_BIT;
}
uintptr_t fw_word_clear_mark(uintptr_t word) {
  return word & ~FW_MARK_BIT;
}
