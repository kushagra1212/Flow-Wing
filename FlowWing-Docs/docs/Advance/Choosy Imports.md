---
sidebar_position: 2
---
import CodeBlock from "../../src/components/common/CodeBlock";

# Choosy Imports


In Flow-Wing, the `bring` statement can selectively import specific exposed items from a file or module. This mechanism is known as choosy imports, where only the necessary components are imported from an external file. This helps in avoiding namespace pollution and enhances code readability and maintainability by importing only what is required.


### Syntax

<CodeBlock code={
`bring {item1, item2, ..., itemN} from "path_to_file"
`} language="fg"/>

-`item1`, `item2`, ..., `itemN`: These are the specific variables, types, classes, or functions that are exposed in the source file and imported into the current file.
+`globalCount, handleData`: These are the specific variables, types, classes, or functions that are exposed in the source file and imported into the current file.
-`path_to_file`: This is the relative path to the file containing the exposed definitions.


### Examples

<CodeBlock code={
`bring {globalCount, handleData} from "dependencies.fg"

print(globalCount) /; Using imported variable
handleData(99)     /; Using imported function

`} language="fg"/>


In the above example, only globalCount and handleData are imported from `dependencies.fg`, meaning that other exposed items from `dependencies.fg` (e.g., Printer, defaultComplexType) are not accessible in the current file.


### Example 2

- `dependencies.fg`

We use `expose` keyword to make the exposed items available to other files.

<CodeBlock code={
`expose var globalCount:int = 2

expose type StringWrapper = {
    value:str 
}

expose type ComplexType = {
    id:int,
    data:StringWrapper[2]
}

expose var defaultComplexType:ComplexType = {}

expose var complexTypeArray:ComplexType[2] 

expose class Printer {
    var count:int 
    var complexData:ComplexType  
  
    init(complexData:ComplexType) -> nthg {
        self.complexData = complexData 
    }

    printData() -> nthg {
        print(self.complexData)
    }
}

expose fun handleData(input:int) -> nthg {
    var printerInstance:Printer = new Printer({data:[{value:"Hello"}]})
    print("Printer Instance Data: ", printerInstance.complexData)

    print("Global Default Complex Type: ", defaultComplexType)

    print("Input Value: ", input)
}

`} language="fg"/>

- `choose_example.fg`

<CodeBlock code={
`bring {globalCount, defaultComplexType, complexTypeArray, handleData, Printer} from "file1.fg"

print(globalCount)

print(defaultComplexType)

print(complexTypeArray)

handleData(88)

var customComplexType:ComplexType  

customComplexType = {id:2}
print("Custom Complex Type: ", customComplexType)

var printerInstance:Printer = new Printer({})
printerInstance.printData()

`} language="fg"/>