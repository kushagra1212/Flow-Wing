---
sidebar_position: 3
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Map Module 

## Overview

The `Map` module provides a data structure that allows you to store key-value pairs, enabling efficient retrieval and management of data. It supports various operations such as insertion, retrieval, checking for existence, and removal of key-value pairs.

## Types

### Map::String

The `Map::String` type represents a map where both keys and values are of type `string`. It provides methods to manipulate the map efficiently.

## Functions

### `new Map::String()`

Creates a new instance of a string map.

#### Returns
- `Map::String`: A new empty string map.

### `insert(key: str, value: str)`

Inserts a key-value pair into the map.

#### Parameters
- `key`: The key to be inserted into the map.
- `value`: The value associated with the key.

### `get(key: str) -> str`

Retrieves the value associated with the specified key.

#### Parameters
- `key`: The key whose value needs to be retrieved.

#### Returns
- `str`: The value associated with the key, or `null` if the key does not exist.

### `contains(key: str) -> bool`

Checks whether the map contains the specified key.

#### Parameters
- `key`: The key to check for existence in the map.

#### Returns
- `bool`: `true` if the key exists, otherwise `false`.

### `remove(key: str)`

Removes the key-value pair associated with the specified key.

#### Parameters
- `key`: The key to be removed from the map.

### `free()`

Frees the memory allocated for the map.

## Example Usage

<CodeBlock code={
`var m: Map::String = new Map::String()
  m.insert("key1", "value1")
  m.insert("key2", "value2")
  m.insert("key3", "value3")
  m.insert("key4", "value4")
  
  print(m.get("key1"))      
  print(m.get("key2"))   
  print(m.contains("key3")) 
  
  m.remove("key3")
  print(m.contains("key3")) 
  
  m.free()
`} language="fg"/>