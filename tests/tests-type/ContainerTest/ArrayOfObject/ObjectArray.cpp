#include "ObjectArray.h"

ObjectArray::ObjectArray() { _test = std::move(Tests::FlowWing::getTest()); }

void ObjectArray::SetUp() { _test->SetUp(); }

void ObjectArray::TearDown() { _test->TearDown(); }

void ObjectArray::setInput(const std::string &input) { _test->setInput(input); }

std::string ObjectArray::getOutput() const { return _test->getOutput(); }

void ObjectArray::runEvaluator() { _test->runEvaluator(); }

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)

TEST_F(ObjectArray, GlobalArrayOfObjectInitializationWithObject) {
  I(R"(
type k = {
   o:int
}

type par ={
    u:str,
    g:k[5]
  }
type t = {
    x:int,
    y:str,
    a:deci,
    b:bool,
    arr:par[1]
}
var arr:t[2] = [1 fill {x:1}]
print(arr)
)");
  O("[{ x : 1, y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g : "
    "[{ o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }, { x : 0, y "
    ": '', a : 0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0 }, { "
    "o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }]");
}

TEST_F(ObjectArray, ContainerExpessionFill1D) {
  I(R"(
  type k = {
   o:int
}
type par ={
    u:str,
    g:k[5]
}
type t = {
    x:int,
    y:str,
    a:deci,
    b:bool,
    arr:par[1]
}

var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true}]
print(arr))");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : '', g "
    ": [{ o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }, { x : 0, "
    "y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0 }, "
    "{ o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }]");
}

TEST_F(ObjectArray, ContainerExpessionFill1DWithArrayInside) {
  I(R"(
type k = {
   o:int
}
type par ={
    u:str,
    g:k[5]
}
type t = {
    x:int,
    y:str,
    a:deci,
    b:bool,
    arr:par[1]
}

var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,arr:[{u:"get"}]}]
print(arr))");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'get', g : [{ o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }, "
    "{ x : 0, y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g : [{ "
    "o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }]");
}

TEST_F(ObjectArray, ContainerExpessionFill1DWithArrayInsideMoreValuesDefault) {
  I(R"(
type k = {
   o:int,
   s:str,
   d:deci,
   i:int
}
type par ={
    u:str,
    g:k[5]
}
type t = {
    x:int,
    y:str,
    a:deci,
    b:bool,
    arr:par[1]
}

var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,arr:[{u:"get"}]}]
print(arr))");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'get', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : "
    "'', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, "
    "i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', "
    "d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : "
    "0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}, { o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }] }]");
}

TEST_F(ObjectArray,
       ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefault) {
  I(R"(
type k = {
   o:int,
   s:str,
   d:deci,
   i:int
}
type par ={
    u:str,
    g:k[2]
}
type t = {
    x:int,
    y:str,
    a:deci,
    b:bool,
    arr:par[1]
}

var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,arr:[{u:"get",g:[{o:100,s:"hello"}]}]}]
print(arr))");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'get', g : [{ o : 100, s : 'hello', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : "
    "0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }] }]");
}

TEST_F(
    ObjectArray,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariable) {
  I(R"(
type k = {
   o:int,
   s:str,
   d:deci,
   i:int
}
type par ={
    u:str,
    g:k[2]
}
type t = {
    x:int,
    y:str,
    a:deci,
    b:bool,
    arr:par[1]
}

var arrvar:t =  {x:2,y:"hello",a:3.3,b:true}
var arr:t[2] = [arrvar]
print(arr)
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : '', g "
    ": [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : "
    "0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b "
    ": false, arr : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : "
    "0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]");
}

TEST_F(
    ObjectArray,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArray) {
  I(R"(
type k = {
   o:int,
   s:str,
   d:deci,
   i:int
}
type par ={
    u:str,
    g:k[2]
}
type t = {
    x:int,
    y:str,
    a:deci,
    b:bool,
    arr:par[1]
}

var arrvar:t =  {x:2,y:"hello",a:3.3,b:true,arr:[{u:"arru",g:[{o:102,s:"sora"}]}]}
var arr:t[2] = [arrvar]
print(arr)
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : "
    "0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }] }]");
}

TEST_F(
    ObjectArray,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArray2) {
  I(R"(
type k = {
   o:int,
   s:str,
   d:deci,
   i:int
}
type par ={
    u:str,
    g:k[2]
}
type t = {
    x:int,
    y:str,
    a:deci,
    b:bool,
    arr:par[1]
}
var gka:k = {o:102,s:"sora"}
var arrvar:t =  {x:2,y:"hello",a:3.3,b:true,arr:[{u:"arru",g:[gka]}]}
var arr:t[2] = [arrvar]
print(arr)
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : "
    "0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }] }]");
}

TEST_F(
    ObjectArray,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArray3) {
  I(R"(
type k = {
   o:int,
   s:str,
   d:deci,
   i:int
}
type par ={
    u:str,
    g:k[2]
}
type t = {
    x:int,
    y:str,
    a:deci,
    b:bool,
    arr:par[1]
}
var gka:k = {o:102,s:"sora"}
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,arr:[{u:"arru",g:[gka]}]}]
print(arr)
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : "
    "0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }] }]");
}

TEST_F(
    ObjectArray,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArrayWithFillExpression) {
  I(R"(
type k = {
   o:int,
   s:str,
   d:deci,
   i:int
}
type par ={
    u:str,
    g:k[2]
}
type t = {
    x:int,
    y:str,
    a:deci,
    b:bool,
    arr:par[1]
}
var gka:k = {o:102,s:"sora"}
var arr:t[3] = [2 fill {x:2,y:"hello",a:3.3,b:true,arr:[{u:"arru",g:[gka]}]}]
print(arr)
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 2, y : 'hello', a : "
    "3.30000000000000, b : true, arr : [{ u : 'arru', g : [{ o : 102, s : "
    "'sora', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : "
    "0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b "
    ": false, arr : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : "
    "0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]");
}

TEST_F(
    ObjectArray,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArrayWithFillExpressionPrint) {
  I(R"(
type k = {
   o:int,
   s:str,
   d:deci,
   i:int
}
type par ={
    u:str,
    g:k[2]
}
type t = {
    x:int,
    y:str,
    a:deci,
    b:bool,
    arr:par[1]
}
var gka:k = {o:102,s:"sora"}
var arr:t[3] = [{x:2,y:"hello",a:3.3,b:true,arr:[{u:"arru",g:[gka]}]}]
print(arr[0])
)");
  O("{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }");
}
TEST_F(ObjectArray, PrintArrayInsideObjectDefault) {
  I(R"(
type p = {
    x:int,
    y:int[2],
    b:deci[2],
    c:str[2],
    d:bool[2],
    f:str
}
var x:p = {x:2}
print(x.y)
print(x.b)
print(x.c)
print(x.d)
print(x.f)
print(x)
)");
  O("[0, 0][0.00000000000000, 0.00000000000000]['', ''][false, false]{ x : 2, "
    "y : [0, 0], b : [0.00000000000000, 0.00000000000000], c : ['', ''], d : "
    "[false, false], f : '' }");
}

TEST_F(ObjectArray, PrintArrayInsideObject) {
  I(R"(
type p = {
    x:int,
    y:int[2],
    b:deci[2],
    c:str[2],
    d:bool[2],
    f:str
}
var x:p = {x:2,y:[2 fill 5],b:[1 fill 2.2],c:["hello"],d:[true,true]}
print(x.y)
print(x.b)
print(x.c)
print(x.d)
print(x.f)
print(x)
)");
  O("[5, 5][2.20000000000000, 0.00000000000000]['hello', ''][true, true]{ x : "
    "2, y : [5, 5], b : [2.20000000000000, 0.00000000000000], c : ['hello', "
    "''], d : [true, true], f : '' }");
}

TEST_F(ObjectArray, PrintArrayInsideObjectComplex) {
  I(R"(
type k = {
  o: int,
  s: str,
  d: deci,
  i: int
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  arr: par[1]
}
var gka: k  = {
  o: 102,
  s: "sora"
}
var arr: t[3] = [{
  x: 2,
  y: "hello",
  a: 3.3,
  b: true,
  arr: [{
    u: "arru",
    g: [gka]
  }]
}]
print(arr[0].x)
print(arr[0].y)
print(arr[0].a)
print(arr[0].b)
print(arr[0].arr)
print(arr[1]) 
)");
  O("2hello3.30000000000000true[{ u : 'arru', g : [{ o : 102, s : 'sora', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }]{ x : 0, y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g "
    ": [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : "
    "0.00000000000000, i : 0 }] }] }");
}

TEST_F(ObjectArray, PrintArrayInsideObjectComplex2) {
  I(R"(
type k = {
  o: int,
  s: str,
  d: deci,
  i: int
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  arr: par[1]
}
var gka: k  = {
  o: 102,
  s: "sora"
}
var arr: t[2] = [{
  x: 2,
  y: "hello",
  a: 3.3,
  b: true,
  arr: [{
    u: "arru",
    g: [gka]
  }]
}]
print(arr[0].x)
print(arr[0].y)
print(arr[0].a)
print(arr[0].b)
print(arr[0].arr)
print(arr[1]) 
)");
  O("2hello3.30000000000000true[{ u : 'arru', g : [{ o : 102, s : 'sora', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }]{ x : 0, y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g "
    ": [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : "
    "0.00000000000000, i : 0 }] }] }");
}

TEST_F(ObjectArray, VariableExpression1) {
  I(R"(
type k = {
  o: int,
  s: str,
  d: deci,
  i: int
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  o: 102,
  s: "sora"
}
var arr: t[2] = [{
  x: 2,
  y: "hello",
  a: 3.3,
  b: true,
  ar: [{
    u: "arru",
    g: [gka]
  }]
}]
print(arr)
print("\n")
print(arr[0])
print("\n")
print(arr[0].x)
print("\n")
print(arr[0].ar)
print("\n")
print(arr[0].ar[0])
print("\n")
print(arr[0].ar[0].u)
print("\n")
print(arr[0].ar[0].g)
print("\n")
print(arr[0].ar[0].g[1])
print("\n")
print(arr[0].ar[0].g[0].s)
print("\n")
print(arr[0].ar[0].g[0].o)
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }
2
[{ u : 'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }]
{ u : 'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }
arru
[{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }]
{ o : 0, s : '', d : 0.00000000000000, i : 0 }
sora
102)");
}

TEST_F(ObjectArray, ArrayDeclarationUsingAnotherVariable) {
  I(R"(
type k = {
  o: int,
  s: str,
  d: deci,
  i: int
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  o: 102,
  s: "sora"
}

var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var arr2:t[2] = arr
print(arr2)
print("\n")
print(arr2[0].ar[0].g[0].d)
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(ObjectArray, ArrayDeclarationUsingAnotherVariableObjectFill) {
  I(R"(
type k = {
  o: int,
  s: str,
  d: deci,
  i: int
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  o: 102,
  s: "sora"
}

var arr2:t[2] = [1 fill {y:"j",a:2.2}]
print(arr2)
print("\n")
print(arr2[0].ar[0].g[0].d)
)");
  O(R"([{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(ObjectArray, ArrayDeclarationUsingAnotherVariableObjectExpression) {
  I(R"(
type k = {
  o: int,
  s: str,
  d: deci,
  i: int
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  o: 102,
  s: "sora"
}

var arr2:t[2] =[{y:"j",a:2.2}]
print(arr2)
print("\n")
print(arr2[0].ar[0].g[0].d)
)");
  O(R"([{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(ObjectArray,
       ArrayDeclarationUsingAnotherVariableObjectExpressionAssignment) {
  I(R"(
type k = {
  o: int,
  s: str,
  d: deci,
  i: int
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}

var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var arr2:t[2] = [1 fill {y:"j",a:2.2}]
print(arr2)
arr2 = arr
print("\n")
print(arr2)
print("\n")
print(arr2[0].ar[0].g[0].d)
)");
  O(R"([{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(
    ObjectArray,
    ArrayDeclarationUsingAnotherVariableObjectExpressionAssignmentPartialInt) {
  I(R"(
type k = {
  o: int,
  s: str,
  d: deci,
  i: int
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var arr2:t[2] = [1 fill {y:"j",a:2.2}]
print(arr2)
arr2[0].x = arr[0].x
print("\n")
print(arr2)
print("\n")
print(arr2[0].ar[0].g[0].d)
)");
  O(R"([{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
[{ x : 2, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(ObjectArray, ArrayDeclarationUsingAnotherVariableObjectTest) {
  I(R"(
type k = {
  o: int,
  s: str,
  d: deci,
  i: int
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var arr2:t[2] = [1 fill {y:"j",a:2.2}]
print(arr)
print("\n")
var p:int[2] = [1,2]
arr[0] = arr2[0]
print(arr)
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
[{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }])");
}

TEST_F(ObjectArray, ArrayDeclarationUsingAnotherVariableObjectTestInitTest) {
  I(R"(
type k = {
  o: int,
  s: str,
  d: deci,
  i: int
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12}]}]}]
print(sec)
)");
  O(R"([{ x : 0, y : '', a : 3.50000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }])");
}

TEST_F(ObjectArray,
       ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2) {
  I(R"(
type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(sec)
)");
  O(R"([{ x : 0, y : '', a : 3.50000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}
TEST_F(ObjectArray,
       ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2Assign) {
  I(R"(
type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(arr)
print("\n")
arr[0].ar[0].g[0].ob = sec[0].ar[0].g[0].ob
print(arr)
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArray,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitive) {
  I(R"(
type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(arr)
print("\n")
arr[0].ar[0].g[0].ob.i = sec[0].ar[0].g[0].ob.i
print(arr)
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 200, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArray,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArray) {
  I(R"(
type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(arr)
print("\n")
arr = []
print(arr)
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArray,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig) {
  I(R"(
type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(arr)
print("\n")
arr[0].x = sec[0].x
arr[0].y = sec[0].y
arr[0].a = sec[0].a 
arr[0].b = sec[0].b 
arr[0].ar[0].u =  sec[0].ar[0].u 
arr[0].ar[0].g[0].s = sec[0].ar[0].g[0].s 
arr[0].ar[0].g[0].i = sec[0].ar[0].g[0].i 
print(arr)
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 0, y : '', a : 3.50000000000000, b : false, ar : [{ u : '', g : [{ o : 102, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArray,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig2) {
  I(R"(
type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(arr)
print("\n")
arr[0].x = sec[0].x
arr[0].y = sec[0].y
arr[0].a = sec[0].a 
arr[0].b = sec[0].b 
arr[0].ar[0].u =  sec[0].ar[0].u 
arr[0].ar[0].g = sec[0].ar[0].g
arr[1].ar[0].g = sec[0].ar[0].g 
print(arr[1])
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArray,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig3) {
  I(R"(
type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(arr)
print("\n")
arr[0].x = sec[0].x
arr[0].y = sec[0].y
arr[0].a = sec[0].a 
arr[0].b = sec[0].b 
arr[0].ar[0].u =  sec[0].ar[0].u 
arr[0].ar[0].g = sec[0].ar[0].g
arr[1].ar[0] = sec[0].ar[0]
print(arr[1])
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArray,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig4) {
  I(R"(
type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(arr)
print("\n")
arr[0].x = sec[0].x
arr[0].y = sec[0].y
arr[0].a = sec[0].a 
arr[0].b = sec[0].b 
arr[0].ar[0].u =  sec[0].ar[0].u 
arr[0].ar[0].g = sec[0].ar[0].g
arr[1].ar[0] = sec[0].ar[0]
print(arr[1])
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(ObjectArray, ArrayInsideObjectAcess) {
  I(R"(
      type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}

var r:par = {g:[]}
print(r.g[1])
    )");

  O("{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }");
}

TEST_F(ObjectArray, ArrayInsideObjectAcessLocal) {
  I(R"(
{
        type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}

var r:par = {g:[]}
print(r.g[1])
}
    )");

  O("{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }");
}

TEST_F(ObjectArray, ArrayInsideObjectAcessLocalPartialLocal) {
  I(R"(

        type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
{
var r:par = {g:[]}
print(r.g[1])
}
    )");

  O("{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }");
}
TEST_F(ObjectArray, ArrayInsideObjectAcessLocalPartialLocal2) {
  I(R"(

        type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}

var r:par = {g:[]}
{
print(r.g[1])
}
    )");

  O("{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }");
}

TEST_F(ObjectArray, ArrayInsideObjectAcessRig) {
  I(R"(

      type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}

var r:par = {g:[{},{d:2.3,s:"Hello",ob:{s:"g"}}]}

print(r.g[1].o)
print(r.g[1].i)
print(r.g[1].s)
print(r.g[1].d)
print(r.g[1].ob)
print("\n")
print(r.g[0].o)
print(r.g[0].i)
print(r.g[0].s)
print(r.g[0].d)
print(r.g[0].ob)
    )");

  O(R"(00Hello2.30000000000000{ i : 0, s : 'g' }
000.00000000000000{ i : 0, s : '' })");
}

TEST_F(ObjectArray, TypeTests) {
  I(R"(
type x = {
    a:int 
  }

  var a:x
fun def() -> int {
  type x = {
      a:int,
      j:str
    }
  var y:x
  print("print y ",y)
  return 0
  }

{
  type x = {s:str}
 {
    var a:x 
    print("print a in block ",a)
  } 
  }
print("print a gloabl",a)
def()
    )");

  O(R"(print a in block { s : '' }print a gloabl{ a : 0 }print y { a : 0, j : '' })");
}
TEST_F(ObjectArray, TypeTestsMultiDimension) {
  I(R"(

type T = {
  a:int 
}

type K = {
  j:T[2][2]
}
var j:K ={j:[[{a:2}]]}

print(j)
    )");

  O(R"({ j : [[{ a : 2 }, { a : 0 }], [{ a : 0 }, { a : 0 }]] })");
}

TEST_F(ObjectArray, TypeTestsMultiDimensionLocal) {
  I(R"(

{
  type T = {
  a:int 
}

type K = {
  j:T[2][2]
}
var j:K ={j:[[{a:2}]]}

print(j)
}
    )");

  O(R"({ j : [[{ a : 2 }, { a : 0 }], [{ a : 0 }, { a : 0 }]] })");
}
TEST_F(ObjectArray, ObjectReturningTest) {
  I(R"(
type t = {

    a:int
}

fun getB(a:int) ->t {
  print("aa",a)
  return {a:111}
}

fun main(b:int) -> t {
    var u:t ={a:b}
    return getB(b)
}

var x:t = main(10)
print(x)
x =main(2)
print(x)
    )");

  O(R"(aa10{ a : 111 }aa2{ a : 111 })");
}
TEST_F(ObjectArray, ObjectReturningTestLocal) {
  I(R"(
type t = {

    a:int
}

fun getB(a:int) ->t {
  print("aa",a)
  return {a:111}
}

fun main(b:int) -> t {
    var u:t ={a:b}
    return getB(b)
}

{
  var x:t = main(10)
print(x)
x =main(2)
print(x)
}
    )");

  O(R"(aa10{ a : 111 }aa2{ a : 111 })");
}
TEST_F(ObjectArray, ObjectReturningTestLocal2) {
  I(R"(
type t = {

    a:int
}

fun getB(a:int) ->t {
  print("aa",a)
  return {a:111}
}

fun main(b:int) -> t {
    var u:t ={a:b}
    return getB(b)
}


  var x:t = main(10)
print(x){
x =main(2)
print(x)
}
    )");

  O(R"(aa10{ a : 111 }aa2{ a : 111 })");
}
TEST_F(ObjectArray, ObjectReturningTestType2) {
  I(R"(
type t = {

    a:int
}

fun getB(a:int) ->t {
  print("aa",a)
  return {a:a}
}

fun main(b:int) -> t {
    var u:t ={a:b}
    return getB(b)
}

var x:t = main(10)
print(x)
x =main(2)
print(x)
    )");

  O(R"(aa10{ a : 10 }aa2{ a : 2 })");
}

TEST_F(ObjectArray, ObjectReturningTestType3) {
  I(R"(
type P = {
  s:str,
  d:deci 
}


type t = {
    b:P[2],
    a:int
}

fun getB(a:int) ->t[5] {
  print("aa",a)
  return [{a:a}]
}

fun main(b:int) -> t[5] {
    var u:t ={a:b}
    return getB(b)
}

var x:t[5] = main(10)
print(x)
x =main(2)
print(x)
    )");

  O(R"(aa10[{ b : [{ s : '', d : 0.00000000000000 }, { s : '', d : 0.00000000000000 }], a : 10 }, { b : [{ s : '', d : 0.00000000000000 }, { s : '', d : 0.00000000000000 }], a : 0 }, { b : [{ s : '', d : 0.00000000000000 }, { s : '', d : 0.00000000000000 }], a : 0 }, { b : [{ s : '', d : 0.00000000000000 }, { s : '', d : 0.00000000000000 }], a : 0 }, { b : [{ s : '', d : 0.00000000000000 }, { s : '', d : 0.00000000000000 }], a : 0 }]aa2[{ b : [{ s : '', d : 0.00000000000000 }, { s : '', d : 0.00000000000000 }], a : 2 }, { b : [{ s : '', d : 0.00000000000000 }, { s : '', d : 0.00000000000000 }], a : 0 }, { b : [{ s : '', d : 0.00000000000000 }, { s : '', d : 0.00000000000000 }], a : 0 }, { b : [{ s : '', d : 0.00000000000000 }, { s : '', d : 0.00000000000000 }], a : 0 }, { b : [{ s : '', d : 0.00000000000000 }, { s : '', d : 0.00000000000000 }], a : 0 }])");
}
TEST_F(ObjectArray, ObjectReturningTestType4) {
  I(R"(
type P = {
  s:str,
  d:deci 
}


type t = {
    b:P[2],
    a:int
}

class A {
  var a:t 

  init(a:t) -> nthg {
    self.a = a 
  }
}

fun getB(a:int) -> A {
  print("aa",a)
  return new A({a:a,b:[1 fill {d:2.2,s:"nice"}]})
}

fun main(b:int) -> A {
    var u:t ={a:b}
    return getB(b)
}

var x:A = main(10)
print(x.a)
x =main(2)
print(x.a)
    )");

  O(R"(aa10{ b : [{ s : 'nice', d : 2.20000000000000 }, { s : '', d : 0.00000000000000 }], a : 10 }aa2{ b : [{ s : 'nice', d : 2.20000000000000 }, { s : '', d : 0.00000000000000 }], a : 2 })");
}
TEST_F(ObjectArray, BasicDeci32Test) {
  I(R"(
var ar:deci32 = 2.2d 
print(ar)
    )");

  O(R"(2.2000000)");
}

TEST_F(ObjectArray, BasicDeci32TestScoped) {
  I(R"(
{
  var ar:deci32 = 2.2d 
print(ar)
}
    )");

  O(R"(2.2000000)");
}
TEST_F(ObjectArray, BasicDeci32TestScoped2) {
  I(R"(

  var ar:deci32 = 2.2d 
  {
print(ar)
}
    )");

  O(R"(2.2000000)");
}
TEST_F(ObjectArray, BasicDeci32TestScoped2Assignment) {
  I(R"(
var ar:deci32 = 2.2d
{
  ar = 32.222d
}
print(ar)
    )");

  O(R"(32.2220001)");
}
TEST_F(ObjectArray, BasicDeci32TestAssignment) {
  I(R"(
var ar:deci32 = 2.2d

  ar = 32.222d

print(ar)
    )");

  O(R"(32.2220001)");
}
TEST_F(ObjectArray, BasicDeci32TestAssignmentArrayTest) {
  I(R"(
var arr:deci32[2] = [2.2d]
print(arr)
    )");

  O(R"([2.2000000, 0.0000000])");
}
TEST_F(ObjectArray, BasicDeci32TestAssignmentArrayTestLocal) {
  I(R"(
{
  var arr:deci32[2] = [2.2d]
print(arr)
}

    )");

  O(R"([2.2000000, 0.0000000])");
}
TEST_F(ObjectArray, BasicDeci32TestAssignmentArrayTestLocal2) {
  I(R"(
var arr:deci32[2] = [2 fill 2.2d]
print(arr)
    )");

  O(R"([2.2000000, 2.2000000])");
}

TEST_F(ObjectArray, BasicDeci32TestAssignmentArrayTestLocal3) {
  I(R"(
{
  var arr:deci32[2] = [2.2d]
print(arr)
}


    )");

  O(R"([2.2000000, 0.0000000])");
}
TEST_F(ObjectArray, BasicDeci32TestAssignmentArrayTestLocal2Function) {
  I(R"(
fun printdec(a:deci32[2]) -> nthg {
    print(a)
 
 }

 printdec([3.2d])
    )");

  O(R"([3.2000000, 0.0000000])");
}
TEST_F(ObjectArray, PrintConstantTest) {
  I(R"(
print("s")
    )");

  O(R"(s)");
}
TEST_F(ObjectArray,
       BasicDeci32TestAssignmentArrayTestLocal2FunctionArrayofObject) {
  I(R"(
type T ={
    a:deci32[2]
  }

var x:T  ={a:[2 fill 2.2d]}

print(x)
    )");

  O(R"({ a : [2.2000000, 2.2000000] })");
}
#endif