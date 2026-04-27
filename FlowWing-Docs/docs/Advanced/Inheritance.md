---
sidebar_position: 2
---
import CodeBlock from "../../src/components/common/CodeBlock";

# Inheritance

## Start here

Flow-Wing uses **single inheritance**: a **subclass** has **one** direct **superclass**, declared with **`extends`**. The child **inherits** fields and methods. In the child's **`init`**, call **`super(…)`** to run the parent's **constructor** before setting child-only fields.

You can **override** a method in the child by writing a new body with the **same** name. **Dynamic dispatch** means the **runtime type** of an object — not the declared type — picks which method runs. Pass a `Car` where a `Vehicle` is expected, and the `Car`'s methods fire automatically. It's like a hotel key card: the base says "door access," but your card knows you're in room 304.

## Your first `extends` (Vehicle → Car)

Read top to bottom: **base class**, then **subclass** with **extra field** and **overridden** **`getDetails` / `printDetails`**.

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

class Car extends Vehicle {
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

## Use the same function for `Vehicle` and `Car` (polymorphism)

A parameter typed as **`Vehicle`** happily accepts a **`Car`**. The **right** `printDetails` and **`getDetails`** run for the **real** object. (The `Vehicle` and `Car` classes are the same as above — `...` shortened for readability.)

<CodeBlock code={
`/* ... Vehicle and Car classes as defined above ... */

fun printVehicleDetails(v: Vehicle) -> nthg {
    v.printDetails()
}

fun fg_main() -> nthg {
    var vehicle:Vehicle = new Vehicle("Toyota", "Camry", 2020)
    var car:Car = new Car("Honda", "Civic", 2022, 4)

    printVehicleDetails(vehicle)
    printVehicleDetails(car)
}

fg_main()
`} language="fg"/>

## More detail: `super`, overrides, and design

- Call **`super(…)`** in **`init`** so **parent** state is set before you assign **subclass** fields. **`super`** works only inside **`init`** — it's not available in regular methods.
- **Override** by redeclaring a **method** in the child. **Return types** and **signatures** must stay compatible with your build's language rules.
- **No multiple inheritance** of classes — only one **`extends`** chain. For "mix in" style patterns, use **composition**: hold another object as a field rather than inheriting from it.

## Source & tests (if you have the repository)

Hundreds of class and **inheritance** test cases live under **`tests/fixtures/LatestTests/ClassTests/`**. A deep tree of **hierarchy** tests is at:

**`tests/fixtures/LatestTests/ClassTests/legacy_Class_fixtures/InheritanceTest/InheritanceTest/`**

(legacy layout name — still useful for seeing how the **binder** and **IR** handle inheritance). You don't need that folder to **learn** **`extends`**.
