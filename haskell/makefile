
#######################
##   customize rule
#######################

#.SUFFIXES:.hs .o
#.hs.o:
#	ghc -c $< -o $@
#accu:accu.hs

srcFiles=accu.hs data.hs func.hs myZip.hs JsonParse.hs deriving.hs eqclass.hs Main.hs

empty=
source_suffix=.hs
obj_suffix=.o

# 下面替换命令的逗号后面不能有空格！
binfiles=$(subst $(source_suffix),$(empty),$(srcFiles))
objfiles=$(subst $(source_suffix),$(obj_suffix),$(srcFiles))

all:$(binfiles)
$(binfiles):%:%.hs
	ghc $< -o $@

clean:
	for file in $(binfiles) ; do \
		rm -rf $$file $$file.hi $$file.o ;\
	done

