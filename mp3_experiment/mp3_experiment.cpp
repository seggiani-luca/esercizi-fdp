#include <iostream>
#include <fstream>
using namespace std;

int BUF_LENGTH = 128;

enum Encoding {
    unicode,
    ascii
};

int strlen(char* str) {
    int i = 0;
    while(*(str+i) != '\0') {
        i++;
    }
    return i;
}
char* look_for(char* buffer, char* str) {
    int tries = 0;
    while(tries < BUF_LENGTH) {
        int found = true;
        for(int i = 0; i < strlen(str); i++) {
            if(buffer[i] != str[i]) {
                found = false;
                break;
            }
        }
        if(found) {
            //don't return search string
            buffer += strlen(str);
            return buffer;
        }
        buffer++;
        tries++;
    }
    return "\0";
}

char* get_encoded_string(char* buffer) {
    //sweep through empty data at beginning of string
    int count = 0;
    int i = 0;
    while(*buffer == 0x00 & i < BUF_LENGTH) {
        count++;
        buffer++;
    }
    count+=2;

    //create string and add terminator
    char* str = new char[count];
    str[count] = '\0';

    //detect encoding
    Encoding encoding;
    if(*buffer == 0xFF) {
        encoding = unicode;
    } else {
        encoding = ascii;
    }
    
    //fill string accordingly
    buffer++;
    switch(encoding) {
        case unicode:
            for(int i = 0; i < count; i++) {
                str[i] = *buffer;
                buffer += 2; //ignore non-ascii characters
            }
            break;
        case ascii:
            for(int i = 0; i < count; i++) {
                str[i] = *buffer;
                buffer++;
            }
            break;
        default:
            //revert to ascii
            for(int i = 0; i < count; i++) {
                str[i] = *buffer;
                buffer++;
            }
    }

    return str;
}

int main(int argc, char** argv) {
    //handle arguments
    if(argc < 2) {
        cout << "No arguments!" << endl;
        return 0;
    }

    //handle stream
    ifstream stream;
    stream.open(argv[1]);

    //allocate buffer
    char * buffer = new char[BUF_LENGTH];
    //read buffer from file
    stream.read(buffer, BUF_LENGTH);
    
    char* tag = "TIT2";
    cout << "Tag " << tag << " trovato: ";
    char* data = new char[BUF_LENGTH];
    data = look_for(buffer, tag);
    char* title = get_encoded_string(data);
    cout << title;
    delete[] title;
    cout << endl;

    //deallocate buffer
    delete[] buffer;
    return 0;
}