<?php

$txtFile = 'cn_sentence.txt';
$audioFile = 'cn_sentence.wav';

$txt = trim(file_get_contents($txtFile));
$audio = file_get_contents($audioFile);
$txt = chr(0xef).chr(0xbb).chr(0xbf).$txt;

try {
	$xf = new xfyun('59cdf93b');
	$raw = $xf->ise($txt, $audio, xfyun::READ_SENTENCE_CN);
	//$raw = $xf->ise($txt, $audio, xfyun::READ_CHAPTER_CN);
	$res = iconv('GBK', 'UTF-8', $raw);
	var_dump($res);
} catch (Exception $e) {
	var_dump($e->getCode(), $e->getMessage());
}
echo 'text: '.$txt.PHP_EOL;
echo 'text len: '.strlen($txt).PHP_EOL;
echo 'audio len: '.strlen($audio).PHP_EOL;
