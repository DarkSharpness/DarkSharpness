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
    a = 255u; // for RGB initialization only 
    uint8_t pre_r = 0u;
    uint8_t pre_g = 0u;
    uint8_t pre_b = 0u;
    uint8_t pre_a = 255u;

    for (int i = 0; i < px_num; ++i) {
        r = QoiReadU8();
        g = QoiReadU8();
        b = QoiReadU8();
        if (channels == 4) a = QoiReadU8();
        
        if(r == pre_r &&
           g == pre_g &&
           b == pre_b &&
           a == pre_a) {
            // use RGBA Encoding
            if(run == 61) { // identical 62 times,so write in first
                QoiWriteU8(QOI_OP_RUN_TAG | 61);
                run = 0;
            } else { // add run by 1
                ++run;
            }
        } else {
            if(run > 0) { // RGB is different,so clear run first
                QoiWriteU8(QOI_OP_RUN_TAG | (run-1));
                run = 0;
            } 
            // hashed index position
            uint8_t index = QoiColorHash(r,g,b,a);

            if(history[index][0] == r &&
               history[index][1] == g &&
               history[index][2] == b &&
               history[index][3] == a) { // successful history match
                QoiWriteU8(QOI_OP_INDEX_TAG | index);
            } else { // history match failed
                    
                    // update history[index]
                    history[index][0] = r;
                    history[index][1] = g;
                    history[index][2] = b;
                    history[index][3] = a;

                    if(a != pre_a) {
                        // RGBA Encoding
                        QoiWriteU8(QOI_OP_RGBA_TAG);
                        QoiWriteU8(r);
                        QoiWriteU8(g);
                        QoiWriteU8(b);
                        QoiWriteU8(a);
                    } else { // RGB difference exists
                        int8_t dr = r - pre_r; // delta_red
                        int8_t dg = g - pre_g; // delta_green
                        int8_t db = b - pre_b; // delta_blue

                        if(dr <=1 && dr >= -2 &&
                           dg <=1 && dg >= -2 &&
                           db <=1 && db >= -2) {
                            // use DIFF Encoding
                            QoiWriteU8(QOI_OP_DIFF_TAG |
                                       (dr+2) << 4     |
                                       (dg+2) << 2     |
                                       (db+2));
                        } else if (dg >= -32 && dg <= 31 &&
                                   dr - dg >= -8 && dr - dg <= 7 &&
                                   db - dg >= -8 && db - dg <= 7) {
                            // use LUMA Encoding 
                            QoiWriteU8(QOI_OP_LUMA_TAG | (dg + 32));
                            QoiWriteU8(((dr - dg + 8) << 4 ) | (db - dg + 8));
                        } else {
                            // use RGB Encoding
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
    if(run > 0) { // file end,so clear run first
        QoiWriteU8(QOI_OP_RUN_TAG | (run-1));
        run = 0;
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

    uint8_t r = 0u;
    uint8_t g = 0u;
    uint8_t b = 0u;
    uint8_t a = 255u;
    uint8_t index; // hashed index position

    for (int i = 0; i < px_num; ++i) {
        if(run) { // RUN Decoding
            --run;
        } else { // not RUN Decoding

            // read header information
            uint8_t head = QoiReadU8();

            if(head == QOI_OP_RGB_TAG) {
                // RGB Decoding
                r = QoiReadU8();
                g = QoiReadU8();
                b = QoiReadU8();
            } else if(head == QOI_OP_RGBA_TAG) {
                // RGBA Decoding
                r = QoiReadU8();
                g = QoiReadU8();
                b = QoiReadU8();
                a = QoiReadU8();
            } else if((head & QOI_MASK_2) == QOI_OP_RUN_TAG) {
                // RUN Decoding
                run = head & 63u; // run = head % 64
            } else if((head & QOI_MASK_2) == QOI_OP_INDEX_TAG) {
                // INDEX Decoding
                index = head & 63u; // index = head % 64
                r = history[index][0];
                g = history[index][1];
                b = history[index][2];
                a = history[index][3];
            } else if((head & QOI_MASK_2) == QOI_OP_DIFF_TAG) {
                // DIFF Decoding
                r += ((head & 48u) >> 4) - 2; // take bit 4,5
                g += ((head & 12u) >> 2) - 2; // take bit 2,3
                b += ((head &  3u)     ) - 2; // take bit 0,1
            } else if((head & QOI_MASK_2) == QOI_OP_LUMA_TAG) {
                //LUMA Decoding

                int8_t  dg   = (head & 63u) - 32; // delta_green
                // recording delta_red - delta_green,delta_blue - delta_green
                uint8_t byte = QoiReadU8();

                r += dg + (((byte & 240u) >> 4) - 8);
                b += dg + (((byte &  15u)     ) - 8);
                g += dg;
            } else { // Incorrectly Encoded
                return false;
            }


            index = QoiColorHash(r,g,b,a);
            // update history
            history[index][0] = r;
            history[index][1] = g;
            history[index][2] = b;
            history[index][3] = a;
        }

        QoiWriteU8(r);
        QoiWriteU8(g);
        QoiWriteU8(b);
        if (channels == 4) QoiWriteU8(a);
    }
    if(run > 0) return false; // too many runs


    bool valid = true;
    for (int i = 0; i < sizeof(QOI_PADDING) / sizeof(QOI_PADDING[0]); ++i) {
        if (QoiReadU8() != QOI_PADDING[i]) valid = false;
    }

    return valid;
}

#endif // QOI_FORMAT_CODEC_QOI_H_
