---
sidebar_position: 2
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Switch Statement

Flow-Wing supports the `switch` keyword to handle multiple cases.

### Example (value match; first matching case wins)

Pattern from the test suite (`SwitchTests` fixtures): the **switched expression** is evaluated once; each **`case`** is compared in order.

<CodeBlock code={
`var a: int = 1
switch a {
  case 1: {
    println("first")
  }
  case 1: {
    println("second")
  }
  default: {
    println("default")
  }
}
`} language="fg"/>

:::warning
Duplicate `case` values are not errors, but only the first matching case executes. The second `case 1:` above is dead code.
:::

**Output:** `first` (the second `case 1` never runs).


<CodeBlock code={
`var a: int = 5
switch true {
    case a > 0 && a < 10: {
        print("a is between 0 and 10")
    }
    case a > 10 && a < 20: {
        print("a is between 10 and 20")
    }
    default: {
        print("default")
    }
}`} language="fg"/>


**Output:**

<CodeBlock code={
`a is between 0 and 10`}/>

This pattern replaces long `if`/`else if` chains when each case tests a different expression. It reads cleaner than nested ternaries.

### Break in Switch

Unlike some languages, Flow-Wing switch cases **do not fall through**. Each case block is self-contained — no `break` needed between cases:

<CodeBlock code={
`switch x {
    case 1: {
        print("one")
    }
    case 2: {
        print("two")
    }
}
`} language="fg"/>

Both cases are independent. The `break` keyword exits the entire switch early, useful inside nested loops:

<CodeBlock code={
`while (true) {
    switch getInput() {
        case "quit": {
            break  // exits the switch, not the while
        }
    }
}
`} language="fg"/>

### Example (discriminant `switch a` with `default`)

<CodeBlock code={
`var a: int = 5
switch a {
    case 0: {
        print("a is 0")
    }
    case 1: {
        print("a is 1")
    }
    case 2: {
        print("a is 2")
    }
    case 3: {
        print("a is 3")
    }
    case 4: {
        print("a is 4")
    }
    default: {
        print("default")
    }
}
`} language="fg"/>



**Output:**

<CodeBlock code={
`default`}/>

Here, the `switch` keyword is used to handle multiple cases.
