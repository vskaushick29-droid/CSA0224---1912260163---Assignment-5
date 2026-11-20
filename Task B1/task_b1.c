#include <stdio.h>
#include <stdlib.h>

long long calls = 0;

long long power_linear(long long base, int exp)
{
    calls++;
    if (exp == 0) return 1;
    return base * power_linear(base, exp - 1);
}

long long power_fast(long long base, int exp)
{
    long long half;
    calls++;
    if (exp == 0) return 1;
    half = power_fast(base, exp / 2);
    if (exp % 2 == 0) return half * half;
    return base * half * half;
}

long long power_naive_divide(long long base, int exp)
{
    calls++;
    if (exp == 0) return 1;
    if (exp % 2 == 0)
        return power_naive_divide(base, exp / 2) * power_naive_divide(base, exp / 2);
    return base * power_naive_divide(base, exp / 2) * power_naive_divide(base, exp / 2);
}

long long power_iterative(long long base, int exp)
{
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result *= base;
        base *= base;
        exp /= 2;
    }
    return result;
}

int sum_digits(long long n)
{
    if (n == 0) return 0;
    return (int)(n % 10) + sum_digits(n / 10);
}

int digital_root_recursive(long long n)
{
    if (n < 0) n = -n;
    if (n < 10) return (int)n;
    return digital_root_recursive(sum_digits(n));
}

int digital_root_formula(long long n)
{
    if (n < 0) n = -n;
    if (n == 0) return 0;
    return 1 + (int)((n - 1) % 9);
}

int main(int argc, char *argv[])
{
    int i;
    long long a, b, c;
    long long root_tests[5] = {0, 1, 9, 38, 9875};
    int pow_exps[4] = {0, 1, 7, 10};
    int sizes[4] = {10, 100, 1000, 10000};

    if (argc == 3 && argv[1][0] == 's') {
        int depth = atoi(argv[2]);
        long long res;
        calls = 0;
        res = power_linear(1, depth);
        printf("linear(1, %d) = %lld in %lld calls\n", depth, res, calls);
        return 0;
    }

    if (argc == 3 && argv[1][0] == 'i') {
        int depth = atoi(argv[2]);
        long long res = power_iterative(1, depth);
        printf("iterative(1, %d) = %lld\n", depth, res);
        return 0;
    }

    calls = 0;
    a = power_linear(2, 30);
    printf("linear: %lld in %lld calls\n", a, calls);

    calls = 0;
    b = power_fast(2, 30);
    printf("fast  : %lld in %lld calls\n", b, calls);

    calls = 0;
    c = power_naive_divide(2, 30);
    printf("naive : %lld in %lld calls\n", c, calls);

    printf("\n--- B1.1 Validation Tests ---\n");
    for (i = 0; i < 5; i++) {
        printf("digital_root(%lld): recursive=%d, formula=%d\n",
               root_tests[i],
               digital_root_recursive(root_tests[i]),
               digital_root_formula(root_tests[i]));
    }

    for (i = 0; i < 4; i++) {
        long long r_lin, c_lin, r_fst, c_fst;
        calls = 0;
        r_lin = power_linear(3, pow_exps[i]);
        c_lin = calls;
        calls = 0;
        r_fst = power_fast(3, pow_exps[i]);
        c_fst = calls;
        printf("3^%d: linear=%lld (%lld calls), fast=%lld (%lld calls), iter=%lld\n",
               pow_exps[i], r_lin, c_lin, r_fst, c_fst, power_iterative(3, pow_exps[i]));
    }

    printf("\n--- B1.3 Call Count Scaling ---\n");
    for (i = 0; i < 4; i++) {
        int n = sizes[i];
        long long lin_calls, fast_calls;
        calls = 0;
        power_linear(1, n);
        lin_calls = calls;

        calls = 0;
        power_fast(1, n);
        fast_calls = calls;

        printf("n = %-6d | linear calls = %-6lld | fast calls = %lld\n",
               n, lin_calls, fast_calls);
    }

    return 0;
}
