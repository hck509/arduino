<?php

function SetInput($a, $b)
{
    $f = fopen('../python/input.txt', 'w');
    fwrite($f, $a . ',' . $b . ';');
    fclose($f);
}

if (isset($argv))
{
    SetInput($argv[1], $argv[2]);
}

?>