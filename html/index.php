<?php

$st = microtime(true);

/**
 * Равномерное изменение размера по большей стороне
 * @method thumbnail(string $newPath, int $width, int $height)
 */
$image = new \Srgiz\OpenCV(__DIR__ . '/php.png');
$thumb = $image->thumbnail(__DIR__ . '/php300.png', 300, 300);

echo sprintf('<pre>%s</pre>', print_r([
    'image' => [
        'path' => $image->getPath(),
        'width' => $image->getWidth(),
        'height' => $image->getHeight(),
    ],
    'thumbnail' => [
        'path' => $thumb->getPath(),
        'width' => $thumb->getWidth(),
        'height' => $thumb->getHeight(),
    ],
    'time' => ((microtime(true) - $st) * 1000) . ' ms',
], true));

/*
$filename = __DIR__ . '/php.png';
//$width = 597;
//$height = 428;
//$percent = 0.5;

// Get new sizes
list($width, $height) = getimagesize($filename);
$newwidth = 300;//(int)($width * $percent);
$newheight = 215;//(int)($height * $percent);

// Load
$thumb = imagecreatetruecolor($newwidth, $newheight);
$source =imagecreatefrompng($filename);

// Resize
imagecopyresized($thumb, $source, 0, 0, 0, 0, $newwidth, $newheight, $width, $height);

// Output
$t=imagepng($thumb, __DIR__ . '/phpGd300.png');
var_dump(((microtime(true) - $st) * 1000) . ' ms');
/**/
