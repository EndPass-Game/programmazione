#include <iostream>
#include <assert.h>

// Questo è un piccolo template per i test. 
// Ci sarebbero delle feature che sarebbe bello se si potesse implementare: 
// TODO:
// 1. Funzione runner nei test: che fa il display della funzione che viene runnata
// e a seconda del risultato fa un ✔️ oppure un ❌
// 2. Una funzione che esegua automaticamente i test presenti nel namespace, o classe
// 3. Una flag, o direttiva che contrassegni se una funzione è da runnare o meno
// 4. Una piccola CLI che gestisca ad alto livello le funzioni da chiamare (un pò come
// cargo test di rust, se si esegue la funzione con un nome di una classe esegue solo
// un insieme di test ben precisato)
// AGGIORNAMENTO: 1,2,3 sono più o meno fatti, 2 non`e automatizzato ma utilizza la table
// 3 basterebbe commentare una entry nella tabella dei test

struct functionMETA {
    void (*funcPtr) ();
    const char *funcName;
};

namespace test {
    void example_test() {
        assert(true); // TODO: Non riesce a darmi un ❌, mi sa che deve essere sovrascritto, un wrapper ad assert?
    }

    // Wrappa una funzione di test per mostrare l'output di una funzione
    // se gli assert dentro la funzione di test sono corretti, da input a schermo
    void run(void (*f) (), const char *name) {
        std::cout << "Testando la funzione: " << name  << " --- ";
        f();
        std::cout << "Ok! ✔️" << std::endl;
    }
}

functionMETA func_table[] = {
    {test::example_test, "example_test"},
};


int main() {
    uint n_tests = sizeof(func_table) / sizeof(functionMETA);
    for (uint i = 0; i < n_tests; i++) {
        test::run(func_table[i].funcPtr, func_table[i].funcName);
    }
}