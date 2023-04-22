#ifndef CODEC_H
#define CODEC_H

#include <QTextCodec>

class codec {
public:
    static const QTextCodec* get_codec() {
        return QTextCodec::codecForName("Utf-8");
    }
};

#endif // CODEC_H
