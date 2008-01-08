<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->setOption_AddFeatureJavascript();
$webpage->head();

$item_number = 0;

function _add( $headline, $additionaltext ) {

	global $item_number;
	
	$item_number ++;
	
?>
<div class="group">

<div class="head" onclick="toggleFeatureItem( <?php echo $item_number; ?> );">
<?php // IE7 removes the space between the sign and the text if split to more than one line ?>
<code><span id="feature-sign-<?php echo $item_number; ?>">+</span>&nbsp;</code><?php echo $headline; ?>
</div>

<div id="feature-more-<?php echo $item_number; ?>" class="more" style="display: none;">
<?php echo $additionaltext; ?>
</div>

</div>

<?php

}

?>

<h1>Features</h1>

<div id="content">

<p>
Bombermaaan already provides these features:
</p>

<div id="featurelist">

<?php

_add( "Classic Bomberman game", "Bombermaaan is a classic Bomberman game. There's a similar game called Dynablaster." );

_add( "Original gameplay and fun with minor adjustments", "If you're familiar with other Bomberman games, you already know how to play Bombermaaan." );

_add( "Up to 5 players on the same computer", "You can play against four human players if you are using joysticks." );

_add( "Various levels of computer AI", "No additional text available." );

_add( "Kick-Punch-Throw items mania", "Your bomber can kick bombs (bomb is moving through the arena), punch bombs (bomb flies three blocks far), or throw bombs (pick up a bomb and throw it in the direction your bomber is currently looking)." );

_add( "Customizable arena levels with a level editor", "No additional text available." );

_add( "Keyboard and joystick support", "No additional text available." );

_add( "Full screen and windowed display modes", "<kbd>F1</kbd>, <kbd>F2</kbd> and <kbd>F3</kbd> are full screen modes. <kbd>F4</kbd> returns to windowed mode." );

_add( "Various power-ups", "At the beginning of a match your bomber can drop only one bomb with a flame size of two blocks. This can be changed during the game by collecting power-up icons. These icons are hidden in the soft walls. Destroy the soft walls to look for the power-ups. These items can improve your bomber skills: additional bomb, increase flame size, ability to kick bombs, increase speed, ability to throw bombs, ability to punch bombs." );

_add( "Various contaminations after skull item is taken", "The skull item influences the health of your bomber. It can result to: inverted controls, bombs with small flames, have no bombs to place, always dropping bombs, slow speed, fast speed, always move, bombs ticking shorter, and bombs ticking longer than usual. <i>Next version: </i>invisibility of a bomber, bomber is flameproof." );

_add( "<i>Next version: </i>Item amount in walls as well as bomber skills on startup can be set on a per-level basis", "For this a new layout for level files has been designed to configure the amount of items and the skills at the start of a match." );

?>

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
More items may follow. A list of planned features can be seen in the <a href="./todo.php">To-Do list</a>.
</p>

</div>

<?php

$webpage->tail();

?>
