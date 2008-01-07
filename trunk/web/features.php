<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

?>

<h1>Features</h1>

<div id="content">

<p>
Bombermaaan already provides these features:
</p>

<ul>
<li>Classic Bomberman game</li>
<li>Original gameplay and fun with minor adjustments</li>
<li>Up to 5 players on the same computer</li>
<li>Various levels of computer AI</li>
<li>Kick-Punch-Throw items mania</li>
<li>Customizable arena levels with a level editor</li>
<li>Keyboard and joystick support</li>
<li>Full screen and windowed display modes</li>
<li>Item amount in walls as well as bomber skills on startup can be set on a per-level basis</li>
<li>Various power-ups</li>
<li>Various contaminations after skull item is taken</li>
</ul>

<div id="featurelist">

<div class="group">

	<div class="head" onclick="document.getElementById('aaa').style.display='';">Headline...</div>
	<div id="aaa" class="more" style="display: none;">
	Bla bla bla
	<br />
	sldkfj
	<br />
	qewrt
	</div>

</div>

</div>

<?php
    /*** Thibaut's list on his website:
		    *  Classic Bomberman game
		    * Original gameplay and fun with minor adjustments
		    * Up to 5 players on the same computer
		    * Various levels of computer AI
		    * Single and team battle
		    * Kick-Punch-Throw items mania
		    * Kangaroos to ride
		    * Possibility to throw bombs in the arena after you died
		    * Various arena closures
		    * Customizable arena levels with a level editor
		    * Many options to customize the game rules
		    * Keyboard and joystick support
		    * Full screen and windowed display modes
		    * Network support (will come after all of the above) 
	***/
?>

<p>
More items may follow. A list of planned features can be seen on the <a href="./todo.php">To-Do list</a>.
</p>

</div>

<?php

$webpage->tail();

?>
