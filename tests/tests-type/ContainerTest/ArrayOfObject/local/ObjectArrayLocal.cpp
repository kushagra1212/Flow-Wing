#include "ObjectArrayLocal.h"

ObjectArrayLocal::ObjectArrayLocal() {
  _test = std::move(Tests::FlowWing::getTest());
}

void ObjectArrayLocal::SetUp() { _test->SetUp(); }

void ObjectArrayLocal::TearDown() { _test->TearDown(); }

void ObjectArrayLocal::setInput(const std::string &input) {
  _test->setInput(input);
}

std::string ObjectArrayLocal::getOutput() const { return _test->getOutput(); }

void ObjectArrayLocal::runEvaluator() { _test->runEvaluator(); }

// #if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)

TEST_F(ObjectArrayLocal, GlobalArrayOfObjectInitializationWithObject) {
  I(R"(
    {
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
    }
)");
  O("[{ x : 1, y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g : "
    "[{ o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }, { x : 0, y "
    ": '', a : 0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0 }, { "
    "o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }]");
}

TEST_F(ObjectArrayLocal, GlobalArrayOfObjectInitializationWithObjectPartial) {
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
 {
var arr:t[2] = [1 fill {x:1}]
print(arr)
    }
)");
  O("[{ x : 1, y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g : "
    "[{ o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }, { x : 0, y "
    ": '', a : 0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0 }, { "
    "o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }]");
}

TEST_F(ObjectArrayLocal, ContainerExpessionFill1D) {
  I(R"(
 {
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
print(arr)
 }
 )");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : '', g "
    ": [{ o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }, { x : 0, "
    "y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0 }, "
    "{ o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }]");
}

TEST_F(ObjectArrayLocal, ContainerExpessionFill1DPartial) {
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
{
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true}]
print(arr)
 }
 )");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : '', g "
    ": [{ o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }, { x : 0, "
    "y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0 }, "
    "{ o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }]");
}

TEST_F(ObjectArrayLocal, ContainerExpessionFill1DWithArrayInside) {
  I(R"(
{
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
print(arr)
})");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'get', g : [{ o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }, "
    "{ x : 0, y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g : [{ "
    "o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }]");
}

TEST_F(ObjectArrayLocal, ContainerExpessionFill1DWithArrayInsidePartial) {
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
{
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,arr:[{u:"get"}]}]
print(arr)
})");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'get', g : [{ o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }, "
    "{ x : 0, y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g : [{ "
    "o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }, { o : 0 }] }] }]");
}
TEST_F(ObjectArrayLocal,
       ContainerExpessionFill1DWithArrayInsideMoreValuesDefault) {
  I(R"(
{
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
print(arr)
})");
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

TEST_F(ObjectArrayLocal,
       ContainerExpessionFill1DWithArrayInsideMoreValuesDefaultPartial) {
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
{
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,arr:[{u:"get"}]}]
print(arr)
})");
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

TEST_F(ObjectArrayLocal,
       ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefault) {
  I(R"(
{
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
print(arr)
}
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'get', g : [{ o : 100, s : 'hello', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : "
    "0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }] }]");
}

TEST_F(ObjectArrayLocal,
       ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultPartial) {
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
{
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,arr:[{u:"get",g:[{o:100,s:"hello"}]}]}]
print(arr)
}
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'get', g : [{ o : 100, s : 'hello', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : "
    "0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }] }]");
}

TEST_F(
    ObjectArrayLocal,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariable) {
  I(R"(
{
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
}
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : '', g "
    ": [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : "
    "0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b "
    ": false, arr : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : "
    "0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]");
}

TEST_F(
    ObjectArrayLocal,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariablePartial) {
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
{
var arrvar:t =  {x:2,y:"hello",a:3.3,b:true}
var arr:t[2] = [arrvar]
print(arr)
}
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : '', g "
    ": [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : "
    "0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b "
    ": false, arr : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : "
    "0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]");
}

TEST_F(
    ObjectArrayLocal,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArray) {
  I(R"(
{
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
}
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : "
    "0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }] }]");
}

TEST_F(
    ObjectArrayLocal,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArrayPartial) {
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
{
var arrvar:t =  {x:2,y:"hello",a:3.3,b:true,arr:[{u:"arru",g:[{o:102,s:"sora"}]}]}
var arr:t[2] = [arrvar]
print(arr)
}
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : "
    "0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }] }]");
}

TEST_F(
    ObjectArrayLocal,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArray2) {
  I(R"(
{
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
}
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : "
    "0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }] }]");
}

TEST_F(
    ObjectArrayLocal,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArray2Partial) {
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
{
var gka:k = {o:102,s:"sora"}
var arrvar:t =  {x:2,y:"hello",a:3.3,b:true,arr:[{u:"arru",g:[gka]}]}
var arr:t[2] = [arrvar]
print(arr)
}
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : "
    "0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }] }]");
}

TEST_F(
    ObjectArrayLocal,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArray3) {
  I(R"(
{
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
}
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : "
    "0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }] }]");
}

TEST_F(
    ObjectArrayLocal,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArray3Partial) {
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
{
var gka:k = {o:102,s:"sora"}
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,arr:[{u:"arru",g:[gka]}]}]
print(arr)
}
)");
  O("[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : "
    "0.00000000000000, b : false, arr : [{ u : '', g : [{ o : 0, s : '', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }] }]");
}

TEST_F(
    ObjectArrayLocal,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArrayWithFillExpression) {
  I(R"(
{
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
}
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
    ObjectArrayLocal,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArrayWithFillExpressionPartial) {
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
{
var gka:k = {o:102,s:"sora"}
var arr:t[3] = [2 fill {x:2,y:"hello",a:3.3,b:true,arr:[{u:"arru",g:[gka]}]}]
print(arr)
}
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
    ObjectArrayLocal,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArrayWithFillExpressionPrint) {
  I(R"(
{
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
}
)");
  O("{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }");
}

TEST_F(
    ObjectArrayLocal,
    ContainerExpessionFill1DWithArrayInsideMoreValuesSemiDefaultWithVariableAndNestedArrayWithFillExpressionPrintPartial) {
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
{
var gka:k = {o:102,s:"sora"}
var arr:t[3] = [{x:2,y:"hello",a:3.3,b:true,arr:[{u:"arru",g:[gka]}]}]
print(arr[0])
}
)");
  O("{ x : 2, y : 'hello', a : 3.30000000000000, b : true, arr : [{ u : "
    "'arru', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : "
    "0, s : '', d : 0.00000000000000, i : 0 }] }] }");
}

TEST_F(ObjectArrayLocal, PrintArrayInsideObjectDefault) {
  I(R"(
{
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
}
)");
  O("[0, 0][0.00000000000000, 0.00000000000000]['', ''][false, false]{ x : 2, "
    "y : [0, 0], b : [0.00000000000000, 0.00000000000000], c : ['', ''], d : "
    "[false, false], f : '' }");
}
TEST_F(ObjectArrayLocal, PrintArrayInsideObjectDefaultPartial) {
  I(R"(

    type p = {
    x:int,
    y:int[2],
    b:deci[2],
    c:str[2],
    d:bool[2],
    f:str
}
{
var x:p = {x:2}
print(x.y)
print(x.b)
print(x.c)
print(x.d)
print(x.f)
print(x)
}
)");
  O("[0, 0][0.00000000000000, 0.00000000000000]['', ''][false, false]{ x : 2, "
    "y : [0, 0], b : [0.00000000000000, 0.00000000000000], c : ['', ''], d : "
    "[false, false], f : '' }");
}

TEST_F(ObjectArrayLocal, PrintArrayInsideObject) {
  I(R"(
{
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
}
)");
  O("[5, 5][2.20000000000000, 0.00000000000000]['hello', ''][true, true]{ x : "
    "2, y : [5, 5], b : [2.20000000000000, 0.00000000000000], c : ['hello', "
    "''], d : [true, true], f : '' }");
}

TEST_F(ObjectArrayLocal, PrintArrayInsideObjectPartial) {
  I(R"(

    type p = {
    x:int,
    y:int[2],
    b:deci[2],
    c:str[2],
    d:bool[2],
    f:str
}
{
var x:p = {x:2,y:[2 fill 5],b:[1 fill 2.2],c:["hello"],d:[true,true]}
print(x.y)
print(x.b)
print(x.c)
print(x.d)
print(x.f)
print(x)
}
)");
  O("[5, 5][2.20000000000000, 0.00000000000000]['hello', ''][true, true]{ x : "
    "2, y : [5, 5], b : [2.20000000000000, 0.00000000000000], c : ['hello', "
    "''], d : [true, true], f : '' }");
}

TEST_F(ObjectArrayLocal, PrintArrayInsideObjectComplex) {
  I(R"(
{
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
}
)");
  O("2hello3.30000000000000true[{ u : 'arru', g : [{ o : 102, s : 'sora', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }]{ x : 0, y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g "
    ": [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : "
    "0.00000000000000, i : 0 }] }] }");
}

TEST_F(ObjectArrayLocal, PrintArrayInsideObjectComplexPartial) {
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
{
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
}
)");
  O("2hello3.30000000000000true[{ u : 'arru', g : [{ o : 102, s : 'sora', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }]{ x : 0, y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g "
    ": [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : "
    "0.00000000000000, i : 0 }] }] }");
}

TEST_F(ObjectArrayLocal, PrintArrayInsideObjectComplex2) {
  I(R"(
{
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
}
)");
  O("2hello3.30000000000000true[{ u : 'arru', g : [{ o : 102, s : 'sora', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }]{ x : 0, y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g "
    ": [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : "
    "0.00000000000000, i : 0 }] }] }");
}

TEST_F(ObjectArrayLocal, PrintArrayInsideObjectComplex2Partial) {
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
{
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
}
)");
  O("2hello3.30000000000000true[{ u : 'arru', g : [{ o : 102, s : 'sora', d : "
    "0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 "
    "}] }]{ x : 0, y : '', a : 0.00000000000000, b : false, arr : [{ u : '', g "
    ": [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : "
    "0.00000000000000, i : 0 }] }] }");
}

TEST_F(ObjectArrayLocal, VariableExpression1) {
  I(R"(
{
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
}
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

TEST_F(ObjectArrayLocal, VariableExpression1Partial) {
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
{
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
}
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

TEST_F(ObjectArrayLocal, ArrayDeclarationUsingAnotherVariable) {
  I(R"(
{
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
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(ObjectArrayLocal, ArrayDeclarationUsingAnotherVariablePartial) {
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
{
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var arr2:t[2] = arr
print(arr2)
print("\n")
print(arr2[0].ar[0].g[0].d)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(ObjectArrayLocal, ArrayDeclarationUsingAnotherVariableObjectFill) {
  I(R"(
{
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
}
)");
  O(R"([{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(ObjectArrayLocal,
       ArrayDeclarationUsingAnotherVariableObjectFillPartail) {
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
{
var arr2:t[2] = [1 fill {y:"j",a:2.2}]
print(arr2)
print("\n")
print(arr2[0].ar[0].g[0].d)
}
)");
  O(R"([{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(ObjectArrayLocal, ArrayDeclarationUsingAnotherVariableObjectExpression) {
  I(R"(
{
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
}
)");
  O(R"([{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(ObjectArrayLocal,
       ArrayDeclarationUsingAnotherVariableObjectExpressionPartial) {
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
{
var arr2:t[2] =[{y:"j",a:2.2}]
print(arr2)
print("\n")
print(arr2[0].ar[0].g[0].d)
}
)");
  O(R"([{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(ObjectArrayLocal,
       ArrayDeclarationUsingAnotherVariableObjectExpressionAssignment) {
  I(R"(
{
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
}
)");
  O(R"([{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(ObjectArrayLocal,
       ArrayDeclarationUsingAnotherVariableObjectExpressionAssignmentPartial) {
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
{
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var arr2:t[2] = [1 fill {y:"j",a:2.2}]
print(arr2)
arr2 = arr
print("\n")
print(arr2)
print("\n")
print(arr2[0].ar[0].g[0].d)
}
)");
  O(R"([{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectExpressionAssignmentPartialInt) {
  I(R"(
{
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
}
)");
  O(R"([{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
[{ x : 2, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectExpressionAssignmentPartialIntPartial) {
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
{
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var arr2:t[2] = [1 fill {y:"j",a:2.2}]
print(arr2)
arr2[0].x = arr[0].x
print("\n")
print(arr2)
print("\n")
print(arr2[0].ar[0].g[0].d)
}
)");
  O(R"([{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
[{ x : 2, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
0.00000000000000)");
}

TEST_F(ObjectArrayLocal, ArrayDeclarationUsingAnotherVariableObjectTest) {
  I(R"(
{
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
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
[{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }])");
}
TEST_F(ObjectArrayLocal,
       ArrayDeclarationUsingAnotherVariableObjectTestPartial) {
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
{
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var arr2:t[2] = [1 fill {y:"j",a:2.2}]
print(arr)
print("\n")
var p:int[2] = [1,2]
arr[0] = arr2[0]
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
[{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }])");
}

TEST_F(ObjectArrayLocal,
       ArrayDeclarationUsingAnotherVariableObjectTestPartial2) {
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
{
print(arr)
print("\n")
var p:int[2] = [1,2]
arr[0] = arr2[0]
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
[{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }])");
}

TEST_F(ObjectArrayLocal,
       ArrayDeclarationUsingAnotherVariableObjectTestPartial3) {
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
{
arr[0] = arr2[0]
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
[{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }])");
}

TEST_F(ObjectArrayLocal,
       ArrayDeclarationUsingAnotherVariableObjectTestPartial4) {
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
{
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }]
[{ x : 0, y : 'j', a : 2.20000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }])");
}

TEST_F(ObjectArrayLocal,
       ArrayDeclarationUsingAnotherVariableObjectTestInitTest) {
  I(R"(
{
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
}
)");
  O(R"([{ x : 0, y : '', a : 3.50000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }])");
}

TEST_F(ObjectArrayLocal,
       ArrayDeclarationUsingAnotherVariableObjectTestInitTestPartial) {
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
{
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12}]}]}]
print(sec)
}
)");
  O(R"([{ x : 0, y : '', a : 3.50000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0 }, { o : 0, s : '', d : 0.00000000000000, i : 0 }] }] }])");
}

TEST_F(ObjectArrayLocal,
       ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2) {
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
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(sec)
}
)");
  O(R"([{ x : 0, y : '', a : 3.50000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(ObjectArrayLocal,
       ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2Partial) {
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
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(sec)
}
)");
  O(R"([{ x : 0, y : '', a : 3.50000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(ObjectArrayLocal,
       ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2Assign) {
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
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(arr)
print("\n")
arr[0].ar[0].g[0].ob = sec[0].ar[0].g[0].ob
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPartial) {
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
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(arr)
print("\n")
arr[0].ar[0].g[0].ob = sec[0].ar[0].g[0].ob
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}
TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPartial2) {
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
{
arr[0].ar[0].g[0].ob = sec[0].ar[0].g[0].ob
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPartial3) {
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
{
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitive) {
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
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(arr)
print("\n")
arr[0].ar[0].g[0].ob.i = sec[0].ar[0].g[0].ob.i
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 200, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitivePartial) {
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
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(arr)
print("\n")
arr[0].ar[0].g[0].ob.i = sec[0].ar[0].g[0].ob.i
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 200, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitivePartial2) {
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
{
arr[0].ar[0].g[0].ob.i = sec[0].ar[0].g[0].ob.i
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 200, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitivePartial3) {
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
{
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 200, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArray) {
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
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(arr)
print("\n")
arr = []
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayPartial) {
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
var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}]
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
print(arr)
print("\n")
arr = []
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayPartial2) {
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
{
arr = []
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig) {
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
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 0, y : '', a : 3.50000000000000, b : false, ar : [{ u : '', g : [{ o : 102, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRigPartial) {
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
{
arr[0].x = sec[0].x
arr[0].y = sec[0].y
arr[0].a = sec[0].a 
arr[0].b = sec[0].b 
arr[0].ar[0].u =  sec[0].ar[0].u 
arr[0].ar[0].g[0].s = sec[0].ar[0].g[0].s 
arr[0].ar[0].g[0].i = sec[0].ar[0].g[0].i 
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 0, y : '', a : 3.50000000000000, b : false, ar : [{ u : '', g : [{ o : 102, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRigPartial2) {
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
{
print(arr)
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 0, y : '', a : 3.50000000000000, b : false, ar : [{ u : '', g : [{ o : 102, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig2) {
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
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig2Partial) {
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
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}
TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig2Partial2) {
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
{
arr[0].x = sec[0].x
arr[0].y = sec[0].y
arr[0].a = sec[0].a 
arr[0].b = sec[0].b 
arr[0].ar[0].u =  sec[0].ar[0].u 
arr[0].ar[0].g = sec[0].ar[0].g
arr[1].ar[0].g = sec[0].ar[0].g 
print(arr[1])
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig2Partial3) {
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
{
print(arr[1])
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig3) {
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
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig3Partial) {
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
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig3Partial2) {
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
{
arr[0].x = sec[0].x
arr[0].y = sec[0].y
arr[0].a = sec[0].a 
arr[0].b = sec[0].b 
arr[0].ar[0].u =  sec[0].ar[0].u 
arr[0].ar[0].g = sec[0].ar[0].g
arr[1].ar[0] = sec[0].ar[0]
print(arr[1])
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig3Partial3) {
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
{
print(arr[1])
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig4) {
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
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig4Partial) {
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
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig4Partial1) {
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
{
print(arr[1])
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayDeclarationUsingAnotherVariableObjectTestInitTestComplex2AssignPrimitiveAssignWithEmptyArrayRig4Partial2) {
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
{
arr[0].x = sec[0].x
arr[0].y = sec[0].y
arr[0].a = sec[0].a 
arr[0].b = sec[0].b 
arr[0].ar[0].u =  sec[0].ar[0].u 
arr[0].ar[0].g = sec[0].ar[0].g
arr[1].ar[0] = sec[0].ar[0]

print(arr[1])
}
)");
  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : 'god', d : 0.00000000000000, i : 12, ob : { i : 200, s : 'some' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(ObjectArrayLocal, ArrayInsideObjectAcess) {
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

TEST_F(ObjectArrayLocal, ArrayInsideObjectAcess1) {
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

TEST_F(ObjectArrayLocal, ArrayInsideObjectAcessLocal) {
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

TEST_F(ObjectArrayLocal, ArrayInsideObjectAcessRig) {
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
 }
    )");

  O(R"(00Hello2.30000000000000{ i : 0, s : 'g' }
000.00000000000000{ i : 0, s : '' })");
}
TEST_F(ObjectArrayLocal, ArrayInsideObjectAcessRigPartial) {
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
{
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
 }
    )");

  O(R"(00Hello2.30000000000000{ i : 0, s : 'g' }
000.00000000000000{ i : 0, s : '' })");
}

TEST_F(ObjectArrayLocal, ArrayInsideObjectAcessPassingAsParam) {
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
fun printF(ar:t[2])->nthg{
  ar[1].x = 100
  ar[1].y = "Hello2"
  ar[1].a = 5.4
  ar[1].b = true 
  ar[1].ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
    print(ar)
}
printF(arr)
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : '', g : [{ o : 0, s : 'go', d : 43.30000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] }])");
}

TEST_F(ObjectArrayLocal,
       ArrayInsideObjectAcessPassingAsParamReturnFromFunction) {
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
fun printF(ar:t[2],ar2:t[2])->t[2]{
  ar[1].x = 100
  ar[1].y = "Hello2"
  ar[1].a = 5.4
  ar[1].b = true 
  ar[1].ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar 
}
print(printF(arr,arr))
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : '', g : [{ o : 0, s : 'go', d : 43.30000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] }])");
}

TEST_F(ObjectArrayLocal,
       ArrayInsideObjectAcessPassingAsParamReturnFromFunctionPreviousPersist) {
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
fun printF(ar:t[2],ar2:t[2])->t[2]{
  ar[1].x = 100
  ar[1].y = "Hello2"
  ar[1].a = 5.4
  ar[1].b = true 
  ar[1].ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar 
}
print(arr)

print("\n")

print(printF(arr,arr))

print("\n")

print(arr)
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : '', g : [{ o : 0, s : 'go', d : 43.30000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(ObjectArrayLocal, ArrayInsideObjectAcessPassingAsParamObject) {
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

var arr:t = {x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
fun printF(ar:t)->nthg{
  ar.x = 100
  ar.y = "Hello2"
  ar.a = 5.4
  ar.b = true 
  ar.ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
    print(ar)
}
print(arr)
print("\n")
printF(arr)
print("\n")
print(arr)
    )");

  O(R"({ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] }
{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(ObjectArrayLocal, ArrayInsideObjectAcessPassingAsParamObjectReturning) {
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

var arr:t = {x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
fun printF(ar:t)->t{
  ar.x = 100
  ar.y = "Hello2"
  ar.a = 5.4
  ar.b = true 
  ar.ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}
print(arr)
print("\n")
print(printF(arr))
print("\n")
print(arr)
    )");

  O(R"({ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] }
{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(ObjectArrayLocal,
       ArrayInsideObjectAcessPassingAsParamObjectReturningInitializeGlobal) {
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

var arr:t = {x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
fun printF(ar:t)->t{
  ar.x = 100
  ar.y = "Hello2"
  ar.a = 5.4
  ar.b = true 
  ar.ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}
print(arr)
print("\n")
var newo:t = printF(arr)
print(newo)
print("\n")
print(arr)
    )");

  O(R"({ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] }
{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(ObjectArrayLocal,
       ArrayInsideObjectAcessPassingAsParamObjectReturningInitializeLocal) {
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

var arr:t = {x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
fun printF(ar:t)->t{
  ar.x = 100
  ar.y = "Hello2"
  ar.a = 5.4
  ar.b = true 
  ar.ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}
print(arr)
print("\n")
{
  var newo:t = printF(arr)
print(newo)
}
print("\n")
print(arr)
    )");

  O(R"({ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] }
{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(ObjectArrayLocal,
       ArrayInsideObjectAcessPassingAsParamObjectReturningInitializeLocal2) {
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

fun printF(ar:t)->t{
  ar.x = 100
  ar.y = "Hello2"
  ar.a = 5.4
  ar.b = true 
  ar.ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}
{

var arr:t = {x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]

print(arr)
print("\n")
  var newo:t = printF(arr)
print(newo)

print("\n")
print(arr)
}
    )");

  O(R"({ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] }
{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayInsideObjectAcessPassingAsParamObjectReturningInitializeAssignGlobal) {
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

var arr:t = {x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
fun printF(ar:t)->t{
  ar.x = 100
  ar.y = "Hello2"
  ar.a = 5.4
  ar.b = true 
  ar.ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}
print(arr)
print("\n")
arr = printF(arr)
print(arr)
print("\n")
print(arr)
    )");

  O(R"({ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] }
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayInsideObjectAcessPassingAsParamObjectReturningInitializeAssignlocal) {
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

var arr:t = {x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
fun printF(ar:t)->t{
  ar.x = 100
  ar.y = "Hello2"
  ar.a = 5.4
  ar.b = true 
  ar.ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}
print(arr)
print("\n")
{

arr = printF(arr)
}
print(arr)
print("\n")
print(arr)
    )");

  O(R"({ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] }
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] })");
}
TEST_F(
    ObjectArrayLocal,
    ArrayInsideObjectAcessPassingAsParamObjectReturningInitializeAssignlocal2) {
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

var arr:t = {x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
fun printF(ar:t)->t{
  ar.x = 100
  ar.y = "Hello2"
  ar.a = 5.4
  ar.b = true 
  ar.ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}
print(arr)
print("\n")
{

arr = printF(arr)

print(arr)
}
print("\n")
print(arr)
    )");

  O(R"({ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] }
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayInsideObjectAcessPassingAsParamObjectReturningInitializeAssignlocal3) {
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

fun printF(ar:t)->t{
  ar.x = 100
  ar.y = "Hello2"
  ar.a = 5.4
  ar.b = true 
  ar.ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}
{

var arr:t = {x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[gka]}]}
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]

print(arr)
print("\n")
arr = printF(arr)

print(arr)

print("\n")
print(arr)
}
    )");

  O(R"({ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] }
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    ArrayInsideObjectAcessPassingAsParamObjectReturningInitializeAssignlocalPassingIndex) {
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
fun printF(ar:t)->t{
  ar.x = 100
  ar.y = "Hello2"
  ar.a = 5.4
  ar.b = true 
  ar.ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}
print(arr)
print("\n")
arr[1] = printF(arr[0])
print(arr)
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] }])");
}
TEST_F(
    ObjectArrayLocal,
    ArrayInsideObjectAcessPassingAsParamObjectReturningInitializeAssignlocalPassingIndexContainer) {
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
fun getOne(ar:t)->t{
  ar.x = 100
  ar.y = "Hello2"
  ar.a = 5.4
  ar.b = true 
  ar.ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}

fun getTwo(ar:t)->t{
  ar.x = 200
  ar.y = "Hello4"
  ar.b = false 
  ar.ar = [{u:"s",g:[{d:55.3,s:"no"},{ob:{s:"bye",i:40}}]}]
  return ar
}


print(arr)
print("\n")
arr[1] = getTwo(getOne(arr[0]))
print(arr)
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 200, y : 'Hello4', a : 5.40000000000000, b : false, ar : [{ u : 's', g : [{ o : 102, s : 'no', d : 55.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 40, s : 'bye' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayInsideObjectAcessPassingAsParamObjectReturningInitializeAssignlocalPassingIndexContainerKeepingOld) {
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
fun getOne(ar:t)->t{
  ar.x = 100
  ar.y = "Hello2"
  ar.a = 5.4
  ar.b = true 
  ar.ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}
fun getTwo(ar:t)->t{
  ar.x = 200
  ar.y = "Hello4"
  ar.b = false 
  ar.ar = [{g:[{d:55.3,},{ob:{s:"bye",i:40}}]}]
  return ar
}
print(arr)
print("\n")
arr[1] = getTwo(getOne(arr[0]))
print(arr)
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 200, y : 'Hello4', a : 5.40000000000000, b : false, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 55.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 40, s : 'bye' } }] }] }])");
}

TEST_F(
    ObjectArrayLocal,
    ArrayInsideObjectAcessPassingAsParamObjectReturningInitializeAssignlocalPassingIndexContainerKeepingOlMultiFun) {
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

fun getOne(ar:t)->t{
  ar.x = 100
  ar.y = "Hello2"
  ar.a = 5.4
  ar.b = true 
  ar.ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}

fun getTwo(ar:t)->t{
  ar.x = 200
  ar.y = "Hello4"
  ar.b = false 
  ar.ar = [{g:[{d:55.3,},{ob:{s:"bye",i:40}}]}]
  return ar
}


print(arr)
print("\n")
var tm:t = getOne(getTwo(arr[0]))
print(tm)
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
{ x : 100, y : 'Hello2', a : 5.40000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 43.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 20, s : 'hi' } }] }] })");
}

TEST_F(ObjectArrayLocal, PassingCalledFunctionAsArg) {
  I(R"(

fun getOne() -> int {
    return 2
}
fun getDeci(num:int) -> deci {
    return 3.2 * num
}

print(getDeci(getOne()))
    )");

  O(R"(6.40000000000000)");
}
TEST_F(ObjectArrayLocal, PassingCalledFunctionAsArg2) {
  I(R"(

fun getOne() -> int {
    return 2
}
fun getDeci(num:int,p:deci) -> deci {
    return 3.2 * num * p 
}

print(getDeci(getOne(),2.3))
    )");

  O(R"(14.72000000000000)");
}
TEST_F(ObjectArrayLocal, PassingCalledFunctionAsArg2WithStr) {
  I(R"(

fun getOne() ->  str {
    return "One"
}
fun getDeci(num:str) -> str {
    return  num + "two" 
}

print(getDeci(getOne()))
    )");

  O(R"(Onetwo)");
}

TEST_F(ObjectArrayLocal, PassingCalledFunctionAsArg2WithArray) {
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
fun getOne(ar:t[2])->t[2]{
  ar[0].x = 100
  ar[0].y = "Hello2"
  ar[0].a = 5.4
  ar[0].b = true 
  ar[0].ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}

fun getTwo(ar:t[2])->t[2]{
  ar[0].x = 200
  ar[0].y = "Hello4"
  ar[0].b = false 
  ar[0].ar = [{g:[{d:55.3,},{ob:{s:"bye",i:40}}]}]
  return ar
}


print(arr)
print("\n")
arr = getTwo(getOne(arr))
print(arr)
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 200, y : 'Hello4', a : 5.40000000000000, b : false, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 55.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 40, s : 'bye' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(ObjectArrayLocal, PassingCalledFunctionAsArg2WithArray2) {
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
fun getOne(ar:t[2])->t[2]{
  ar[0].x = 100
  ar[0].y = "Hello2"
  ar[0].a = 5.4
  ar[0].b = true 
  ar[0].ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}

fun getTwo(ar:t[2])->t[2]{
  ar[0].x = 200
  ar[0].y = "Hello4"
  ar[0].b = false 
  ar[0].ar = [{g:[{d:55.3,},{ob:{s:"bye",i:40}}]}]
  return ar
}


print(arr)
print("\n")
print(getTwo(getOne(arr)))
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 200, y : 'Hello4', a : 5.40000000000000, b : false, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 55.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 40, s : 'bye' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(ObjectArrayLocal, PassingCalledFunctionAsArg2WithArray2Local) {
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
fun getOne(ar:t[2])->t[2]{
  ar[0].x = 100
  ar[0].y = "Hello2"
  ar[0].a = 5.4
  ar[0].b = true 
  ar[0].ar = [1 fill {g:[{d:43.3,s:"go"},{ob:{s:"hi",i:20}}]}]
  return ar
}

fun getTwo(ar:t[2])->t[2]{
  ar[0].x = 200
  ar[0].y = "Hello4"
  ar[0].b = false 
  ar[0].ar = [{g:[{d:55.3,},{ob:{s:"bye",i:40}}]}]
  return ar
}

{

print(arr)
print("\n")
print(getTwo(getOne(arr)))
}
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]
[{ x : 200, y : 'Hello4', a : 5.40000000000000, b : false, ar : [{ u : 'get', g : [{ o : 102, s : 'go', d : 55.30000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 40, s : 'bye' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(ObjectArrayLocal, InitializeArrayObjectWithFun) {
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
fun getGKA() -> k {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}

    return gka 
  }

var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:[getGKA()]}]}]
print(arr)
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(ObjectArrayLocal, InitializeArrayObjectWithFunArray) {
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
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

var arr:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:getGKA()}]}]
print(arr)
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(ObjectArrayLocal, InitializeArrayObjectWithFunArrayMultiple) {
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
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }
fun getArr()-> t[2] {
var a:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:getGKA()}]}]
return a
  }
var arr:t[2] = getArr()
print(arr)
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(ObjectArrayLocal, InitializeArrayObjectWithFunArrayMultipleLocal) {
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
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }
fun getArr()-> t[2] {
var a:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:getGKA()}]}]
return a
  }
{
  var arr:t[2] = getArr()
print(arr)
}
    )");

  O(R"([{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(ObjectArrayLocal, InitializeArrayObjectWithFunArrayMultipleLocal2) {
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
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }
fun getArr()-> t[2] {
var a:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:getGKA()}]}]
return a
  }
var arr:t[2] =[{x:300,y:"eee",a:4.3,b:true,ar:[{g:getGKA()}]}]
print(arr)
print("\n\n")
arr = getArr()
print(arr)
arr[0].ar[0].g = getGKA()
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
    )");

  O(R"([{ x : 300, y : 'eee', a : 4.30000000000000, b : true, ar : [{ u : '', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]

[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(ObjectArrayLocal, InitializeArrayObjectWithFunArrayMultipleLocal2GKA) {
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
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }
fun getArr()-> t[2] {
var a:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:getGKA()}]}]
return a
  }

  var arr:t[2] =[{x:300,y:"eee",a:4.3,b:true,ar:[{g:getGKA()}]}]
print(arr)
print("\n\n")
arr = getArr()
print(arr)
{
arr[0].ar[0].g = getGKA()
}
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]

    )");

  O(R"([{ x : 300, y : 'eee', a : 4.30000000000000, b : true, ar : [{ u : '', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]

[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(ObjectArrayLocal,
       InitializeArrayObjectWithFunArrayMultipleLocal2GKALocal) {
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
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }
fun getArr()-> t[2] {
var a:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:getGKA()}]}]
return a
  }
{
  var arr:t[2] =[{x:300,y:"eee",a:4.3,b:true,ar:[{g:getGKA()}]}]
print(arr)
print("\n\n")
arr = getArr()
print(arr)
arr[0].ar[0].g = getGKA()
}
var sec:t[3] = [{a:3.5,ar:[{g:[{s:"god",i:12,ob:{s:"some",i:200}}]}]}]
    )");

  O(R"([{ x : 300, y : 'eee', a : 4.30000000000000, b : true, ar : [{ u : '', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]

[{ x : 2, y : 'hello', a : 3.30000000000000, b : true, ar : [{ u : 'get', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(ObjectArrayLocal,
       InitializeArrayObjectWithFunArrayMultipleLocal2GKAOBJECTFUN) {
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
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {x:243,y:"NO",a:2.3,b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }

var u:t  = {x:32}
print(u)
u = getT()
print("\n")
print(u)
    )");

  O(R"({ x : 32, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 243, y : 'NO', a : 2.30000000000000, b : true, ar : [{ u : 'eeet', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(ObjectArrayLocal,
       InitializeArrayObjectWithFunArrayMultipleLocal2GKAOBJECTFUN2) {
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
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {x:243,y:"NO",b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }

var u:t  = {x:32}
print(u)
u = getT()
print("\n")
print(u)
    )");

  O(R"({ x : 32, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 243, y : 'NO', a : 0.00000000000000, b : true, ar : [{ u : 'eeet', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(ObjectArrayLocal,
       InitializeArrayObjectWithFunArrayMultipleLocal2GKAOBJECTFUN2Initialize) {
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
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {x:243,y:"NO",b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }

var u:t  = getT()
print(u)

    )");

  O(R"({ x : 243, y : 'NO', a : 0.00000000000000, b : true, ar : [{ u : 'eeet', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(ObjectArrayLocal,
       InitializeArrayObjectWithFunArrayMultipleLocal2GKAOBJECTFUN2LOCAL) {
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
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {x:243,y:"NO",b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }

{
  var u:t  = {x:32}
print(u)
u = getT()
print("\n")
print(u)
}
    )");

  O(R"({ x : 32, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 243, y : 'NO', a : 0.00000000000000, b : true, ar : [{ u : 'eeet', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectArrayLocal,
    InitializeArrayObjectWithFunArrayMultipleLocal2GKAOBJECTFUN2InitializeLocal) {
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
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {x:243,y:"NO",b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }
{

var u:t  = getT()
print(u)
}

    )");

  O(R"({ x : 243, y : 'NO', a : 0.00000000000000, b : true, ar : [{ u : 'eeet', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

// #endif