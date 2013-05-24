\# vim: textwidth=60 ft=groff:
\# fonts
.fp 0 MT
.fp 1 MT
.fp 2 MT
.fp 3 MT
.bd MR 3
.de bold endbold
\\$3\f[MR]\\$1\fP\\$2
.endbold
.ds author Ken Smith
.ds email kgsmith@gmail.com
\# title
.DA
.TL
.bold "\*[title]"
.AU
\*[author]
.AI
\*[email]
\#
\# open document with index visible
.pdfview /PageMode /UseOutlines
\#
\# pdf index has 3 levels of sections
.nr PDFOUTLINE.FOLDLEVEL 4
\#
\# pdf metadata
.pdfinfo /Title     \*[title]
.pdfinfo /Author    \*[author]
.pdfinfo /Subject   \*[title]
.pdfinfo /Keywords  \*[title]
\#.nr PD 1.0v
.de normal endnormal
.ps 10
.endnormal
.de small endsmall
.ps 8
.de large endlarge
.ps 12
.endlarge
.endsmall
.de sectiontmpl endsectiontmpl
.SH \\$1
\f[MR]
.XN "\\$2"
\fP
.LP
.nf
.in 0.75i
.normal
.endsectiontmpl
.de section endsection
.sectiontmpl 1 "\\$1"
.endsection
.de subsection endsubsection
.sectiontmpl 2 "\\$1"
.endsubsection
.de subsubsection endsubsubsection
.sectiontmpl 3 "\\$1"
.endsubsubsection
.de subsubsubsection endsubsubsubsection
.sectiontmpl 4 "\\$1"
.endsubsubsubsection
.de note endnote

.small
.bold NOTE
\\$*
.endnote
.de endnote endendnote
.normal
.endendnote
.de todo endtodo
.small
.bold TODO
\\$*
.endtodo
.de endtodo endendtodo
.normal
.endendtodo
.de quip
.in 2.0i
..
.de endquip 
.in 0.75i
..
