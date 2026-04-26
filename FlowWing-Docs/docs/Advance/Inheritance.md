---
sidebar_position: 2
---
import CodeBlock from "../../src/components/common/CodeBlock";

# Inheritance

Flow-Wing supports Single Inheritance.

### Classes

Flow-Wing supports object-oriented programming with class definitions. Classes can contain properties and methods. Here's an example:

### Example:

<CodeBlock code={
`class Vehicle {
    var make:str
    var model:str
    var year:int

    init(make:str, model:str, year:int) -> nthg {
        self.make = make
        self.model = model
        self.year = year
    }

    getDetails() -> str {
        return self.year + " " + self.make + " " + self.model
    }

    printDetails() -> nthg {
        print("Vehicle: ", self.getDetails())
    }
}
`} language="fg"/>

### Inheritance

Classes can inherit from other classes using the `extends` keyword. Here's an example of a Car class that inherits from Vehicle:

### Example:

<CodeBlock code={
`class Car extends Vehicle {
    var doors: int
    init(make: str, model: str, year: int, doors: int) -> nthg {
        super(make, model, year)
        self.doors = doors
    }

    getDetails() -> str {
        return self.year + " " + self.make + " " + self.model + " with " + self.doors + " doors"
    }

    printDetails() -> nthg {
        print("Car: ", self.getDetails())
    } 

}
`} language="fg"/>

### Using Classes and Functions
Here’s how you can use these classes and functions in a main function:


<CodeBlock code={
`fun printVehicleDetails(v: Vehicle) -> nthg {
    v.printDetails()
}

fun main() -> nthg {
    var vehicle:Vehicle = new Vehicle("Toyota", "Camry", 2020)
    var car:Car = new Car("Honda", "Civic", 2022, 4)

    printVehicleDetails(vehicle)
    printVehicleDetails(car)
}

main()
`} language="fg"/>