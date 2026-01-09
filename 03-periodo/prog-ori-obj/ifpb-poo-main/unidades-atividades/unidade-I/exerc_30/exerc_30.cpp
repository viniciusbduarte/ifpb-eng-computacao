void paraMinusculas(std::string& str) {
    for (char& c : str) {
        c = std::tolower(c);
    }
}
