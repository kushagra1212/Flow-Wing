---
sidebar_position: 2
---
import CodeBlock from "../../src/components/common/CodeBlock";

# Bring (Import Exports)

### Bring Statement in Flow-Wing

The `bring` statement in Flow-Wing is used to import external files or modules into the current file. It allows the code to access functions, types, classes, and variables defined in other files. This feature enhances modularity and code reuse, allowing developers to organize their code into multiple files, keeping concerns separated.

The `bring` keyword functions similarly to an "import" statement found in other programming languages like Python or JavaScript. By using bring, you can include definitions from other `Flow-Wing` files without needing to rewrite the same code multiple times.

### Syntax

<CodeBlock code={
`bring "path_to_file.fg"`
} language="fg"/>

- `path_to_file`: This is the relative path to the file you want to import, enclosed in double quotes.

<CodeBlock code={
`bring "utils.fg" /; Imports definitions from utils.fg

print(someVariableFromUtils)
`
} language="fg"/>

In the example, the bring statement includes all the public symbols from the `utils.fg` file, allowing access to any types, variables, or functions declared there.


### Examples

- `dependencies.fg`

<CodeBlock code={
`var globalCount:int = 2

type StringWrapper = {
    value:str 
}

type ComplexType = {
    id:int,
    data:StringWrapper[2]
}

var defaultComplexType:ComplexType = {}

var complexTypeArray:ComplexType[2] 

class Printer {
    var count:int 
    var complexData:ComplexType  
  
    init(complexData:ComplexType) -> nthg {
        self.complexData = complexData 
    }

    displayComplexData() -> nthg {
        print(self.complexData)
    }
}

fun handleData(input:int) -> nthg {
    var printerInstance:Printer = new Printer({data:[{value:"Hello"}]})
    print("Printer Instance Data: ", printerInstance.complexData)

    print("Global Default Complex Type: ", defaultComplexType)

    print("Input Value: ", input)
}

`} language="fg"/>


- `bring_example.fg`

<CodeBlock code={
`bring "dependencies.fg"

print(globalCount)

print(defaultComplexType)

print(complexTypeArray)

handleData(88)

var customComplexType:ComplexType  

customComplexType = {id:2}
print("Custom Complex Type: ", customComplexType)

`} language="fg"/>