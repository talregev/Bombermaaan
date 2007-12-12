<?php

include_once( "inc/webpage.php" );


header("Vary: Accept");
#if (stristr($_SERVER["HTTP_ACCEPT"], "application/xhtml+xml")) 
    header("Content-Type: application/xhtml+xml; charset=utf-8");
#else
#    header("Content-Type: text/html; charset=utf-8");

?>
<?php echo '<?' . 'xml version="1.0" encoding="UTF-8"?>' . "\n"; ?>
<?php echo '<!' . 'DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">' . "\n"; ?>

<?php

$webpage = new WebPage();
$webpage->head();

?>

<h1>Bombermaaan screenshots</h1>

<div id="content">

<p>

<img style="padding: 2em;" src="screenshots/screen1.png" alt="Screenshot #1" />
<img style="padding: 2em;" src="screenshots/screen7.png" alt="Screenshot #2" />
<img style="padding: 2em;" src="screenshots/screen8.png" alt="Screenshot #3" />

</p>

</div>

<?php

$webpage->tail();

?>
