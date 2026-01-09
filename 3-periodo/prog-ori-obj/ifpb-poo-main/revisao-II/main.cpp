#include "Bruxo.hpp"
#include "Mala.hpp"
#include "Varinha.hpp"

int main() {
    Bruxo h("Harry Potter", "Grifinória");

    Varinha v("Azevinho", 27.5);
    h.empunharVarinha(&v);

    Mala m(3);
    h.pegarMala(&m);

    h.setFeitico("Expecto Patronum");

    h.display();
    h.lancarFeitico();

    h.soltarVarinha();
    h.lancarFeitico();

    return 0;
}
