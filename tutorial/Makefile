#
# Makefile to generate the HTML pages of the tutorial.
#

all : Introduction.html Basics.html

%.html: %.gmd
	gmic it $< gmd2html strvar d strvar "{b}" out=\$$\{\} ot \$$out.html
