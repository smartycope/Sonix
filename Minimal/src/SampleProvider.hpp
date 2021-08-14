#include <QObject>
#include <QString>
#include <QtCore/qglobal.h>
#include <string>
#include <QIODevice>
#include <QDataStream>
// #include <qqml.h>

#include <QAudioOutput>
#include <QAudio>
#include <QFile>
#include <QBuffer>
#include <QAudioOutput>



#include <string>
#include <QByteArray>

class SampleProvider: public QObject{
    Q_OBJECT
public:
    QBuffer* audioBuffer;
    QAudioOutput* audioOut;
    QIODevice* audioOutDevice;

    SampleProvider();
    ~SampleProvider();

    std::string printQAudioError(QAudio::Error err);
    std::string printQAudioState(QAudio::State state);
    void audioStateChanged(QAudio::State state);
};