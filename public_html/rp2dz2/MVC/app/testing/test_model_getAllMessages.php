<?php 

require_once __DIR__ . '/../../model/chatservice.class.php';
require_once __DIR__ . '/../../model/user.class.php';
require_once __DIR__ . '/../../model/message.class.php';
require_once __DIR__ . '/../../model/channel.class.php';

$ls = new ChatService();
//$users = $ls->getAllMessagesByChannel(4);
$users = $ls->getAllMessagesByUser(4);
echo '<pre>';
print_r( $users );
echo '</pre>';
?>
