<?php //require_once __DIR__ . '/_header.php'; ?>

<form <?php echo 'action="index.php?rt=messages/create&id_channel='. $_GET['id_channel'] . '"' ?> method="post">
	Unesi poruku:
	<input type="text" name="message">
	<button type="submit">Pošalji poruku</button>
</form>

<?php //require_once __DIR__ . '/_footer.php'; ?>