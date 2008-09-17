#!/usr/bin/perl

open(FIND, "find usr -type f|") or die("find");
	@lines = <FIND>;
close(FIND);

open(MD5, ">DEBIAN/md5sums") or die ("md5");
for $line (@lines) {
	$line =~ s/\n//;
	open (MD5SUM, "md5sum $line|");
		@sums = <MD5SUM>;
	close(MD5SUM);
	print MD5 $sums[0];
}
close(MD5);
