#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
	int address;
	int value;
} Node;

typedef struct _HashTable
{
	Node *node;
	int hashSize;
} HashTable;

HashTable *createHash(int hashSize)
{
	HashTable *hashTable = (HashTable*)malloc(sizeof(HashTable));

	hashTable->node = (Node*)malloc(sizeof(Node) * hashSize);
	hashTable->hashSize = hashSize;
	return (hashTable);
}

int makeHash(int value, int hashSize)
{
	return value % hashSize;
}

void setHash(HashTable *hashTable, int value)
{
	int address = makeHash(value, hashTable->hashSize);

	hashTable->node[address].address = address;
	hashTable->node[address].value = value;
}

int getHash(HashTable *hashTable, int value)
{
	int address = makeHash(value, hashTable->hashSize);
	return (hashTable->node[address].value);
}

void hashDelete(HashTable *hash)
{
	free(hash->node);
	free(hash);
}

int main(void)
{
	HashTable *hash = createHash(193);

	setHash(hash, 100);
	setHash(hash, 103);
	setHash(hash, 10302);

	//int address = makeHash(10302, hash->hashSize);
	printf("%d\n", getHash(hash, 100));
	printf("%d\n", getHash(hash, 103));
	printf("%d\n", getHash(hash, 10302));

}