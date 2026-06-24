#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26
#define MAX_WORD_LEN 100

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEnd;
} TrieNode;

/*=========================================================
  Create Node
=========================================================*/
TrieNode* createNode(void) {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    if (!node) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;

    node->isEnd = false;
    return node;
}

/*=========================================================
  Insert Word
=========================================================*/
void insert(TrieNode* root, const char* word) {
    TrieNode* curr = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (index < 0 || index >= ALPHABET_SIZE)
            continue; // skip non-lowercase letters

        if (curr->children[index] == NULL)
            curr->children[index] = createNode();

        curr = curr->children[index];
    }

    curr->isEnd = true;
}

/*=========================================================
  Search Full Word
=========================================================*/
bool search(TrieNode* root, const char* word) {
    TrieNode* curr = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (index < 0 || index >= ALPHABET_SIZE)
            return false;

        if (curr->children[index] == NULL)
            return false;

        curr = curr->children[index];
    }

    return curr->isEnd;
}

/*=========================================================
  Search Prefix
=========================================================*/
bool startsWith(TrieNode* root, const char* prefix) {
    TrieNode* curr = root;

    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = prefix[i] - 'a';

        if (index < 0 || index >= ALPHABET_SIZE)
            return false;

        if (curr->children[index] == NULL)
            return false;

        curr = curr->children[index];
    }

    return true;
}

/*=========================================================
  Check if Node Has No Children
=========================================================*/
bool isEmpty(TrieNode* node) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL)
            return false;
    }
    return true;
}

/*=========================================================
  Delete Word (Recursive)
=========================================================*/
TrieNode* deleteWord(TrieNode* root, const char* word, int depth) {
    if (root == NULL)
        return NULL;

    if (word[depth] == '\0') {
        if (root->isEnd)
            root->isEnd = false;
    } else {
        int index = word[depth] - 'a';

        if (index >= 0 && index < ALPHABET_SIZE) {
            root->children[index] =
                deleteWord(root->children[index], word, depth + 1);
        }
    }

    if (root->isEnd)
        return root;

    if (!isEmpty(root))
        return root;

    free(root);
    return NULL;
}

/*=========================================================
  Count Stored Words
=========================================================*/
int countWords(TrieNode* root) {
    if (root == NULL)
        return 0;

    int count = root->isEnd ? 1 : 0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        count += countWords(root->children[i]);

    return count;
}

/*=========================================================
  Print All Words
=========================================================*/
void printAllWordsHelper(TrieNode* root, char* buffer, int depth) {
    if (root == NULL)
        return;

    if (root->isEnd) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            buffer[depth] = 'a' + i;
            printAllWordsHelper(root->children[i], buffer, depth + 1);
        }
    }
}

void printAllWords(TrieNode* root) {
    char buffer[MAX_WORD_LEN];
    printAllWordsHelper(root, buffer, 0);
}

/*=========================================================
  Free Entire Trie
=========================================================*/
void freeTrie(TrieNode* root) {
    if (root == NULL)
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        freeTrie(root->children[i]);

    free(root);
}

/*=========================================================
  Main Example
=========================================================*/
int main(void) {
    TrieNode* root = createNode();

    /* Insert words */
    insert(root, "cat");
    insert(root, "car");
    insert(root, "cart");
    insert(root, "dog");
    insert(root, "apple");

    /* Search full words */
    printf("search(cat)   = %d\n", search(root, "cat"));   // 1
    printf("search(ca)    = %d\n", search(root, "ca"));    // 0
    printf("search(dog)   = %d\n", search(root, "dog"));   // 1
    printf("search(cow)   = %d\n", search(root, "cow"));   // 0

    /* Prefix search */
    printf("startsWith(ca)  = %d\n", startsWith(root, "ca"));
    printf("startsWith(app) = %d\n", startsWith(root, "app"));
    printf("startsWith(z)   = %d\n", startsWith(root, "z"));

    /* Count words */
    printf("\nTotal words = %d\n", countWords(root));

    /* Print all words */
    printf("\nWords in Trie:\n");
    printAllWords(root);

    /* Delete a word */
    root = deleteWord(root, "car", 0);

    printf("\nAfter deleting 'car':\n");
    printf("search(car) = %d\n", search(root, "car"));
    printf("search(cart)= %d\n", search(root, "cart"));

    printf("\nWords in Trie now:\n");
    printAllWords(root);

    printf("\nTotal words = %d\n", countWords(root));

    /* Free memory */
    freeTrie(root);

    return 0;
}
