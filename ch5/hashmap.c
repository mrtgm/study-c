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

    while (entry != NULL)
    {
        if (strcmp(entry->key, key) == 0)
        {
            free(entry->value);
            entry->value = strdup(value);
            return;
        }
        entry = entry->next;
    }

    entry = malloc(sizeof(Entry)); // ここで entry は新しい要素を指すようになる
    entry->key = strdup(key);
    entry->value = strdup(value);
    entry->next = hashmap->entries[index]; // 先頭の要素を新しい要素の next にぶちこみ、
    hashmap->entries[index] = entry;       // 先頭に新しい要素をぶちこむ
}

char *getValueFromHashMap(Hashmap *hashmap, const char *key)
{
    unsigned int index = hash(key, hashmap->size);

    printf("%d:get\n", index);
    Entry *entry = hashmap->entries[index];
    while (entry != NULL)
    {
        if (strcmp(entry->key, key) == 0)
        {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void freeEntry(Entry *entry)
{
    while (entry != NULL)
    {
        Entry *next = entry->next;
        free(entry->key);
        free(entry->value);
        free(entry);
        entry = next;
    }
}

void freeHashMap(Hashmap *hashmap)
{
    for (int i = 0; i < hashmap->size; i++)
    {
        freeEntry(hashmap->entries[i]);
    }
    free(hashmap->entries);
    free(hashmap);
}

int removeFromHashMap(Hashmap *hashmap, const char *key)
{
    unsigned int index = hash(key, hashmap->size);
    Entry *entry = hashmap->entries[index];

    Entry *pred = NULL;
    while (entry != NULL)
    {
        if (strcmp(entry->key, key) == 0)
        {
            break;
        }
        pred = entry;        // 削除する要素の一つ前の要素を保存
        entry = entry->next; // 削除する要素を保存
    }

    if (entry == NULL) // 要素が見つからなかった場合
        return -1;
    if (pred == NULL)                          // 先頭の要素を削除する場合
        hashmap->entries[index] = entry->next; // この場合、entry は先頭の要素を指す、先頭の次の要素を先頭にする
    else
        pred->next = entry->next; // 一つ前の要素の next を削除する要素の next と繋ぐ

    free(entry->key);
    free(entry->value);
    free(entry);

    return 0;
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
