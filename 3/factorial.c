static unsigned long long factorial(int n) {
    unsigned long long res = 1;
	if (n <= 0)
		return 0;
    for (int i = 1; i <= n; i++)
        res *= i;
    return res;
}