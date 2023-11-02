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

char* my_strchr(char* dest, char c) {
	while(*dest != '\0') {
		if(*dest == c)
			return dest;
		dest++;
	}
	return nullptr;
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
	
	char* frase = "Il grande elefante bianco";
	char carattere = 'g';
	cout << "La stringa e': " << frase << endl;
	char* p = my_strchr(frase, carattere);
	if(p != NULL) {
		cout << "Il carattere " << carattere << " si trova in posizione: " << (p - frase) << endl;;
	} else {
		cout << "Il carattere "  << carattere <<  " non si trova nella stringa" << endl;
	}
	char carattere2 = 'z';
	p = my_strchr(frase, carattere2);
	if(p != NULL) {
		cout << "Il carattere " << carattere2 << " si trova in posizione: " << (p - frase) << endl;;
	} else {
		cout << "Il carattere "  << carattere2 <<  " non si trova nella stringa" << endl;
	}

    return 0;
}
