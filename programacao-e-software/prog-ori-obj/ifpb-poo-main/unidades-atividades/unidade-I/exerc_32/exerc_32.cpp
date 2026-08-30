bool contemPrimo(const std::vector<int>& vec) {
    for (int n : vec)
        if (ehPrimo(n)) return true;
    return false;
}
