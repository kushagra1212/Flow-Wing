// Starting points in the Examples menu. Each one prints the same output as a
// native build of it.

export type Example = { title: string; source: string };

export const EXAMPLES: Example[] = [
  {
    title: "Hello",
    source: `/; Welcome to the Flow-Wing playground.
/; Edit the code, then press Run (or Ctrl+Enter).

fun greet(name: str) -> str {
  return "Hello, " + name + "!"
}

println(greet("Flow-Wing"))
`,
  },
  {
    title: "Fibonacci",
    source: `fun fib(n: int) -> int {
  if n < 2 {
    return n
  }
  return fib(n - 1) + fib(n - 2)
}

for var i: int = 0 to 15 {
  print(String(fib(i)) + " ")
}
println("")
`,
  },
  {
    title: "Classes",
    source: `class Animal {
  var name: str

  fun init(name: str) -> nthg {
    self.name = name
  }

  fun speak() -> str {
    return self.name + " makes a sound"
  }
}

class Dog extends Animal {
  fun init(name: str) -> nthg {
    super(name)
  }

  fun speak() -> str {
    return self.name + " barks"
  }
}

/; Both are Animals; speak() runs the version of the real class.
var cat: Animal = new Animal("Cat")
var rex: Animal = new Dog("Rex")
println(cat.speak())
println(rex.speak())
`,
  },
  {
    title: "Tasks (spawn)",
    source: `/; spawn runs a function as a task. sys::sleep inside a task lets the
/; other tasks run while it waits.
bring sys

fun worker(name: str, delay: int64) -> nthg {
  for var step: int = 1 to 3 {
    sys::sleep(delay)
    println(name + " finished step " + String(step))
  }
}

spawn worker("fast", 100)
spawn worker("slow", 250)
println("Both tasks started")
`,
  },
];
