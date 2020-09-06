#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node
{
    char *key;
    char *value;
    struct _Node *next;
} Node;

typedef Node *List;

typedef struct _HashTable
{
    int tableSize;
    List *table;
} HashTable;

int makeHash(const char *key, int keyLength, int tableSize)
{
    int hashValue = 0;
    for (int i = 0; i < keyLength; i++)
    {
        hashValue = (hashValue << 3) + key[i];
    }
    hashValue = hashValue % tableSize;
    return (hashValue);
}

HashTable *createHashTable(int tableSize)
{
    HashTable *hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->table = (List*)malloc(sizeof(List) * tableSize);
    bzero(hashTable->table, sizeof(List)*tableSize);
    hashTable->tableSize = tableSize;

    return (hashTable);
}

Node *createNode(const char *key, const char *value)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(newNode->key, key);
    newNode->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(newNode->value, value);
    newNode->next = NULL;
    return (newNode);
}

void destroyNode(Node *node)
{
    free(node->key);
    free(node->value);
    free(node);
}

void valueSet(HashTable *hashTable, const char *key, const char *value)
{
    int keyLen = strlen(key);
    int address = makeHash(key, keyLen, hashTable->tableSize);

    Node *newNode = createNode(key, value);

    if (hashTable->table[address] == NULL)
    {
        hashTable->table[address] = newNode;
    }
    else
    {
        List list = hashTable->table[address];
        newNode->next = list;
        hashTable->table[address] = newNode;
    }
}

char *getValue(HashTable *hashTable, const char *key)
{
    int address = makeHash(key, strlen(key), hashTable->tableSize);
    List list = hashTable->table[address];
    List target = NULL;

    if (list == NULL)
        return (NULL);
    while (1)
    {
        if (strcmp(list->key, key) == 0)
        {
            target = list;
            break ;
        }
        if (list->next == NULL)
            return (NULL);
        else
            list = list->next;
    }
    return (target->value);
}

void destroyList(List list)
{
    if (list == NULL)
        return ;
    if (list->next != NULL)
    {
        destroyList(list->next);
    }
    destroyNode(list);
}

void destroyHashTable(HashTable * hash)
{
    for (int i = 0; i < hash->tableSize; i++)
    {
        List list = hash->table[i];
        destroyList(list);
    }
}

int main(void)
{
    HashTable *hashTable = createHashTable(12289);
    valueSet(hashTable, "MSFT", "Microsoft Corporation");
    valueSet(hashTable, "JAVA", "Sun Microsystems");

    valueSet(hashTable, "APAC", "Apach Org");
    valueSet(hashTable, "ZYMZZ", "Unisys Ops Check");

    printf("%s\n", getValue(hashTable, "MSFT"));
    printf("%s\n", getValue(hashTable, "JAVA"));
    printf("%s\n", getValue(hashTable, "APAC"));
    printf("%s\n", getValue(hashTable, "ZYMZZ"));
    return (0);
}
