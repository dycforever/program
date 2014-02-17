
srcFiles=accu.hs data.hs func.hs myZip.hs JsonParse.hs

empty=
suffix=.hs
binfiles=$(subst $(suffix),$(empty),$(srcFiles))

all:$(srcFiles)
	for file in $(binfiles) ; do \
		ghc $$file ;\
	done


clean:
	for file in $(binfiles) ; do \
		rm -rf $$file $$file.hi $$file.o ;\
	done
