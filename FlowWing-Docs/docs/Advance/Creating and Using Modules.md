---
sidebar_position: 3
---
import CodeBlock from "../../src/components/common/CodeBlock";

# Creating and Using Modules

Modules in Flow-Wing are defined using the `module` keyword, followed by the `module` name enclosed in square brackets. The `module` file should be suffixed with `-module.fg` to clearly indicate that it is a module.

### Syntax for Creating a Module:

<CodeBlock code={
`module [module_name]
`} language="fg"/>

### Example

<CodeBlock code={
`module [local]

type T = {
    a:int
}

var x:int

`} language="fg"/>

### Using a Module

To use items from a module, the `bring` statement is employed. Once a module is brought in, its `types`, `classes`, `variables`, and `functions` can be accessed using the module's namespace `(module_name::item`).


### Syntax for Creating a Module:


<CodeBlock code={
`bring module_name
`} language="fg"/>

**OR**

<CodeBlock code={
`bring "module_name-module.fg"
`} language="fg"/>


### Accessing Items in the Module:

<CodeBlock code={
`var instance:module_name::Type = {}
var obj:module_name::ClassName = new module_name::ClassName()
`} language="fg"/>


### Example

- `local-module.fg`


<CodeBlock code={
`module [local]

type T = {
    a:int 
}

var x:int

class A {
    var tInstance:local::T 
    var u:int

    init() -> nthg {
        self.tInstance = {a:0}
        self.u = 0
    }

    printData() -> nthg {
        print("T instance: ", self.tInstance)
        print("U value: ", self.u)
    }
}
`} language="fg"/>


- `task.fg`


<CodeBlock code={
`bring local

var localInstance: local::T = {}
var objectInstance: local::A = new local::A()

print(objectInstance.tInstance)
print(objectInstance.u)

objectInstance.tInstance = {a:21}
print(objectInstance.tInstance)

objectInstance.printData()

`} language="fg"/>