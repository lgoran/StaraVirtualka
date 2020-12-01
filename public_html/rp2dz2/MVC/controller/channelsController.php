<?php 
require_once __DIR__ . '/../model/chatservice.class.php';

class ChannelsController
{
	public function index() 
	{
		$cs = new ChatService();

		$title = 'Popis svih kanala';
		$channelList = $cs->getAllChannels();
		require_once __DIR__ . '/../view/channels_index.php';
	}
	public function create()
	{
		$title = 'Stvori kanal';
		require_once __DIR__ . '/../view/channels_create.php';
	}
	public function createResult()
	{
		$title = 'Stvori kanal';
		$cs = new ChatService();
		$cs->createChannel($_SESSION['user'],$_POST['channel_name']);
		header( 'Location: index.php' );
	}
	public function userChannels()
	{
		$cs = new ChatService();

		$title = 'Popis Vaših kanala';
		
		$channelList = $cs->getAllChannelsByUser($_SESSION['user']);
		require_once __DIR__ . '/../view/channels_index.php';
	}
}; 

?>
