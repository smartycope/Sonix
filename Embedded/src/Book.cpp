#include "Book.h"
#include "sndfile.h"
// #include "sndfile.h"


Book::Book(string filepath): filepath(filepath){
    int pos;
    string title;
    string author;
    string narrator;
    string description;
    string releaseDate;

    /* open file for modification */
    // MP4FileHandle file = MP4Read(filepath.c_str()); // MP4Modify( argv[1], MP4_DETAILS_ERROR, 0 );
    // if(file == MP4_INVALID_FILE_HANDLE) {
    //     printf( "MP4Modify failed\n" );
    //     // return 1;
    //     quit(1);
    // }
    // /* show existing iTMF items */
    // MP4ItmfItemList* list = MP4ItmfGetItems(file);
    // printf("list=%p\n", list);
    // if(list) {
    //     printf( "list size=%u\n", list->size );
    //     uint32_t i;
    //     for( i = 0; i < list->size; i++ ) {
    //         MP4ItmfItem* item = &list->elements[i];
    //         printf( "item[%u] type=%s\n", i, item->code );
    //         if( item->mean )
    //             printf( " mean=%s\n", item->mean );
    //         if( item->name )
    //             printf( " name=%s\n", item->name );
    //         int j;
    //         for( j = 0; j < item->dataList.size; j++ ) {
    //             MP4ItmfData* data = &item->dataList.elements[j];
    //             printf( " data[%u] typeCode=%u valueSize=%u\n", j, data->typeCode, data->valueSize );
    //         }
    //     }
    //     /* caller responsiblity to free */
    //     MP4ItmfItemListFree( list );
    // }


    SF_INFO info;
    file = sf_open(filepath.c_str(), SFM_READ, &info);
    channels   = info.channels;
    format     = info.format;
    frames     = info.frames;
    samplerate = info.samplerate;
    sections   = info.sections;
    seekable   = info.seekable;

    _debug(frames);
    _debug(channels);
    _debug(seekable);

    //* Get metadata here

    // const char* TITLE = sf_get_string(file, SF_STR_TITLE);
    // const char* ARTIST = sf_get_string(file, SF_STR_ARTIST);
    // const char* COMMENT = sf_get_string(file, SF_STR_COMMENT);
    // const char* COPYRIGHT = sf_get_string(file, SF_STR_COPYRIGHT);
    // const char* ALBUM = sf_get_string(file, SF_STR_ALBUM);
    // const char* DATE = sf_get_string(file, SF_STR_DATE);
    // const char* GENRE = sf_get_string(file, SF_STR_GENRE);
    // const char* LICENSE = sf_get_string(file, SF_STR_LICENSE);
    // const char* SOFTWARE = sf_get_string(file, SF_STR_SOFTWARE);
    // const char* TRACKNUMBER = sf_get_string(file, SF_STR_TRACKNUMBER);

    // printf("TITLE: %s", TITLE);
    // printf("ARTIST: %s", ARTIST);
    // printf("COMMENT: %s", COMMENT);
    // printf("COPYRIGHT: %s", COPYRIGHT);
    // printf("ALBUM: %s", ALBUM);
    // printf("DATE: %s", DATE);
    // printf("GENRE: %s", GENRE);
    // printf("LICENSE: %s", LICENSE);
    // printf("SOFTWARE: %s", SOFTWARE);
    // printf("TRACKNUMBER: %s", TRACKNUMBER);


    // std::cout
    //           << "TITLE: "       << TITLE       << '\n'
    //           << "ARTIST: "      << ARTIST      << '\n'
    //           << "COMMENT: "     << COMMENT     << '\n'
    //           << "COPYRIGHT: "   << COPYRIGHT   << '\n'
    //           << "ALBUM: "       << ALBUM       << '\n'
    //           << "DATE: "        << DATE        << '\n'
    //           << "GENRE: "       << GENRE       << '\n'
    //           << "LICENSE: "     << LICENSE     << '\n'
    //           << "SOFTWARE: "    << SOFTWARE    << '\n'
    //           << "TRACKNUMBER: " << TRACKNUMBER << '\n';
    // std::cout << sf_get_string(file, SF_STR_FIRST) << '\n';
    // std::cout << sf_get_string(file, SF_STR_LAST) << '\n';

}

Book::~Book(){
    sf_close(file);
}
