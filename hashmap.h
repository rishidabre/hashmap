#ifndef hashmap
#define hashmap

#define INIT_CAPACITY 16
#define LOAD_FACTOR 0.75
#define SUFFIX_LENGTH 5 

// Bucket for holding key and value
typedef struct BucketList {
	char *key;
	void *value;
	struct BucketList *next;
} BucketNode;

// Main HashMap structure
typedef struct HashMap {
	BucketNode **arr;
	int size;
	int ksize;
	int capacity;
	int load_factor;
} HashMap;

// Initializes the hash map
void init(HashMap **cash);

// Adds given key value pair to hash map (replaces for duplicate key)
void put(HashMap **map, char *key, void *value);

// Returns value corresponding to given key
void * get(HashMap *map, char *key);

// Deletes value (and key, when no more values) corresponding to given key
void del(HashMap **map, char *key);

// Returns 1 if hash map is empty, 0 otherwise
int empty(HashMap *map);

// Prints all the entries of hash map
void print(HashMap *map);

// Frees up all the memory being used, init() must be called to reinitialize
void free_map(HashMap **map);

#endif
