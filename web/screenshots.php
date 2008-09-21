<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

?>

<h1>Bombermaaan screenshots</h1>

<div id="content">

<div id="quicklinks">
<p style="float: right; margin-right: 0.8em; font-style: italic;">Quick links</p>
<ul>
<li><a href="#v102">Version 1.02</a></li>
<li><a href="#pr528">Preview version Rev. 528</a></li>
<li><a href="#pr153">Preview version Rev. 153</a></li>
</ul>
</div>

<h2><a id="v102">Version 1.02</a></h2>

<p>
<img style="padding: 2em;" src="screenshots/screen1.png" alt="Screenshot #1" />
<img style="padding: 2em;" src="screenshots/screen7.png" alt="Screenshot #2" />
<img style="padding: 2em;" src="screenshots/screen8.png" alt="Screenshot #3" />
</p>

<h2><a id="pr528">Preview version Rev. 528</a></h2>

<p>
Showing the feature &quot;remote fusing bombs&quot;
</p>

<p>
<img style="padding: 2em;" src="screenshots/rev528_01.png" alt="Screenshot #1" />
</p>

<h2><a id="pr153">Preview version Rev. 153</a></h2>

<p>
Running Bombermaaan on Vista
</p>

<p>
<img style="padding: 2em;" src="screenshots/rev153_01.png" alt="Screenshot #1" />
</p>

</div>

<?php

$webpage->tail();

?>
