//una history è una lista di eventi
//un evento è rappresentato da:
//anno (unsigned con enum bc ac oppure int)
//descrizione di 30 caratteri

#include <ostream>
#define STR_LEN 100

#ifndef HISTORY_COMPITO_H
#define HISTORY_COMPITO_H

class History {
private:
    struct Entry {
        int date; //ISO 8601, year = 0 -> 1BC; year = 1 -> 1AD
        char description[STR_LEN + 1];
        Entry* next;
    };
    Entry* _root;
    int _length(); //helper che restituisce il numero di elementi

    //occulto costruttori di copia e assegnamento
    History(History& hist);
    History& operator=(History& hist);
public:
    History();
    ~History();
    friend std::ostream& operator<<(std::ostream& stream, const History& hist);
    void record(int year, const char* descr);
    void forget(const char* descr);

    //seconda parte
    int longest_period();
    void forget(int from_year, int to_year);
    friend History* create_alternative(const History& hist1, int fork_year, const History& hist2);
};

#endif //HISTORY_COMPITO_H
