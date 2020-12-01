<?php require_once __DIR__ . '/_header.php'; ?>

<form action="index.php?rt=channels/createResult" method="post">
	Unesi ime kanala:
	<input type="text" name="channel_name">
	<button type="submit">Dodaj u bazu</button>
</form>

<?php require_once __DIR__ . '/_footer.php'; ?>