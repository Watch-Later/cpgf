BEGIN {
	my $p = $0;
	$p =~ s![^/\\]+$!!;
	unshift @INC, $p;
}

use strict;
use warnings;

use gendocparser;

use HTML::EasyTags;
use HTML::TokeParser;
use HTML::Entities;
use File::Basename;

my @tags = (
	{
		tag => "autotoc",
		needClose => 1,
		handler => \&handlerAutoToc,
	},

	{
		tag => "autobr",
		needClose => 1,
		handler => \&handlerAutoBR,
	},

	{
		tag => "sgroup", # param: indent
		needClose => 1,
		handler => \&handlerSectionGroup,
	},

	{
		tag => "sh", #param: id
		needClose => 0,
		handler => \&handlerSectionHead,
	},

	{
		tag => "sc",
		needClose => 0,
		handler => \&handlerSectionContent,
	},

	{
		tag => "code",
		needClose => 1,
		handler => \&handlerCode,
	},
);

my @inputFiles = ();
my $outputPath = undef;
my $outHTML = 1;

my $overwriteAllFiles = 1;

my $yes = 1;
my $no = 2;
my $all = 3;


my @HTMLTags = qw(
	a abbr acronym address applet area
	b base basefont bdo big blockquote body br button
	caption center cite code col colgroup
	dd del dfn dir div dl dt
	em
	fieldset font form frame frameset
	h1 h2 h3 h4 h5 h6 head hr html
	i iframe img input ins isindex
	kbd
	label legend li link
	map menu meta
	noframes noscript
	object ol optgroup option
	p param pre
	q
	s
	samp script select small span strike strong style sub sup
	table tbody td textarea tfoot th thead title tr tt
	u ul
	var
);

my $HTMLTagMap = undef;

&doMain;

sub doMain
{
	&parseCommandLine;
	&doFilePattern(\@inputFiles);
}

sub parseCommandLine
{
	foreach(@ARGV) {
		my $arg = $_;

		if($arg =~ /^\-o\=(.*)/) {
			my $path = $1;
			die "Duplicated output path.\n" if(defined $outputPath);
			$outputPath = $path;

			next;
		}

		push @inputFiles, $arg;
	}

	$outputPath = './' unless(defined $outputPath);
	if($outputPath !~ /[\\|\/]$/) {
		$outputPath .= '/';
	}

	die "No input files.\n" if($#inputFiles < 0);
}

sub askYesNoAll
{
	my ($msg) = @_;
	
	while(1) {
		print $msg, " (Yes/No/All)";
		my $input = <STDIN>;
		return $yes if($input =~ /y|yes/i);
		return $no if($input =~ /n|no/i);
		return $no if($input =~ /a|all/i);
	}
}

sub doFilePattern
{
	my ($patternList) = @_;

	foreach(@$patternList) {
		my $pattern = $_;
		my @files = glob($pattern);
		if($#files < 0) {
			print "Warning: can't find file for $pattern.\n";
		}
		else {
			foreach(@files) {
				my $fileName = $_;
				&doFile($fileName);
			}
		}
	}
}

sub doFile
{
	my ($fileName) = @_;

	my $name = basename($fileName);
	my $outName = $outputPath . $name . '.html';

	if(! open FH, '<' . $fileName) {
		print "Warning: can't open file $fileName to read.\n";

		return;
	}

	my @lines = <FH>;

	close FH;

	my $parser = new TagParser();
	
	my $atomList = $parser->parse(\@lines);
#$parser->dump($atomList);

	my $context = new DocContext;

	my $processor = new TagProcessor(\@tags, $context, \&textHandler);
	$processor->verify($atomList);
	$processor->process($atomList);
	
	$context->finish;
	
	$context->{tocContent} = &formatHTML($context->{tocContent});
	$context->{content} = &formatHTML($context->{content});
	
	if((not $overwriteAllFiles) && (-e $outName)) {
		my $answer = &askYesNoAll("Overwrite file " . $outName . "?");
		return if($answer == $no);
		if($answer == $all) {
			$overwriteAllFiles = 1;
		}
	}

	if(! open FH, '>' . $outName) {
		print "Warning: can't open file $outName to write.\n";

		return;
	}

	if($outHTML) {
		print FH <<EOM;
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
<title></title>
</head>
<body><div style="width:900px">
EOM
		print FH "\n\n\n";
	}

	print FH $context->{beforeTocContent}, "\n\n";
	print FH $context->{topAnchor}, "\n\n";
	print FH $context->{tocContent}, "\n\n";
	print FH $context->{content}, "\n";

	if($outHTML) {
		print FH "\n\n\n</div></body></html>";
	}

	close FH;

}

sub textHandler
{
	my ($tagProcessor, $context, $text) = @_;

	$context->newText($text);
}

sub handlerAutoToc
{
	my ($tagProcessor, $context, $tagName, $closeTag) = @_;
	
	$context->changeAutoTOCLevel($closeTag);
}

sub handlerAutoBR
{
	my ($tagProcessor, $context, $tagName, $closeTag) = @_;

	$context->changeAutoBRLevel($closeTag);
}

sub handlerSectionGroup
{
	my ($tagProcessor, $context, $tagName, $closeTag) = @_;
	
	if($closeTag) {
		$context->closeSectionGroup();
	}
	else {
		$context->newSectionGroup($tagProcessor);
	}
}

sub handlerSectionHead
{
	my ($tagProcessor, $context, $tagName, $closeTag) = @_;
	
	return if($closeTag);
	
	$context->newSectionHead($tagProcessor);
}

sub handlerSectionContent
{
	my ($tagProcessor, $context, $tagName, $closeTag) = @_;
	
	return if($closeTag);
}

sub handlerCode
{
	my ($tagProcessor, $context, $tagName, $closeTag) = @_;

	if($closeTag) {
		$context->appendContent('</pre>');
	}
	else {
		$context->appendContent('<pre>');
	}

	$context->changeCodeLevel($closeTag);
}

sub noLineBreak
{
	my ($s) = @_;
	
	$s =~ s/^\n+//ms;
	$s =~ s/\n+$//ms;
	
	return $s;
}

sub formatHTML
{
	my ($html) = @_;
	
	if(not defined $HTMLTagMap) {
		$HTMLTagMap = {};
		foreach(@HTMLTags) {
			$HTMLTagMap->{$_} = 1;
		}
	}

	my $parser = HTML::TokeParser->new(\$html);
	my $result = '';
	
	while(1) {
		my $token = $parser->get_token;
		
		last unless defined $token;
		
		my $type = lc $token->[0];
		my $text;
		my $tag = undef;
		
		if($type eq 't') {
			$text = $token->[1];
		}
		else {
			$text = $token->[$#{$token}];
		}
		
		if($type =~ /[set]/) {
			my $encode = 1;
			
			if($type =~ /[se]/) {
				my $tag = lc $token->[1];
				if($HTMLTagMap->{$tag}) {
					$encode = 0;
				}
			}
			
			if($encode) {
				$text = encode_entities(decode_entities($text));
			}
		}
		
		$result .= $text . "";
	}
	
	return $result;
}

package DocContext;

sub new
{
	my $class = shift || {};

	my $self = {
		beforeTocContent => undef,

		tocLevel => 0,
		tocContent => '',
		
		brLevel => 0,
		
		content => '',
		
		tagHelper => new TagHelper,
		
		html => HTML::EasyTags->new(),
		
		nextID => 1,
		
		sectionGroup => 0,
		
		needSectionGroupHeader => 0,
		sectionGroupIndent => 0,

		codeLevel => 0,

		topAnchor => '<a id="top"></a>',
	};

	bless $self, $class;

	return $self;
}

sub changeAutoTOCLevel
{
	my ($self, $close) = @_;
	
	if($close) {
		--$self->{tocLevel};
	}
	else {
		++$self->{tocLevel};
	}
	
	$self->{tocLevel} = 0 if($self->{tocLevel} < 0);
	
	if($self->{tocLevel}) {
		if(not defined $self->{beforeTocContent}) {
			$self->{beforeTocContent} = $self->{content};
			$self->{content} = '';
		}
	}
	else {
		$self->{tocLevel} = 1;
		$self->closeSectionGroup();
		$self->{tocLevel} = 0;
	}
}

sub changeAutoBRLevel
{
	my ($self, $close) = @_;
	
	if($close) {
		--$self->{brLevel};
	}
	else {
		++$self->{brLevel};
	}

	$self->{brLevel} = 0 if($self->{brLevel} < 0);
}

sub changeCodeLevel
{
	my ($self, $close) = @_;
	
	if($close) {
		--$self->{codeLevel};
	}
	else {
		++$self->{codeLevel};
	}

	$self->{codeLevel} = 0 if($self->{codeLevel} < 0);
}

sub getNextID
{
	my ($self) = @_;
	
	return $self->{nextID}++;
}

sub formatContent
{
	my ($self, $text) = @_;

	if($self->{brLevel}) {
		$text =~ s/\n/<br \/>\n/msg;
	}
	
	if($self->{codeLevel}) {
		while($text =~ s/\A\t/    /msg) {}
	}
	
	return $text;
}

sub appendTOC
{
	my ($self, $text) = @_;
	
	return unless($self->{tocLevel} > 0);
	
	$self->{tocContent} .= $text;
}

sub appendContent
{
	my ($self, $text) = @_;

	$self->{content} .= $text;
}

sub makeAnchor
{
	my ($self) = @_;
	
	return "linkid" . $self->getNextID;
}

sub newSectionGroup
{
	my ($self, $tagProcessor) = @_;
	
	my $text = $self->{tagHelper}->getAllText($tagProcessor);
	
	$self->closeSectionGroup();
	
	if(defined $text) {
		my $id = $self->{tagHelper}->paramAsString($tagProcessor->getCurrentAtom->{paramMap}, "id");
		
		if(not defined $id) {
			$id = $self->makeAnchor;
		}

		$self->appendTOC(
			$self->{html}->p(
				$self->{html}->b(
					$self->{html}->a(
						href => '#' . $id, text => $self->{html}->strong($text)
					)
				)
			)
		);
	
		$self->_addNewAnchor($id);
		
		$self->appendContent(
			$self->{html}->h3(
				$text
			)
		);
		
	}
	$self->{sectionGroupIndent} = $self->{tagHelper}->paramAsInt($tagProcessor->getCurrentAtom->{paramMap}, "indent", 0);
	$self->{needSectionGroupHeader} = 1;
	
	++$self->{sectionGroup};
}

sub checkNeedSectionGroupHeader
{
	my ($self) = @_;
	
	if($self->{needSectionGroupHeader}) {
		$self->{needSectionGroupHeader} = 0;
	
		my $indent = $self->{sectionGroupIndent} * 60;

		$self->appendTOC(
			$self->{html}->div_start(
				style=>"margin-left:" . $indent . "px"
			) .
			$self->{html}->ul_start(
			),
		);
	}
}

sub newSectionHead
{
	my ($self, $tagProcessor) = @_;
	
	my $text = $self->{tagHelper}->getAllText($tagProcessor);
	
	$self->_checkDefaultSectionGroup($tagProcessor);

	if(defined $text) {
		$self->checkNeedSectionGroupHeader;
		
		my $id = $self->{tagHelper}->paramAsString($tagProcessor->getCurrentAtom->{paramMap}, "id");
		
		if(not defined $id) {
			$id = $self->makeAnchor;
		}

		$self->appendTOC(
			$self->{html}->li(
				$self->{html}->a(
					href => '#' . $id, text => $self->{html}->strong($text)
				)
			)
		);
	
		$self->_addNewAnchor($id);
		
		$self->appendContent(
			$self->{html}->p(
				$self->{html}->strong($text) .
				'<span style="margin-left:100px;font-size:small"><a href="#top">back top</a></span>'
			)
		);
	}
}

sub newText
{
	my ($self, $text) = @_;

	if(defined $text) {
		$self->appendContent(
			$self->formatContent($text)
		);
	}
}

sub finish
{
	my ($self) = @_;
	
	$self->closeSectionGroup();

	if(not defined $self->{beforeTocContent}) {
		$self->{beforeTocContent} = '';
	}
}

sub _addNewAnchor
{
	my ($self, $id) = @_;

	$self->appendContent('<p><a id="' . $id . '"></a></p>'
	);
}

sub _checkDefaultSectionGroup
{
	my ($self, $tagProcessor) = @_;
	
	if(not $self->{sectionGroup}) {
		$self->newSectionGroup($tagProcessor);
	}
}

sub closeSectionGroup
{
	my ($self) = @_;
	
	return if($self->{sectionGroup} <= 0);
	
	if($self->{sectionGroup}) {
		if(not $self->{needSectionGroupHeader}) {
			$self->appendTOC(
				$self->{html}->ul_end() .
				$self->{html}->div_end()
			);
		}
	}
	
	--$self->{sectionGroup};
}

