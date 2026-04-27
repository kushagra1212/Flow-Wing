---
sidebar_position: 2
---
import CodeBlock from "../../src/components/common/CodeBlock";

# Inheritance

## Start here

Flow-Wing uses **single inheritance**: a **subclass** has **one** direct **superclass**, declared with **`extends`**. The child **inherits** fields and methods; **`init` in the child** usually calls **`super(…)`** to run the parent’s **constructor** before setting child-only data. You can **override** a method in the child by writing a new body with the **same** name; **dynamic dispatch** means the **actual** class of an object picks which method runs (for example when you call **`printDetails`** on a value typed as the **parent** but holding a **child** instance).

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

A parameter typed as **`Vehicle`** can receive a **`Car`**: the **right** `printDetails` and **`getDetails`** run for the **real** object.

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

- Call **`super(…)`** in **`init`** so **parent** state is set before you assign **subclass** fields.
- **Override** by redeclaring a **method** in the child; **return types** and **signatures** must stay compatible with the **language** rules in your build.
- **No multiple inheritance** of classes—only one **`extends`** chain; use **composition** (hold another object as a field) for “mix in” style patterns.

## Source & tests (if you have the repository)

Hundreds of class and **inheritance** cases live under **`tests/fixtures/LatestTests/ClassTests/`**; a deep tree of **hierarchy** tests is under

**`tests/fixtures/LatestTests/ClassTests/legacy_Class_fixtures/InheritanceTest/InheritanceTest/`**

(legacy layout name, still useful when **reading** how the **binder** and **IR** are exercised). You do **not** need that folder to **learn** **`extends`**.
