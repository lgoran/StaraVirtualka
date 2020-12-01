<?php require_once __DIR__ . '/_header.php'; ?>

<table>
	
	<?php 
		if(count($channelList)!=0)
		{
			echo '<tr><th>Ime kanala</th></tr>';
		}
		else 
		{
			echo 'Nema podataka';
		}
		foreach( $channelList as $channel )
		{
			echo '<tr>' .
				 '<td>' . '<a href="index.php?rt=messages/searchByChannel&id_channel=' . $channel->id . '">'. $channel->name . '</a>' . '</td>' .
			     '</tr>';
		}
	?>
</table>

<?php require_once __DIR__ . '/_footer.php'; ?>
