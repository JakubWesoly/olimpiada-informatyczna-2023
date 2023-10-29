#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdint>

std::vector<char> GetMostFrequentChar(const std::string &str)
{
  std::unordered_map<char, int> charCounts;

  for (char c : str)
  {
    charCounts[c]++;
  }

  int maxCount = 0;
  for (const auto &entry : charCounts)
  {
    maxCount = std::max(maxCount, entry.second);
  }

  std::vector<char> mostFrequent;
  for (const auto &entry : charCounts)
  {
    if (entry.second == maxCount)
    {
      mostFrequent.push_back(entry.first);
    }
  }

  return mostFrequent;
}

char GetAdditionalChar(const std::string &chars)
{
  std::vector<char> mostFrequentChar = GetMostFrequentChar(chars);
  if (mostFrequentChar.size() == 1)
  {
    return mostFrequentChar[0];
  }
  else if (mostFrequentChar.size() > 1)
  {
    return *std::min_element(mostFrequentChar.begin(), mostFrequentChar.end());
  }
  return 'a';
}

void ComputeLPSArray(const std::string &pat, int M, std::vector<int> &lps)
{
  int len = 0;
  int i = 1;
  lps[0] = 0;

  while (i < M)
  {
    if (pat[i] == pat[len])
    {
      len++;
      lps[i] = len;
      i++;
    }
    else
    {
      if (len != 0)
      {
        len = lps[len - 1];
      }
      else
      {
        lps[i] = len;
        i++;
      }
    }
  }
}

std::string KMPSearch(const std::string &pat, const std::string &txt)
{
  int M = pat.length();
  int N = txt.length();
  std::string answer = "";
  std::vector<int> lps(M, 0);

  int j = 0;

  ComputeLPSArray(pat, M, lps);

  int i = 0;
  while ((N - i) >= (M - j))
  {
    if (pat[j] == txt[i])
    {
      j++;
      i++;
    }
    if (j == M)
    {
      if (i < N)
      {
        answer += txt[i];
      }
      j = lps[j - 1];
    }
    else if (i < N && pat[j] != txt[i])
    {
      if (j != 0)
        j = lps[j - 1];
      else
        i = i + 1;
    }
  }

  return answer;
}

std::string GetAnswer(int64_t n, int64_t k, int64_t a, int64_t b, const std::string &s)
{
  std::string result = s;
  while (result.length() < b)
  {
    std::string chars = KMPSearch(result.substr(result.length() - k), result);
    result += GetAdditionalChar(chars);
  }
  if (a <= result.length())
  {
    return result.substr(a - 1, std::min(b - a + 1, result.length() - a + 1));
  }
  else
  {
    return "";
  }
}

int main()
{
  std::ios_base::sync_with_stdio(0);
  int64_t n, k, a, b;
  std::string s;
  std::cin >> n >> k >> a >> b >> s;
  std::cout << GetAnswer(n, k, a, b, s) << std::endl;
  return 0;
}
