
#include "REPL/Repl.h"

int main() {

  std::unique_ptr<Repl> repl = std::make_unique<Repl>();

  repl->run();

  return 0;
}
