#include <stdio.h>
#include <stdlib.h>

typedef struct{
    void* key;
    void* value;
}ht_item;

typedef int (*HashFunction) (void* key, int capacity);


typedef struct
{   
    //items here is a pointer to an array of pointers
    //Each of those pointers points to a ht_item struct

    /*
    items ──►  [ ptr ]──► ht_item { key: "apple", value: "red" }
               [ ptr ]──► ht_item { key: "banana", value: "yellow" }
               [ ptr ]──► NULL
    */
    ht_item** items;       
    int initialCapacity;
    int capacity;
    int size;
    HashFunction hashfunction;
}hashtable;


//this is a generic hashfunction signatures
//the user will provide a hash function based on the key type



hashtable createHashTable(HashFunction hashfunction){
   hashtable table;
   table.size = 0;
   table.initialCapacity = 100;
   table.capacity = table.initialCapacity;
   table.items = malloc(sizeof(ht_item*) * table.initialCapacity);
   table.hashfunction = hashfunction;

   if(table.items == NULL){
    printf("Memory allocation failed\n");
    exit(1);
   }

   return table;
}

int stringHash(void* key, int capacity){
    int hash = 0;
    char* k =(char*)key;
    for (int i = 0; k[i] != '\0'; i++) {
    hash = (hash * 31 + k[i]) % capacity;
    }
    return hash;
}

int intHash(void* key, int capacity){

    //(int *) --> we tell the compiler treat this as a pointer to an int instead of pointing to unknown type
    // then deferencing to int value
    int k = *(int*)key;
    return k % capacity;
}



// void put(hashtable* table, char* key, int value){
//     if(get(table ,  key)) 
//     int index = hash(key , table->capacity);
//     table->items[index] = value;
//     table->size++;
// }

// int get(hashtable* table, char* key){
//     int index = hash(key, table->capacity);
//     return table->items[index];
// }

// int size(hashtable* table){
//     return table->size;
// }

// void clear(hashtable* table){
//     free(table);
// }

int main() {
    int array[50];
    hashtable table = createHashTable(stringHash);
    // put(&table, "king", 10);
    // put(&table, "lion", 20);
    // put(&table, "zeko", 30);
    // put(&table, "lolo", 20);
    // put(&table, "lolo", 15);
    
    // printf("%d\n", get(&table ,"boda"));
    // printf("%d\n", size(&table));

    return 0;
}