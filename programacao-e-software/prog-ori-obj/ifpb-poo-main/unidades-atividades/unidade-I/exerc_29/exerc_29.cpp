bool contemMaiuscula(const std::string& str) {
    for (char c : str) {
        if (std::isupper(c)) return true;
    }
    return false;
}
