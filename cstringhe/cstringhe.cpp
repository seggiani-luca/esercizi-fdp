#include <iostream>
using namespace std;


int my_strlen(char* str) {
    int len = 0;
    while(*str != '\0') {
        str++;
        len++;
    }
    return len;
}

void my_strcpy(char* dest, const char* src) {
    while(*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = *src;
}

void my_strcat(char* dest, const char* src) {
    int i = 0;
    while(*(dest+i) != '\0')
        i++;
    while(*src != '\0') {
        *(dest+i) = *src;
        i++;
        src++;
    }
}

int main() {
    char* str = "Stringa";
    cout << my_strlen(str) << endl;

    char* src = "Texas";
    char dest[my_strlen(src) + 1];
    my_strcpy(dest, src);
    cout << dest << endl;

    char concDest[11];
    my_strcpy(concDest, "Carpe");
    char* concSrc = " Diem";
    my_strcat(concDest, concSrc);
    cout << concDest << endl;

    return 0;
}
