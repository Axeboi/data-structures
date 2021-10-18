#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct String{
  uint32_t start;
  uint32_t len;
  char * string;
} String;

typedef struct CollisionList {
  struct CollisionList *next;
  char *str;
  uint32_t len;
} CollisionList;

typedef struct HashTable {
  uint32_t sz;
  CollisionList **table;
} HashTable;

void hash_table_add(HashTable *table, uint32_t index, char * str, uint32_t len) {
  if (table->table[index % table->sz] == NULL)
  {
    CollisionList *item = (CollisionList*) malloc(sizeof(CollisionList));
    item->next = NULL;
    item->str = str;
    item->len = (uint32_t) strlen(str + 1);

    table->table[index % table->sz] = item;
  } else
  {
    CollisionList *next = table->table[index % table->sz];
    while(next->next != NULL)
    {
      if (strcmp(next->str, str))
      {
        return;
      }
      next = next->next;
    }

    CollisionList *item = (CollisionList*) malloc(sizeof(CollisionList));
    item->next = NULL;
    item->str = str;
    item->len = (uint32_t) strlen(str + 1);

    next->next = item;
  }
}

void hash_table_free()
{
  // Implement
}

uint32_t fna_hash(char *data, uint32_t len)
{
  uint32_t hash = 2166136261;
  for(char *byte = data; byte < (data + len); byte++)
  {
    hash ^= *byte;
    hash *= 16777619;
  }
  return hash;
}

int main(int argc, char **argv)
{
  HashTable hash_table;
  hash_table.sz = 1024;
  CollisionList **init_list = (CollisionList **) malloc(hash_table.sz * sizeof(CollisionList));
  hash_table.table = init_list;

  for(uint32_t i = 0; i < hash_table.sz; i++)
  {
    hash_table.table[i] = NULL;
  }

  for(uint32_t i = 1; i < argc; i++)
  {
    uint32_t hash_value = fna_hash(argv[i], strlen(argv[i]) + 1);
    hash_table_add(&hash_table, hash_value, argv[i], strlen(argv[i]) + 1);
  }

  if (argv[1])
  {
    uint32_t hash_value = fna_hash(argv[1], strlen(argv[1])+1);
    printf("Hash: %s\n", hash_table.table[hash_value % 1024]->str);
  }
}