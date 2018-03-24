#include<stdio.h>
#include "hashmap.h"

void main() {

	// Keys and values
        char *a = "a", *b = "b", *m = "m";
        char *x = "Hello", *y = "World", *z = "Mello";

	// Declare and initialize map
        HashMap *hashMap;
	init(&hashMap);

	// Add keys and values
        put(&hashMap, b, y);
        put(&hashMap, a, x);
        put(&hashMap, b, y);
        put(&hashMap, m, z);

	// Print map entries
        print(hashMap);

	// Get values for specific keys
        printf("Value for key %s: %s\n", a, (char *)get(hashMap, a));
        printf("Value for key %s: %s\n", m, (char *)get(hashMap, m));

	// Delete values against keys
        del(&hashMap, b);
        del(&hashMap, a);
        del(&hashMap, m);

	// Verify
        print(hashMap);

	// Delete all values
        del(&hashMap, m);

	// Clean up map
        free_map(&hashMap);

	// Reinitialize and use
	init(&hashMap);
        put(&hashMap, b, y);
        print(hashMap);

	// Clean up
        free_map(&hashMap);

	return;
}
