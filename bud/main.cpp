#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cmath>

constexpr size_t NOT_COLIDING = std::numeric_limits<size_t>::max();

struct Point
{
  size_t x;
  size_t y;
};

void print_point_pair(const std::pair<Point, Point> &points)
{
  std::cout << "{[" << points.first.x << ", " << points.first.y << "], [" << points.second.x << ", " << points.second.y << "]}\n";
}

std::vector<std::pair<Point, Point>> get_possible_horizontal_free_spaces(const std::vector<std::string> &airport, int n)
{
  std::vector<std::pair<Point, Point>> ranges;

  for (size_t y = 0; y < n; y++)
  {
    const std::string &row = airport[y];
    size_t startX = 0;

    for (size_t x = 0; x < n; x++)
    {
      if (row[x] == '.')
      {
        if (x == n - 1)
        {
          ranges.push_back(std::make_pair(Point{startX, y}, Point{x, y}));
        }
      }
      else
      {
        if (startX < x)
        {
          ranges.push_back(std::make_pair(Point{startX, y}, Point{x - 1, y}));
        }
        startX = x + 1;
      }
    }
  }

  return ranges;
}

std::vector<std::pair<Point, Point>> get_possible_vertical_free_spaces(const std::vector<std::string> &airport, int n)
{
  std::vector<std::pair<Point, Point>> ranges;

  for (size_t x = 0; x < n; x++)
  {
    size_t startY = 0;

    for (size_t y = 0; y < n; y++)
    {
      if (airport[y][x] == '.')
      {
        if (y == n - 1)
        {
          ranges.push_back(std::make_pair(Point{x, startY}, Point{x, y}));
        }
      }
      else
      {
        if (startY < y)
        {
          ranges.push_back(std::make_pair(Point{x, startY}, Point{x, y - 1}));
        }
        startY = y + 1;
      }
    }
  }

  return ranges;
}

Point where_are_coliding(const std::pair<Point, Point> &horizontal, const std::pair<Point, Point> &vertical)
{

  if ((horizontal.first.y <= vertical.second.y && horizontal.first.y >= vertical.first.y) &&
      (vertical.first.x <= horizontal.second.x && vertical.first.x >= horizontal.first.x))
  {
    return Point{
        .x = vertical.first.x,
        .y = horizontal.first.y};
  }

  return Point{
      .x = NOT_COLIDING,
      .y = NOT_COLIDING};
}

std::vector<int> calculate_horizontal_lengths(const std::vector<std::pair<Point, Point>> &points)
{
  std::vector<int> lengths{};
  for (auto point : points)
  {
    lengths.push_back(point.second.x - point.first.x + 1);
  }
  return lengths;
}

int calculate_horizontal_length(const std::pair<Point, Point> &point)
{
  return point.second.x - point.first.x + 1;
}

int calculate_vertical_length(const std::pair<Point, Point> &point)
{
  return point.second.y - point.first.y + 1;
}

std::vector<int> calculate_vertical_lengths(const std::vector<std::pair<Point, Point>> &points)
{
  std::vector<int> lengths{};
  for (auto point : points)
  {
    lengths.push_back(point.second.y - point.first.y + 1);
  }
  return lengths;
}

// void print_point(const Point &p)
// {
//   std::cout << "[" << p.x << ", " << p.y << "]\n";
// }

int main(void)
{

  // 1 ≤ n ≤ 1500
  unsigned int n = 0;

  // 1 ≤ m ≤ 2
  unsigned int m = 0;

  std::vector<std::string> airport;
  airport.reserve(n);

  // ========================================
  //           Wczytywanie danych
  // ========================================
  std::ios_base::sync_with_stdio(0);
  std::cin >> n >> m;

  for (int i = 0; i < n; i++)
  {
    std::string line;
    std::cin >> line;
    airport.push_back(line);
  }

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
  //   airport.push_back("XXXXXXXXXX");
  // }
  // airport[5] = "..........";
  // OCZEKIWANY OUTPUT: 1
  // CRASUHE SIE XPP

  // ========================================
  //                 Algorytm
  // ========================================
  auto horizontal_spaces = get_possible_horizontal_free_spaces(airport, n);
  // TODO: Pionowe zakresy mogą być wyciągnięte z poziomych. nie trzeba przechodzic jeszcze raz przez lotnisko
  auto vertical_spaces = get_possible_vertical_free_spaces(airport, n);

  auto horizontal_lengths = calculate_horizontal_lengths(horizontal_spaces);
  auto vertical_lengths = calculate_vertical_lengths(vertical_spaces);

  const int horizontal_spaces_size = horizontal_spaces.size();
  const int vertical_spaces_size = vertical_spaces.size();

  size_t max = 0;

  if (m == 1)
  {
    for (const auto &length : horizontal_lengths)
    {
      if (length > max)
        max = length;
    }
    for (const auto &length : vertical_lengths)
    {
      if (length > max)
        max = length;
    }
    std::cout << max;
    return 0;
  }
  else if (m != 2)
    return -1;

  size_t longest_horizontal = 0;
  size_t second_longest_horizontal = 0;

  for (auto h_length : horizontal_lengths)
  {
    if (h_length >= longest_horizontal)
    {
      second_longest_horizontal = longest_horizontal;
      longest_horizontal = h_length;
    }
    else if (h_length >= second_longest_horizontal)
    {
      second_longest_horizontal = h_length;
    }
  }

  if (second_longest_horizontal >= max)
    max = second_longest_horizontal;

  size_t longest_vertical = 0;
  size_t second_longest_vertical = 0;

  // std::cout << "DLUGOSCI PIONOWE: ";
  for (auto v_length : vertical_lengths)
  {
    // std::cout << v_length << ", ";
    if (v_length >= longest_vertical)
    {
      second_longest_vertical = longest_vertical;
      longest_vertical = v_length;
    }
    else if (v_length >= second_longest_vertical)
    {
      second_longest_vertical = v_length;
    }
  }

  if (second_longest_vertical > max)
    max = second_longest_vertical;

  for (int horizontal_iterator = 0; horizontal_iterator < horizontal_spaces_size; horizontal_iterator++)
  {
    if (horizontal_lengths[horizontal_iterator] / 2 > max)
      max = horizontal_lengths[horizontal_iterator] / 2;

    if (horizontal_lengths[horizontal_iterator] < max)
      continue;

    for (int vertical_iterator = 0; vertical_iterator < vertical_spaces_size; vertical_iterator++)
    {
      if (vertical_lengths[vertical_iterator] < max)
        continue;
      auto &current_horizontal = horizontal_spaces[horizontal_iterator];
      auto &current_vertical = vertical_spaces[vertical_iterator];

      // std::cout << "ITERATION RESULTS: \n";
      // print_point_pair(current_horizontal);
      // print_point_pair(current_vertical);

      if (vertical_lengths[vertical_iterator] / 2 > max)
        max = vertical_lengths[vertical_iterator] / 2;

      Point colision = where_are_coliding(horizontal_spaces[horizontal_iterator], vertical_spaces[vertical_iterator]);

      if (colision.x == NOT_COLIDING)
      {
        size_t smaller_length = std::min(horizontal_lengths[horizontal_iterator], vertical_lengths[vertical_iterator]);

        if (smaller_length > max)
          max = smaller_length;

        // std::cout << "BRAK KOLIZJI\n";
        // std::cout << "MAX: " << max << "\n";
        // std::cout << "\n";

        continue;
      }

      // TODO: potencjalna optymalizacja, nwm czy ma sens xd
      // if (vertical_lengths[vertical_iterator] == 1 || horizontal_lengths[horizontal_iterator] == 1)
      //   continue;

      std::pair<Point, Point> top{
          Point{
              .x = colision.x,
              .y = current_vertical.first.y},
          Point{
              .x = colision.x,
              .y = colision.y - 1}};

      std::pair<Point, Point> right{
          Point{
              .x = current_horizontal.first.x,
              .y = colision.y},
          Point{
              .x = colision.x + 1,
              .y = colision.y}};

      std::pair<Point, Point> down{
          Point{
              .x = colision.x,
              .y = colision.y + 1},
          Point{
              .x = colision.x,
              .y = current_vertical.second.y}};

      std::pair<Point, Point> left{
          Point{
              .x = colision.x + 1,
              .y = colision.y},
          Point{
              .x = current_horizontal.second.x,
              .y = colision.y}};

      int top_length = calculate_vertical_length(top);
      int right_length = calculate_horizontal_length(right);
      int down_length = calculate_vertical_length(down);
      int left_length = calculate_horizontal_length(left);

      int bigger_horizontal = std::max(right_length, left_length);
      int bigger_vertical = std::max(top_length, down_length);

      int biggest_combo = std::max(calculate_horizontal_length(current_horizontal) + bigger_vertical, calculate_vertical_length(current_vertical) + bigger_horizontal);

      // std::cout
      //     << "MAX: " << max << "\n";
      // std::cout << "\n";
    }
  }

  std::cout << max;

  return 0;
}
