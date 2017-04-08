use strict;
use warnings;

my ($file) = @ARGV;
open my $info, $file or die "Could not open $file: $!";

while( my $line = <$info>)  {   
	my $lst= substr $line, -2;
	chomp($lst);
	#print "lat char is ", $lst,"\n";
	if($lst eq "\""){
		chomp($line);
	    print $line.",\n"; 
	}
	else{
	    print $line;
	}
}
close $file;
