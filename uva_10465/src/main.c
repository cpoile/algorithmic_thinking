#include <stdlib.h>
#include <stdio.h>

/* fill memo up to t with combinations of m and n */
void fill(int memo[], int t, int m, int n)
{
    int i;
    for (i = 1; i * m <= t; i++) {
        memo[i * m] = i;
    }
    for (i = 1; i * n <= t; i++) {
        if (memo[i * n] < i) {
            memo[i * n] = i;
        }
    }
}

int find_highest_combination(const int memo[], int t)
{
    /* if there was an even # of burgers at time t, start with that. */
    int highest = memo[t], i;

    for (i = t - 1; i > 0; i--) {
        /* if two combinations adding up to t both have burgers, that's a valid combination. */
        if (memo[i] && memo[t - i]) {
            if ((memo[i] + memo[t - i]) > highest) {
                highest = memo[i] + memo[t - i];
            }
        }
    }
    return highest;
}

int main(void)
{
    /* freopen("in2.txt", "r", stdin); */

    int m, n, t;

    while (scanf("%d %d %d", &m, &n, &t) != EOF) {
        int memo[10000] = {0};
        fill(memo, t, m, n);

        int beer = -1, answer = 0;
        while (answer == 0 && t - beer > 0) {
            beer++;
            answer = find_highest_combination(memo, t - beer);
        }

        if (beer > 0) {
            printf("%d %d\n", answer, beer);
        } else {
            printf("%d\n", answer);
        }
    }

    return EXIT_SUCCESS;
}
