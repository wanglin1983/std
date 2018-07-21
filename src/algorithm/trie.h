#ifndef __MYSTD_TRIE_H__
#define __MYSTD_TRIE_H__

#include "base/base.h"

namespace mystd {

#define MAX_TRIE_NODE 100000
#define MAX_TRIE_CHILD 26

  class Trie
  {
  public:
    struct TrieNode
    {
      TrieNode() {
        child_count = 0;
        v = '\0';
        parent = NULL;
        for (int i = 0; i < MAX_TRIE_CHILD; ++i) {
          child[i] = NULL;
        }
      }

      TrieNode* AddChildNode(char c) {
        int index = c - 'a';
        TrieNode* child_node = child[index];
        if (child_node)
          return child_node;
        child_node = new TrieNode;
        child_node->v = c;
        child[index] = child_node;
        child_node->parent = this;
        ++child_count;
        return child_node;
      }

      int child_count;
      char v;
      TrieNode* parent;
      TrieNode* child[MAX_TRIE_CHILD];
    };

    Trie();
    ~Trie();

    void AddToTrie(char* str);
    void RemoveTrieNode(TrieNode* node);
    TrieNode* FindNode(char* str);

  private:
    TrieNode* root;
  };

  Trie::Trie()
  {
    root = new TrieNode;
  }

  Trie::~Trie()
  {
    delete root;
  }

  void Trie::AddToTrie(char* str) {
    TrieNode* node = root;
    while (*str) {
      node = node->AddChildNode(*str++);
    }
  }

  void Trie::RemoveTrieNode(Trie::TrieNode* node) {
    TrieNode* parent = node->parent;
    while (parent) {
      int index = node->v - 'a';
      --parent->child_count;
      if (node->child_count == 0)
        parent->child[index] = NULL;
    }
  }

  Trie::TrieNode* Trie::FindNode(char* str) {
    TrieNode* node = root;
    while (*str) {
      int index = *str - 'a';
      if (!node->child[index])
        return NULL;
      node = node->child[index];
      ++str;
    }
    return node;
  }

}

#endif