<?php
if(isset($_GET['v1']) && isset($_GET['v2']) && isset($_GET['v3'])) {
$volt=($_GET['v1'] * 256 + $_GET['v2']) * 5 / 1024;
$volt=round($volt, 3);
$a2="<!DOCTYPE html><br><html><br>" . $volt . " V<br>input=" . $_GET['v3'] . "<br><html>";
$fp = fopen("a2.php", "w");
fwrite($fp, $a2);
fclose($fp);

echo $volt . " V  input=" . $_GET['v3'];
} 
?>