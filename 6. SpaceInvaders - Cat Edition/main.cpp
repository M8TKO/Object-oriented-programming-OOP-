#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Prozor.h"
#include "Igra.h"
#include "neprijatelj.h"
#include "metak.h"
#include "secret.h"

using namespace std;

int main() {
    Igra igra;
    while (!igra.dohvatiProzor()->jelGotov()) {
        igra.obradiUlaz();
        igra.update();
        igra.renderiraj();
        igra.restartSata();
    }

    return 0;
}
