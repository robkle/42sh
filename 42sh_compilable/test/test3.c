#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef char *KeyType;
typedef char *ValueType;

enum ElementStatus
{
    EMPTY = 0,
    OCCUPIED = 1
};

typedef struct _ElementType
{
    KeyType key;
    ValueType value;
    enum ElementStatus status;
} ElementType;

typedef struct _HashTable
{
    int occupiedCount;
    int tableSize;
    ElementType *table;
} HashTable;

HashTable   *OAHT_CreateHashTable(int tableSize);
void        OAHT_DestroyHashTable(HashTable *hashTable);
void        OAHT_CrearElement(ElementType * element);
void        OAHT_Set(HashTable **hashTable, const KeyType key, const ValueType value);
ValueType   OAHT_Get(HashTable *hashTable, const KeyType key);
int         OAHT_Hash(const KeyType key, int keyLength, int tableSize);
int         OAHT_Hash2(const KeyType key, int keyLength, int tableSize);

void        OAHT_Rehash(HashTable **HashTable);

HashTable   *OAHT_CreateHashTable(int tableSize)
{
    HashTable *hashTable = (HashTable*)malloc(sizeof(HashTable));

    hashTable->table = (ElementType*)malloc(sizeof(ElementType) * tableSize);
    memset(hashTable->table, 0, sizeof(ElementType) * tableSize);
    hashTable->tableSize = tableSize;
    hashTable->occupiedCount = 0;
    return (hashTable);
}

void        OAHT_Set(HashTable **hashTable, const KeyType key, const ValueType value)
{
    int keyLen;
    int address;
    int stepSize;
    double usage;

    usage = (double)(*hashTable)->occupiedCount / (*hashTable)->tableSize;
    if(usage > 0.6)
        OAHT_Rehash(hashTable);
    keyLen = strlen(key);
    address = OAHT_Hash(key, keyLen, (*hashTable)->tableSize);
    stepSize = OAHT_Hash2(key, keyLen, (*hashTable)->tableSize);
    while((*hashTable)->table[address].status != EMPTY &&
            strcmp((*hashTable)->table[address].key, key) != 0)
    {
        address = (address + stepSize) % (*hashTable)->tableSize;
    }

    (*hashTable)->table[address].key = (char*)malloc(sizeof(char) * (keyLen + 1));
    strcpy((*hashTable)->table[address].key, key);
    (*hashTable)->table[address].value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    strcpy((*hashTable)->table[address].value, value);

    (*hashTable)->table[address].status = OCCUPIED;
    (*hashTable)->occupiedCount++;
}

ValueType OAHT_Get(HashTable *hashTable, const KeyType key)
{
    int keyLen = strlen(key);
    int address = OAHT_Hash(key, keyLen, hashTable->tableSize);
    int stepSize = OAHT_Hash2(key, keyLen, hashTable->tableSize);

    while (hashTable->table[address].status != EMPTY &&
            strcmp(hashTable->table[address].key, key) != 0)
    {
        address = (address + stepSize) % hashTable->tableSize;
    }
    return (hashTable->table[address].value);
}

void        OAHT_CrearElement(ElementType * element)
{
    if (element->status == EMPTY)
        return ;
    free(element->key);
    free(element->value);
}

void        OAHT_DestroyHashTable(HashTable *hashTable)
{
    int i = 0;

    for (i = 0; i < hashTable->tableSize; i++)
    {
        OAHT_CrearElement(&(hashTable->table[i]));
    }
    free(hashTable->table);
    free(hashTable);
}

int         OAHT_Hash(const KeyType key, int keyLength, int tableSize)
{
    int i = 0;
    int hashValue = 0;
    for (i = 0; i < keyLength; i++)
    {
        hashValue = (hashValue << 3) + key[i];
    }
    hashValue = hashValue % tableSize;
    return (hashValue);
}

int         OAHT_Hash2(const KeyType key, int keyLength, int tableSize)
{
    int i = 0;
    int hashValue = 0;

    for (i = 0; i < keyLength; i++)
    {
        hashValue = (hashValue << 2) + key[i];
    }
    hashValue = hashValue % (tableSize - 3);
    return (hashValue + 1);
}

void OAHT_Rehash(HashTable **hashTable)
{
    int i = 0;
    ElementType *oldTable = (*hashTable)->table;
    HashTable *newHashTable = OAHT_CreateHashTable((*hashTable)->tableSize * 2);
    
    for (i = 0; i < (*hashTable)->tableSize; i++)
    {
        if (oldTable[i].status == OCCUPIED)
        {
            OAHT_Set(&newHashTable, oldTable[i].key, oldTable[i].value);
        }
    }
    OAHT_DestroyHashTable((*hashTable));
    (*hashTable) = newHashTable;
    printf("%d\n", newHashTable->tableSize);
}

int main(void)
{
    HashTable *HT = OAHT_CreateHashTable(11);

    OAHT_Set(&HT, "MSFT", "Microsoft Corporation");
    OAHT_Set(&HT, "JAVA", "Sun Microsystems");
    OAHT_Set(&HT, "REDH", "Red Hat Linux");
    OAHT_Set(&HT, "APAC", "Apache Org");
    OAHT_Set(&HT, "ZYMZZ", "Unisys Ops Check");
    OAHT_Set(&HT, "IBM", "IBM Ltd.");
    OAHT_Set(&HT, "ORCL", "Oracle Corporation");
    OAHT_Set(&HT, "CSCO", "Cisco Systems, Inc.");
    OAHT_Set(&HT, "GOOG", "Google Inc.");
    OAHT_Set(&HT, "YHOO", "Yahoo! Inc.");
    OAHT_Set(&HT, "NOVL", "Novell, Inc.");

    printf("\n");
    printf("Key:%s, Value:%s\n", "MSFT", OAHT_Get(HT, "MSFT"));
    printf("Key:%s, Value:%s\n", "REDH", OAHT_Get(HT, "REDH"));
    printf("Key:%s, Value:%s\n", "APAC", OAHT_Get(HT, "APAC"));
    printf("Key:%s, Value:%s\n", "ZYMZZ", OAHT_Get(HT, "ZYMZZ"));
    printf("Key:%s, Value:%s\n", "JAVA", OAHT_Get(HT, "JAVA"));
    printf("Key:%s, Value:%s\n", "IBM", OAHT_Get(HT, "IBM"));
    printf("Key:%s, Value:%s\n", "ORCL", OAHT_Get(HT, "ORCL"));
    printf("Key:%s, Value:%s\n", "CSCO", OAHT_Get(HT, "CSCO"));
    printf("Key:%s, Value:%s\n", "GOOG", OAHT_Get(HT, "GOOG"));
    printf("Key:%s, Value:%s\n", "YHOO", OAHT_Get(HT, "YHOO"));
    printf("Key:%s, Value:%s\n", "NOVL", OAHT_Get(HT, "NOVL"));

    OAHT_DestroyHashTable(HT);
    return (0);
}