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

<h1>Bombermaaan game project on sourceforge.net</h1>

<div id="content">

<h2>Introduction</h2>

Bombermaaan is a classic bomberman game. Thibaut Tollemer started this
project on July 2000. He's been using this project as a demo of what he 
could do as a game programmer, in order to be hired.

As he was hired, he published the source code and created a project space on sourceforge.net.

<h2>Resources</h2>

You may want to view ...

<ul>
<li><a href="http://fury94.free.fr/">Thibaut's original project page</a></li>
<li>the <a href="https://sourceforge.net/projects/bombermaaan/">project page on sourceforge.net</a></li>
<li>the <a href="https://sourceforge.net/project/showfiles.php?group_id=81520">download section on sourceforge.net</a></li>
<li>the <a href="http://bombermaaan.svn.sourceforge.net/viewvc/bombermaaan/">subversion repository</a> on sourceforge.net</li>
<li>the <a href="http://bombermaaan.svn.sourceforge.net/viewvc/*checkout*/bombermaaan/trunk/docs/Readme.html?revision=5&amp;pathrev=5">README file</a> (very latest version out of the subversion repository)</li>
</ul>

Pages on sourceforge.net ...

<ul>
<li><a href="http://sourceforge.net/tracker/?atid=563210&amp;group_id=81520&amp;func=browse">bug reporting</a></li>
<li><a href="http://sourceforge.net/tracker/?atid=563213&amp;group_id=81520&amp;func=browse">feature requests</a></li>
<li><a href="http://sourceforge.net/forum/?group_id=81520">forums</a></li>
<li><a href="http://sourceforge.net/export/rss2_project.php?group_id=81520">list of RSS feeds</a></li>
</ul>

</div>

<?php

$webpage->tail();

?>
