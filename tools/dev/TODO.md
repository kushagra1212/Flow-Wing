## Bug
- multidimentional nessated array 
- class initilizer when during inheritance
- class inheriance

## Current Work

- Array inside Object (test all cases)
- assigning array to an array object element (test all cases)
- passing called function in the function call and assigning Object
```
type t = {
    x:int,
  }

fun getT()-> t{
    var v:t ={x:2}
    return v
}

fun pass(u:t)-> nthg {
    print(u)
  }
pass(getT())
```
- passing called function in the function call and assigning Array

### Not right now needed
- Creation of array of objects
- add support for this print({a: 1, b: 2}) (unintialized)      
- add support for this     
      fun main() -> t1 {
        return { a:"ram",b:11,c:11.11,d:false }
  }


## In Future

- lamda function
- passing function as param
- returning function from function
- function as object property
- fix -45.10000000000000 With Decimal (Current work arround -1*45.10000000000000)
- etc

## Done

- declaring object with return value from function call
- assigning object with return value from function call
- returning object from function 
- assign object property by return value from function call