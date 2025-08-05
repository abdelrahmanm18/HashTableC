#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*HashFunction) (void* key, int capacity);
typedef int (*ComapreFunction) (void* a, void* b);

typedef struct{
    void* key;
    void* value;
    ht_item* next;
}ht_item;



typedef struct
{   
    //buckets here is a pointer to an array of pointers
    //Each of those pointers points to a ht_item struct

    /*
    buckets ──►  ptr ──► ht_item { key: "eg", value: "egypt" }
               ptr ──► ht_item { key: "fr", value: "france" }
               ptr ──► NULL
    */
    ht_item** buckets;       
    int initialCapacity;
    int capacity;
    int size;
    HashFunction hashfunction;
    ComapreFunction comparefunction;
}hashtable;


//this is a generic hashfunction signatures
//the user will provide a hash function based on the key type



hashtable createHashTable(HashFunction hashfunction, ComapreFunction comparefunction){
   hashtable table;
   table.size = 0;
   table.initialCapacity = 100;
   table.capacity = table.initialCapacity;
   table.buckets = malloc(sizeof(ht_item*) * table.initialCapacity);
   table.hashfunction = hashfunction;

   if(table.buckets == NULL){
    printf("Memory allocation failed\n");
    exit(1);
   }

   return table;
}

//helper methods for hashing and comparing keys

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

int intCompare(void* a, void* b){
    return *(int*)a != *(int*)b;
}

int stringCompare(void* a, void* b){
    return strcmp((char*) a, (char*)b);
}


void put(hashtable* table, void* key, void* value){
    int index = table->hashfunction(key , table->capacity);
    ht_item* current = table->buckets[index];
    while(current != NULL){
        if(table->comparefunction(current->key,key) == 0){
            current->value = value;
            return;
        }
        current = current->next;
    }

    ht_item* item = malloc(sizeof(ht_item));
    item->key = key;
    item->value = value;
    item->next = table->buckets[index];
    table->buckets[index] = item;
    table->size++;
}


void* get(hashtable* table, void* key){
    int index = table->hashfunction(key, table->capacity);
    if(table->buckets[index] == NULL){
        return NULL;
    }
    return table->buckets[index]->value;
}

void* getOrDefault(hashtable* table, void* key, void* defaultValue){
    

}

int size(hashtable* table){
    return table->size;
}


void clear(hashtable* table){
    for(int i = 0; i < table->capacity; i++){
        if(table->buckets[i] != NULL){
            free(table->buckets[i]);
        }
    }

    free(table->buckets);
    table->buckets = NULL;
    table->size = 0;
    table->capacity = 0;
    table->initialCapacity = 100;

}

int main() {
    hashtable table = createHashTable(stringHash, stringCompare);
    int value = 10;
    put(&table, "king", &value);
    int* res = get(&table, "zeko");
    if(res == NULL){
        printf("%s\n", "element not found");
    }else{
        printf("%d\n", *res);
    }

    
    // printf("%d\n", get(&table ,"boda"));
    // printf("%d\n", size(&table));

    return 0;
}