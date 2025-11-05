//
// Created by 20648 on 2023/7/21.
//

#ifndef QT_RTSP_H
#define QT_RTSP_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <QTimer>
#include <QString>
#include <QMutex>

extern "C"
{
    #include "libavformat/avformat.h"
    #include "libavutil/dict.h"
    #include "libswscale/swscale.h"
    #include "libavutil/imgutils.h"
    #include "libavcodec/avcodec.h"
};

class rtsp : public QObject
{
Q_OBJECT

public:
    explicit  rtsp(QObject *parent = nullptr);
    ~rtsp();

Q_SIGNALS:
    void sigData(uint8_t* rgbBuffer, int width, int height, bool pixel);
    void sigErr(QString errStr);
    void readFrameErr();

public Q_SLOTS:
    void pull_stream();

public:
    enum {
        OPENING,
        OPEN_FALSE,
        OPEN_SUCCESS
    };
    void setUrl(QString url, int devnum);

    void stopThread();
    void pauseThread();
    void resumeThread();
    void restartThread();

    bool start_decodeStream_status = false;
    int8_t rtsp_init_status = OPENING;
private:
    QString m_url;
    int thisdevnum;
    bool isCanRun = true;
    bool readFrame_status = true;
    bool is_rgb_image = true;

    AVFormatContext* m_pFormatCtx = NULL;
    AVCodecContext* m_pCodecCtx = NULL;
    // = NULL;
    //AVFrame *m_frame = NULL;
    //视频index
    int m_videoIndex = -1;
    //视频总时间,单位ms
    int64_t m_totalTime = 0;
    //视频宽度;
    int m_width = 0;
    //视频高度;
    int m_height = 0;
    //视频帧率;
    int m_fps = 0;

    QMutex pauseLock;

    void free_m_pFormatCtx();
    void free_m_pCodecCtx();

protected:
    double r2d(AVRational r);
    void decodeStream();
};



#endif //QT_RTSP_H
