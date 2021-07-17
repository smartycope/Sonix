#ifndef COPE
#define COPE

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

// I like bool. It helps the programmer know what the variable is
//   supposed to be used for
#define true  1
#define false 0
#define byte  unsigned char

// I LIKE these.
#define not !
#define or  ||
#define and &&
#define nor && !

// Not sure why you need to do this twice, but it works this way
#define CONCAT(a, b) a##b
#define CC(a, b) CONCAT(a, b)

#define __LIST_OF_TYPES__ \
    void *:                   "void*",                   \
    _Bool:                    "bool",                    \
    _Bool *:                  "bool*",                   \
    char:                     "char",                    \
    char *:                   "char*",                   \
    signed char:              "signed char",             \
    signed char *:            "signed char*",            \
    unsigned char:            "unsigned char",           \
    unsigned char *:          "unsigned char*",          \
    short int:                "short",                   \
    short int *:              "short*",                  \
    unsigned short int:       "unsigned short",          \
    unsigned short int *:     "unsigned short*",         \
    int:                      "int",                     \
    int *:                    "int*",                    \
    unsigned int:             "unsigned int",            \
    unsigned int *:           "unsigned int*",           \
    long int:                 "long int",                \
    long int *:               "long int*",               \
    unsigned long int:        "unsigned long int",       \
    unsigned long int *:      "unsigned long int*",      \
    long long int:            "long long int",           \
    long long int *:          "long long int*",          \
    unsigned long long int:   "unsigned long long int",  \
    unsigned long long int *: "unsigned long long int*", \
    float:                    "float",                   \
    float*:                   "float*",                  \
    double:                   "double",                  \
    double*:                  "double*",                 \
    long double:              "long double",             \
    long double*:             "long double*",            \
                                                         \
    const void *:                   "const void*",                   \
    const _Bool:                    "const bool",                    \
    const _Bool *:                  "const bool*",                   \
    const char:                     "const char",                    \
    const char *:                   "const char*",                   \
    const signed char:              "const signed char",             \
    const signed char *:            "const signed char*",            \
    const unsigned char:            "const unsigned char",           \
    const unsigned char *:          "const unsigned char*",          \
    const short int:                "const short",                   \
    const short int *:              "const short*",                  \
    const unsigned short int:       "const unsigned short",          \
    const unsigned short int *:     "const unsigned short*",         \
    const int:                      "const int",                     \
    const int *:                    "const int*",                    \
    const unsigned int:             "const unsigned int",            \
    const unsigned int *:           "const unsigned int*",           \
    const long int:                 "const long int",                \
    const long int *:               "const long int*",               \
    const unsigned long int:        "const unsigned long int",       \
    const unsigned long int *:      "const unsigned long int*",      \
    const long long int:            "const long long int",           \
    const long long int *:          "const long long int*",          \
    const unsigned long long int:   "const unsigned long long int",  \
    const unsigned long long int *: "const unsigned long long int*", \
    const float:                    "const float",                   \
    const float*:                   "const float*",                  \
    const double:                   "const double",                  \
    const double*:                  "const double*",                 \
    const long double:              "const long double",             \
    const long double*:             "const long double*",            \
                                                                                       \
    const volatile void *:                   "const volatile void*",                   \
    const volatile _Bool:                    "const volatile bool",                    \
    const volatile _Bool *:                  "const volatile bool*",                   \
    const volatile char:                     "const volatile char",                    \
    const volatile char *:                   "const volatile char*",                   \
    const volatile signed char:              "const volatile signed char",             \
    const volatile signed char *:            "const volatile signed char*",            \
    const volatile unsigned char:            "const volatile unsigned char",           \
    const volatile unsigned char *:          "const volatile unsigned char*",          \
    const volatile short int:                "const volatile short",                   \
    const volatile short int *:              "const volatile short*",                  \
    const volatile unsigned short int:       "const volatile unsigned short",          \
    const volatile unsigned short int *:     "const volatile unsigned short*",         \
    const volatile int:                      "const volatile int",                     \
    const volatile int *:                    "const volatile int*",                    \
    const volatile unsigned int:             "const volatile unsigned int",            \
    const volatile unsigned int *:           "const volatile unsigned int*",           \
    const volatile long int:                 "const volatile long int",                \
    const volatile long int *:               "const volatile long int*",               \
    const volatile unsigned long int:        "const volatile unsigned long int",       \
    const volatile unsigned long int *:      "const volatile unsigned long int*",      \
    const volatile long long int:            "const volatile long long int",           \
    const volatile long long int *:          "const volatile long long int*",          \
    const volatile unsigned long long int:   "const volatile unsigned long long int",  \
    const volatile unsigned long long int *: "const volatile unsigned long long int*", \
    const volatile float:                    "const volatile float",                   \
    const volatile float*:                   "const volatile float*",                  \
    const volatile double:                   "const volatile double",                  \
    const volatile double*:                  "const volatile double*",                 \
    const volatile long double:              "const volatile long double",             \
    const volatile long double*:             "const volatile long double*",            \
                                                                           \
    volatile void *:                   "volatile void*",                   \
    volatile _Bool:                    "volatile bool",                    \
    volatile _Bool *:                  "volatile bool*",                   \
    volatile char:                     "volatile char",                    \
    volatile char *:                   "volatile char*",                   \
    volatile signed char:              "volatile signed char",             \
    volatile signed char *:            "volatile signed char*",            \
    volatile unsigned char:            "volatile unsigned char",           \
    volatile unsigned char *:          "volatile unsigned char*",          \
    volatile short int:                "volatile short",                   \
    volatile short int *:              "volatile short*",                  \
    volatile unsigned short int:       "volatile unsigned short",          \
    volatile unsigned short int *:     "volatile unsigned short*",         \
    volatile int:                      "volatile int",                     \
    volatile int *:                    "volatile int*",                    \
    volatile unsigned int:             "volatile unsigned int",            \
    volatile unsigned int *:           "volatile unsigned int*",           \
    volatile long int:                 "volatile long int",                \
    volatile long int *:               "volatile long int*",               \
    volatile unsigned long int:        "volatile unsigned long int",       \
    volatile unsigned long int *:      "volatile unsigned long int*",      \
    volatile long long int:            "volatile long long int",           \
    volatile long long int *:          "volatile long long int*",          \
    volatile unsigned long long int:   "volatile unsigned long long int",  \
    volatile unsigned long long int *: "volatile unsigned long long int*", \
    volatile float:                    "volatile float",                   \
    volatile float*:                   "volatile float*",                  \
    volatile double:                   "volatile double",                  \
    volatile double*:                  "volatile double*",                 \
    volatile long double:              "volatile long double",             \
    volatile long double*:             "volatile long double*",            \
    \
    default: "unknown"


#define typename(x) _Generic((x), __LIST_OF_TYPES__)

#define printf_dec_format(x) _Generic((x), \
    char: "%c", \
    signed char: "%hhd", \
    unsigned char: "%hhu", \
    signed short: "%hd", \
    unsigned short: "%hu", \
    signed int: "%d", \
    unsigned int: "%u", \
    long int: "%ld", \
    unsigned long int: "%lu", \
    long long int: "%lld", \
    unsigned long long int: "%llu", \
    float: "%f", \
    double: "%f", \
    long double: "%Lf", \
    char *: "%s", \
    void *: "%p")

// print var / print var same line
#define nl() puts((char*)"\n");
#define printvsl(x) printf(printf_dec_format(x), x);
#define printv(x) printf(printf_dec_format(x), x), nl();

#define debug_0()    printDebugCount(), printf("HERE! HERE!\n");
#define debug_1(var) printDebugCount(), printf("[%u] %s %s = ", __LINE__, typename(var), #var), printv(var);

#define debug_X(x, var, FUNC, ...) FUNC
#define debug(...)  debug_X(,##__VA_ARGS__,  \
                        debug_1(__VA_ARGS__),\
                        debug_0(__VA_ARGS__) \
                    )


unsigned long debugCount = 0;

static void printDebugCount(){
    ++debugCount;
    printf("%lu: ", debugCount);
}

static void print(char *str){
    printv((char*)str);
    nl();
}



//* How to do optional-arguement macros
/*
// The multiple macros that you would need anyway
#define XXX_0()                     <code for no arguments>
#define XXX_1(A)                    <code for one argument>
#define XXX_2(A,B)                  <code for two arguments>
#define XXX_3(A,B,C)                <code for three arguments>
#define XXX_4(A,B,C,D)              <code for four arguments>

// The interim macro that simply strips the excess and ends up with the required macro
#define XXX_X(x,A,B,C,D,FUNC, ...)  FUNC

// The macro that the programmer uses
#define XXX(...)                    XXX_X(,##__VA_ARGS__,\
                                          XXX_4(__VA_ARGS__),\
                                          XXX_3(__VA_ARGS__),\
                                          XXX_2(__VA_ARGS__),\
                                          XXX_1(__VA_ARGS__),\
                                          XXX_0(__VA_ARGS__)\
                                         )
*/


#endif // COPE
