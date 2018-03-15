<?php

#$txtFile = '/home/jiafd/ise_cn/cn_sentence.txt';
$txtFile = '/home/jiafd/ise_cn/cn_sentence1.txt';
$audioFile = '/home/jiafd/ise_cn/cn_sentence.wav';

#$txtFile = '/home/jiafd/ise/bin/ise_cn/cn_sentence1.txt';
#$audioFile = '/home/jiafd/ise/bin/ise_cn/cn_sentence.wav';

$txt = trim(file_get_contents($txtFile));
$audio = file_get_contents($audioFile);
$txt = chr(0xef).chr(0xbb).chr(0xbf).$txt;

try {
	$xf = new xfyun('59cdf93b');
	$raw = $xf->ise($txt, $audio, xfyun::READ_SENTENCE_CN);
	$res = iconv('GBK', 'UTF-8', $raw);
	var_dump($res);
} catch (Exception $e) {
	var_dump($e->getCode(), $e->getMessage());
}
var_dump($txt, strlen($txt));
