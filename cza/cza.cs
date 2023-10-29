using System;
using System.Collections.Generic;
using System.Linq;

public class Solution {
	public string GetAnswer(int n,int k,int a,int b,string s)
	{
		while(s.Length<b)
		{
			string chars = KMPSearch(s.Substring(s.Length-k),s);
			s += GetAdditionalChar(chars);
		}
		return s.Substring(a-1,b+1-a);
	}

	private char GetAdditionalChar(string chars)
	{
		char[] mostFrequentChar = GetMostFrequentChar(chars);
		if(mostFrequentChar.Length == 1)
		{
			return mostFrequentChar[0];
		}else if(mostFrequentChar.Length > 1)
		{
			return GetTheSmallestChar(mostFrequentChar);
		}
		return 'a';
	}

	private char GetTheSmallestChar(char[] chars)
	{
		char result = chars[0];
		for(int i = 1;i < chars.Length; i++)
		{
			if(chars[i] < result)
			{
				result = chars[i];
			}
		}
		return result;
	}

	private char[] GetMostFrequentChar(string str)
	{
		Dictionary<char, int> chars = new Dictionary<char, int>();

		foreach (char c in str)
		{
			if (chars.ContainsKey(c)) chars[c]++;
			else chars.Add(c, 1);
		}

		int max = chars.Values.Max();
		return chars.Where(b => b.Value == max).Select(b => b.Key).ToArray();
	}

    private string KMPSearch(string pat, string txt)
    {
        int M = pat.Length;
        int N = txt.Length;
		string answer = "";
        int[] lps = new int[M];

        int j = 0;

        computeLPSArray(pat, M, lps);

        int i = 0;
        while ((N - i) >= (M - j)) {
            if (pat[j] == txt[i]) {
                j++;
                i++;
            }
            if (j == M) {
				if(i<N)
				{
					answer += txt[i];
				}
                j = lps[j - 1];
            }

            else if (i < N && pat[j] != txt[i]) {

                if (j != 0)
                    j = lps[j - 1];
                else
                    i = i + 1;
            }
        }

		return answer;
    }

    void computeLPSArray(string pat, int M, int[] lps)
    {
        int len = 0;
        int i = 1;
        lps[0] = 0;

        while (i < M) {
            if (pat[i] == pat[len]) {
                len++;
                lps[i] = len;
                i++;
            }
            else
            {
                if (len != 0) {
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

    public static void Main()
    {
		int n,k,a,b;
		string s;
		n = 11;
		k = 3;
		a = 12;
		b = 13;
		s = "abaaabababa";
		Console.WriteLine(new Solution().GetAnswer(n,k,a,b,s));
    }
}