<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

?>

<h1>Feedback</h1>

<div id="content">

<?php

$outputfilename = "./external/feedback_output.html";

// Check for file size
// Function filesize prints warning if used without @ and file does not exist
if ( @filesize( $outputfilename ) < 500000 ) {
    if ( isset( $_POST[ "feedback_timestamp" ] ) ) {
        processSubmit( $outputfilename );
    } else {
        showForm();
    }
} else {
    showError();
}

?>

</div>

<?php

$webpage->tail();

exit;


/////////////////////////////////////////////////////////////////
//
//

function showForm() {

?>

<h2>Please...</h2>

<p>
... let us know what <strong>you</strong> think about Bombermaaaan. You don't have to fill every block. Just give us the informations you'd like to. You can also just leave a short message for us - see <a href="#message">input box 5</a>.
</p>

<p>

<form action="feedback.php" method="post" accept-charset="utf-8">

<h2>Please choose...</h2>

<div class="feedback_block">
<div>
1. How much do you like Bombermaaan?
</div>
<label><input type="radio" name="likeit" value="1" /> 1 (like it very much)</label><br />
<label><input type="radio" name="likeit" value="2" /> 2</label><br />
<label><input type="radio" name="likeit" value="3" /> 3</label><br />
<label><input type="radio" name="likeit" value="4" /> 4 (don't like it)</label><br />
</div>

<div class="feedback_block">
<div>
2. How often do you play Bombermaaan?
</div>
<label><input type="radio" name="playit" value="1" /> Sometimes, not very often</label><br />
<label><input type="radio" name="playit" value="2" /> About twice a week</label><br />
<label><input type="radio" name="playit" value="3" /> Almost every day</label><br />
<label><input type="radio" name="playit" value="4" /> Every day</label><br />
</div>

<h2>Please fill in...</h2>

<div class="feedback_block">
<div>
3. What do you like in Bombermaaan?
</div>
<textarea name="likewhat" cols="50" rows="8"></textarea>
</div>

<div class="feedback_block">
<div>
4. What do you <strong>not</strong> like in Bombermaaan?
</div>
<textarea name="dontlikewhat" cols="50" rows="8"></textarea>
</div>

<div class="feedback_block">
<div>
<a id="message">5. Your message for us</a>
</div>
<textarea name="message" cols="50" rows="8"></textarea>
</div>

<div class="feedback_block">
For verification, please type in the <strong>last four characters</strong> of this string:<br />
<?php
$verification = floor( time() / 1000 );
echo $verification;
?>
&nbsp;&nbsp;&nbsp;
<input type="text" name="verification" />
</div>

<p>
<input type="submit" /> -
<input type="reset" />
</p>

<input type="hidden" name="feedback_timestamp" value="<?php echo time(); ?>" />

</form>

</p>

<?php

}


/////////////////////////////////////////////////////////////////
//
//

function showError() {

?>

<h2>Function not available</h2>

<p>
The size of the feedback file is too big. We're sorry, but you cannot give feedback now. You can contact a project administrator if you wish. See the <a href="https://sourceforge.net/project/memberlist.php?group_id=81520">member list</a> on SourceForge.net.
</p>

<p>
Please visit this page soon again!
</p>

<?php

}



/////////////////////////////////////////////////////////////////
//
//

function processSubmit( $outputfilename ) {

if ( get_magic_quotes_gpc() ) {
	// Strip slashes if magic quotes are enabled
	foreach( $_POST as $key => $value ) {
		$_POST[ $key ] = stripslashes( $value );
	}
}

$replace_newlines = array( "\r\n", "\n", "\r" );

$logentry = "<tr>";
$logentry .= "<td>" . date( "Y-m-d" ) . "</td>";
$logentry .= "<td><!--01_likeit-->" . htmlentities( $_POST[ "likeit" ], ENT_COMPAT, "UTF-8" ) . "</td>";
$logentry .= "<td><!--02_playit-->" . htmlentities( $_POST[ "playit" ], ENT_COMPAT, "UTF-8" ) . "</td>";
$logentry .= "<td><!--03_likewhat-->" . str_replace( $replace_newlines, "<br />", htmlentities( $_POST[ "likewhat" ], ENT_COMPAT, "UTF-8" ) ) . "</td>";
$logentry .= "<td><!--04_dontlikewhat-->" . str_replace( $replace_newlines, "<br />", htmlentities( $_POST[ "dontlikewhat" ], ENT_COMPAT, "UTF-8" ) ) . "</td>";
$logentry .= "<td><!--05_message-->" . str_replace( $replace_newlines, "<br />", htmlentities( $_POST[ "message" ], ENT_COMPAT, "UTF-8" ) ) . "</td>";
$logentry .= "<td><!--formtimestamp-->" . htmlentities( $_POST[ "feedback_timestamp" ], ENT_COMPAT, "UTF-8" ) . "</td>";
$logentry .= "<td><!--verification-->" . htmlentities( $_POST[ "verification" ], ENT_COMPAT, "UTF-8" ) . "</td>";
$logentry .= "<td><!--difference_verification-->" . htmlentities( substr( $_POST[ "feedback_timestamp" ], -7, 4 ) * 1 - $_POST[ "verification" ] * 1, ENT_COMPAT, "UTF-8" ) . "</td>";
$logentry .= "</tr>";
$logentry .= "\n";

//echo "<pre>"; var_dump( $_POST ); echo "</pre>";

$fp = fopen( $outputfilename, "aw+" );
fputs( $fp, $logentry );
fclose( $fp );

?>

<h2>Thank you</h2>

<p>
Thank you very much for your feedback!
</p>

<?php

}

?>
