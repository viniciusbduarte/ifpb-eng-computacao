bool ehPrimo(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

bool contemPrimo(const int* arr, int tamanho) {
    for (int i = 0; i < tamanho; ++i)
        if (ehPrimo(arr[i])) return true;
    return false;
}
