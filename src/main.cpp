// Copyright 2022 NNTU-CS
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "tree.h"

template <typename Func, typename... Args>
long long measureTime(Func func, Args&&... args) {
  auto start = std::chrono::high_resolution_clock::now();
  func(std::forward<Args>(args)...);
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end - start)
      .count();
}

int main() {
  std::ofstream dataFile("result/performance_data.csv");
  dataFile << "n,getAllPerms,getPerm1,getPerm2\n";

  std::default_random_engine generator;
  std::uniform_int_distribution<int> dist(1, 1000000);

  for (int n = 1; n <= 10; ++n) {
    std::vector<char> symbols(n);
    for (int i = 0; i < n; ++i) {
      symbols[i] = '1' + i;
    }

    PMTree tree(symbols);
    int total = tree.getTotalPermutations();
    int randomNum = dist(generator) % total + 1;

    long long timeGetAllPerms = measureTime([&]() { getAllPerms(tree); });
    long long timeGetPerm1 = measureTime([&]() { getPerm1(tree, randomNum); });
    long long timeGetPerm2 = measureTime([&]() { getPerm2(tree, randomNum); });

    dataFile << n << "," << timeGetAllPerms << "," << timeGetPerm1 << ","
             << timeGetPerm2 << "\n";
    std::cout << "n=" << n << ", "
              << "timeGetAllPerms=" << timeGetAllPerms << "μs, "
              << "timeGetPerm1=" << timeGetPerm1 << "μs, "
              << "timeGetPerm2=" << timeGetPerm2 << "μs\n";
  }

  dataFile.close();

  return 0;
}
