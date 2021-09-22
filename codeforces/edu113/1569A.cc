// ID  : 1569A (Balanced Substring)
// URL : https://codeforces.com/contest/1569/problem/A

#include <stdio.h>

// Trivial; just find a substring which contains equal numbers of 'a's and 'b's.

int main()
{
    int t;
    scanf("%d", &t);
 
    char buf[64];
    int numA[64];
    int numB[64];
    for (int i = 0; i < t; ++i)
    {
        int n;
        scanf("%d", &n);
        scanf("%s", buf);

	// Subsum tables
        for (int j = 0; j < n; ++j)
        {
            numA[j] = numB[j] = 0;
        }
        for (int j = 0; j < n; ++j)
        {
            if (buf[j] == 'a')
            {
                numA[j] += 1;
            }
            else
            {
                numB[j] += 1;
            }
        }
        for (int j = 1; j < n; ++j)
        {
            numA[j] += numA[j-1];
            numB[j] += numB[j-1];
        }

	// Find a balanced substring
        bool found = false;
        for (int x = 0; x < n; ++x)
        {
            for (int y = x; y < n; ++y)
            {
                if (numA[y] - (x == 0 ? 0 : numA[x-1]) == numB[y] - (x == 0 ? 0 : numB[x-1]))
                {
                    printf("%d %d\n", x+1, y+1);
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found)
        {
            puts("-1 -1");
        }
    }
 
    return 0;
}

