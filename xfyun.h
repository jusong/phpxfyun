#ifndef XFYUN_H
#define XFYUN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "qtts.h"
#include "msp_cmn.h"
#include "msp_errors.h"

#define FRAME_LEN	    640		/* 写入语音数据的帧大小, 16k,16bit格式的WAV音频，一帧320个采样点，
								   则一帧大小：320 × 16bit / 8 = 640byte; 一帧时长：320 / 16000 * 1000 = 20ms */

#define MAX_TEXT_LEN    4194304	/* 评测文本最大长度 */
#define MAX_LEN         4096    /* 行最大长度 */

//测评分类
enum _category {
  read_syllable_cn,				/* 中文字 */
  read_word_cn,					/* 中文词语 */
  read_sentence_cn,				/* 中文句子 */
  read_chapter_cn				/* 中文篇章 */
};

//错误码
enum {
  XFYUN_ERROR_LOGIN             = 10001, /* 登录失败 */
  XFYUN_ERROR_LOGOUT            = 10002, /* 登出失败 */
  XFYUN_ERROR_INVALID_PARAMS    = 10003, /* 无效的参数 */
  XFYUN_ERROR_INVALID_CATE      = 10004, /* 无效的测评分类 */
  XFYUN_ERROR_TOO_LONG_TEXT     = 10005, /* 评测文本太长 */
  XFYUN_ERROR_ALLOC_MEMORY      = 10006, /* 申请内存失败 */
  XFYUN_ERROR_SESSION_BEGIN     = 10007, /* 开始测评失败 */
  XFYUN_ERROR_SESSION_END       = 10008, /* 结束测评失败 */
  XFYUN_ERROR_TEXT_PUT          = 10009, /* 写入测评文本失败 */
  XFYUN_ERROR_AUDIO_WRITE       = 10010, /* 写入语音数据失败 */
  XFYUN_ERROR_GET_RESULT        = 10011, /* 获取结果失败 */
  XFYUN_ERROR_INVALID_RES       = 10012, /* 无效结果 */
};

void throw_exception(int errcode, const char *errmsg TSRMLS_DC);
const char* ssb_param(enum _category);
int concat(char **dst, const char *src, int src_len);

#define ISE_EXIT(code,message,inner_code)               \
    if (0 != inner_code) {                              \
        sprintf(errmsg, "%s[%d]", message, inner_code); \
    } else {                                            \
        strcpy(errmsg, message);                        \
    }                                                   \
	errcode    = code;                                  \
	goto ise_exit;

#define THROW_EXCEPTION(errcode,errformat,...) { zend_throw_exception_ex(zend_exception_get_default(), errcode TSRMLS_CC, errformat, ##__VA_ARGS__); RETURN_NULL(); }

#endif	/* XFYUN_H */
