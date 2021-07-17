class Player(){
public:
    bool togglePaused();
    void skip(int amount);
    void jump(int chapters);
    void flushStream();
private:
    SNDFILE* sndFile;
    SF_INFO sfInfo;
    int filePosition;
    int sonicPosition;
    int outputPosition;
    float* sonicBuffer;
}