// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <memory>
#include <vector>

class PMTreeNode {
 public:
  explicit PMTreeNode(char val);
  char value;
  std::vector<std::unique_ptr<PMTreeNode>> children;
};

class PMTree {
 public:
  explicit PMTree(const std::vector<char>& symbols);
  ~PMTree();

  PMTreeNode* getRoot() const;
  int getTotalPermutations() const;

 private:
  void buildSubtree(PMTreeNode* node,
                    const std::vector<char>& remainingSymbols);
  std::unique_ptr<PMTreeNode> root;
  int totalPermutations;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
