// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

#include "tree.h"

void collectAllPerms(PMTreeNode* node, std::vector<char>& currentPath,
                     std::vector<std::vector<char>>& allPerms) {
  if (node->children.empty()) {
    if (!currentPath.empty()) {
      allPerms.push_back(currentPath);
    }
    return;
  }

  for (const auto& child : node->children) {
    currentPath.push_back(child->value);
    collectAllPerms(child.get(), currentPath, allPerms);
    currentPath.pop_back();
  }
}

int factorial(int n) {
  if (n <= 1) return 1;
  return n * factorial(n - 1);
}

PMTreeNode::PMTreeNode(char val) : value(val) {}

PMTree::PMTree(const std::vector<char>& symbols) {
  std::vector<char> sorted = symbols;
  std::sort(sorted.begin(), sorted.end());
  root = std::make_unique<PMTreeNode>('\0');

  buildSubtree(root.get(), sorted);

  totalPermutations = 1;
  for (int i = 2; i <= symbols.size(); ++i) {
    totalPermutations *= i;
  }
}

PMTree::~PMTree() = default;

PMTreeNode* PMTree::getRoot() const { return root.get(); }

int PMTree::getTotalPermutations() const { return totalPermutations; }

void PMTree::buildSubtree(PMTreeNode* node,
                          const std::vector<char>& remainingSymbols) {
  if (remainingSymbols.empty()) return;

  for (size_t i = 0; i < remainingSymbols.size(); ++i) {
    char curr = remainingSymbols[i];
    node->children.push_back(std::make_unique<PMTreeNode>(curr));

    std::vector<char> next;
    for (size_t j = 0; j < remainingSymbols.size(); ++j) {
      if (j != i) next.push_back(remainingSymbols[j]);
    }

    buildSubtree(node->children.back().get(), next);
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  collectAllPerms(tree.getRoot(), path, result);
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  if (num < 1 || num > tree.getTotalPermutations()) return {};

  std::vector<std::vector<char>> perms;
  std::vector<char> path;
  collectAllPerms(tree.getRoot(), path, perms);
  return perms[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  if (num < 1 || num > tree.getTotalPermutations()) return {};

  std::vector<char> result;
  PMTreeNode* node = tree.getRoot();
  int index = num - 1;

  while (!node->children.empty()) {
    int subSize = factorial(static_cast<int>(node->children.size()) - 1);
    int idx = index / subSize;
    result.push_back(node->children[idx]->value);
    node = node->children[idx].get();
    index %= subSize;
  }

  return result;
}
