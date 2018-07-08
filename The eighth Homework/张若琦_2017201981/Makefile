bin_dir=.
include_dir=include
src_dir=src
command=g++ -std=c++11 -O3 -I $(include_dir)

all: $(bin_dir)/init $(bin_dir)/Query

$(bin_dir)/init: $(src_dir)/init.cc $(src_dir)/buildlist.cc $(include_dir)/buildlist.h
	$(command) -o $(bin_dir)/init $(src_dir)/init.cc $(src_dir)/buildlist.cc

# --------------------

objects = query.o LoadDict.o Search.o

$(bin_dir)/Query: $(bin_dir)/$(objects)
	g++ -std=c++11 -O3 -o Query $(objects)

$(bin_dir)/query.o : $(src_dir)/query.cc $(include_dir)/LoadDict.h $(include_dir)/Search.h
	$(command) -c $(src_dir)/query.cc

$(bin_dir)/LoadDict.o : $(src_dir)/LoadDict.cc $(include_dir)/LoadDict.h
	$(command) -c $(src_dir)/LoadDict.cc

# $(bin_dir)/QueryParse.o : $(src_dir)/QueryParse.cc $(include_dir)/QueryParse.h
#	$(command) -c $(src_dir)/QueryParse.cc

$(bin_dir)/Search.o : $(src_dir)/Search.cc $(include_dir)/Search.h
	$(command) -c $(src_dir)/Search.cc

.PHONY : clean
clean :
	-rm init Query $(objects)
