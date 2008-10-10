#!/usr/bin/perl

use strict;
use Captcha::reCAPTCHA;
use CGI;
use DBI qw(:sql_types);
use CGI::Carp qw(fatalsToBrowser);
use Digest::MD5;

my $cgi = new CGI;

print $cgi->header(-type => 'text/html');

# mySQL configuration
my $db_host;

my $uploadInterval = 3; # allow one upload in 3 minutes

my $path;
my $levelPreview;
my $levelPreviewPath;
my $passwordFile;

if (index($ENV{'HTTP_HOST'}, "uni-karlsruhe.de") > -1)
{
	$db_host = "mysql.stud.uni-karlsruhe.de";

	$path = "/home/ws/uabdq/.public_html/bombermaaan/levels";
	$levelPreviewPath = "/home/ws/uabdq/level";
	$passwordFile = "$levelPreviewPath/passwords.txt";
}
else
{
	$db_host = "localhost";

	$path = "/home/otto/homepages/bombermaaan/levels";
	$levelPreviewPath = "/home/otto/Projects/Bombermaaan/LEVELPREVIEW";
	$passwordFile = "$path/../inc/passwords.txt";
}
$levelPreview = "$levelPreviewPath/LevelPreview";

my @passes;
open (PASS, $passwordFile) or die "Could not read password file.";
	@passes = <PASS>;
close (PASS);

my $db_user = $passes[0];
my $db_pass = $passes[1];
my $db_data = $passes[2];
my $private_key = $passes[3];

$db_user =~ s/\n$//;
$db_pass =~ s/\n$//;
$db_data =~ s/\n$//;
$private_key =~ s/\n$//;

# cgi parameters
my $file = $cgi->param("file");
my $username = $cgi->param("name");
my $comment = $cgi->param("comment");
my $description = $cgi->param("description");
my $copyright = $cgi->param("nocopyright");

my $challenge = $cgi->param("recaptcha_challenge_field");
my $response = $cgi->param("recaptcha_response_field");

my $ip = $ENV{'REMOTE_ADDR'};

my $filename; # level file
my $imagename; # image file

my $connect_error = 0;

my $result;
my $c = Captcha::reCAPTCHA->new;

my $is_valid = 1;
my $maxFileSize = 2048;

my $levelnumber;

my $datetime;

# what time is it? (UTC)
my $ignore;
my ($sec, $min, $hours, $day, $month, $year);
($sec, $min, $hours, $day, $month, $year, $ignore, $ignore, $ignore) = gmtime(time);

$year += 1900;
$month++;

$datetime = "$year-" . sprintf("%02d", $month) . "-" . sprintf("%02d", $day) . " " . sprintf("%02d", $hours) . ":" . sprintf("%02d", $min) . ":" . sprintf("%02d", $sec);

# $_[0]: $db handle
sub validateDatabaseIntegrity($)
{
  my $db = $_[0];
		
  my $sql = "SHOW DATABASES";
  my $input1 = $db->prepare($sql);
  $input1->execute or return -1;
  my $data_base;
  my $found = 0;
  my $create_table = 0;
  
  $input1->bind_col(1, \$data_base, undef);
  
  while ($input1->fetch()) {
  	if ($data_base eq $db_data)
  	{
  		$found = 1;
  		last;
  	}
  }
  
  $input1->finish();
  
  #if (!$found)
  #{
  #	$sql = "CREATE DATABASE `$db_data`";
  #	$input1 = $db->prepare($sql);
  #	$input1->execute or return -2;
  #	$input1->finish();
  #	$create_table = 1; # create table as well
  #}
  	
	#$sql = "USE DATABASE `$db_data`";
	#$input1 = $db->prepare($sql);
	#$input1->execute or return -3;
	#$input1->finish();
	
	if (!$create_table)
	{
	  $sql = "SHOW TABLES";
	  $input1 = $db->prepare($sql);
	  $input1->execute or return -4;
	  my $table;
	  $create_table = 1;
	  
	  $input1->bind_col(1, \$table, undef);
	  
	  while ($input1->fetch()) {
	  	if ($table eq "levels")
	  	{
	  		$create_table = 0;
	  		last;
	  	}
	  }
	  
  	$input1->finish();
  	
	  if (!$create_table)
	  {
	  	# table found, check if columns are valid
		  $sql = "SHOW COLUMNS FROM `levels`";
		  $input1 = $db->prepare($sql);
		  $input1->execute or return -5;
		  my $col_name;
		  my $col_type;
		  
		  my $min_columns = 11;
		  my $max_columns = 11;
		  my @col_names = ("id", "levelnumber", "creator", "comment", "description", "datetime", "ip", "md5sum", "mark", "votes", "downloads");
		  my @col_types = ("bigint(20)", "bigint(20)", "varchar(64)", "varchar(128)", "varchar(128)", "datetime", "varchar(15)", "varchar(32)", "float", "int(11)", "bigint(20)");
		  my $column = 0;
		  $create_table = 0;
		  
		  $input1->bind_col(1, \$col_name, undef);
		  $input1->bind_col(2, \$col_type, undef);
		  
		  while ($input1->fetch()) {
		  	if ($column >= $max_columns)
		  	{
		  		$create_table = 1;
		  		last;
		  	}
		  	elsif ($col_name ne $col_names[$column] || $col_type ne $col_types[$column])
		  	{
		  		$create_table = 1;
		  		last;
		  	}
		  	$column++;
		  }
		  
		  if ($column < $min_columns)
		  {
		  	$create_table = 1;
		  }
		  
		  $input1->finish();
		  
		  if ($create_table)
		  {
		  	# wrong table format, delete table
		  	$sql = "DROP TABLE `levels`";
			  $input1 = $db->prepare($sql);
			  $input1->execute or return -6;
			  $input1->finish();
		  }
	  }
	}
  
  if ($create_table)
  {
  	$sql = " CREATE TABLE `levels` (" .
			"`id` BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY ," .
			"`levelnumber` BIGINT NOT NULL ," .
			"`creator` VARCHAR( 64 ) NOT NULL ," .
			"`comment` VARCHAR( 128 ) NOT NULL ," .
			"`description` VARCHAR( 128 ) NOT NULL ," .
			"`datetime` DATETIME NOT NULL ," .
			"`ip` VARCHAR( 15 ) NOT NULL ," .
			"`md5sum` VARCHAR( 32 ) NOT NULL ," .
			"`mark` FLOAT NOT NULL ," .
			"`votes` INT NOT NULL ," .
			"`downloads` BIGINT NOT NULL ," .
			"INDEX ( `levelnumber` )" .
			") TYPE = MYISAM";   
		$input1 = $db->prepare($sql);
		$input1->execute or return -7;
		$input1->finish();
  }
  
	return 1; # valid database
}

sub errorOccured($)
{
	my $error = $_[0];
	
	print "$error</div></body></html>\n";
	die();
}

sub numberinwords($)
{
	my $n = $_[0];
	
	if ($n == 1)
	{
		return "first";
	}
	elsif ($n == 2)
	{
		return "second";
	}
	elsif ($n == 3)
	{
		return "third";
	}
	elsif ($n > 3 && $n < 20)
	{
		return $n."th";
	}
	elsif ($n % 10 == 1)
	{
		return $n."st";
	}
	elsif ($n % 10 == 2)
	{
		return $n."nd";
	}
	elsif ($n % 10 == 3)
	{
		return $n."rd";
	}
	else
	{
		return $n."th";
	}
}

print '<?xml version="1.0" encoding="UTF-8"?>'."\n";
print '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">'."\n";
print '<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">'."\n";
print "<head>\n";
print '<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />'."\n";
print '<meta name="Title" content="Bombermaaan game project" />'."\n";
print '<meta name="author" content="Markus Drescher"/>'."\n";
print '<meta name="Revisit" content="After 15 days" />'."\n";
print '<meta name="Keywords" content="bomberman bomber man bombermaaan maaan fury game windows download arena bomb explosion item wall victory player players play" />'."\n";
print '<meta name="Description" content="Bombermaaan game project. A DirectX Bomberman game for Windows 95 and later. Original and classic game play. Up to 5 players on the same computer..." />'."\n";
print '<meta name="Abstract" content="Bombermaaan game project. A DirectX Bomberman game for Windows 95 and later. Original and classic game play. Up to 5 players on the same computer..." />'."\n";
print '<meta name="Robots" content="INDEX,FOLLOW" />'."\n";
print '<meta name="Language" content="English" />'."\n";
print '<link rel="stylesheet" href="../bombermaaan/css.css" type="text/css" />'."\n";
print '<title>Bombermaaan game project</title>'."\n";
print "</head>\n";
print "<body>\n";

# menu

my $sfpath = "http://bombermaaan.sourceforge.net";
print '<div id="side">'."\n\n";
print '<div id="logoimage">'."\n";
print '<a href="'.$sfpath.'/"><img src="../bombermaaan/images/title.png" alt="The Bombermaaan logo" /></a>'."\n";
print "</div>\n\n";
print '<div id="menu">'."\n\n";
print "<div>\n";
print '<a href="'.$sfpath.'/">Home</a>'."\n";
print "</div>\n\n";
print "<div>\n";
print '<a href="'.$sfpath.'/download.php">Download</a>'."\n";
print "</div>\n\n";
print "<div>\n";
print '<a href="'.$sfpath.'/license.php">License</a>'."\n";
print "</div>\n\n";
print "<div>\n";
print '<a href="'.$sfpath.'/screenshots.php">Screenshots</a>'."\n";
print "</div>\n\n";
print "<hr />\n";
print "<div>\n\n";
print '<a href="'.$sfpath.'/features.php">Features</a>'."\n";
print "</div>\n\n";
print "<div>\n";
print '<a href="'.$sfpath.'/todo.php">To-Do</a>'."\n";
print "</div>\n\n";
print "<div>\n";
print '<a href="'.$sfpath.'/faq.php">FAQ</a>'."\n";
print "</div>\n\n";
print "<div>\n";
print '<a href="'.$sfpath.'/changelog.php">Changelog</a>'."\n";
print "</div>\n\n";
print "<div>\n";
print '<a href="'.$sfpath.'/history.php">History</a>'."\n";
print "</div>\n\n";
print "<hr />\n";
print "<div>\n\n";
print '<a href="../bombermaaan/levels.php">Levels</a>'."\n";
print "</div>\n\n";
print "<hr />\n";
print "<div>\n";
print '<a href="'.$sfpath.'/development.php">Development</a>'."\n";
print "</div>\n\n";
print "<div>\n";
print '<a href="'.$sfpath.'/contact.php">Contact</a>'."\n";
print "</div>\n\n";
print "</div>\n\n";
print '<div style="margin-top: 2em; text-align: center;">'."\n";
print '<img src="../bombermaaan/images/bomber_a.png" alt="A bomber" />'."\n";
print "</div>\n\n";
print "</div>\n\n";

# content
print "<h1>Bombermaaan Level Upload</h1>\n\n";
print '<div id="content">'."\n";

my $sql;
my $input1;

if ($file)
{
	# check captcha
	if (index($ENV{'HTTP_HOST'}, "uni-karlsruhe.de") > -1)
	{
		my $result = $c->check_answer(
			$private_key, $ip,
		  $challenge, $response
		);
		
		if ($result->{is_valid})
		{
			$is_valid = 1;
		}
		else
		{
			$is_valid = 0;
		}
	}
	
	# check ip
	my $ip_valid = 1;
	$result = 1;
	my $db_valid = 1;
	my $digest_found = 0;
	
  my $db = DBI->connect("DBI:mysql:$db_data:$db_host",
		$db_user, $db_pass, {'timeout' => 15}) or $db_valid = 0;

	if ($db_valid)
	{
  	$result = validateDatabaseIntegrity($db);
				  	
	  if ($result < 1)
	  {
	    print "<b>Warning</b>: Could not connect to the database ($result). No meta information will be available<br/>\n";
	    $db_valid = 0;
	  }
	}
		
	if ($db_valid)
	{
		$sql = "SELECT * FROM `levels` WHERE DATE_SUB( UTC_TIMESTAMP() ,INTERVAL $uploadInterval MINUTE ) <= `datetime` AND `ip` = '$ip'";
		$input1 = $db->prepare($sql);
		$input1->execute;
	  if ($input1->rows() > 0)
	  {
	  	$ip_valid = 0;
	  }
	  
	  $input1->finish();
	}

	if ($is_valid && $copyright && $ip_valid)
	{
		# find valid level file
		for ($levelnumber = 1; $levelnumber < 100000000; $levelnumber++)
		{
			$filename  = sprintf("%08d", $levelnumber) . ".TXT";
			$imagename = sprintf("%08d", $levelnumber) . ".png";
			
			if (! -e "$path/$filename" && ! -e "$path/$imagename")
			{
				last;
			}
		}
		
		# open level file and write data
		open (DAT, '>'."$path/$filename") or errorOccured('Could not save file');
		
		# switch files to binary mode
		binmode $file;
		binmode DAT;
		
		my $data;
		my $filesize = 0;
		my $bytes;

		my $ctx = Digest::MD5->new;
		my $digest;
		
		while($bytes = read $file,$data,1024) {
			$filesize += $bytes;
		  print DAT $data;
			$ctx->add($data);
		  if ($filesize > $maxFileSize)
		  {
		  	last;
		  }
		}
		close DAT;
		
		$digest = $ctx->hexdigest;
		my $page_with_digest_found = 0;
		my $number_on_page = 0;
		my $number_on_page_in_words = "";
		my $levelsPerPage = 12; # check levels.php

		if ($db_valid)
		{
			$sql = "SELECT levelnumber FROM `levels` WHERE `md5sum` = '$digest'";
			$input1 = $db->prepare($sql);
			$input1->execute;
		  if ($input1->rows() > 0)
		  {
			  $input1->bind_col(1, \$page_with_digest_found, undef);
			  
			  if ($input1->fetch())
			  {
		  		$digest_found = 1;
		  		$number_on_page = $page_with_digest_found % $levelsPerPage;
		  		if ( $number_on_page == 0 )
		  		{
		  			$number_on_page = $levelsPerPage;
		  		}
		  		$page_with_digest_found = int($page_with_digest_found / $levelsPerPage);
		  		$page_with_digest_found++;
		  		
		 			$number_on_page_in_words = numberinwords($number_on_page);
		  	}
		  }
		  
		  $input1->finish();
	  }

		# file saved, convert to png
		if ($filesize <= $maxFileSize && !$digest_found)
		{
			if (-e "$path/$filename")
			{
				$ENV{'LD_LIBRARY_PATH'} = $levelPreviewPath; 
				my @args = ($levelPreview, "$filename", "$imagename"); 
			  if (chdir($path))
			  {
			  	$result = system(@args);
			  }
			  else
			  {
			  	$result = 0;
			  }
			  
			  if (($? >> 8) == 1)
			  {
			  	if ($db_valid)
			  	{
				  	my $table = "levels";
			      $sql = "INSERT INTO $table VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
			      $input1 = $db->prepare($sql);
			      
			      $input1->bind_param(2, "$levelnumber", undef);
			      $input1->bind_param(3, "$username", undef);
			      $input1->bind_param(4, "$comment", undef);
			      $input1->bind_param(5, "$description", undef);
			      $input1->bind_param(6, "$datetime", undef);
			      $input1->bind_param(7, "$ip", undef);
			      $input1->bind_param(8, "$digest", undef);
			      $input1->bind_param(9, "0", undef); # mark (v_1 + v_2 + ... + v_n) / n
			      $input1->bind_param(10, "0", undef); # votes (n)
			      $input1->bind_param(11, "0", undef); # downloads			
			      $input1->execute or print "<b>Warning</b>: Could insert data into the database. No meta information will be available<br/>\n";
			      
			      $input1->finish();
			      $db->disconnect();
		     	}
			  
			  	print "The image has been successfully created.<br/>\n";
			  }
			  else
			  {
					print "Could not recognize the file as a Bombermaaan level.<br/>\n";
					unlink("$path/$filename");
				}
			}
			else {
				print "There was an error saving the file. Sorry.<br/>\n";
			}
		}
		else
		{
			unlink("$path/$filename");
			
			if ($digest_found && $page_with_digest_found > 0)
			{
				print "The file you have uploaded exists already. It is the same file <a href=\"../bombermaaan/levels.php?page=$page_with_digest_found\">on this page</a> (it is the $number_on_page_in_words level).<br/>\n";
			}
			else
			{
				print "The file you have uploaded is too big (max size: $maxFileSize Bytes) and thus rejected.<br/>\n";
			}
		}
	}
	else
	{
		if (!$copyright)
		{
			print "If you want to upload your level you have to accept that it will be released into the public domain.<br/>\n";
		}
		elsif (!$ip_valid)
		{
			print "You have already uploaded a level in the past $uploadInterval minutes. Please wait a while, then you may upload another level.<br/>\n";
		}
		else
		{
			print "Please enter the two words in the field. Or use the audio challenge.<br/>\n";
		}
	}
}

print '<a href="../bombermaaan/levels.php">Go back to the levels page</a>'."\n";
print "</div>\n";
print '<div id="tail">'."\n";
print "<p>\n";
print '<a href="http://bombermaaan.sourceforge.net/">http://bombermaaan.sourceforge.net/</a>'."\n";
print "</p>\n";
print "<p>\n";
print '<a href="http://sourceforge.net"><img style="border: 0px;" src="http://sflogo.sourceforge.net/sflogo.php?group_id=81520&amp;type=4" width="125" height="37" alt="SourceForge.net Logo" /></a>'."\n";
print '<a href="http://validator.w3.org/check?uri=referer"><img style="border: 0px;" src="http://www.w3.org/Icons/valid-xhtml11-blue" alt="Valid XHTML 1.1" height="31" width="88" /></a>'."\n";
print '<a href="http://jigsaw.w3.org/css-validator/check/referer">'."\n";
print '  <img style="border:0;width:88px;height:31px"'."\n";
print '       src="http://jigsaw.w3.org/css-validator/images/vcss"'."\n"; 
print '       alt="Valid CSS!" />'."\n";
print " </a>\n";
print "</p>\n";
print "</div>\n\n";
print "</body>\n\n";
print "</html>\n";
