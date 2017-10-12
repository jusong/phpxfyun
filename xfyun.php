<?php
$txtFile = '/home/xiaodong/Downloads/ise/bin/ise_cn/cn_sentence.txt';
$audioFile = '/home/xiaodong/Downloads/ise/bin/ise_cn/cn_sentence.wav';
//$audioFile = '/home/xiaodong/Downloads/test.wav';
$txt = trim(file_get_contents($txtFile));
$audio = file_get_contents($audioFile);

try {
//    $xf = new Xfyun('59ccc4d4');

        $xf = new Xfyun('59cdf93b');
    for ($i = 0; $i < 1; $i++) {
    $res = $xf->ise(iconv('UTF-8', 'GBK', $txt), $audio, Xfyun::READ_SENTENCE_CN);

    $res = iconv('GBK', 'UTF-8', $res);
    var_dump($res);
    }
} catch (Exception $e) {
//    var_dump($e);
    var_dump($e->getCode());
    var_dump($e->getMessage());
}
