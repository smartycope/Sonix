#include "Book.h"

const Book& Book::operator =(const Book& book){
    Book* b = (Book*)malloc(sizeof(Book*));
//    Book* b = new Book(book);
    // debugs("Here!");
    return *const_cast<Book*>(b);
}

void Book::_onAuthorChanged(){ }
void Book::_onTitleChanged(){ }
void Book::_onCoverChanged(){ }
void Book::_onPositionChanged(){ }

void Book::init(){
    note()
    connect(this, SIGNAL(onAuthorChanged()),   SLOT(_onAuthorChanged()));
    connect(this, SIGNAL(onTitleChanged()),    SLOT(_onTitleChanged()));
    connect(this, SIGNAL(onCoverChanged()),    SLOT(_onCoverChanged()));
    connect(this, SIGNAL(onPositionChanged()), SLOT(_onPositionChanged()));
    note()
}
