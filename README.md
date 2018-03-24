# hashmap
A simple working implementation of HashMap in C.

## Overview
This map can be used to map objects, or more precisely their addresses, against string keys. The index for a given key is computed using a hash function and the correponding pair is then inserted in map. In case of collisions, values are replaced for equal (by value) keys and chained ([separate chaining with list head cells](https://en.wikipedia.org/wiki/Hash_table#Separate_chaining_with_list_head_cells)) for different keys. Also, the map doubles its capacity in case it is more than 75% full and rehashes all its entries.

The hash function uses the formula `index = s % c` for calculating the index of keys in the array where,
- s is the sum of ASCII codes of last 5 (at max, or less as applicable) characters of key
- c is the current capacity of map

Refer to [hashmap.h](hashmap.h) for the internal data structures used.

*Note: This module was built and tested on Ubuntu 16.04 LTS with gcc version 5.4.0.*

## Specifications
- Initial capacity  : 16
- Load factor       : 0.75
- Key type          : `char *`
- Value type        : `void *` (or specifically, no specific type)

## Functions

`void init(HashMap **map)`
- Initializes the hash map, must be called before using map

`void put(HashMap **map, char *key, void *value)`
- Adds given key value pair to hash map (replaces for duplicate key)

`void * get(HashMap *map, char *key)`
- Returns value corresponding to given key

`void del(HashMap **map, char *key)`
- Deletes value (and key, when no more values remain) corresponding to given key

`int empty(HashMap *map)`
- Returns 1 if hash map is empty, 0 otherwise

`void print(HashMap *map)`
- Prints all the entries of hash map

`void free_map(HashMap **map)`
- Frees up all the memory used by internal data structures, init() must be called to reinitialize

## Usage
To prevent some internal functions from being exposed outside the module, using the precompiled static library is recommended.

### Using static library
Download the header file [hashmap.h](hashmap.h), static library [libhmap.a](libhmap.a) and the included example [demo.c](demo.c) in a new directory. Run the following command:

`gcc demo.c -L . -lhmap`

You shall see the following result:

```
Map:
(a, Hello)
(b, World)
(m, Mello)
3 item(s)
Value for key a: Hello
Value for key m: Mello
Map:
0 item(s)
Map:
(b, World)
1 item(s)
```

#### Recompiling
Should you wish to make any changes in the source files and recompile the library, you can do so as follows:
```
rm libhmap.a hashmap.o
gcc hashmap.h hashmap.c -c
ar -vq libhmap.a hashmap.o
```

### Using source files
Download the main source file [hashmap.c](hashmap.c) and the header file [hashmap.h](hashmap.h) in your project directory. Now instead of the header file, include the main file in your module as follows:

`#include "hashmap.c"`

Your module shall compile without errors.

## References
[1] https://en.wikipedia.org/wiki/Hash_table
