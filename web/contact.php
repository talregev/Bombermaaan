<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

?>

<h1>Contact</h1>

<div id="content">

<h2>Developers</h2>

<p>
<strong>Thibaut</strong> created this project. He doesn't have the time to work on Bombermaaan at the moment.
</p>

<p>
<strong>Bernd</strong> joined the project in the end of 2007. 
You can <a href="https://sourceforge.net/sendmessage.php?touser=988911">send him a message</a> via SourceForge.net.
This requires that you are loggend in with your SourceForge.net account.
</p>

<h2>Trackers</h2>

<p>
<a href="https://sourceforge.net/tracker/?atid=563210&group_id=81520&func=browse">Bug tracker</a>: Report and view bugs.
</p>

<p>
<a href="https://sourceforge.net/tracker/?atid=563213&group_id=81520&func=browse">Feature requests</a>: List feature requests for Bombermaaan or submit your own.
</p>

<h2>Forums</h2>

<p>
You can visit the <a href="https://sourceforge.net/forum/?group_id=81520">forums</a> on SourceForge.net.
</p>

</div>

<?php

$webpage->tail();

?>
