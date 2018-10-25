#include "loadfile.h"
#include <string>
std::string loadFile(std::string filedir){

    FILE *filep;
    filep=fopen(filedir.c_str(),"r");
    std::string file = std::string();
    char temp_char;
    while(0==0){
        temp_char=fgetc(filep);
        if(temp_char==EOF){
            break;
        }else{
            file.push_back(temp_char);
        }
    }
    fclose(filep);
    return file;
}