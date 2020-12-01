<?php 

require_once __DIR__ . '/../../model/user.class.php';

$title = 'Popis korisnika';

$userList = [];
$userList[] = new User( 1, 'Pero', 'pero', 'pero@gmail.com', 'abc','1');
$userList[] = new User( 2, 'Ana', 'ana', 'ana@gmail.com', 'abc','1');
$userList[] = new User( 3, 'Maja', 'maja', 'maja@gmail.com', 'abc','1');

require_once __DIR__ . '/../../view/users_index.php';

?>

