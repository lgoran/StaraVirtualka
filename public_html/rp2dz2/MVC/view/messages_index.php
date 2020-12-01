<?php require_once __DIR__ . '/_header.php'; ?>
<table>
	
	<?php 
		$size=count($messageList);
		if($size!=0)
		{
			echo '<tr><th>Korisnik</th><th>Datum</th><th>Poruka</th><th>Lajkovi</th></tr>';
		}
		else
			echo 'Nema podataka';
		for( $i=0;$i<$size;$i++)
		{
			$message=$messageList[$i];
			echo '<tr>' .
				 '<td>' . $userList[$i] . '</td>' .
			     '<td>' . $message->date . '</td>' .
				 '<td>' . $message->content . '</td>' .
				 '<td>' . $message->thumbs_up . '</td>'
				 ?>
				<td>
					<form 
					<?php 
						if(isset($_GET['id_channel'])) echo 'action="index.php?rt=messages/thumbs_up&id_channel=' . $_GET['id_channel'] . '"';  
						else echo 'action="index.php?rt=messages/thumbs_up"';
					?>
					method="post">
					<input type="image" src="thumbs_up.jpeg" alt="thumbs_up" width="20" height="20">
					<input type="hidden" name="submit" value=<?php echo $message->id; ?>>
					</form>
				</td>
				<?php
				 '</tr>';
			
		}
		
	?>
</table>

<?php 
if(isset($_GET['id_channel']))
	require_once __DIR__ . '/messages_create.php';
require_once __DIR__ . '/_footer.php'; 
?>