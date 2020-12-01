<?php
$ploca = array(
    '.KK..KKKKK',
    '.......D..',
    '..D.......',
    '..D.K.....',
    '....KK..D.',
    '.D........',
    '...KD.D...',
    '..K.......',
    '.K.....K..',
    '...D......'
);

// ----------------------------------
// Dodajte svoj kod ispod.
// ----------------------------------
function sendJSONandExit( $message )
{
    // Kao izlaz skripte pošalji $message u JSON formatu i prekini izvođenje.
    header( 'Content-type:application/json;charset=utf-8' );
    echo json_encode( $message );
    flush();
    exit( 0 );
}
$odg=[];
if(isset($_GET['pozicija']))
{
    $pozicija=(int)$_GET['pozicija'];
    $pozicijax=$pozicija%10;
    $pozicijay=(int)($pozicija/10);
    $odg['otkriveno']=$ploca[$pozicijay][$pozicijax];
    sendJSONandExit($odg);
}
?>