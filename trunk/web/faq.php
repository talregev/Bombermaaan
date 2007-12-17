<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

?>

<h1>Bombermaaan Frequently Asked Questions</h1>

<div id="content">

<?php

function _Q( $q ) {
?>
<div class="qablock">

<div class="question">
<abbr title="Question">Q:</abbr>
<?php echo htmlentities( $q ); ?>
</div>
<?php
}

function _A( $a ) {
?>
<div class="answer">
<abbr title="Answer">A:</abbr>
<?php echo htmlentities( $a ); ?>
</div>

</div>

<?php
}

_Q( "I get an error message about DDRAW.DLL." );
_A( "Please ensure you have downloaded and installed Microsoft DirectX 7.0 or later. You can download it from the Microsoft site." );

_Q( "I get an error message about FMOD.DLL." );
_A( "Please ensure you have unzipped the ZIP file in a directory before launching the executable." );

_Q( "(When) Will you add network support?" );
_A( "Thibaut already started adding some code, but this task is currently suspended. Thibaut doesn't have time to implement this and Bernd doesn't have the knowledge." );

_Q( "How do I make joysticks work?" );
_A( "You have to plug in the joystick(s) to your machine, install it within Windows, ensure Windows can read the joystick(s) state. Finally, launch the game, and you will be able to select JOYSTICK1, JOYSTICK2, and so on, according to the number of joysticks you have." );

_Q( "My computer beeps when there are too many keys pressed on the keyboard." );
_A( "This is a known bug. In fact, it depends if your keyboard's hardware supports a lot of keys pressed at once. Generally USB and PS2 keyboards are OK with this. Older keyboards generally can't have a lot of keys pressed together." );

_Q( "Sometimes the bombers don't accept moving commands." );
_A( "This could happen if too many keys are pressed on the keyboard at the same time. In fact, it depends if your keyboard's hardware supports a lot of keys pressed at once. Generally USB and PS2 keyboards are OK with this. Older keyboards generally can't have a lot of keys pressed together." );

_Q( "I've found a bug. Are you interested?" );
_A( "Yes, we are. Please report bugs to the bug tracker at sourceforge.net by submitting a new tracker item." );

_Q( "I start Bombermaaan, but I don't get any windows. Additionally, I don't see a running Bombermaaan task in the task manager." );
_A( "Maybe Bombermaaan encountered an error and quit. There should be a log file created by Bombermaaan where the Bombermaaan.exe file resides. You can check this by yourself and/or open a support request item at the sourceforge.net support tracker." );

?>
<?php

$webpage->tail();

?>
