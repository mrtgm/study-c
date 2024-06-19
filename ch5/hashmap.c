#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry
{
    char *key;
    char *value;
    struct entry *next;
} Entry;

typedef struct Hashmap
{
    Entry **entries; // ポインタの配列
    int size;
} Hashmap;

Hashmap *newHashmap(int size)
{
    Hashmap *h = malloc(sizeof(Hashmap));
    h->size = size;

    h->entries = malloc(sizeof(Entry) * size);
    for (int i = 0; i < h->size; i++)
    {
        h->entries[i] = NULL;
    }
    return h;
}

unsigned int hash(const char *key, const int size)
{
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash = hash * 31 + key[i];
    }
    return hash % size;
}

void insertToHashMap(Hashmap *hashmap, const char *key, const char *value)
{
    unsigned int index = hash(key, hashmap->size);
    printf("%d:ins\n", index);
    Entry *entry = hashmap->entries[index];

    // コリジョンを防ぐためにチェーン法ってのをつかうらしいけど、時間切れ・・・
    // https://zenn.dev/fikastudio/articles/efcfe246642553

    entry = malloc(sizeof(Entry));
    entry->key = strdup(key);
    entry->value = strdup(value);
    hashmap->entries[index] = entry;
}

char *getValueFromHashMap(Hashmap *hashmap, const char *key)
{
    unsigned int index = hash(key, hashmap->size);

    printf("%d:get\n", index);
    Entry *entry = hashmap->entries[index];
    if (entry == NULL)
    {
        return '\0';
    }
    return entry->value;
}

int main(void)
{
    int size = 100;
    Hashmap *hashmap = newHashmap(size);

    insertToHashMap(hashmap, "key1", "value1");
    insertToHashMap(hashmap, "key2", "value2");
    char *value = getValueFromHashMap(hashmap, "key1");

    printf("key1: %s\n", value); // key1: value1
    return 0;
}
