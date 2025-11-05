//
// Created by 20648 on 2023/7/21.
//

#include "rtsp.h"
#include "rtspUI/rtspui.h"
#include "videoWin/videoLabel.h"
#include <QDebug>
#include <QCoreApplication>

rtsp::rtsp(QObject *parent) : QObject(parent)
{
    isCanRun = true;
}

rtsp::~rtsp()
{

}

void rtsp::restartThread()
{
    readFrame_status = true;
}

void rtsp::setUrl(QString url, int devnum)
{
    m_url = url;
    thisdevnum = devnum;

    //m_url.contains("deep",Qt::CaseInsensitive) ||
    if(m_url.contains("ir",Qt::CaseInsensitive)) {
        is_rgb_image = false;
        qDebug() << "is gray image";
    }
    else {
        is_rgb_image = true;
        qDebug() << "is rgb image";
    }
}

void rtsp::pull_stream()
{
    QString errStr;
    AVCodec *pCodec;

    qDebug()<<"rtsp thread run";
    while(isCanRun) {
        //打开输入视频文件
        if (avformat_open_input(&m_pFormatCtx, m_url.toStdString().c_str(), NULL, NULL) != 0) {
            printf("Couldn't open input stream.\n");
            errStr = "Couldn't open input stream.";
            goto m_pFormatCtx_err;
        }

        qDebug() << "avformat_open_input success";
        rtsp_init_status = OPEN_SUCCESS;

        if (avformat_find_stream_info(m_pFormatCtx, NULL) < 0) {
            printf("Couldn't find stream information.\n");
            errStr = "Couldn't find stream information.";
            goto m_pFormatCtx_err;
        }

        for (int i = 0; i < m_pFormatCtx->nb_streams/*视音频流的个数*/; i++) {
            //查找视频
            if (m_pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                m_videoIndex = i;
                break;
            }
        }
        if (m_videoIndex == -1) {
            printf("Couldn't find a video stream.\n");
            errStr = "Couldn't find a video stream.";
            goto m_pFormatCtx_err;
        }

        /**
        *  不赞成这样使用
        *  pCodecCtx = pFormatCtx->streams[videoIndex]->codec;	//指向AVCodecContext的指针
        */

        m_pCodecCtx = avcodec_alloc_context3(NULL);
        if (m_pCodecCtx == NULL) {
            printf("Could not allocate AVCodecContext\n");
            errStr = "Could not allocate AVCodecContext.";
            goto m_pCodecCtx_err;
        }
        avcodec_parameters_to_context(m_pCodecCtx, m_pFormatCtx->streams[m_videoIndex]->codecpar);

        //指向AVCodec的指针.查找解码器
        pCodec = avcodec_find_decoder(m_pCodecCtx->codec_id);
        if (pCodec == NULL) {
            printf("Codec not found pCodec\n");
            errStr = "Codec not found pCodec.";
            goto m_pCodecCtx_err;
        }
        //打开解码器
        if (avcodec_open2(m_pCodecCtx, pCodec, NULL) < 0) {
            printf("Could not open codec.\n");
            errStr = "Could not open codec.";
            goto m_pCodecCtx_err;
        }

        //视频宽
        m_width = m_pFormatCtx->streams[m_videoIndex]->codecpar->width;

        //视频高
        m_height = m_pFormatCtx->streams[m_videoIndex]->codecpar->height;

        //获取帧率;
        m_fps = r2d(m_pFormatCtx->streams[m_videoIndex]->avg_frame_rate);
        if (m_fps == 0) {
            m_fps = 25;
        }

        //开始解码
        decodeStream();

        /*解码过程出现问题 无法读取帧数据*/
        while(!readFrame_status) QThread::sleep(1);
    }
    return;

m_pCodecCtx_err:
    free_m_pCodecCtx();
m_pFormatCtx_err:
    free_m_pFormatCtx();

    qDebug()<<"-----emit sigErr(errStr)------";
    rtsp_init_status = OPEN_FALSE;
    emit sigErr(errStr);
}

double rtsp::r2d(AVRational r)
{
    return r.den == 0 ? 0 : (double)r.num / (double)r.den;
}

void rtsp::decodeStream()
{
    int width;
    int height;
    int nBGRFrameSize;
    int ret;
    start_decodeStream_status = true;
    qDebug()<<"start decodeStream";
    while (1) {
        //初始化AVPacket
        AVPacket* m_avpacket = av_packet_alloc();
        m_avpacket->data = NULL;
        //从输入视频文件中读取一帧数据，并且将其存储在这个指针中。如果读取成功，这个函数会返回一个非负数
        if (av_read_frame(m_pFormatCtx, m_avpacket) >= 0) {
            // 线程锁在业务开始和和结束的地方
            pauseLock.lock();
            if (m_avpacket->stream_index == m_videoIndex) { //这个数据包是否属于视频流
                //将这个数据包发送给解码器上下文。解码器上下文是一个结构体，用来存储解码器的相关信息和状态
                ret = avcodec_send_packet(m_pCodecCtx, m_avpacket);
                if (ret >= 0) {
                    //初始化frame,
                    AVFrame *m_frame = av_frame_alloc();
                    //从解码器上下文中接收一帧解码后的数据
                    ret = avcodec_receive_frame(m_pCodecCtx, m_frame);
                    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                        qDebug()<<"avcodec_receive_frame error: ret = " << ret;
                    } else if (ret < 0) {
                        qDebug()<<"avcodec_receive_frame error: ret < 0";
                    } else {

                        width = m_frame->width;
                        height = m_frame->height;

                        AVFrame *pFrameRGB = av_frame_alloc();//申请内存
                        //以字节为单位的缓冲区大小，在发生故障时为负错误码
                        if (is_rgb_image)
                            nBGRFrameSize = av_image_get_buffer_size(AV_PIX_FMT_RGB32, width, height, 1);
                        else
                            nBGRFrameSize = av_image_get_buffer_size(AV_PIX_FMT_GRAY8, width, height, 1);
                        uint8_t *rgbBuffer = (uint8_t *) av_malloc(nBGRFrameSize);

                        /*根据指定的图像参数和提供的数组设置数据指针和行大小。使用指向图像数据缓冲区的src地址填充给定图像的字段。
                         * 根据指定的像素格式，将设置一个或多个图像数据指针和行大小。*/
                        av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize,
                                             rgbBuffer, is_rgb_image ? AV_PIX_FMT_RGB32 : AV_PIX_FMT_GRAY8,
                                             width, height, 1);

                        SwsContext *img_convert_ctx;
                        switch (m_pCodecCtx->pix_fmt) {
                            case AV_PIX_FMT_YUV422P: {
                                //改变像素格式
                                img_convert_ctx = sws_getContext(width, height,
                                                                 AV_PIX_FMT_YUV422P,
                                                                 width, height,
                                                                 AV_PIX_FMT_RGB32,
                                                                 SWS_BICUBIC,
                                                                 NULL, NULL, NULL);
                                break;
                            }

                            case AV_PIX_FMT_YUV420P: {
                                //改变像素格式
                                img_convert_ctx = sws_getContext(width, height,
                                                                 AV_PIX_FMT_YUV420P,
                                                                 width, height,
                                                                 is_rgb_image ? AV_PIX_FMT_RGB32 : AV_PIX_FMT_GRAY8,
                                                                 SWS_BICUBIC,
                                                                 NULL, NULL, NULL);
                                break;
                            }

                            default: {
                                printf("default format:%d\n", m_pCodecCtx->pix_fmt);
                                return;
                            }
                        }

                        //颜色空间转换 yuv420p --> rgb32
                        sws_scale(img_convert_ctx,
                                  (uint8_t const *const *) m_frame->data,
                                  m_frame->linesize, 0, height, pFrameRGB->data,
                                  pFrameRGB->linesize);
                        //发送信号，转换后的rgb buffer

                        emit sigData(rgbBuffer, width, height, is_rgb_image);

                        //释放内存
                        av_frame_free(&pFrameRGB);
                        sws_freeContext(img_convert_ctx);
                    }
                    av_frame_free(&m_frame);
                }
            }
            pauseLock.unlock();
            if (!isCanRun) {
                qDebug()<<"退出RTSP拉流循环";
                readFrame_status = true; //退出等待readFrame_status标志位成立的循环 以便能够正常退出线程
                av_packet_free(&m_avpacket);
                break;
            }
        }
        else {
            qDebug()<<"av_read_frame ERROR";
            readFrame_status = false;
            av_packet_free(&m_avpacket);
            emit readFrameErr();
            break;
        }
        av_packet_free(&m_avpacket);//释放内存
    }

    //释放内存
    free_m_pCodecCtx();
    free_m_pFormatCtx();
}

//void rtsp::free_m_avpacket() {
//    av_packet_unref(m_avpacket);
//    delete m_avpacket;
//    m_avpacket = NULL;
//}
//
//void rtsp::free_m_frame() {
//    av_frame_free(&m_frame);
//    m_frame = NULL;
//}

void rtsp::free_m_pCodecCtx() {
    avcodec_close(m_pCodecCtx);
    avcodec_free_context(&m_pCodecCtx);
    m_pCodecCtx = NULL;
}

void rtsp::free_m_pFormatCtx() {
    avformat_close_input(&m_pFormatCtx);
    avformat_free_context(m_pFormatCtx);
    m_pFormatCtx = NULL;
}

/*停止*/
void rtsp::stopThread()
{
    /*已保证先点击暂停按钮，才能删除*/
    if (this->pauseLock.try_lock()) {

    } else {
        qDebug()<<"pauseLock unlock";
        this->pauseLock.unlock();
    }
    isCanRun = false;
}

/*暂停*/
void rtsp::pauseThread()
{
    qDebug()<<"pauseThread";
    this->pauseLock.lock();
}

/*恢复*/
void rtsp::resumeThread()
{
    qDebug()<<"resumeThread";
    this->pauseLock.unlock();
}
