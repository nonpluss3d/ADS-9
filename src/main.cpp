// Copyright 2022 NNTU-CS
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "tree.h"

template <typename Func, typename... Args>
int64_t measureTime(Func func, Args&&... args) {
  auto start = std::chrono::high_resolution_clock::now();
  func(std::forward<Args>(args)...);
  auto end = std::chrono::high_resolution_clock::now();
  return static_cast<int64_t>(
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count());
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

    int64_t timeGetAllPerms = measureTime([&]() { getAllPerms(tree); });
    int64_t timeGetPerm1 = measureTime([&]() { getPerm1(tree, randomNum); });
    int64_t timeGetPerm2 = measureTime([&]() { getPerm2(tree, randomNum); });

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
