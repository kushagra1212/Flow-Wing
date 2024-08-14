#include "MultipleAssignment.h"

void MultipleAssignment::SetUp() { _test->SetUp(); }

void MultipleAssignment::TearDown() { _test->TearDown(); }

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
TEST_F(MultipleAssignment, MABasic) {
  I(R"(
var x:int, y:str = 2,"hello"

print(x,y)

y,x = "Hi",5

print(x,y)

    )");

  EXPECT_EQ(getOutput(), R"(2hello5Hi)");
}
TEST_F(MultipleAssignment, MABasic2) {
  I(R"(
var x:int, y:str = 2,"hello"

print(x,y)

y,x = "Hi",5

print(x,y)


type J ={
  a:str 
}

type T = {

  a:int,
  b:deci,
  c:J
}

var a:int,b:str,c:deci,e:bool,g:T  = 2,"e"


c,g = 2.3,{b:3.3}
print(a,b,c,e,g)

    )");

  EXPECT_EQ(
      getOutput(),
      R"(2hello5Hi2e2.30000000000000false{ a : 0, b : 3.30000000000000, c : { a : '' } })");
}
TEST_F(MultipleAssignment, MABasic2Scoped) {
  I(R"(
var x:int, y:str = 2,"hello"

print(x,y)

y,x = "Hi",5

print(x,y)


type J ={
  a:str 
}

type T = {

  a:int,
  b:deci,
  c:J
}

var a:int,b:str,c:deci,e:bool,g:T  = 2,"e"

{

c,g = 2.3,{b:3.3}
print(a,b,c,e,g)
}

    )");

  EXPECT_EQ(
      getOutput(),
      R"(2hello5Hi2e2.30000000000000false{ a : 0, b : 3.30000000000000, c : { a : '' } })");
}
TEST_F(MultipleAssignment, MABasic3Scoped) {
  I(R"(
var x:int, y:str = 2,"hello"

print(x,y)

y,x = "Hi",5

print(x,y)


type J ={
  a:str 
}

type T = {

  a:int,
  b:deci,
  c:J
}{

var a:int,b:str,c:deci,e:bool,g:T  = 2,"e"



c,g = 2.3,{b:3.3}
print(a,b,c,e,g)
}

    )");

  EXPECT_EQ(
      getOutput(),
      R"(2hello5Hi2e2.30000000000000false{ a : 0, b : 3.30000000000000, c : { a : '' } })");
}
TEST_F(MultipleAssignment, MABasic3ScopedArrayAndClass) {
  I(R"(
var x:int, y:str = 2,"hello"

print(x,y)

y,x = "Hi",5

print(x,y)


type J ={
  a:str 
}

type T = {

  a:int,
  b:deci,
  c:J
}

class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x
  }

  printX() -> nthg {
    print(x)
  }
}

var a:int,b:str,c:deci,e:bool,g:T,f:T[10]  = 2,"e"

var l:int,aa:A = 45,new A(22)

c,g = 2.3,{b:3.3}

e,f  =true,[{a:10}]

print(e,f)
print(aa.x)
aa.printX()

l,aa = 12,new A(32)
print(l)
print(aa.x)
aa.printX()

    )");

  EXPECT_EQ(
      getOutput(),
      R"(2hello5Hitrue[{ a : 10, b : 0.00000000000000, c : { a : '' } }, { a : 0, b : 0.00000000000000, c : { a : '' } }, { a : 0, b : 0.00000000000000, c : { a : '' } }, { a : 0, b : 0.00000000000000, c : { a : '' } }, { a : 0, b : 0.00000000000000, c : { a : '' } }, { a : 0, b : 0.00000000000000, c : { a : '' } }, { a : 0, b : 0.00000000000000, c : { a : '' } }, { a : 0, b : 0.00000000000000, c : { a : '' } }, { a : 0, b : 0.00000000000000, c : { a : '' } }, { a : 0, b : 0.00000000000000, c : { a : '' } }]2222123232)");
}

TEST_F(MultipleAssignment, MABasic3ScopedArrayAndClassUsingFunction) {
  I(R"(
fun get() -> int,str {
  return 2,"H"
}

fun getX() ->  int {
    return 2
  }
var g:int = getX()
print(g)
var x:int,y:str = getX(),"Helo"
print(x,y)
y,x = "r",43
print(x,y)
y,x = "e",getX()
print(x,y)
x,y = get()
print(x,y)

type T = {
 a:int 
}
type L = {
  x:int,
  u:str,
  g:T,
  l:T[2]
}

var f:L[2],i:str = [{l:[{a:2}]}],"I"
print(f,i)

fun getFAndI() -> L[2],str {
  return [{},{g:{a:4}}],"ER"
}

f,i = getFAndI()
print("\n")
print(f,i)
    )");

  EXPECT_EQ(
      getOutput(),
      R"(22Helo43r2e2H[{ x : 0, u : '', g : { a : 0 }, l : [{ a : 2 }, { a : 0 }] }, { x : 0, u : '', g : { a : 0 }, l : [{ a : 0 }, { a : 0 }] }]I
[{ x : 0, u : '', g : { a : 0 }, l : [{ a : 2 }, { a : 0 }] }, { x : 0, u : '', g : { a : 4 }, l : [{ a : 0 }, { a : 0 }] }]ER)");
}
TEST_F(MultipleAssignment, MABasic3ScopedArrayAndClassUsingFunctionScoped) {
  I(R"(
fun get() -> int,str {
  return 2,"H"
}

fun getX() ->  int {
    return 2
  }
{
var g:int = getX()
print(g)
var x:int,y:str = getX(),"Helo"
print(x,y)
y,x = "r",43
print(x,y)
y,x = "e",getX()
print(x,y)
x,y = get()
print(x,y)}

type T = {
 a:int 
}
type L = {
  x:int,
  u:str,
  g:T,
  l:T[2]
}

var f:L[2],i:str = [{l:[{a:2}]}],"I"
{
print(f,i)}

fun getFAndI() -> L[2],str {
  return [{},{g:{a:4}}],"ER"
}
{

f,i = getFAndI()
print("\n")
print(f,i)}
    )");

  EXPECT_EQ(
      getOutput(),
      R"(22Helo43r2e2H[{ x : 0, u : '', g : { a : 0 }, l : [{ a : 2 }, { a : 0 }] }, { x : 0, u : '', g : { a : 0 }, l : [{ a : 0 }, { a : 0 }] }]I
[{ x : 0, u : '', g : { a : 0 }, l : [{ a : 2 }, { a : 0 }] }, { x : 0, u : '', g : { a : 4 }, l : [{ a : 0 }, { a : 0 }] }]ER)");
}

TEST_F(MultipleAssignment,
       MABasic3ScopedArrayAndClassUsingFunctionClasesAndPrimitive) {
  I(R"(
class A {
  var x:int 

  init(x:int) -> nthg {
      self.x =x 
  }

  printX() -> nthg {
      print(x)
    }

}

fun getFAndA() -> int, A  {
  return 2,new A(32)
}

fun getP() -> A {
    return new A(21)
  }

{
    var a:A = getP()

    

a.printX()


var u:int ,b:A = getFAndA()
b.printX()
print(u)
print(b.x)
  }

var u:int ,b:A = getFAndA()
b.printX()
print(u)
print(b.x)
    )");

  EXPECT_EQ(getOutput(), R"(213223232232)");
}
TEST_F(MultipleAssignment,
       MABasic3ScopedArrayAndClassUsingFunctionClasesAndPrimitiveAssignment) {
  I(R"(
class A {
  var x:int 

  init(x:int) -> nthg {
      self.x =x 
  }

  printX() -> nthg {
      print(x)
    }

}

fun getFAndA() -> int, A  {
  return 2,new A(32)
}

fun getP() -> A {
    return new A(21)
  }

    var a:A = getP()

    

a.printX()


var u:int ,b:A

u,b= getFAndA()
b.printX()
print(u)
print(b.x)
    )");

  EXPECT_EQ(getOutput(), R"(2132232)");
}

TEST_F(
    MultipleAssignment,
    MABasic3ScopedArrayAndClassUsingFunctionClasesAndPrimitiveAssignmentScoped) {
  I(R"(
class A {
  var x:int 

  init(x:int) -> nthg {
      self.x =x 
  }

  printX() -> nthg {
      print(x)
    }

}

fun getFAndA() -> int, A  {
  return 2,new A(32)
}

fun getP() -> A {
    return new A(21)
  }

{
    var a:A = getP()

    

a.printX()


var u:int ,b:A

u,b= getFAndA()
b.printX()
print(u)
print(b.x)
  }
    )");

  EXPECT_EQ(getOutput(), R"(2132232)");
}

TEST_F(
    MultipleAssignment,
    MABasic3ScopedArrayAndClassUsingFunctionClasesAndPrimitiveAssignmentComplex) {
  I(R"(
class A {
  var x:int 

  init(x:int) -> nthg {
      self.x =x 
  }

  printX() -> nthg {
      print(x)
    }

}
fun get() -> int,str {
  return 2,"H"
}

fun getX() ->  int {
    return 2
  }


type T = {
 a:int 
}
type L = {
  x:int,
  u:str,
  g:T,
  l:T[2]
}

fun getFAndA() -> T[2], A  {
  return [],new A(32)
}


var u:T[2] ,b:A

u,b =  getFAndA()
b.printX()
print(u)
print(b.x)
    )");

  EXPECT_EQ(getOutput(), R"(32[{ a : 0 }, { a : 0 }]32)");
}

TEST_F(
    MultipleAssignment,
    MABasic3ScopedArrayAndClassUsingFunctionClasesAndPrimitiveAssignmentComplexScoped) {
  I(R"(
class A {
  var x:int 

  init(x:int) -> nthg {
      self.x =x 
  }

  printX() -> nthg {
      print(x)
    }

}
fun get() -> int,str {
  return 2,"H"
}

fun getX() ->  int {
    return 2
  }


type T = {
 a:int 
}
type L = {
  x:int,
  u:str,
  g:T,
  l:T[2]
}

fun getFAndA() -> T[2], A  {
  return [],new A(32)
}


{
var u:T[2] ,b:A

u,b =  getFAndA()
b.printX()
print(u)
print(b.x)}
    )");

  EXPECT_EQ(getOutput(), R"(32[{ a : 0 }, { a : 0 }]32)");
}

TEST_F(
    MultipleAssignment,
    MABasic3ScopedArrayAndClassUsingFunctionClasesAndPrimitiveAssignmentComplexDefaultPrint) {
  I(R"(


class A {
  var x:int 

  init(x:int) -> nthg {
      self.x =x 
  }

  printX() -> nthg {
      print(x)
    }

}
fun get() -> int,str {
  return 2,"H"
}

fun getX() ->  int {
    return 2
  }


type T = {
 a:int 
}
type L = {
  x:int,
  u:str,
  g:T,
  l:T[2]
}

fun getFAndA() -> T[2], A  {
  return [{a:10}],new A(32)
}


var u:T[2] ,b:A
print(u)
u,b =  getFAndA()
b.printX()
print(u)
print(b.x)
    )");

  EXPECT_EQ(getOutput(),
            R"([{ a : 0 }, { a : 0 }]32[{ a : 10 }, { a : 0 }]32)");
}

TEST_F(
    MultipleAssignment,
    MABasic3ScopedArrayAndClassUsingFunctionClasesAndPrimitiveAssignmentComplexAssign) {
  I(R"(



class A {
  var x:int 

  init(x:int) -> nthg {
      self.x =x 
  }

  printX() -> nthg {
      print(x)
    }

}
fun get() -> int,str {
  return 2,"H"
}

fun getX() ->  int {
    return 2
  }


type T = {
 a:int 
}
type L = {
  x:int,
  u:str,
  g:T,
  l:T[2]
}

fun getFAndA() -> T[2], A  {
  return [{a:10}],new A(32)
}


var u:T[2] ,b:A = getFAndA() 
b.printX()
print(u)
print(b.x)
    )");

  EXPECT_EQ(getOutput(), R"(32[{ a : 10 }, { a : 0 }]32)");
}

TEST_F(
    MultipleAssignment,
    MABasic3ScopedArrayAndClassUsingFunctionClasesAndPrimitiveAssignmentComplexAssignReturnFunction) {
  I(R"(
                              
                              
class A {                     
  var x:int                   
                              
  init(x:int) -> nthg {       
      self.x =x               
  }                           
                              
  printX() -> nthg {          
      print(x)                
    }                         
                              
}                             
fun get() -> int,str {        
  return 2,"H"                
}                             
                              
fun getX() ->  int {          
    return 2                  
  }                           
                              
                              
type T = {                    
 a:int                        
}                             
type L = {                    
  x:int,                      
  u:str,                      
  g:T,                        
  l:T[2]                      
}                             
                              
fun getT() -> T[2] {          
    return [{a:10}]           
  }                           
                              
                              
fun getA() -> A {             
return new A(23)              
                              
  }                           
                              
fun getFAndA() -> T[2], A  {  
  return getT(),getA()        
}                             
                              
                              
var u:T[2] ,b:A = getFAndA()  
b.printX()                    
print(u)                      
print(b.x)                    
                              
                              

    )");

  EXPECT_EQ(getOutput(), R"(23[{ a : 10 }, { a : 0 }]23)");
}

TEST_F(
    MultipleAssignment,
    MABasic3ScopedArrayAndClassUsingFunctionClasesAndPrimitiveAssignmentComplexAssignReturnFunctionComplex) {
  I(R"(
                                     
                                
class A {                       
  var x:int                     
                                
  init(x:int) -> nthg {         
      self.x =x                 
  }                             
                                
  printX() -> nthg {            
      print(x)                  
    }                           
                                
}                               
fun get() -> int,str {          
  return 2,"H"                  
}                               
                                
fun getX() ->  int {            
    return 2                    
  }                             
                                
                                
type T = {                      
 a:int                          
}                               
type L = {                      
  x:int,                        
  u:str,                        
  g:T,                          
  l:T[2]                        
}                               
                                
fun getT() -> T[2] {            
    return [{a:10}]             
  }                             
                                
                                
fun getA() -> A {               
return new A(23)                
                                
  }                             
                                
fun getFAndAPar() -> T[2], A  { 
  return getT(),getA()          
}                               
fun getFAndA() -> T[2], A  {    
  return getFAndAPar()          
}                               
                                
                                
var u:T[2] ,b:A = getFAndA()    
b.printX()                      
print(u)                        
print(b.x)                      
                                


    )");

  EXPECT_EQ(getOutput(), R"(23[{ a : 10 }, { a : 0 }]23)");
}
#endif