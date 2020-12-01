<?php 

require_once __DIR__ . '/../model/chatservice.class.php';

class MessagesController
{
	public function searchByUser()
	{
		$cs = new ChatService();

		$title = 'Popis poruka korisnika';
		$messageList = $cs->getAllMessagesByUser($_SESSION['user']);
		$userList = $cs->getUsernamesByMessagelist($messageList);
		require_once __DIR__ . '/../view/messages_index.php'; 
	}
	
	public function searchResultsByUser()
	{
		if(isset($_POST['id_user']))
		{
			$cs = new ChatService();

			$title = 'Popis poruka korisnika';
			$messageList = $cs->getAllMessagesByUser($_SESSION['user']);
			$userList = $cs->getUsernamesByMessagelist($messageList);
			require_once __DIR__ . '/../view/messages_index.php'; 
		}
		else
		{
			$title='Greška';
			require_once __DIR__ . '/../view/messages_error.php'; 
		}
		
	}
	public function searchByChannel()
	{
		$title='Popis poruka u kanalu';
		if(isset($_GET['id_channel']))
		{
			$cs = new ChatService();

			$title='Popis poruka u kanalu';
			$messageList = $cs->getAllMessagesByChannel($_GET['id_channel']);
			$userList = $cs->getUsernamesByMessagelist($messageList);
			require_once __DIR__ . '/../view/messages_index.php';
		}
		else
		{
			$title='Greška';
			require_once __DIR__ . '/../view/messages_error.php'; 
		}
	}
	public function create()
	{
		if(isset($_POST['message'])&& isset($_GET['id_channel']) && $_POST['message']!='')
		{
			$cs = new ChatService();
			$cs->createMessage($_SESSION['user'],$_GET['id_channel'],$_POST['message']);
			header( 'Location: index.php?rt=messages/searchByChannel&id_channel='.$_GET['id_channel'] );
		}
		else
		{
			$title='Greška';
			require_once __DIR__ . '/../view/messages_error.php'; 
		}
	}
	public function thumbs_up()
	{
		if(isset($_POST['submit']))
		{
			$cs = new ChatService();
			$cs->incrementThumbsUp($_POST['submit']);
			if(isset($_GET['id_channel']))
				header( 'Location: index.php?rt=messages/searchByChannel&id_channel='.$_GET['id_channel'] );
			else
				header( 'Location: index.php?rt=messages/searchByUser' );
		}
	}
}; 

?>
