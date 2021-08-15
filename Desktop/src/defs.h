#pragma once

#include <stdint.h>

#define ABOUT_MSG "This is the SuperSonic Audiobook player! It allows you to listen to any audiobook, in any format, at any speed.\n"\
                  "This program is free software (free as in freedom, not free beer). It lets you listen to YOUR books how YOU like.\n"\
                  "To listen to audible books, you can download them*, and either convert them to a 'normal' file format**, or you can\n"\
                  "even listen to them directly, however to do that, you need to get and enter your audible activation code***.\n"\
                  "\n"\
                  "* You can either download audible books directly from their website (go to library and click the download button), or\n"\
                  "free software like OpenAudible (LINK) can do it for you.\n"\
                  "** OpenAudible can automatically convert audible books for you, or you can do it with more free software like: (LINKS)\n"\
                  "***To get the audible activation code linked with your account, you can use these programs: (LINKS)\n"\
                  "\n"\
                  "If you like this program, since it is free software (free as in freedom AND free beer), consider donating to me to pay for\n"\
                  "my ever growing addiction to audiobooks.\n"\
                  "If instead, you hate this program and would like to point out what's wrong with it, please do! I made this myself in my\n"\
                  "proverbial basement. I would love feedback.\n"\
                  "Either way, feel free to reach out to me at smartycope@gmail.com.\n"\
                  "\n"\
                  "NOT-copyright 2021, Copeland Carter. No rights reserved."

bool verbose;

typedef struct{
    ulong hour;
    ulong min;
    ulong sec;
}PrettyTime;


static PrettyTime getPrettyTime(const ulong& secs){
    PrettyTime t;
    t.hour = secs / 3600;
    t.min  = (secs % 3600) / 60;
    t.sec  = (secs % 3600) % 60;
    return t;
}


static void addAuthcode(const string& file, stringstream& stream, const string& authcode){
    int len = file.length() - 1;
    if (file[len - 2] == 'a' and file[len - 1] == 'a' and file[len] == 'x'){
        if (not authcode.empty()){
            stream << " -activation_bytes " << authcode;
            if (verbose)
                printf("The file ends in .aax, using activation bytes: %s\n", authcode.c_str());
        }
        else{
            printf("Can't play .aax files without an authcode.");
            exit(2);
        }
    }
}