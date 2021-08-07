#ifndef __COPE__
#define __COPE__

#include "cope.h"

// #ifdef __cplusplus
//     extern "C"{
// #endif

static void _printMetaData(int line, char* func, char* file){
    printsl(METADATA_COLOR);

    #ifdef METADATA_FORMAT_STANDARD
        #if defined PRINT_FILE || defined PRINT_FUNC || defined PRINT_LINE
            printsl("[");
        #endif
        #ifdef PRINT_FILE
            printsl(file);
            printsl("->");
        #endif
        #ifdef PRINT_FUNC
            printsl(func);
            printsl("->");
        #endif
        #ifdef PRINT_LINE
            printsl(line);
        #endif
        #if defined PRINT_FILE || defined PRINT_FUNC || defined PRINT_LINE
            printsl("] ");
        #endif
    #else
        #ifdef METADATA_FORMAT_VSCODE
            printsl("[\"");
            printsl(file);
            printsl("\", line ");
            printsl(line);
            #ifdef PRINT_FUNC
                printsl(", in ")
                printsl(func);
            #endif
            printsl("] ")
        #endif
    #endif

    printsl(COLOR_RESET);
}

static void printDebugCount(){
    ++debugCount;
    printfclrsl(DEBUG_COUNT_COLOR, "%lu: ", debugCount);
}

/*
static char* color(char* str, char* color){
    char* tmp = (char*)malloc(MAX_STR_LEN);
    strcat(tmp, color);
    strcat(tmp, str);
    strcat(tmp, COLOR_RESET);
    strcat(tmp, "\0");

    return tmp;
    // return strcat(strcat(color, str), COLOR_RESET);
}
*/

static char* _fmt(char* str, ...){
    // char* tmp;
    char* tmp = (char*)malloc(MAX_STR_LEN);
    // char tmp[MAX_PARAM_LEN];
    va_list args;
    va_start(args, str);
    // vsnprintf(tmp, MAX_PARAM_LEN, str, args);
    vsnprintf(tmp, MAX_STR_LEN, str, args);
    va_end(args);
    return tmp;
}

static void printfclr(const char* color, const char* str, ...){
    printsl(color);

    va_list args;
    va_start(args, str);
    vprintf(str, args);
    va_end(args);

    print(COLOR_RESET);
}

static void printfclrsl(const char* color, const char* str, ...){
    printsl(color);

    va_list args;
    va_start(args, str);
    vprintf(str, args);
    va_end(args);

    printsl(COLOR_RESET);
}

static void printclrsl(const char* color, const char* str){
    printsl(color);
    printsl(str);
    printsl(COLOR_RESET);
}

static void printclr(const char* color, const char* str){
    printsl(color);
    printsl(str);
    print(COLOR_RESET);
}

static std::string color(std::string str, std::string color){
    return color + str + COLOR_RESET;
}

static std::string fmt(std::string str, ...){
    // char* tmp;
    char* tmp = (char*)malloc(str.size() + 1);
    // char tmp[MAX_PARAM_LEN];
    va_list args;
    va_start(args, str);
    // vsnprintf(tmp, MAX_PARAM_LEN, str, args);
    vsnprintf(tmp, str.size(), str.c_str(), args);
    va_end(args);
    return tmp;
}

// #ifdef __cplusplus
//     }
// #endif

// #endif

#endif // __COPE__
