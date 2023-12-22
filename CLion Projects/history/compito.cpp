#include "compito.h"
#include <cstring>

//funzioni helper per le stringhe
void copia_stringa(char dest[], const char* orig) {
    //ci si aspetta che il controllo sulla orig sia fatto dal chiamante
    int i = 0;
    do {
        dest[i] = *(orig + i);
        i++;
    } while(*(orig + i) != '\0');
}

bool confronta_stringa(const char str1[], const char* str2) {
    int i = 0;
    do {
        if(str1[i] != *(str2 + i)) {
            return false;
        }
        i++;
    } while(*(str2 + i) != '\0');
    return true;
}

History::History() {
    _root = nullptr;
}

History::~History() {
    Entry* current;
    current = _root;
    while(current != nullptr) {
        Entry* temp = current;
        current = current->next;
        delete temp;
    }
}

void History::record(const int year, const char *descr) {
    if(strlen(descr) > STR_LEN) {
        return; //descrizione troppo lunga
    }
    Entry* entry = new Entry;
    entry->date = year;
    copia_stringa(entry->description, descr);
    entry->next = nullptr;
    //append
    if(_root == nullptr) { //primo elemento inserito
        _root = entry;
        return;
    }
    if(year < _root->date) { //va messo in prima posizione
        entry->next = _root;
        _root = entry;
        return;
    }
    Entry* current;
    Entry* temp = nullptr;
    for(current = _root; current != nullptr && current->date <= year; current = current->next) {
        temp = current;
    }
    //posizione intermedia o finale (in quel caso current varrebbe comunque nullptr)
    temp->next = entry;
    entry->next = current;
}

void History::forget(const char *descr) {
    if(strlen(descr) > STR_LEN) {
        return; //descrizione troppo lunga
    }
    if(_root == nullptr) { //lista vuota
        return;
    }
    Entry* current;
    Entry* temp = nullptr;
    for(current = _root; current != nullptr && !confronta_stringa(current->description, descr); current = current->next) {
        temp = current;
    }
    if(current == nullptr) { //elemento inesistente
        return;
    }
    if(temp == nullptr) {
        _root = current->next;
    } else {
        temp->next = current->next;
    }
    delete current;
}

std::ostream &operator<<(std::ostream &stream, const History &hist) {
    stream << "-- HISTORY --\n";
    History::Entry* current = hist._root;
    while(current != nullptr){
        if(current->date <= 0) { //BC
            stream << (-current->date + 1) << " BC\n";
        } else { //AD
            stream << current->date << " AD\n";
        }
        stream << current->description << "\n";
        stream << "-----\n";
        current = current->next;
    }
    return stream;
}

//seconda parte
int History::_length() {
    int count = 0;
    Entry* current = _root;
    while(current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

int History::longest_period() {
    if(_length() < 2) {
        return -1; //caso speciale
    }
    int max = 0;
    Entry* current;
    Entry* temp = nullptr;
    for(current = _root; current != nullptr; current = current->next) {
        if(temp != nullptr) {
            int newMax = current->date - temp->date;
            if(newMax > max) {
                max = newMax;
            }
        }
        temp = current;
    }
    return max;
}

void History::forget(const int from_year, const int to_year) {
    if(_root == nullptr) { //lista vuota
        return;
    }
    Entry* current = _root;
    Entry* temp = nullptr;
    while(current != nullptr) {
        if(current->date > from_year && current->date < to_year) {
            if(temp == nullptr) {
                Entry* deleter = current;
                _root = current->next;
                current = current->next;
                delete deleter;
            } else {
                Entry* deleter = current;
                temp->next = current->next;
                current = current->next;
                delete deleter;
            }
        } else {
            current = current->next;
            if(temp == nullptr) {
                temp = _root;
            } else {
                temp = temp->next;
            }
        }
    }
}

History* create_alternative(const History& hist1, const int fork_year, const History& hist2) {
    History* newHistory = new History();
    for(int i = 0; i < 2; i++) {
        History::Entry* current;
        if(i == 0) {
            current = hist1._root;
        } else {
            current = hist2._root;
        }
        while(current != nullptr) {
            bool condition;
            if(i == 0) {
                condition = current->date < fork_year;
            } else {
                condition = current->date >= fork_year;
            }
            if(condition) {
                newHistory->record(current->date, current->description);
            } else {
                if(i == 0) {
                    break;
                }
            }
            current = current->next;
        }
    }
    return newHistory;
}

