#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#include <qt5/QtCore/qobject.h>
#include <QThread>
#include <QApplication>
#include <QObject>
#include <QString>
#include <QtCore/qglobal.h>
#include <QIODevice>
#include <QDataStream>
#include <QAudioOutput>
#include <QAudio>
#include <QFile>
#include <QBuffer>
#include <QAudioOutput>
#include <QByteArray>

#include "audiooutput.h"
#include "sonic.h"


// Because string operations in C SUCK
#define MANUAL_FILE "/home/marvin/Media/Audiobooks/Snapshot.wav"



int main(int argc, char** argv) {
    QApplication app(argc, argv);
    //* app.setApplicationName("Audio Output Test");

    const char command[] = "ffmpeg -hide_banner -loglevel error -i \""
                           MANUAL_FILE
                           "\" -codec pcm_u8 -vn -f u8 -ac 2 -ar 44100 -ss 3 -t 20 -";

    const char cntFramesCmd[] = "ffprobe -hide_banner -loglevel error -select_streams a -count_packets "
                                "-show_entries stream=nb_read_packets -of csv=p=0 -i \""
                                MANUAL_FILE "\"";

    //* It's a bit crowded, but all this does is stuff the output of /|\ into data->frames
    // {
    //     FILE* framePipe;
    //     framePipe = popen(cntFramesCmd, "r");
    //     if (framePipe == NULL) { printf("Error: Failed to open frame count pipe"); return 5; }
    //     char tmp[16];
    //     short digits = fread(tmp, sizeof(char), 16, framePipe);
    //     data->frames = strtol(tmp, NULL, 10);
    //     int tmprtn = pclose(framePipe);
    //     if (tmprtn) { printf("\"%s\" returned error: %d", command, tmprtn); return tmprtn; }
    //     printf("%ld\n", data->frames);
    // }


    // //* If it's a .aax file and we are given an authcode, tell ffmpeg so it can decrypt it
    // int len = filepath.length() - 1;
    // if (filepath[len - 2] == 'a' and filepath[len - 1] == 'a' and filepath[len] == 'x'){
    //     if (authcode){
    //         printf("The file ends in .aax, using activation bytes: %s\n", authcode);
    //         command << " -activation_bytes " << authcode;
    //     }
    //     else
    //         leave(2, "Can't play .aax files without an authcode.");
    // }


    printf("Executing command: \"%s\"\n", command);

    FILE* pipe = popen(command, "r");
    if (pipe == NULL) { printf("Error: Failed to open pipe"); return 5; }

    AudioPlayer player(pipe);
    app.exec();

    int rtn = pclose(pipe);
    if (rtn) { printf("\"%s\" returned error: %d\n", command, rtn); return rtn; }

    return 0;
}


/*
static int setargs(char *args, char **argv)
{
    int count = 0;

    while (isspace(*args)) ++args;
    while (*args) {
        if (argv) argv[count] = args;
        while (*args && !isspace(*args)) ++args;
        if (argv && *args) *args++ = '\0';
        while (isspace(*args)) ++args;
        count++;
    }
}

char **parsedargs(char *args, int *argc)
{
    char **argv = NULL;
    int    argn = 0;

    if (args && *args
        && (args = strdup(args))
        && (argn = setargs(args,NULL))
        && (argv = malloc((argn+1) * sizeof(char *)))) {
          *argv++ = args;
          argn = setargs(args,argv);
    }

    if (args && !argv) free(args);

    *argc = argn;
    return argv;
}

void freeparsedargs(char **argv)
{
    if (argv) {
        free(argv[-1]);
        free(argv-1);
    }
}
    return count;
}

int main()
{
    char **argv;
    char *cmd;
    int argc;

    cmd = "ffmpeg -i infile outfile";
    argv = parsedargs(cmd,&argc);
    ffmpeg(argc, argv);
}
*/