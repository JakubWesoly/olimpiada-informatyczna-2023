#include <iostream>
#include <vector>
#include <string>

std::vector<std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>> get_possible_free_spaces(const std::vector<std::string> &airport, int n)
{
  std::vector<std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>> possible_free_spaces{};
  std::pair<size_t, size_t> begin = {0, 0};
  for (size_t i = 0; i < n; i++)
  {
    for (size_t j = 1; j < n; j++)
    {
      if (airport[i][j] != '.' && airport[i][j - 1] == '.')
      {
        possible_free_spaces.push_back({begin, {i, j - 1}});
        begin = {i, j + 1};
        j++;
      }
    }

    if (airport[i][n - 1] == '.')
    {
      possible_free_spaces.push_back({begin, {i, n - 1}});
    }
    begin = {i + 1, 0};
  }
  return possible_free_spaces;
}

int main(void)
{

  // 1 ≤ n ≤ 1500
  unsigned int n = 0;

  // 1 ≤ m ≤ 2
  unsigned int m = 0;

  std::vector<std::string> airport;
  // airport.reserve(n);

  // ========================================
  //           Wczytywanie danych
  // ========================================
  // std::ios_base::sync_with_stdio(0);
  // std::cin >> n >> m;

  // for (int i = 0; i < n; i++)
  // {
  //   std::string line;
  //   std::cin >> line;
  //   airport.push_back(line);
  // }

  // PRZYKŁAD I
  n = 5;
  m = 2;
  airport.push_back(".X...");
  airport.push_back(".XXXX");
  airport.push_back("XX...");
  airport.push_back(".....");
  airport.push_back(".X.X.");
  // OCZEKIWANY OUTPUT: 3
  // DZIAŁA

  // PRZYKŁAD II
  // n = 2;
  // m = 1;
  // airport.push_back("..");
  // airport.push_back("..");
  // OCZEKIWANY OUTPUT: 2
  // DZIAŁA

  // PRZYKŁAD III
  // n = 2;
  // m = 2;
  // airport.push_back(".X");
  // airport.push_back("..");
  // OCZEKIWANY OUTPUT: 1
  // DZIAŁA

  // PRZYKŁAD IV
  // n = 10;
  // m = 2;
  // for (int i = i; i < n; i++)
  // {
  //   airport.push_back("..........");
  // }
  // airport[5] = "..........";
  // OCZEKIWANY OUTPUT: 1
  // DZIAŁA

  // ========================================
  //                 Algorytm
  // ========================================
  auto free_spaces = get_possible_free_spaces(airport, n);

  for (auto spaces : free_spaces)
  {
    std::cout << "{[" << spaces.first.first << ", " << spaces.first.second << "], [" << spaces.second.first << ", " << spaces.second.second << "]}\n";
  }
  return 0;
}