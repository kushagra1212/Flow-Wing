---
sidebar_position: 2
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Switch Statment

Flow-Wing supports the `switch` keyword to handle multiple cases.

### Example Usage:

<CodeBlock code={
`var a:int = 5
switch true {
    case a > 0 && a < 10:{
        print("a is between 0 and 10")
    }
    case a > 10 && a < 20:{
        print("a is between 10 and 20")
    }
    default: { 
        print("default")
    }
}`} language="fg"/>


**Output:**

<CodeBlock code={
`a is between 0 and 10`}/>

Here, the `switch` keyword is used to handle multiple cases.

### Example Usage:

<CodeBlock code={
`var a:int = 5

switch a {
    case 0:{
        print("a is 0")
    } case 1:{
        print("a is 1")
    } case 2:{
        print("a is 2")
    } case 3:{
        print("a is 3")
    } case "Hello":{
        print("a is Hello")
    } default:{
        print("default")
    }
}
`} language="fg"/>



**Output:**

<CodeBlock code={
`default`}/>

Here, the `switch` keyword is used to handle multiple cases.
