#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <functional>
#include <stack>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <unordered_set>
#include <set>
#define INF 10e12
#define FOR(start,end,incre) for(int i = start; i < end; i += incre)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ill;
typedef vector<ill> vp;
int* compute_lps(char*);
void search_kmp(char* text,char* pat)
{
    int i = 0;
    int j = 0;
    int m = strlen(text);
    int n = strlen(pat);
    int* lps = compute_lps(pat);
    while(i < m)
    {
        if(text[i] == text[j])
        {
            i++;
            j++;
        }
        if(j == m)
        {
            printf("found start : %d end : %d\n",j - n,j-1);
        }
        if(text[i] != text[j])
        {
            if(j != 0)
            {
                j = lps[j-1];
            }
            else
            {
                i++;
            }
        }
    }
}
int* compute_lps(char* pat)
{
    int i = 1;
    int j = 0;
    int str_len = strlen(pat);
    int* lps = new int[str_len];
    lps[0] = 0;
    while(i < str_len)
    {
        if(pat[i] == pat[j])
        {
            lps[i] = j+1;
            i++;
            j++;
        }
        else
        {
            if(j != 0)
            {
                j = lps[j-1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}
int main()
{
    char* pat = "ABABCABAB";
    char* text = "ABABDABACDABABCABAB";
    search_kmp(text, pat);
	return 0;

}
