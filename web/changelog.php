<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

?>

<h1>Bombermaaan Changelog</h1>

<div id="content">

<p>
You are informed of what was changed, fixed, added, and removed in each version.
</p>

<?php

$fp = @fopen( "CHANGELOG.txt", "r" );

if ( $fp ) {

	while ( ! feof( $fp ) ) {
	
		$line = rtrim( fgets( $fp, 2048 ) );
		
		if ( strlen( $line ) == 0 ) {
		} elseif ( preg_match( "/^(New feature|Bug fix|Changed): (.*)/", $line, $match )  or  preg_match( "/^: (.*)/", $line, $match ) ) {
			$html = htmlentities( $match[ 2 ] );
			switch ( $match[ 1 ] ) {
				case "New feature": $atid = 563213; break;
				case "Bug fix": $atid = 563210; break;
				default: $atid = 0;
			}
			if ( $atid != 0 ) {
				$html = preg_replace_callback( "/#([[:digit:]]+)/", create_function( '$matches', 'return "<a href=\"https://sourceforge.net/tracker/index.php?func=detail&amp;aid=" . $matches[ 1 ] . "&amp;group_id=81520&amp;atid=' . $atid . '\">" . $matches[ 0 ] . "</a>";' ), $html );
			}
			echo "<div><strong>" . htmlentities( $match[ 1 ] ) . "</strong>: " . $html . "</div>";
		} elseif ( preg_match( "/^Version .*/", $line )  or  preg_match( "/^Next version/", $line ) ) {
			echo "<h2>" . htmlentities( $line ) . "</h2>";
		} elseif ( preg_match( "/^--+/", $line ) ) {
			echo "<hr style='margin-top: 2em;'/>";
		} elseif ( preg_match( "/^Released on /", $line ) ) {
			echo "<div style='margin-bottom: 1em;'>" . htmlentities( $line ) . "</div>";
		} else {
			echo "<ul><li>" . htmlentities( $line ) . "</li></ul>";
		}
	}
	
	fclose ( $fp );
	
} else {

	echo "<p>";
	echo htmlentities( "There is an error with the Changelog. You may report this error in the forum if you wish." );
	echo "</p>";
	
}

?>

</div>

<?php

$webpage->tail();

?>
