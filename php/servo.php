<?php

include 'lib/serial/src/PhpSerial.php';

$serial = new PhpSerial;
$serial->deviceSet("COM11");
//$serial->confBaudRate(9600);
//$serial->confParity("even");
//$serial->confCharacterLength(7);
//$serial->confStopBits(1);
//$serial->confFlowControl("rts/cts");
$serial->deviceOpen('w+');

sleep(5);

// We may need to return if nothing happens for 20 seconds
stream_set_timeout($serial->_dHandle, 20);

for ($i = 0; $i < 100; ++$i)
{
    $serial->sendMessage("30,50;");
    var_dump($serial->readPort());
    sleep(0.03);
}

$serial->deviceClose();

?>