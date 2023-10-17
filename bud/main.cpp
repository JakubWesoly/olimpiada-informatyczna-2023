#include <iostream>
#include <vector>
#include <string>

// TODO: Has to check if space will be "occupied"
void check_max_free_spaces(const std::vector<std::string> &airport, const unsigned int n, const unsigned int m, int &max_free_spaces, int &second_max_free_spaces)
{
  std::vector<std::vector<bool>> checked(n, std::vector<bool>(n, false)); // create a 2D vector to keep track of checked fields

  // Sprawdzanie maksymalnej liczby wolnych miejsc w kolumnie
  for (int i = 0; i < n; i++)
  {
    int free_spaces = 0;
    int max_sequence = 0;
    for (int j = 0; j < n; j++)
    {
      if (airport[i][j] == '.' && !checked[i][j]) // check if the field is empty and not checked
      {
        free_spaces++;
        max_sequence = std::max(max_sequence, free_spaces);
        checked[i][j] = true; // mark the field as checked
      }
      else
      {
        free_spaces = 0;
      }
    }
    if (max_sequence > max_free_spaces)
    {
      second_max_free_spaces = max_free_spaces;
      max_free_spaces = max_sequence;
    }
    else if (max_sequence > second_max_free_spaces)
    {
      second_max_free_spaces = max_sequence;
    }
  }

  // Sprawdzanie maksymalnej liczby wolnych miejsc w wierszu
  for (int i = 0; i < n; i++)
  {
    int free_spaces = 0;
    int max_sequence = 0;
    for (int j = 0; j < n; j++)
    {
      if (airport[j][i] == '.' && !checked[j][i]) // check if the field is empty and not checked
      {
        free_spaces++;
        max_sequence = std::max(max_sequence, free_spaces);
        checked[j][i] = true; // mark the field as checked
      }
      else
      {
        free_spaces = 0;
      }
    }
    if (max_sequence > max_free_spaces)
    {
      second_max_free_spaces = max_free_spaces;
      max_free_spaces = max_sequence;
    }
    else if (max_sequence > second_max_free_spaces)
    {
      second_max_free_spaces = max_sequence;
    }
  }
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
  // n = 5;
  // m = 2;
  // airport.push_back(".X...");
  // airport.push_back(".XXXX");
  // airport.push_back("XX...");
  // airport.push_back(".....");
  // airport.push_back(".X.X.");
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
  n = 2;
  m = 2;
  airport.push_back(".X");
  airport.push_back("..");
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

  int max_free_spaces = 0;
  int second_max_free_spaces = 0;

  check_max_free_spaces(airport, n, m, max_free_spaces, second_max_free_spaces);

  if (m == 1)
  {
    std::cout << max_free_spaces << std::endl;
  }
  else
  {
    std::cout << second_max_free_spaces << std::endl;
  }

  return 0;
}