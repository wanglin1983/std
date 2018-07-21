#ifndef __MYSTD_HASH_TABLE__
#define __MYSTD_HASH_TABLE__

#include "base/base.h"
#include "base/memory.h"
#include "base/string.h"

namespace mystd {

#define MAX_HASH_TABLE_SIZE 100000013
#define MAX_STR_SIZE 20

  class HashTable
  {
  public:
    struct HashNode
    {
      HashNode() {
        key = 0;
        MemSet(str, MAX_STR_SIZE);
        next = NULL;
      }
      LL key;
      char str[MAX_STR_SIZE];
      HashNode* next;
    };

    HashTable(LL size = MAX_HASH_TABLE_SIZE);
    ~HashTable();

    LL GetHashKey(char* str) {
      unsigned int value = 131;
      while (*str)
        value += (value << 5) + *str++;
      return value % size_;
    }

    void AddToHashTable(char* str) {
      LL index = GetHashKey(str);
      HashNode& node = hash_table_[index];
      if (!node.key) {
        // not used
        node.key = index;
        StrCopy(node.str, str);
      } else {
        // already used
        HashNode* insert_node = &node;
        while (true) {
          if (StrSame(str, insert_node->str)) {
            // Already exist in hash_table
            insert_node = 0;
            break;
          } else {
            if (!insert_node->next)
              break;
            else
              insert_node = insert_node->next;
          }
        }

        if (insert_node) {
          insert_node->next = new HashNode;
          insert_node->next->key = index;
          StrCopy(insert_node->next->str, str);
        }
      }
    }

    HashNode* Find(char* str) {
      LL index = GetHashKey(str);
      HashNode* node = &hash_table_[index];
      while (node) {
        if (StrSame(node->str, str))
          return node;
        else
          node = node->next;
      }
      return NULL;
    }

  private:
    LL size_;
    HashNode *hash_table_;
  };

  HashTable::HashTable(LL size)
  {
    size_ = size;
    hash_table_ = new HashNode[size_];
  }

  HashTable::~HashTable()
  {
    size_ = 0;
    delete hash_table_;
    hash_table_ = NULL;
  }

} // namespace mystd

#endif // __MYSTD_HASH_TABLE__