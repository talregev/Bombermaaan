<?php
$no_redirect = 1; // required for passwords.php

include_once( "inc/webpage.php" ); // this is the same as in trunk/web/inc
include_once( "inc/passwords.php" ); // defines $mysql_user, $mysql_pass, $mysql_data and $public_keyrequire_once('inc/recaptchalib.php'); // available at http://recaptcha.net/plugins/php/

/* define these variables:
$mysql_user = "";
$mysql_pass = "";
$mysql_data = "";
$public_key = "";
*/

$dir = "levels/";
$levelsPerPage = 12;

if (strstr($_SERVER['SERVER_NAME'], "uni-karlsruhe.de"))
	$mysql_host = "mysql.stud.uni-karlsruhe.de";
else
	$mysql_host = "localhost";
	

// check mode: level or image?
if ($_REQUEST["level"])
{
	$download_level = floor($_REQUEST["level"]) + 1 - 1; 
	$extension = "";
	$fullFileName = "";
	
	if ($download_level > 0)
	{
		// download level
		$file = sprintf("%08d", $download_level);
		header('Content-type: text/plain');
		$extension = ".txt";
	}

	if (is_dir($dir) && $extension != "")
	{
		$found = false;
		
		if ($dh = opendir($dir))
		{
			while (($fileInDir = readdir($dh)) !== false)
			{
				if (is_file($dir . $fileInDir))
				{
					if (substr($fileInDir, 0, strlen($file)) == $file && 
						strtolower(substr($fileInDir, strlen($file), 4)) == $extension)
					{
						// found image/level in dir
						$found = true;
						$fullFileName = $fileInDir;
						break;
					}
				}
			}
			closedir($dh);
		}
		
		if ($found)
		{
			// update download count
			$link = mysql_connect($mysql_host, $mysql_user, $mysql_pass);
			
			if ($link && !mysql_select_db($mysql_data, $link))
			{
		    mysql_close($link);
		    $link = FALSE;
		  }
		  
		  if ($link)
		  {
		  	// update meta information
		  	$res = mysql_query("SELECT id,downloads FROM levels WHERE `levelnumber` = $download_level", $link);
		  	if (!$res)
		  	{
			    mysql_close($link);
			    $link = FALSE;
		  	}
		  	else
		  	{
					if ($row = mysql_fetch_array($res)) {
						$id = $row["id"];
				  	$downloads = $row["downloads"] + 1;
				  	
				  	mysql_free_result($res);
				  	
				  	// update this row
				  	$res = mysql_query("UPDATE levels SET `downloads` = $downloads WHERE `id` = $id", $link);
					}
					else
					{
						mysql_free_result($res);
					}
		  	}
		  }
			
			if ($link) mysql_close($link);
			
			// only show image/download level if the file is present in the directory
			header('Content-Disposition: attachment; filename="' . $fullFileName . '"');
		
			readFile($dir . $fullFileName);
		}
	}
	die();
}
else if ($_REQUEST["vote"])
{
	$vote_level = floor($_REQUEST["vote"]) + 1 - 1;
	$mark = floor($_REQUEST["mark"]) + 1 - 1;
	
	if ($vote_level > 0 && $mark > 0 && $mark <= 5)
	{
		$link = mysql_connect($mysql_host, $mysql_user, $mysql_pass);
		
		if ($link && !mysql_select_db($mysql_data, $link))
		{
	    mysql_close($link);
	    $link = FALSE;
	  }
	  
	  if ($link)
	  {
	  	// update meta information
	  	$res = mysql_query("SELECT id,mark,votes FROM levels WHERE `levelnumber` = $vote_level", $link);
	  	if (!$res)
	  	{
		    mysql_close($link);
		    $link = FALSE;
	  	}
	  	else
	  	{
				if ($row = mysql_fetch_array($res)) {
					$id = $row["id"];
			  	$old_mark = $row["mark"];
			  	$votes = $row["votes"];
			  	
			  	// update values
			  	$mark = ($old_mark * $votes + $mark) / ($votes + 1);
			  	$votes++; 
			  	
			  	mysql_free_result($res);
			  	
			  	// update this row
			  	$res = mysql_query("UPDATE levels SET `mark` = '$mark', `votes` = '$votes' WHERE `id` = $id", $link);
				}
				else
				{
					mysql_free_result($res);
				}
	  	}
	  }
		
		if ($link) mysql_close($link);
	}
	  
	$page = floor($vote_level / $levelsPerPage) + 1;
	if ($page > 0)
		header('Location: levels.php?page='.$page);
	else
		header('Location: levels.php');
}
else {
	// normal webpage
	$webpage = new WebPage();
	$webpage->head();
}

?>

<h1>Bombermaaan Levels</h1>

<div id="content">

<div class="description">
	On this page you can <a href="#download">download</a> levels for Bombermaaan. You can <a href="#upload">upload</a> your own level, too.<br/>
	All levels on this site are public domain which means there is no copyright for any level.<br/>
	To save a level <b>right-click the level image</b> you want to download, click <b>Save Link As</b>... and choose your Bombermaaan Levels folder.<br/>
	<br/>
	Markus is responsible for this level section. Feel free to <a href="http://bombermaaan.sourceforge.net/contact.php">contact</a> him if you find bugs or have suggestions. You may also use the tracker. 
</div>

<h2><a id="download">Download Levels</a></h2>

<?php
	function parseLevelFile($fd, &$levelarray)
	{
		$line = fgets($fd);
		
		if (preg_match('/^; Bombermaaan level file version=\d/', $line))
		{
			// level version >= 2: meta information available
			do
			{
				$line = fgets($fd);
				
				
				if (preg_match('/^Width=(\d+)/', $line, $matches))
				{
					$levelarray["width"] = $matches[1];
				}
				else if (preg_match('/^Height=(\d+)/', $line, $matches))
				{
					$levelarray["height"] = $matches[1];
				}
				else if (preg_match('/^MaxPlayers=(\d+)/', $line, $matches))
				{
					$levelarray["maxplayers"] = $matches[1];
				}
				else if (preg_match('/^MinPlayers=(\d+)/', $line, $matches))
				{
					$levelarray["minplayers"] = $matches[1];
				}
				else if (preg_match('/^Creator=(.+)/', $line, $matches))
				{
					$levelarray["creator"] = $matches[1];
				}
				else if (preg_match('/^Comment=(.+)/', $line, $matches))
				{
					$levelarray["comment"] = $matches[1];
				}
				else if (preg_match('/^Description=(.+)/', $line, $matches))
				{
					$levelarray["description"] = $matches[1];
				}
			}
			while (!feof($fd));
		}
		else
		{
			// level version 1: fill with default values
			$levelarray["width"] = 15;
			$levelarray["height"] = 13;
			$levelarray["maxplayers"] = 5;
			$levelarray["minplayers"] = 1;
		}
	}
	
	// scan dir for files
	$files = array();
	$shortname = "";
	$rowsPerLevel = 8;	
	
	if ($_REQUEST["page"])
		$page = floor($_REQUEST["page"]);
	else
		$page = 1;
		
	if ($page < 1) $page = 1;

	function previousnextrow($sizeoffiles, $colspan)
	{
		global $levelsPerPage, $page;
		$pages = (int)floor($sizeoffiles / $levelsPerPage) + 1; 
		
		if ($sizeoffiles > $levelsPerPage)
		{
			echo "\t<tr>\n";
			echo "\t\t<td align=\"left\">\n";
			if ($page > 1)
				echo "<a href=\"levels.php?page=" . ($page-1) . "\">&lt;&lt;</a>\n";
			else
				echo "&lt;&lt;";
				
			echo "\t\t</td>\n";
			echo "\t\t<td align=\"center\" colspan=\"$colspan\">";
			if ($page != 1)
				echo "<a href=\"levels.php\">[1]</a>";
			else
				echo "[1]";
			
			if ($page > 3)
				echo " ..."; 
				
			if ($page > 2)
				echo " <a href=\"levels.php?page=".($page-1)."\">[".($page-1)."]</a>";

			if ($page != 1 && $page != $pages)
				echo " [".($page)."]";
			
			if ($page + 1 < $pages)
				echo " <a href=\"levels.php?page=".($page+1)."\">[".($page+1)."]</a>";
				
			if ($page + 2 < $pages)
				echo " ...";
				
			if ($pages > 1 && $page != $pages)
				echo " <a href=\"levels.php?page=$pages\">[$pages]</a>";
			else if ($pages > 1)
				echo " [$pages]";
				
			echo "</td>\n";
			echo "\t\t<td align=\"right\">\n";
			
			if ($page * $levelsPerPage < $sizeoffiles)
				echo "<a href=\"levels.php?page=" . ($page+1) . "\">&gt;&gt;</a>\n";
			else
				echo "&gt;&gt;";
				
			echo "\t\t</td>\n";
			echo "\t</tr>\n";
		}
	}
	
		
	if (is_dir($dir))
	{
		if ($dh = opendir($dir))
		{
			while (($file = readdir($dh)) !== false)
			{
				if (is_file($dir . $file))
				{
					if (strtolower(substr($file, strlen($file) - 4, 4)) == ".txt")
					{
						$shortname = substr($file, 0, strlen($file) - 4);
						
						// this is a level file
						if (!$files[$shortname])
							$files[$shortname] = array("filename" => $file);
						else
							$files[$shortname]["filename"] = $file;
							
						// parse level file
						if ($fd = fopen($dir . $file, "r"))
						{
							parseLevelFile($fd, $files[$shortname]);
							fclose($fd);
						}
						
						$files[$shortname]["datetime"] = date("Y-m-d H:i:s", filemtime($dir . $file));
						
						// default values
				  	$files[$shortname]["mark"] = 0;
				  	$files[$shortname]["votes"] = 0;
				  	$files[$shortname]["downloads"] = 0;
					}
					else if (strtolower(substr($file, strlen($file) - 4, 4)) == ".png")
					{
						$shortname = substr($file, 0, strlen($file) - 4);
						
						// this is the thumbnail to a level file
						if (!$files[$shortname])
							$files[$shortname] = array("thumbnail" => $file);
						else
							$files[$shortname]["thumbnail"] = $file;
					}
				}
			}
			closedir($dh);
		} 
	}
	
	$link = mysql_connect($mysql_host, $mysql_user, $mysql_pass);
	if (!$link) {
	    echo "<b>Warning</b>: The database connection could not be established. Meta information will not be shown correctly. Error: " . mysql_error() . "<br/>";
	}
	
	if (!mysql_select_db($mysql_data, $link))
	{
    echo "<b>Warning</b>: The database could not be selected. Meta information will not be shown correctly. Error: " . mysql_error() . "<br/>";
    mysql_close($link);
    $link = FALSE;
  }
  
  if ($link)
  {
  	// update meta information
  	$res = mysql_query("SELECT levelnumber,creator,comment,description,datetime,mark,votes,downloads FROM levels", $link);
  	if (!$res)
  	{
	    echo "<b>Warning</b>: The levels table could not be queried. Meta information will not be shown correctly. Error: " . mysql_error() . "<br/>";
	    mysql_close($link);
	    $link = FALSE;
  	}
  	else
  	{
			while($row = mysql_fetch_array($res)) {
				$shortname = sprintf("%08d", $row["levelnumber"]);
			
				if ($files[$shortname])
				{
					if ($row["creator"])
			  		$files[$shortname]["creator"] = $row["creator"];
			  	if ($row["comment"])
			  		$files[$shortname]["comment"] = $row["comment"];
			  	if ($row["description"])
			  		$files[$shortname]["description"] = $row["description"];
			  	if ($row["datetime"])
			  		$files[$shortname]["datetime"] = $row["datetime"];
			  	
			  	$files[$shortname]["mark"] = round($row["mark"] * 100) / 100;
			  	$files[$shortname]["votes"] = $row["votes"];
			  	$files[$shortname]["downloads"] = $row["downloads"];
			  }
			}
			
			mysql_free_result($res);
  	}
  }
	
	if ($link) mysql_close($link);
	
	// sort pages?
	$key = $_REQUEST["sort"];
	$order = $_REQUEST["order"]; // 2: descending, 1: ascending
	
	// default values if invalid
	if (strcmp($key,"description") && strcmp($key,"creator") &&
		strcmp($key,"comment") && strcmp($key,"datetime") &&
		strcmp($key,"downloads") && strcmp($key,"mark"))
		$key = "datetime";
		
	if ($order < 1 || $order > 2)
	{
		if ($key == "datetime" || $key == "mark" || $key == "downloads") // descending is standard
			$order = 2;
		else // ascending is standard
			$order = 1;
	}
	
	function cmp_by_field($a, $b)
	{
		global $key, $order;
		
		if ($order == 2) return strcmp($a[$key],$b[$key]) * -1;
		else return strcmp($a[$key],$b[$key]);
	}

	// sort by key
	if ($key)
		uasort($files, "cmp_by_field");
	else
		ksort($files, SORT_STRING);
	
	reset($files);
	if ($page > 1)
	{
		while (($page-1) * $levelsPerPage > sizeof($files))
		{
			$page--;
			if ($page == 1) break;
		}
	}

	if ($page == 1)
	{
		$firstLevel = 0;
	}
	else
	{
		$firstLevel = ($page-1) * $levelsPerPage;
		for ($do_next = $firstLevel; $do_next > 0; $do_next--)
			next($files);
	}
	
?>
<script type="text/javascript">
	<!--
	var ratings = new Array(<?php echo min($firstLevel + $levelsPerPage, sizeof($files)); ?>);
<?php
	for ($level = 0; $level < min($firstLevel + $levelsPerPage, sizeof($files)) - $firstLevel ; $level++, next($files))
	{
		$levelName = key($files);
		echo "\t" . "ratings[" . $level . "] = " . $files[$levelName]["mark"] . ";\n";
	}
?>
	
	function voteOnMouseOver(element, mark)
	{
		eval("document.vote" + element + "_1").src="images/bomb_vote1.png";
		if (mark > 1) eval("document.vote" + element + "_2").src="images/bomb_vote1.png";
		else eval("document.vote" + element + "_2").src="images/bomb_vote2.png";
		
		if (mark > 2) eval("document.vote" + element + "_3").src="images/bomb_vote1.png";
		else eval("document.vote" + element + "_3").src="images/bomb_vote2.png";
		
		if (mark > 3) eval("document.vote" + element + "_4").src="images/bomb_vote1.png";
		else eval("document.vote" + element + "_4").src="images/bomb_vote2.png";
		
		if (mark > 4) eval("document.vote" + element + "_5").src="images/bomb_vote1.png";
		else eval("document.vote" + element + "_5").src="images/bomb_vote2.png";
	}

	function voteOnMouseOut(element, mark)
	{
		if (ratings[element] > .999) eval("document.vote" + element + "_1").src="images/bomb_vote1.png";
		else eval("document.vote" + element + "_1").src="images/bomb_vote2.png";
		
		if (ratings[element] > 1.999) eval("document.vote" + element + "_2").src="images/bomb_vote1.png";
		else if (ratings[element] > 1.499) eval("document.vote" + element + "_2").src="images/bomb_vote3.png";
		else eval("document.vote" + element + "_2").src="images/bomb_vote2.png";
		
		if (ratings[element] > 2.999) eval("document.vote" + element + "_3").src="images/bomb_vote1.png";
		else if (ratings[element] > 2.499) eval("document.vote" + element + "_3").src="images/bomb_vote3.png";
		else eval("document.vote" + element + "_3").src="images/bomb_vote2.png";
		
		if (ratings[element] > 3.999) eval("document.vote" + element + "_4").src="images/bomb_vote1.png";
		else if (ratings[element] > 3.499) eval("document.vote" + element + "_4").src="images/bomb_vote3.png";
		else eval("document.vote" + element + "_4").src="images/bomb_vote2.png";
		
		if (ratings[element] > 4.999) eval("document.vote" + element + "_5").src="images/bomb_vote1.png";
		else if (ratings[element] > 4.499) eval("document.vote" + element + "_5").src="images/bomb_vote3.png";
		else eval("document.vote" + element + "_5").src="images/bomb_vote2.png";
	}

	// -->
</script>
<table>
	<tr>
		<th colspan="5">Levels created by Users</th>
	</tr>
	<tr>
		<td colspan="5" align="right">Sort by:
<?php
		echo "<a href=\"levels.php?page=$page&amp;sort=comment";
		if ($key == "comment")
			echo "&amp;order=" . (($order == 2)?1:2) . "\"><b>Comment</b></a> ";
		else
			echo "\">Comment</a> ";
	
		echo "<a href=\"levels.php?page=$page&amp;sort=creator";
		if ($key == "creator")
			echo "&amp;order=" . (($order == 2)?1:2) . "\"><b>Creator</b></a> ";
		else
			echo "\">Creator</a> ";

		echo "<a href=\"levels.php?page=$page&amp;sort=description";
		if ($key == "description")
			echo "&amp;order=" . (($order == 2)?1:2) . "\"><b>Description</b></a> ";
		else
			echo "\">Description</a> ";
		
		echo "<a href=\"levels.php?page=$page&amp;sort=downloads";
		if ($key == "downloads")
			echo "&amp;order=" . (($order == 2)?1:2) . "\"><b>No. of Downloads</b></a> ";
		else
			echo "\">No. of Downloads</a> ";
		
		echo "<a href=\"levels.php?page=$page&amp;sort=mark";
		if ($key == "mark")
			echo "&amp;order=" . (($order == 2)?1:2) . "\"><b>Rating</b></a> ";
		else
			echo "\">Rating</a> ";
		
		echo "<a href=\"levels.php?page=$page&amp;sort=datetime";
		if ($key == "datetime")
			echo "&amp;order=" . (($order == 2)?1:2) . "\"><b>Upload Date</b></a>";
		else
			echo "\">Upload Date</a>";
		
?>
		</td>
	</tr>
<?php

	previousnextrow(sizeof($files), 3);

	// find array element again.
	reset($files);
	
	if ($page == 1)
	{
		$firstLevel = 0;
	}
	else
	{
		$firstLevel = ($page-1) * $levelsPerPage;
		for ($do_next = $firstLevel; $do_next > 0; $do_next--)
			next($files);
	}

	for ($level = $firstLevel; $level < min($firstLevel + $levelsPerPage, sizeof($files)) ; $level++, next($files))
	{
		echo "\t<tr>";
		echo "\t\t<td rowspan=\"$rowsPerLevel\">&nbsp;</td>\n";
		
		$current = current($files);
		$levelName = key($files);
		$levelFile = floor($levelName) + 1 - 1;
		$levelImage = $dir . urlencode($levelName . ".png");
		
		if ($level < sizeof($files))
		{
			if ($files[$levelName]["thumbnail"])
				echo "\t\t\t<td align=\"left\" style=\"width: 210px;\" rowspan=\"$rowsPerLevel\"><a href=\"levels.php?level=$levelFile\"><img src=\"$levelImage\" width=\"240\" height=\"208\" alt=\"Level Preview\" /></a></td>\n";
			else
				echo "\t\t\t<td align=\"left\" style=\"width: 210px;\" rowspan=\"$rowsPerLevel\"><a href=\"levels.php?level=$levelFile\">(no preview available)</a><td/>\n";

			// description
			echo "\t\t\t<td align=\"right\"><b>Description: </b></td>\n";
			if ($files[$levelName]["description"])
				echo "\t\t\t<td align=\"left\">".$files[$levelName]["description"]."</td>\n";
			else
				echo "\t\t\t<td align=\"left\">(none)</td>\n";
			echo "\t\t\t<td>&nbsp;</td>\n";
			echo "\t\t</tr>\n\t\t<tr>\n";

			// creator
			echo "\t\t\t<td align=\"right\"><b>Created by: </b></td>\n";
			if ($files[$levelName]["creator"])
				echo "\t\t\t<td align=\"left\">".$files[$levelName]["creator"]."</td>\n";
			else
				echo "\t\t\t<td align=\"left\">(Anonymous)</td>\n";
			echo "\t\t\t<td>&nbsp;</td>\n";
			echo "\t\t</tr>\n\t\t<tr>\n";
			
			// comment
			echo "\t\t\t<td align=\"right\"><b>Comment: </b></td>\n";
			if ($files[$levelName]["comment"])
				echo "\t\t\t<td align=\"left\">".$files[$levelName]["comment"]."</td>\n";
			else
				echo "\t\t\t<td align=\"left\">(none)</td>\n";
			echo "\t\t\t<td>&nbsp;</td>\n";
			echo "\t\t</tr>\n\t\t<tr>\n";
			
			// level size
			echo "\t\t\t<td align=\"right\"><b>Size: </b></td>\n";
			echo "\t\t\t<td align=\"left\">".$files[$levelName]["width"] . "x" . $files[$levelName]["height"]."</td>\n";
			echo "\t\t\t<td>&nbsp;</td>\n";
			echo "\t\t</tr>\n\t\t<tr>\n";

			// min/max players
			echo "\t\t\t<td align=\"right\"><b>Players: </b></td>\n";
			echo "\t\t\t<td align=\"left\">".$files[$levelName]["minplayers"] . "-" . $files[$levelName]["maxplayers"]."</td>\n";
			echo "\t\t\t<td>&nbsp;</td>\n";
			echo "\t\t</tr>\n\t\t<tr>\n";
			
			// date/time
			echo "\t\t\t<td align=\"right\"><b>Uploaded: </b></td>\n";
			if ($files[$levelName]["datetime"])
				echo "\t\t\t<td align=\"left\">".$files[$levelName]["datetime"]." UTC</td>\n";
			else
				echo "\t\t\t<td align=\"left\">(no timestamp)</td>\n";
			echo "\t\t\t<td>&nbsp;</td>\n";
			echo "\t\t</tr>\n\t\t<tr>\n";

			// downloads
			echo "\t\t\t<td align=\"right\"><b>Downloaded: </b></td>\n";
			if ($files[$levelName]["downloads"] > 1)
				echo "\t\t\t<td align=\"left\">".$files[$levelName]["downloads"]." times</td>\n";
			else if ($files[$levelName]["downloads"] == 1)
				echo "\t\t\t<td align=\"left\">once</td>\n";
			else
				echo "\t\t\t<td align=\"left\">(no downloads yet)</td>\n";
			echo "\t\t\t<td>&nbsp;</td>\n";
			echo "\t\t</tr>\n\t\t<tr>\n";

			// rating
			echo "\t\t\t<td align=\"right\"><b>Rating: </b></td>\n";
			if ($files[$levelName]["votes"] > 0)
			{
				echo "\t\t\t<td align=\"left\">";
				
				for ($i = 1; $i <= 5; $i++)
				{
					if ($files[$levelName]["mark"] > ($i - .001)) $j = 1;
					else if ($files[$levelName]["mark"] > ($i - .501)) $j = 3;
					else $j = 2;
					
					echo "\t\t\t\t<a href=\"levels.php?vote=" . $levelFile . "&amp;mark=$i\" onmouseover=\"voteOnMouseOver(" . ($level - $firstLevel) . ", $i)\" onmouseout=\"voteOnMouseOut(" . ($level - $firstLevel) . ", $i)\"><img id=\"vote" . ($level - $firstLevel) . "_$i\" src=\"images/bomb_vote$j.png\" width=\"16\" height=\"16\" alt=\"Rate with $i/5\" /></a>\n";
				}
					
				echo "\t\t\t\t" . $files[$levelName]["mark"]." (".$files[$levelName]["votes"]." votes)</td>\n";
			}
			else
			{
				echo "\t\t\t<td align=\"left\">\n";
				
				for ($i = 1; $i <= 5; $i++)
					echo "\t\t\t\t<a href=\"levels.php?vote=" . $levelFile . "&amp;mark=$i\" onmouseover=\"voteOnMouseOver(" . ($level - $firstLevel) . ", $i)\" onmouseout=\"voteOnMouseOut(" . ($level - $firstLevel) . ", $i)\"><img id=\"vote" . ($level - $firstLevel) . "_$i\" src=\"images/bomb_vote2.png\" width=\"16\" height=\"16\" alt=\"Rate with $i/5\" /></a>\n";
				
				echo "\t\t\t(no votes yet)</td>\n";
			}
			echo "\t\t\t<td>&nbsp;</td>\n";
		}
		else
		{
			// white space for this cell
			echo "\t\t\t<td align=\"right\" rowspan=\"$rowsPerLevel\">&nbsp;</td>\n";
			echo "\t\t\t<td align=\"left\" rowspan=\"$rowsPerLevel\">&nbsp;</td>\n";
			echo "\t\t\t<td rowspan=\"$rowsPerLevel\">&nbsp;</td>\n";
		}

		echo "\t</tr>\n";
	}
	
	previousnextrow(sizeof($files), 3);
?>
</table>

<h2><a id="upload">Upload your Level</a></h2>

<div class="upload">
	<script type="text/javascript">
		<!--
		var fresh = new Array(2);
		fresh[0] = true;
		fresh[1] = true;
		
		function clearIfFresh(element)
		{
			if (fresh[element])
			{
				if (element == 0)
				{
					document.forms[0].description.value = "";
				}
				else if (element == 1)
				{
					document.forms[0].comment.value = "";
				}
				
				fresh[element] = false;
			} 
		}
		// -->
	</script>
	<div class="description">
 	Here you may upload a level you have created.
 	</div>
	<form action="../cgi-bin/upload.cgi" method="post" enctype="multipart/form-data">
  	<table>
			<tr>
				<th colspan="2">Upload Level</th>
			</tr>
			<tr>
				<td>Your name*:</td><td><input type="text" name="name" value="" maxlength="64" /></td>
			</tr>
			<tr>
				<td>Your Level*:</td><td><input type="file" name="file" /></td>
			</tr>
			<tr>
				<td valign="top">Description:</td>
				<td><textarea name="description" rows="2" cols="40" onfocus="clearIfFresh(0)">Leave this field empty if you want to use the description in the level file.</textarea></td>
			</tr>
			<tr>
				<td valign="top">Comment:</td>
				<td><textarea name="comment" rows="2" cols="40" onfocus="clearIfFresh(1)">Leave this field empty if you want to use the comment in the level file.</textarea></td>
			</tr>
			<tr>
				<td valign="top">No Copyright*:</td>
				<td>Your level will be released into the public domain which means that you renounce any copyright.<br/>
					This applies worldwide. In case this is not legally possible: You grant anyone the right to use this work for any purpose, without any conditions, unless such conditions are required by law.<br/>
					<input type="checkbox" name="nocopyright" /> I renounce any copyright and I hereby release my level into public domain.</td>
			</tr>
			<tr>
				<td valign="top">Captcha*:</td>
				<td>For spam protection reasons, type in the two words displayed here (powered by <a href="http://recaptcha.net/">reCaptcha</a>):<br/>
<?php
	if (strstr($_SERVER['SERVER_NAME'], "uni-karlsruhe.de"))
		echo recaptcha_get_html($publickey);
	else
		echo "reCAPTCHA only works on *.uni-karlsruhe.de";
?>				
					</td>
			</tr>
			<tr>
				<td colspan="2"><input type="submit" name="submit" value="Upload Level" /></td>
			</tr>
  	</table>
	</form>
	* Required fields.
</div>
</div>

<?php

$webpage->tail();

?>
