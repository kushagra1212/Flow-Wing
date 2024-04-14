#include "ObjectArray.h"

ObjectArray::ObjectArray() { _test = std::move(FlowWing::getTest()); }

void ObjectArray::SetUp() { _test->SetUp(); }

void ObjectArray::TearDown() { _test->TearDown(); }

void ObjectArray::setInput(const std::string &input) { _test->setInput(input); }

std::string ObjectArray::getOutput() const { return _test->getOutput(); }

void ObjectArray::runEvaluator() { _test->runEvaluator(); }

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)

TEST_F(ObjectArray, GlobalArrayOfObjectInitializationWithObject) {
  I(R"(type k = {
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
print(arr))");
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
  O("[0, 0][0.00000000000000, 0.00000000000000][, ][false, false]{ x : 2, y : "
    "[0, 0], b : [0.00000000000000, 0.00000000000000], c : [, ], d : [false, "
    "false], f : '' }");
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
  O("[5, 5][2.20000000000000, 0.00000000000000][hello, ][true, true]{ x : 2, y "
    ": [5, 5], b : [2.20000000000000, 0.00000000000000], c : [hello, ], d : "
    "[true, true], f : '' }");
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

#endif