#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hashmap.h"

// Initializes the hash map
void init(HashMap **map) {
	(*map) = malloc(sizeof(HashMap));
	(*map)->capacity = INIT_CAPACITY;
	(*map)->arr = malloc(sizeof(BucketNode *) * INIT_CAPACITY);
	(*map)->size = 0;
}

// Computes and returns the hash index for given key
static int hash_index(HashMap *map, char *key) {
	if(!key || !map)
		return -1;
	int l = strlen(key), i, code = 0;
	i = l - 1;
	while(i >= 0 && i > l - SUFFIX_LENGTH)
		code += (int)key[i--];
	return (code % map->capacity);
}

// Checks and returns if the hash map is overloaded for its capacity
static int overload(HashMap *map) {
	if(!map)
		return 0;
	return (map->size >= (LOAD_FACTOR * map->capacity));
}

// Adds an entry to hash table
static void add(HashMap **map, int hash_index, char *key, void *value) {
	if(!map)
		return;
	if(hash_index == -1) {
		return;
	}
	BucketNode *bucket = (*map)->arr[hash_index];
	if(!bucket) {
		// Sole entry
		(*map)->arr[hash_index] = malloc(sizeof(BucketNode));
		bucket = (*map)->arr[hash_index];
	} else {
		// Collision, perform separate chaining with list head cells
		do {
			if(!strcmp(bucket->key, key)) {
				bucket->value = value;
				return;
			}
			if(!bucket->next)
				break;
			bucket = bucket->next;
		} while(bucket->next != NULL);
		bucket->next = malloc(sizeof(BucketNode));
		bucket = bucket->next;
	}
	bucket->key = key;
	bucket->value = value;
	bucket->next = NULL;
	(*map)->size += 1;
	return;
}

// Resizes, rehashes and repopulates the hash map with doubled capacity
static void rehash(HashMap **map) {
	int i, i_new, old_cap = (*map)->capacity;
	// Double the capacity
	(*map)->capacity *= 2;
	// Reset size (as it will be overwritten)
	(*map)->size = 0;
	// Maintain link to old bucket list
	BucketNode **old = (*map)->arr;
	// Allocate new memory to bucket list in map
	(*map)->arr = malloc(sizeof(BucketNode *) * (*map)->capacity);
	BucketNode *node;
	// Rehash all entries and repopulate the map
	for(i = 0 ; i < old_cap ; i++) {
		node = old[i];
		while(node) {
			i_new = hash_index(*map, node->key);
			add(map, i_new, node->key, node->value);
			node = node->next;
		}
	}
	free(old);
	return;
}

// Adds given key value pair to hash map (replaces for duplicate key)
void put(HashMap **map, char *key, void *value) {
	if(!(*map))
		return;
	if(!key)
		return;
	int i = hash_index(*map, key);
	add(map, i, key, value);
	// Check if hash map is overloaded
	if(overload(*map))
		rehash(map);
	return;
}

// Returns value corresponding to given key
void * get(HashMap *map, char *key) {
	if(!map)
		return NULL;
	int i = hash_index(map, key);
	BucketNode *bucket = map->arr[i];
	while(bucket != NULL) {
		if(!strcmp(bucket->key, key))
			return bucket->value;
		bucket = bucket->next;
	}
	return NULL;
}

// Deletes value (and key, when no more values) corresponding to given key
void del(HashMap **map, char *key) {
	if(!(*map))
		return;
	BucketNode *prev = NULL, *bucket;
	// Obtain hash index
	int i = hash_index(*map, key);
	// Obtain bucket
	bucket = (*map)->arr[i];
	while(bucket != NULL) {
		// Check for key match
		if(!strcmp(bucket->key, key)) {
			if(prev) {
				// More than 1 buckets
				prev->next = bucket->next;
			} else {
				// Only bucket
				(*map)->arr[i] = NULL;
			}
			(*map)->size -= 1;
			return;
		}
		prev = bucket;
		bucket = bucket->next;
	}
	return;
}

// Returns 1 if hash map is empty, 0 otherwise
int empty(HashMap *map) {
	if(!map)
		return 1;
	return (map->size == 0 ? 1 : 0);
}

// Prints all the entries of hash map
void print(HashMap *map) {
	if(!map)
		return;
	int i;
	BucketNode *node;
	printf("Map:\n");
	for(i = 0 ; i < map->capacity ; i++) {
		node = map->arr[i];
		while(node) {
			printf("(%s, %s)\n", node->key, (char *)(node->value));
			node = node->next;
		}
	}
	printf("%d item(s)\n", map->size);
	return;
}

// Frees up all the memory being used, init() must be called to reinitialize
void free_map(HashMap **map) {
	if(!(*map))
		return;
	int i;
	BucketNode *node;
	for(i = 0 ; i < (*map)->capacity ; i++) {
		node = (*map)->arr[i];
		while(node) {
			free(node);
			node = node->next;
		}
	}
	free(*map);
}
