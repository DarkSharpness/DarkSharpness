#ifndef QOI_FORMAT_CODEC_QOI_H_
#define QOI_FORMAT_CODEC_QOI_H_

#include "utils.h"

constexpr uint8_t QOI_OP_INDEX_TAG = 0x00;
constexpr uint8_t QOI_OP_DIFF_TAG  = 0x40;
constexpr uint8_t QOI_OP_LUMA_TAG  = 0x80;
constexpr uint8_t QOI_OP_RUN_TAG   = 0xc0; 
constexpr uint8_t QOI_OP_RGB_TAG   = 0xfe;
constexpr uint8_t QOI_OP_RGBA_TAG  = 0xff;
constexpr uint8_t QOI_PADDING[8] = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u};
constexpr uint8_t QOI_MASK_2 = 0xc0;

/**
 * @brief encode the raw pixel data of an image to qoi format.
 *
 * @param[in] width image width in pixels
 * @param[in] height image height in pixels
 * @param[in] channels number of color channels, 3 = RGB, 4 = RGBA
 * @param[in] colorspace image color space, 0 = sRGB with linear alpha, 1 = all channels linear
 *
 * @return bool true if it is a valid qoi format image, false otherwise
 */
bool QoiEncode(uint32_t width, uint32_t height, uint8_t channels, uint8_t colorspace = 0);

/**
 * @brief decode the qoi format of an image to raw pixel data
 *
 * @param[out] width image width in pixels
 * @param[out] height image height in pixels
 * @param[out] channels number of color channels, 3 = RGB, 4 = RGBA
 * @param[out] colorspace image color space, 0 = sRGB with linear alpha, 1 = all channels linear
 *
 * @return bool true if it is a valid qoi format image, false otherwise
 */
bool QoiDecode(uint32_t &width, uint32_t &height, uint8_t &channels, uint8_t &colorspace);


bool QoiEncode(uint32_t width, uint32_t height, uint8_t channels, uint8_t colorspace) {

    // qoi-header part

    // write magic bytes "qoif"
    QoiWriteChar('q');
    QoiWriteChar('o');
    QoiWriteChar('i');
    QoiWriteChar('f');
    // write image width
    QoiWriteU32(width);
    // write image height
    QoiWriteU32(height);
    // write channel number
    QoiWriteU8(channels);
    // write color space specifier
    QoiWriteU8(colorspace);

    /* qoi-data part */
    int run = 0;
    int px_num = width * height;

    uint8_t history[64][4];
    memset(history, 0, sizeof(history));

    uint8_t r, g, b, a;
    a = 255u;
    uint8_t pre_r, pre_g, pre_b, pre_a;
    pre_r = 0u;
    pre_g = 0u;
    pre_b = 0u;
    pre_a = 255u;
    uint8_t run = 0u; // count of runs

    for (int i = 0; i < px_num; ++i) {
        r = QoiReadU8();
        g = QoiReadU8();
        b = QoiReadU8();
        if (channels == 4) a = QoiReadU8();

        // TODO

        if(a != pre_a) { // use RGBA encoding
            QoiWriteU8(QOI_OP_RGBA_TAG);
            QoiWriteU8(r);
            QoiWriteU8(g);
            QoiWriteU8(b);
            QoiWriteU8(a);
        } else { // a identical now
            if(r == pre_r && 
               b == pre_b &&
               g == pre_g) { // rgb also identical,use RUN encoding
                if(run == 61) { //identical 62 times,so write in first 
                    QoiWriteU8(QOI_OP_RUN_TAG | run);
                    run = 0;
                } else { // add run by 1
                    ++run;
                }
            } else {
                if(run > 0) { // rgb different,so clear run first
                    QoiWriteU8(QOI_OP_RUN_TAG | (run-1));
                    run = 0;
                } 
                // index_position 
                uint8_t index = (r * 3 + g * 5 + b * 7 + a * 11) % 64; 
                if(history[index][0] == r &&
                   history[index][1] == g &&
                   history[index][2] == b &&
                   history[index][3] == a) { // successful history match
                   QoiWriteU8(QOI_OP_INDEX_TAG | index);
                } else { 
                    // update history[index]
                    history[index][0] = r;
                    history[index][1] = g;
                    history[index][2] = b;
                    history[index][3] = a;
                    int8_t dr = r - pre_r;
                    int8_t dg = g - pre_g;
                    int8_t db = b - pre_b;
                    if(dr <=1 && dr >= -2 &&
                       dg <=1 && dg >= -2 &&
                       db <=1 && db >= -2) { // use DIFF encoding
                        QoiWriteU8(QOI_OP_DIFF_TAG |
                                   (dr+2) << 4     |
                                   (dg+2) << 2     |
                                   (db+2));
                    } else if (dg >= -32 && dg <= 31 &&  
                               dr - dg >= -8 && dr - dg <= 7 &&
                               db - dg >= -8 && db - dg <= 7) {
                        // use LUMA encoding 
                        QoiWriteU8(QOI_OP_LUMA_TAG | (dg + 32));
                        QoiWriteU8((dr - dg + 8) << 4 | (db - dg + 8));
                    } else { // use RGB encoding
                        QoiWriteU8(QOI_OP_RGB_TAG);
                        QoiWriteU8(r);
                        QoiWriteU8(g);
                        QoiWriteU8(b);
                    }
                }
            }
        }
        pre_r = r;
        pre_g = g;
        pre_b = b;
        pre_a = a;
    }

    // qoi-padding part
    for (int i = 0; i < sizeof(QOI_PADDING) / sizeof(QOI_PADDING[0]); ++i) {
        QoiWriteU8(QOI_PADDING[i]);
    }

    return true;
}

bool QoiDecode(uint32_t &width, uint32_t &height, uint8_t &channels, uint8_t &colorspace) {

    char c1 = QoiReadChar();
    char c2 = QoiReadChar();
    char c3 = QoiReadChar();
    char c4 = QoiReadChar();
    if (c1 != 'q' || c2 != 'o' || c3 != 'i' || c4 != 'f') {
        return false;
    }

    // read image width
    width = QoiReadU32();
    // read image height
    height = QoiReadU32();
    // read channel number
    channels = QoiReadU8();
    // read color space specifier
    colorspace = QoiReadU8();

    int run = 0;
    int px_num = width * height;

    uint8_t history[64][4];
    memset(history, 0, sizeof(history));

    uint8_t r, g, b, a;
    a = 255u;

    for (int i = 0; i < px_num; ++i) {

        // TODO

        QoiWriteU8(r);
        QoiWriteU8(g);
        QoiWriteU8(b);
        if (channels == 4) QoiWriteU8(a);
    }

    bool valid = true;
    for (int i = 0; i < sizeof(QOI_PADDING) / sizeof(QOI_PADDING[0]); ++i) {
        if (QoiReadU8() != QOI_PADDING[i]) valid = false;
    }

    return valid;
}

#endif // QOI_FORMAT_CODEC_QOI_H_
