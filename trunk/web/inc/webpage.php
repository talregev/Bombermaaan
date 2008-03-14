<?php

class WebPage {

	var $option_addFeatureJavascript;
	
	function WebPage() {
	
		// By default, do not include the javascript script (only used by the feature list so far)
		$this->option_addFeatureJavascript = 0;
		
	}
	
	function head() {
	
		#header( "Vary: Accept" );
		#if (stristr($_SERVER["HTTP_ACCEPT"], "application/xhtml+xml")) 
		#    header( "Content-Type: application/xhtml+xml; charset=utf-8" );
		#else
		    header("Content-Type: text/html; charset=utf-8");

		echo '<?' . 'xml version="1.0" encoding="UTF-8"?>' . "\n";
		echo '<!' . 'DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">' . "\n";
		?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="Title" content="Bombermaaan game project" />
<meta name="Author" content="Thibaut Tollemer, Bernd Arnold" />
<meta name="Revisit" content="After 15 days" />
<meta name="Keywords" content="bomberman bomber man bombermaaan maaan fury game windows download arena bomb explosion item wall victory player players play" />
<meta name="Description" content="Bombermaaan game project. A DirectX Bomberman game for Windows 95 and later. Original and classic game play. Up to 5 players on the same computer..." />
<meta name="Abstract" content="Bombermaaan game project. A DirectX Bomberman game for Windows 95 and later. Original and classic game play. Up to 5 players on the same computer..." />
<meta name="Robots" content="INDEX,FOLLOW" />
<meta name="Language" content="English" />
<link rel="icon" href="/favicon.ico" type="image/ico" />
<link rel="shortcut icon" href="/favicon.ico" type="image/ico" />
<link rel="stylesheet" href="/css.php" type="text/css" />
<title>Bombermaaan game project</title>
		<?php
		
		if ( $this->option_addFeatureJavascript == 1 ) {
			$this->javascript_FeatureList();
		}
		
		?>
</head>

<body>
		<?php
		
		$this->menu();

	}
	
	function tail() {
	
		?>
<div id="tail">
<p>
<a href="http://bombermaaan.sourceforge.net/">http://bombermaaan.sourceforge.net/</a>
</p>
<p>
<a href="http://sourceforge.net"><img style="border: 0px;" src="http://sflogo.sourceforge.net/sflogo.php?group_id=81520&amp;type=4" width="125" height="37" alt="SourceForge.net Logo" /></a>
<a href="http://validator.w3.org/check?uri=referer"><img style="border: 0px;" src="http://www.w3.org/Icons/valid-xhtml11-blue" alt="Valid XHTML 1.1" height="31" width="88" /></a>
<a href="http://jigsaw.w3.org/css-validator/check/referer">
  <img style="border:0;width:88px;height:31px"
       src="http://jigsaw.w3.org/css-validator/images/vcss" 
       alt="Valid CSS!" />
 </a>
</p>
</div>

</body>

</html>
        <?php
	
	}
	
	function menu() {

		?>
<div id="side">

<div id="logoimage">
<a href="/"><img src="images/title.png" alt="The Bombermaaan logo" /></a>
</div>

<div id="menu">

<div>
<a href="/">Home</a>
</div>

<div>
<a href="download.php">Download</a>
</div>

<div>
<a href="license.php">License</a>
</div>

<div>
<a href="screenshots.php">Screenshots</a>
</div>

<hr />
  
<div>
<a href="features.php">Features</a>
</div>

<div>
<a href="todo.php">To-Do</a>
</div>

<div>
<a href="faq.php">FAQ</a>
</div>

<div>
<a href="changelog.php">Changelog</a>
</div>

<hr />

<div>
<a href="development.php">Development</a>
</div>
<div>
<a href="contact.php">Contact</a>
</div>
<div>
<a href="feedback.php">Feedback <sup>New!</sup></a>
</div>

</div>

<div style="margin-top: 2em; text-align: center;">
<img src="images/bomber_a.png" alt="A bomber" />
</div>

</div>
		<?php

	}
	
	function javascript_FeatureList() {
	
		?>
<script type="text/javascript">
<!--
function toggleFeatureItem( nr ) {

    e = document.getElementById( "feature-more-" + nr );
    sign = document.getElementById( "feature-sign-" + nr );
	
	if ( e == null || sign == null ) return;
	
	if ( e.style.display == 'none' ) {
		e.style.display = '';
		sign.firstChild.data = "-";
	} else {
		e.style.display = 'none';
		sign.firstChild.data = "+";
	}

}
//-->
</script>
		<?php
		
	}
	
	function setOption_AddFeatureJavascript() {
	
		$this->option_addFeatureJavascript = 1;
	
	}
	
}

?>