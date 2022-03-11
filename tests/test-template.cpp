#include <iostream>
#include <cassert>

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
namespace test {
    void example_test() {
        // TODO: è molto noioso ripetere questi due cout, inizio e fine, si riesce a generalizzare in una funzione runner?
        std::cout << "Testando la funzione: " << __func__ << " --- ";
        assert(true); // TODO: Non riesce a darmi un ❌, mi sa che deve essere sovrascritto, un wrapper ad assert?
        std::cout << "Ok! ✔️" << std::endl;
    }
}

int main() {
    test::example_test();
}