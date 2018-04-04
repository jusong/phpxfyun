/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2010 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 297205 2010-03-30 21:09:07Z johannes $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_xfyun.h"
#include "xfyun.h"

/* If you declare any globals in php_xfyun.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(xfyun)
*/

/* True global resources - no need for thread safety here */
static int le_xfyun;
zend_class_entry *xfyun_ce;

ZEND_BEGIN_ARG_INFO(arg_construct, 0)
        ZEND_ARG_INFO(0, appid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arg_ise, 0)
        ZEND_ARG_INFO(0, text)
        ZEND_ARG_INFO(0, audio)
        ZEND_ARG_INFO(0, cate)
ZEND_END_ARG_INFO()

/* {{{ xfyun_functions[]
 *
 * Every user visible function must have an entry in xfyun_functions[].
 */
const zend_function_entry xfyun_functions[] = {
	PHP_FE(confirm_xfyun_compiled,	NULL)		/* For testing, remove later. */
	{NULL, NULL, NULL}	/* Must be the last line in xfyun_functions[] */
};
/* }}} */

/* {{{ xfyun_methods[]
 *  *
 *   * Every user visible method must have an entry in xfyun_methods[].
 *    */
const zend_function_entry xfyun_methods[] = {
	PHP_ME(xfyun, __construct, arg_construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(xfyun, __destruct, NULL, ZEND_ACC_DTOR|ZEND_ACC_PUBLIC)
	PHP_ME(xfyun, ise, arg_ise, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL, 0, 0 }
};
/* }}} */

/* {{{ xfyun_module_entry
 */
zend_module_entry xfyun_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"xfyun",
	xfyun_functions,
	PHP_MINIT(xfyun),
	PHP_MSHUTDOWN(xfyun),
	PHP_RINIT(xfyun),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(xfyun),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(xfyun),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_XFYUN
ZEND_GET_MODULE(xfyun)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("xfyun.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_xfyun_globals, xfyun_globals)
    STD_PHP_INI_ENTRY("xfyun.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_xfyun_globals, xfyun_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_xfyun_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_xfyun_init_globals(zend_xfyun_globals *xfyun_globals)
{
	xfyun_globals->global_value = 0;
	xfyun_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(xfyun)
{
	/* If you have INI entries, uncomment these lines 
	   REGISTER_INI_ENTRIES();
	   */
	zend_class_entry xfyun; 
	INIT_CLASS_ENTRY(xfyun, "xfyun", xfyun_methods); 
	xfyun_ce = zend_register_internal_class(&xfyun TSRMLS_CC); 

	//zend_declare_property_null(xfyun_ce, "_appid", sizeof("_appid") - 1, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_class_constant_long(xfyun_ce, "READ_SYLLABLE_CN", sizeof("READ_SYLLABLE_CN") - 1, read_syllable_cn TSRMLS_CC);
	zend_declare_class_constant_long(xfyun_ce, "READ_WORD_CN", sizeof("READ_WORD_CN") - 1, read_word_cn TSRMLS_CC);
	zend_declare_class_constant_long(xfyun_ce, "READ_SENTENCE_CN", sizeof("READ_SENTENCE_CN") - 1, read_sentence_cn TSRMLS_CC);
	zend_declare_class_constant_long(xfyun_ce, "READ_CHAPTER_CN", sizeof("READ_CHAPTER_CN") - 1, read_chapter_cn TSRMLS_CC);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(xfyun)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(xfyun)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(xfyun)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(xfyun)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "xfyun support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_xfyun_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_xfyun_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "xfyun", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

const char *lgi_param = "appid = 59ccc4d4";
PHP_METHOD(xfyun, __construct) {

        zval *appid;
        int  ret;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &appid) == FAILURE) { //获取构造函数参数 
                WRONG_PARAM_COUNT; 
        }
//        zend_update_property(xfyun_ce, getThis(), "_appid", sizeof("_appid") - 1, appid TSRMLS_CC);

        //初始化msc，用户登录
        ret = MSPLogin(NULL, NULL, lgi_param);
        if (MSP_SUCCESS != ret) {
			THROW_EXCEPTION(XFYUN_ERROR_LOGIN, "MSPLogin failed[%d]", ret);
        }
}

PHP_METHOD(xfyun, __destruct) {

	php_printf("__destruct called\n");
	int ret = MSPLogout();
	if (MSP_SUCCESS != ret) {
		THROW_EXCEPTION(XFYUN_ERROR_LOGOUT, "MSPLogout failed[%d]", ret);
	}
	php_printf("__destruct end\n");
}


PHP_METHOD(xfyun, ise) {

        char            *text			= NULL;
		char            *audio			= NULL;
		char            *output			= NULL;
		char            errmsg[MAX_LEN]	= {'\0'};
        int             text_len		= 0;
		int             audio_len		= 0;
		int             ret				= 0;
		int             errcode			= 0;
		int				inner_code		= 0;
		int				audio_idx		= 0;
        const char		*session_id		= NULL;
		const char		*ssb			= NULL;
        unsigned int	res_len			= 0;
        int				audio_stat		= MSP_AUDIO_SAMPLE_CONTINUE;    //音频发送状态
        int				ep_status       = MSP_EP_LOOKING_FOR_SPEECH;    //端点检测状态
        int				rec_status      = MSP_REC_STATUS_SUCCESS;       //测评器状态
        int				cate            = read_sentence_cn;             //评测类型，默认是中文句子

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|l", &text, &text_len, &audio, &audio_len, &cate) == FAILURE) {
                WRONG_PARAM_COUNT;
        }

        if (!text_len || !audio_len) {
                THROW_EXCEPTION(XFYUN_ERROR_INVALID_PARAMS, "Invalid parameter");
        }

        if (text_len > MAX_TEXT_LEN) {
                THROW_EXCEPTION(XFYUN_ERROR_TOO_LONG_TEXT, "Too long text");
        }

        //开启一次测评
        if (NULL == (ssb = ssb_param(cate))) {
                THROW_EXCEPTION(XFYUN_ERROR_INVALID_CATE, "Invalid category");
        }
        session_id = QISESessionBegin(ssb, NULL, &ret);
        if (MSP_SUCCESS != ret) {
                THROW_EXCEPTION(XFYUN_ERROR_SESSION_BEGIN, "QISESessionBegin failed [%d]", ret);
        }

        //写入待评测的文本
        ret = QISETextPut(session_id, text, (unsigned int)text_len, NULL);
        if (MSP_SUCCESS != ret) {
                ISE_EXIT(XFYUN_ERROR_TEXT_PUT, "QISETextPut failed", ret);
        }
        //写入待评测的音频
        audio_idx = 0;
#ifdef DEBUG_MODE
		int write_count = 0;
		int read_count = 0;
#endif
        while (1) {
                unsigned int len = 10 * FRAME_LEN;// 每次写入200ms音频(16k，16bit)，6400byte=6.25K：1帧音频20ms，10帧=200ms。16k采样率的16位音频，一帧的大小为640Byte

                        if (0 == audio_idx) {
                                audio_stat = MSP_AUDIO_SAMPLE_FIRST;
                        } else {
                                audio_stat = MSP_AUDIO_SAMPLE_CONTINUE;
                        }

                if (audio_len <= 2 * len) {
                        len           = audio_len;
                }
                if (len <= 0) {
                        break;
                }

                //写入语音数据
#ifdef DEBUG_MODE
				write_count++;
#endif
                ret = QISEAudioWrite(session_id, (const void *)(audio + audio_idx), len, audio_stat, &ep_status, &rec_status);
                if (MSP_SUCCESS != ret) {
                        ISE_EXIT(XFYUN_ERROR_AUDIO_WRITE, "QISEAudioWrite failed", ret);
                }

                audio_idx += len;
                audio_len -= len;

                //有测评结果返回，读取结果
                if (MSP_REC_STATUS_SUCCESS == rec_status) {

#ifdef DEBUG_MODE
					read_count++;
#endif
                        const char *res = QISEGetResult(session_id, &res_len, &rec_status, &ret);
                        if (MSP_SUCCESS != ret) {
                                ISE_EXIT(XFYUN_ERROR_GET_RESULT, "QISEGetResult failed", ret);
                        }

                        if (NULL != res) {
                                if (-1 == concat(&output, res, res_len)) {
                                        ISE_EXIT(XFYUN_ERROR_ALLOC_MEMORY, "Alloc memory failed", 0);
                                }
                        }
                }
                if (MSP_EP_AFTER_SPEECH == ep_status) { /* 检测到音频的后端点，后继的音频会被MSC忽略 */
                        break;
                } else if (
                                MSP_EP_TIMEOUT == ep_status ||
                                MSP_EP_ERROR == ep_status ||
                                MSP_EP_MAX_SPEECH == ep_status
                                ) {

                        /*****************************************
                         * MSP_EP_TIMEOUT = 4        超时
                         * MSP_EP_ERROR = 5          出现错误
                         * MSP_EP_MAX_SPEECH = 6     音频过大
                         *****************************************/

                        ISE_EXIT(XFYUN_ERROR_AUDIO_WRITE, "QISEAudioWrite failed, End Point error", ep_status);
                }

                //如果是实时采集音频,可以省略此操作。5KB大小的16KPCM持续的时间是160毫秒
                usleep(200000);
        }
        //写入最后一句结束                                                                                                
        ret = QISEAudioWrite(session_id, (const void *)NULL, 0, MSP_AUDIO_SAMPLE_LAST, &ep_status, &rec_status);
        if (MSP_SUCCESS != ret) {
                ISE_EXIT(XFYUN_ERROR_AUDIO_WRITE, "QISEAudioWrite failed", ret);
        }

        //读取结果
        while (MSP_REC_STATUS_COMPLETE != rec_status) {

#ifdef DEBUG_MODE
					read_count++;
#endif
                const char *res = QISEGetResult(session_id, &res_len, &rec_status, &ret);
                if (MSP_SUCCESS != ret) {
                        ISE_EXIT(XFYUN_ERROR_GET_RESULT, "QISEGetResult failed", ret);
                }

                if (NULL != res) {      /* 读取到结果 */
                        if (-1 == concat(&output, res, res_len)) {
                                ISE_EXIT(XFYUN_ERROR_ALLOC_MEMORY, "Alloc memory failed", 0);
                        }
                } else {                /* 暂时没有测评结果，睡150毫秒 */
                        usleep(150000);
                }
        }
ise_exit:
		ret = QISESessionEnd(session_id, NULL);
		if (MSP_SUCCESS != ret) {
			if (NULL != output) {
				efree(output);
			}
			THROW_EXCEPTION(XFYUN_ERROR_SESSION_END, "QISESessionEnd failed[%d]", ret);
		}
		if (errcode) {
			if (NULL != output) {
				efree(output);
			}
			THROW_EXCEPTION(errcode, errmsg);
		}

		array_init(return_value);
		add_next_index_string(return_value, session_id, 1);
		if (NULL != output) {
			add_next_index_string(return_value, output, 1);
			efree(output);
		}
}

const char* ssb_param(enum _category cate) {

	switch (cate) {

		case read_syllable_cn:      /* 中文字 */
                        return "sub=ise,category=read_syllable,language=zh_cn,aue=speex-wb;7,auf=audio/L16;rate=16000";

                case read_word_cn:          /* 中文词语 */
                        return "sub=ise,category=read_word,language=zh_cn,aue=speex-wb;7,auf=audio/L16;rate=16000";

                case read_sentence_cn:      /* 中文句子 */
                        return "sub=ise,category=read_sentence,language=zh_cn,aue=speex-wb;7,auf=audio/L16;rate=16000";
                case read_chapter_cn:       /* 中文篇章 */
                        return "sub=ise,category=read_chapter,language=zh_cn,aue=speex-wb;7,auf=audio/L16;rate=16000";

                default:                    /* 未定义 */
                        return NULL;
        }
}

//将src字符串拼接到*dst后面，dst为空时自动申请内存
int concat(char **dst, const char *src, int src_len) {

        if (NULL == src || src_len <= 0) {
                return -1;
        }

		char *tmp_dst;
        int dst_len;

        if (NULL == *dst) {
                if ((tmp_dst = emalloc(src_len + 1)) == NULL) {
                        return -1;
                }
                dst_len = 0;
                memcpy(tmp_dst, src, src_len);
                tmp_dst[src_len] = '\0';
                *dst = tmp_dst;
        } else {
                dst_len = strlen(*dst);
                if ((tmp_dst = erealloc(*dst, dst_len + src_len + 1)) == NULL) {
                        return -1;
                }
                memcpy(tmp_dst + dst_len, src, src_len);
                tmp_dst[dst_len + src_len] = '\0';
                *dst = tmp_dst;
        }
        return dst_len + src_len;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
