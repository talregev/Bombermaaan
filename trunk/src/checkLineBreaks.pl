#!/usr/bin/perl

# This small scripts checks if all source files have the Windows Linebreaks
# Only tested in Linux
my @directories = ("Bombermaaan", "RESGEN", "LEVELPREVIEW");
my $rep;

foreach $directory (@directories)
{
	opendir (DIR, $directory) or next;
		@files = readdir(DIR);
	closedir (DIR);

	foreach $file (@files)
	{
		if (lc($file) =~ /\.cpp$/ || lc($file) =~ /\.h$/)
		{
			# read file
			open (FILE, "$directory/$file") or die "Could not open $directory/$file for reading\n";
				@lines = <FILE>;
			close(FILE);

			# count how many changes have to be made
			$rep = 0;
			foreach $line (@lines)
			{
				if ($line !~ /\r\n$/ && $line =~ /\n$/)
				{
					$rep++;
				}
				print OUT $line;
			}

			# write file
			if ($rep > 0)
			{
				open (OUT, ">$directory/$file") or die "Could not open $directory/$file for writing\n";
					foreach $line (@lines)
					{
						if ($line !~ /\r\n$/ && $line =~ /\n$/)
						{
							$line =~ s/\n$/\r\n/;
						}
						print OUT $line;
					}
				close (OUT);

				print "Edited $file. There were $rep replacements.\n";
			}
		}
	}
}
