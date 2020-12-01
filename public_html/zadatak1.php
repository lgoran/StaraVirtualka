<?php
function isNumber($str)
{
    return preg_match('/^[0-9]{1,20}$/',$str);
}
if(isset($_POST["txt1"]) && isset($_POST["txt2"]))
{
    $prvi=(int)$_POST["txt1"];
    $drugi=(int)$_POST["txt2"];
    echo $prvi+$drugi;
}

?>
