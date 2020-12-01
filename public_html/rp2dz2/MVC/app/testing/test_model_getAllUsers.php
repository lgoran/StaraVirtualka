<?php 

require_once __DIR__ . '/../../model/chatservice.class.php';
require_once __DIR__ . '/../../model/user.class.php';

$ls = new ChatService();
$users = $ls->getAllUsers();

echo '<pre>';
print_r( $users );
echo '</pre>';
?>
