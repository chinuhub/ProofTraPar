use strict;
use warnings;

my ($file) = @ARGV;
open my $info, $file or die "Could not open $file: $!";

my $prevline=<$info>;
while( my $line = <$info>)  {   
	my $prevlst= substr $prevline, -2;
	chomp($prevlst);
	my $thislst = substr $line, -2;
	chomp($thislst);
	#print "lat char is ", $lst,"\n";
	if($prevlst eq "\""){# && $thislst eq "\""){
		chomp($prevline);
	    print $prevline.",\n"; 
		$prevline=$line;
	}
	else{
	    print $prevline;
		$prevline=$line;
	}
}
print $prevline;
close $file;
