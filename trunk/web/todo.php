<?php

include_once( "inc/webpage.php" );


header("Vary: Accept");
#if (stristr($_SERVER["HTTP_ACCEPT"], "application/xhtml+xml")) 
    header("Content-Type: application/xhtml+xml; charset=utf-8");
#else
#    header("Content-Type: text/html; charset=utf-8");

$downloads = array(
	array(
	"http://downloads.sourceforge.net/bombermaaan/Bombermaaan_1.02_Setup.exe?modtime=1197055380&big_mirror=0",
	"Installer for Win32 - Version 1.02",
	"4a708baed1d671be6ff0ba14bcd851e2", // MD5
	"d57361ee3c83f4cd03bee0d881f14a02b6a953ad"  // SHA1
	),
	array(
	"http://downloads.sourceforge.net/bombermaaan/Bombermaaan_1.02.zip?modtime=1197405778&big_mirror=0",
	"Zip file for Win32 - Version 1.02",
	),
	array(
	"http://downloads.sourceforge.net/bombermaaan/Bombermaaan_102_src.zip?modtime=1083110400&big_mirror=0",
	"Source files - Version 1.02",
	),
);


?>
<?php echo '<?' . 'xml version="1.0" encoding="UTF-8"?>' . "\n"; ?>
<?php echo '<!' . 'DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">' . "\n"; ?>

<?php

$webpage = new WebPage();
$webpage->head();

?>

<h1>Bombermaaan To-Do list</h1>

<div id="content">

<p>
This list shows the ideas we had and don't want to forget.
</p>

<table>

<tr>
<th>Item</th>
<th>Progress</th>
<th>Status</th>
<th>Description</th>
<th>Added</th>
<th>Last changed</th>
</tr>

<tr>
<td>Blocks where bombs start moving/change direction</td>
<td>0 %</td>
<td>Planned</td>
<td>There are certain blocks in the arena. When a bomber puts a bomb there or when a moving bomb arrives there, the bomb begins moving or changes the direction.</td>
<td>2007-12-10</td>
<td>2007-12-10</td>
</tr>

<tr>
<td>Skins</td>
<td>0 %</td>
<td>Planned</td>
<td>Skins with different images.</td>
<td>2007-12-10</td>
<td>2007-12-10</td>
</tr>

<tr>
<td>More than two keyboard inputs</td>
<td>0 %</td>
<td>Planned</td>
<td>Since you can plug many USB keyboards, it could be possible to have five human players in the same game.</td>
<td>2007-12-10</td>
<td>2007-12-10</td>
</tr>

<tr>
<td>Team mode</td>
<td>0 %</td>
<td>Planned</td>
<td>Players can be assigned to teams. The match is finished if there is only one team alive. In addition, there could be an option if items are shared in a team.</td>
<td>2007-12-11</td>
<td>2007-12-11</td>
</tr>

</table>

</div>

<?php

$webpage->tail();

?>
