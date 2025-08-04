#include <stdio.h>
#include <stdlib.h>


typedef struct hashtable
{   
    int* items;       
    int initialCapacity;
    int capacity;
    int size;
}hashtable;

hashtable createHashTable(){
   hashtable newHashTable;
   newHashTable.size = 0;
   newHashTable.initialCapacity = 100;
   newHashTable.capacity = newHashTable.initialCapacity;
   newHashTable.items = malloc(sizeof(int) * 100);
   return newHashTable;
}

int hash(char* key, int capacity){
    int hash = 0;
    if(capacity == 0){
        capacity = 1;
    }
    for (int i = 0; key[i] != '\0'; i++) {
    hash = (hash * 31 + key[i]) % capacity;
    }
    return hash;
}

void put(hashtable* table, char* key, int value){
    int index = hash(key , table->capacity);
    table->items[index] = value;
    table->size++;
}

int get(hashtable* table, char* key){
    int index = hash(key, table->capacity);
    return table->items[index];
}

int size(hashtable* table){
    return table->size;
}

int main() {
    int array[50];
    hashtable table = createHashTable();
    put(&table, "king", 10);
    put(&table, "lion", 20);
    put(&table, "zeko", 30);
    put(&table, "lolo", 20);
    put(&table, "lolo", 15);
    
    printf("%d\n", get(&table ,"lolo"));
    printf("%d\n", size(&table));

    return 0;
}