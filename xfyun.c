/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
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

/* $Id$ */

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

ZEND_BEGIN_ARG_INFO(arg_construct, 1)
ZEND_ARG_INFO(0, appid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arg_ise, 4)
ZEND_ARG_INFO(0, text)
ZEND_ARG_INFO(0, audio)
ZEND_ARG_INFO(0, cate)
ZEND_END_ARG_INFO()

/* {{{ xfyun_functions[]
 *
 * Every user visible function must have an entry in xfyun_functions[].
 */
const zend_function_entry xfyun_functions[] = {
	{ NULL, NULL, NULL, 0, 0 }
};
const zend_function_entry xfyun_methods[] = {
	PHP_ME(Xfyun, __construct, arg_construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(Xfyun, __destruct, NULL, ZEND_ACC_DTOR|ZEND_ACC_PUBLIC)
	PHP_ME(Xfyun, ise, arg_ise, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL, 0, 0 }
};

void throw_exception(int, const char *, int);
const char* ssb_param(enum _category);
char *concat(char *, const char *, int);
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

zend_class_entry *Xfyun_ce;
/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(xfyun)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
    zend_class_entry Xfyun; 
    INIT_CLASS_ENTRY(Xfyun, "Xfyun", xfyun_methods); //第二个参数为类名，第三个参数为类的函数列表 
    Xfyun_ce = zend_register_internal_class(&Xfyun TSRMLS_CC); //注册类 
    zend_declare_property_null(Xfyun_ce, "_appid", sizeof("_appid") - 1, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_class_constant_long(Xfyun_ce, "READ_SYLLABLE_CN", sizeof("READ_SYLLABLE_CN") - 1, read_syllable_cn TSRMLS_DC);
	zend_declare_class_constant_long(Xfyun_ce, "READ_WORD_CN", sizeof("READ_WORD_CN") - 1, read_word_cn TSRMLS_DC);
	zend_declare_class_constant_long(Xfyun_ce, "READ_SENTENCE_CN", sizeof("READ_SENTENCE_CN") - 1, read_sentence_cn TSRMLS_DC);
	zend_declare_class_constant_long(Xfyun_ce, "READ_WORD_EN", sizeof("READ_WORD_EN") - 1, read_word_en TSRMLS_DC);
	zend_declare_class_constant_long(Xfyun_ce, "READ_SENTENCE_EN", sizeof("READ_SENTENCE_EN") - 1, read_sentence_en TSRMLS_DC);

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
PHP_METHOD(Xfyun, __construct) {

	zval *appid = NULL;
	zend_class_entry *ce;
	int  ret;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &appid) == FAILURE) { //获取构造函数参数 
		WRONG_PARAM_COUNT; 
    }
	
	ce = Z_OBJCE_P(getThis());
	zend_update_property(ce, getThis(), "_appid", sizeof("_appid") - 1, appid TSRMLS_CC);

	char *lgi_param = emalloc(20);
	sprintf(lgi_param, "appid = %s", Z_LVAL_P(appid));
	ret = MSPLogin(NULL, NULL, lgi_param);
	efree(lgi_param);
	if (MSP_SUCCESS != ret)	{
		throw_exception(XFYUN_ERROR_LOGIN, "MSPLogin failed [%d]", ret);
	}
}

PHP_METHOD(Xfyun, __destruct) {

	int ret = MSPLogout();
	if (MSP_SUCCESS != ret)	{
		throw_exception(XFYUN_ERROR_LOGOUT, "MSPLogout failed [%d]", ret);
	}
}

PHP_METHOD(Xfyun, ise) {

	int  cate    = read_sentence_cn;
	char *text   = NULL;
	char *audio  = NULL;
	int  text_len       = 0;
	int  audio_len      = 0;
	const char *session_id    = NULL;
	char *out_put       = NULL;
	char *out_put_ptr   = NULL;
	unsigned int  res_len    = 0;
	int  audio_idx      = 0;
	int  audio_stat     = MSP_AUDIO_SAMPLE_CONTINUE;
	int  ep_status      = MSP_EP_LOOKING_FOR_SPEECH;
	int  rec_status     = MSP_REC_STATUS_SUCCESS;
	int  ret            = 0;
	int  errcode        = 0;
	char *errmsg        = NULL;
	int  inner_code     = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|l", &text, &text_len, &audio, &audio_len, &cate) == FAILURE) {
		WRONG_PARAM_COUNT; 
	}

	if (NULL == text || text_len <= 0 || NULL == audio || audio_len <= 0) {
		throw_exception(XFYUN_ERROR_INVALID_PARAMS, "Invalid parameter", 0);
	}

	if (text_len > MAX_TEXT_LEN) {
		throw_exception(XFYUN_ERROR_TOO_LONG_TEXT, "Too long text", 0);
	}

	//开启一次测评
	session_id   = QISESessionBegin(ssb_param(cate), NULL, &ret);
	if (MSP_SUCCESS != ret)	{
		throw_exception(XFYUN_ERROR_SESSION_BEGIN, "QISESessionBegin failed [%d]", ret);
	}

	//写入待评测的文本
	ret = QISETextPut(session_id, text, (unsigned int)text_len, NULL);
	if (MSP_SUCCESS != ret)	{
		errcode    = XFYUN_ERROR_TEXT_PUT;
		errmsg     = "QISETextPut failed [%d]";
		inner_code = ret;
		goto ise_exit;
	}

	//写入待评测的音频
	while (1) {
		unsigned int len = 10 * FRAME_LEN;// 每次写入200ms音频(16k，16bit)：1帧音频20ms，10帧=200ms。16k采样率的16位音频，一帧的大小为640Byte

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
		ret = QISEAudioWrite(session_id, (const void *)&audio[audio_idx], len, audio_stat, &ep_status, &rec_status);
		if (MSP_SUCCESS != ret) {
			errcode    = XFYUN_ERROR_AUDIO_WRITE;
			errmsg     = "QISEAudioWrite failed [%d]";
			inner_code = ret;
			goto ise_exit;
		}

		audio_idx += (long)len;
		audio_len -= (long)len;

		//有测评结果返回，读取结果
		if (MSP_REC_STATUS_SUCCESS == rec_status) {
			
			const char *res = QISEGetResult(session_id, &res_len, &rec_status, &ret);
			
			if (MSP_SUCCESS != ret) {
				errcode    = XFYUN_ERROR_GET_RESULT;
				errmsg     = "QISEGetResult failed [%d]";
				inner_code = ret;
				goto ise_exit;
			}
			
			if (NULL != res) {
				out_put = concat(out_put, res, res_len);
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
			
			errcode    = XFYUN_ERROR_AUDIO_WRITE;
			errmsg     = "QISEAudioWrite failed, End Point error[%d]";
			inner_code = ep_status;
			goto ise_exit;
		}

		//如果是实时采集音频,可以省略此操作。5KB大小的16KPCM持续的时间是160毫秒
		usleep(200000);
	}

	//写入最后一句结束
	ret = QISEAudioWrite(session_id, (const void *)NULL, 0, 4, &ep_status, &rec_status);
	if (MSP_SUCCESS != ret)	{
		errcode    = XFYUN_ERROR_AUDIO_WRITE;
		errmsg     = "QISEAudioWrite failed [%d]";
		inner_code = ret;
		goto ise_exit;
	}

	//读取结果
	while (MSP_REC_STATUS_COMPLETE != rec_status) {
		
		const char *res = QISEGetResult(session_id, &res_len, &rec_status, &ret);
		
		if (MSP_SUCCESS != ret) {
			errcode    = XFYUN_ERROR_GET_RESULT;
			errmsg     = "QISEGetResult failed [%d]";
			inner_code = ret;
			goto ise_exit;
		}
		
		if (NULL != res) {		/* 读取到结果 */
			out_put = concat(out_put, res, res_len);
		} else {				/* 暂时没有测评结果，睡150毫秒 */
			usleep(150000);
		}
	}
	

 ise_exit:
	ret = QISESessionEnd(session_id, NULL);
	if (MSP_SUCCESS != ret) {
		throw_exception(XFYUN_ERROR_SESSION_END, "QISESessionEnd failed [%d]", ret);
	}
	if (errcode) {
		throw_exception(errcode, errmsg, inner_code);
	}
	if (NULL == out_put) {
		RETURN_NULL();
	}
	RETURN_STRING(out_put, 0);
}

void throw_exception(int errcode, const char *errmsg, int inner_code) {

	if (0 != inner_code) {
		int  errmsg_len = strlen(errmsg) + 10;
		char errmsg_buf[errmsg_len];
		sprintf(errmsg_buf, errmsg, inner_code);
		zend_throw_exception(zend_exception_get_default(), (const char*)errmsg_buf, errcode TSRMLS_CC);
	} else {
		zend_throw_exception(zend_exception_get_default(), errmsg, errcode TSRMLS_CC);
	}
}

const char* ssb_param(enum _category cate) {

	switch (cate) {
		
	case read_syllable_cn:		/* 中文字 */
		return "sub=ise,category=read_syllable,language=zh_cn,aue=speex-wb;7,auf=audio/L16;rate=16000";
		
	case read_word_cn:			/* 中文词语 */
		return "sub=ise,category=read_word,language=zh_cn,aue=speex-wb;7,auf=audio/L16;rate=16000";
		
	case read_sentence_cn:		/* 中文句子 */
		return "sub=ise,category=read_sentence,language=zh_cn,aue=speex-wb;7,auf=audio/L16;rate=16000";
		
	case read_word_en:			/* 英文单词 */
		return "sub=ise,category=read_word,language=en_us,aue=speex-wb;7,auf=audio/L16;rate=16000";
		
	case read_sentence_en:		/* 英文句子 */
		return "sub=ise,category=read_sentence,language=en_us,aue=speex-wb;7,auf=audio/L16;rate=16000";
		
	default:					/* 未定义 */
		throw_exception(XFYUN_ERROR_INVALID_CATE, "Invalid cate", 0);
	}
}

//将src字符串拼接到*dst后面，dst为空时自动申请内存
char *concat(char *dst, const char *src, int src_len) {

	if (NULL == src || src_len <= 0) {
		return dst;
	}

	if (NULL == dst) {
		printf("emalloc %d\n", src_len + 1);
		if ((dst = emalloc(src_len + 1)) == NULL) {
			throw_exception(XFYUN_ERROR_ALLOC_MEMORY, "Alloc memory failed", 0);
		}
		strncpy(dst, src, src_len);
		dst[src_len] = '\0';
	} else {
		int dst_len = strlen(dst);
		printf("erealloc %d\n", src_len + dst_len + 1);
		if ((dst = erealloc(dst, dst_len + src_len + 1)) == NULL) {
			throw_exception(XFYUN_ERROR_ALLOC_MEMORY, "Realloc memory failed", 0);
		}
		strncpy(dst + dst_len, src, src_len);
		dst[dst_len + src_len] = '\0';
	}
	return dst;
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
