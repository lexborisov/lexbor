/*
 * Copyright (C) 2019 Alexander Borisov
 *
 * Author: Alexander Borisov <borisov@lexbor.com>
 */

/*
 * Caution!
 * This file generated by the script "utils/lexbor/encoding/single-byte.py"!
 * Do not change this file!
 */

#include <unit/test.h>

#include <lexbor/encoding/encoding.h>
#include <lexbor/encoding/single.h>


TEST_BEGIN(decode)
{
    size_t size;
    lxb_char_t data;
    lxb_status_t status;
    lxb_codepoint_t cp;
    const lxb_char_t *ref;
    lxb_encoding_decode_t ctx;
    const lxb_encoding_data_t *enc_data;
    const lxb_encoding_multi_index_t *entry;

    enc_data = lxb_encoding_data(%%CONST_NAME%%);

    size = sizeof(%%DATA%%)
           / sizeof(lxb_encoding_multi_index_t);

    test_ne(size, 0);

    for (lxb_codepoint_t i = 0; i < 0x80; i++) {

        data = (lxb_char_t) (i);
        ref = &data;

        lxb_encoding_decode_init(&ctx, enc_data, &cp, 1);

        status = enc_data->decode(&ctx, &ref, ref + 1);
        test_ne(status, LXB_STATUS_ERROR);
        test_eq(*ctx.buffer_out, i);
    }

    for (size_t i = 0; i < size; i++) {

        entry = &%%DATA%%[i];
        if (entry->codepoint == LXB_ENCODING_ERROR_CODEPOINT) {
            continue;
        }

        data = (lxb_char_t) (i + 0x80);
        ref = &data;

        lxb_encoding_decode_init(&ctx, enc_data, &cp, 1);

        status = enc_data->decode(&ctx, &ref, (ref + 1));
        test_ne(status, LXB_STATUS_ERROR);
        test_eq(*ctx.buffer_out, entry->codepoint);
    }
}
TEST_END

TEST_BEGIN(encode)
{
    size_t size;
    lxb_char_t data;
    lxb_status_t status;
    lxb_encoding_encode_t ctx;
    const lxb_codepoint_t *cp;
    const lxb_encoding_data_t *enc_data;
    const lxb_encoding_multi_index_t *entry;

    enc_data = lxb_encoding_data(%%CONST_NAME%%);

    size = sizeof(%%DATA%%)
           / sizeof(lxb_encoding_multi_index_t);

    test_ne(size, 0);

    for (lxb_codepoint_t i = 0; i < 0x80; i++) {
        cp = &i;

        lxb_encoding_encode_init(&ctx, enc_data, &data, sizeof(data));

        status = enc_data->encode(&ctx, &cp, (cp + 1));
        test_ne(status, LXB_STATUS_ERROR);
        test_eq(ctx.buffer_used, 1);
        test_eq(data, (lxb_char_t) i);
    }

    for (size_t i = 0; i < size; i++) {
        entry = &%%DATA%%[i];
        if (entry->codepoint == LXB_ENCODING_ERROR_CODEPOINT) {
            continue;
        }

        cp = &entry->codepoint;

        lxb_encoding_encode_init(&ctx, enc_data, &data, sizeof(data));

        status = enc_data->encode(&ctx, &cp, (cp + 1));
        test_eq(ctx.buffer_used, 1);
        test_eq(data, (lxb_char_t) (i + 0x80));
    }
}
TEST_END

int
main(int argc, const char * argv[])
{
    TEST_INIT();

    TEST_ADD(decode);
    TEST_ADD(encode);

    TEST_RUN("lexbor/encoding/%%NAME%%");
    TEST_RELEASE();
}
