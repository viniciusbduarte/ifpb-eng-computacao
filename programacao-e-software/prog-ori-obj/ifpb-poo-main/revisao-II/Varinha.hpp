#pragma once
#include <string>
using namespace std;

class Varinha {
private:
    string madeira;
    float comprimento;

public:
    Varinha(string madeira = "", float comprimento = 0.0);
    string getMadeira() const;
    float getComprimento() const;
};
