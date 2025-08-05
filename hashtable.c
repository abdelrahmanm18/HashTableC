#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    void* key;
    void* value;
    ht_item* next;
}ht_item;

typedef int (*HashFunction) (void* key, int capacity);


typedef struct
{   
    //items here is a pointer to an array of pointers
    //Each of those pointers points to a ht_item struct

    /*
    items ──►  ptr ──► ht_item { key: "eg", value: "egypt" }
               ptr ──► ht_item { key: "fr", value: "france" }
               ptr ──► NULL
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

int compare_keys(void* a, void* b){

}


void put(hashtable* table, void* key, void* value){
    int index = table->hashfunction(key , table->capacity);
    ht_item* current = table->items[index];
    while(current != NULL){
        if(current->key == key){
            current->value = value;
            return;
        }

        current = current->next;
    }

    ht_item* item = malloc(sizeof(ht_item));
    item->key = key;
    item->value = value;
    item->next = table->items[index];
    table->items[index] = item;
    table->size++;
}


void* get(hashtable* table, void* key){
    int index = table->hashfunction(key, table->capacity);
    if(table->items[index] == NULL){
        return NULL;
    }
    return table->items[index]->value;
}

void* getOrDefault(hashtable* table, void* key, void* defaultValue){
    

}

int size(hashtable* table){
    return table->size;
}


void clear(hashtable* table){
    for(int i = 0; i < table->capacity; i++){
        if(table->items[i] != NULL){
            free(table->items[i]);
        }
    }

    free(table->items);
    table->items = NULL;
    table->size = 0;
    table->capacity = 0;
    table->initialCapacity = 100;

}

int main() {
    hashtable table = createHashTable(stringHash);
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