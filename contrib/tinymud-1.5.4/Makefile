#################################################################
#
# Makefile for TinyMUD source code...June 6, 1990
#
#################################################################
#
# Whatever you put in for $(CC) must be able to grok ANSI C.
#

# GCC:
CC=gcc
OPTIM= -g -O2 -pipe -Wall -W -Wno-parentheses -Wno-unused

# The suffix appended to executables.  
# This should be set for Cygwin and Windows.
EXE = .exe
#EXE =

# 
# To log failed commands (HUH's) to stderr, include -DLOG_FAILED_COMMANDS
# To restrict object-creating commands to users with the BUILDER bit,
#   include -DRESTRICTED_BUILDING
# To log all commands, include -DLOG_COMMANDS
# To force fork_and_dump() to use vfork() instead of fork(), include 
#   -DUSE_VFORK.
# To force grow_database() to be clever about its memory management,
#   include -DDB_DOUBLING.  Use this only if your realloc does not allocate
#   in powers of 2 (if you already have a clever realloc, this option will
#   only cost you extra space).
# By default, db.c initially allocates enough space for 10000 objects, then
#   grows the space if needed.  To change this value, include
#   -DDB_INITIAL_SIZE=xxxx where xxxx is the new value (minimum 1).
# To include code for keeping track of the number of blocks allocated,
#   include -DTEST_MALLOC.
# To include code which attempts to compress string data, include -DCOMPRESS.
# To eliminate the message third parties see when a player whispers, include
#   -DQUIET_WHISPER.
# To include Stephen White's gender flags and pronoun substitution code, 
#   include -DGENDER.
# To give set (!)WIZARD and extended WHO privs only to id #1,
#   include -DGOD_PRIV.  When this option is set, two other options
#   become meanigful
#	-DGOD_MODE		Restricts host names some commands to #1
#	-DGOD_ONLY_PCREATE	Restricts @pcreate to player #1
# To have logs and WHO use hostnames instead of addresses, include
#   -DHOST_NAME.
# To have messages for connect and disconnect, include -DCONNECT_MESSAGES.
# To use a hashed player list for player name lookups, 
#   include -DPLAYER_LIST.
# To disable login-time creation of players, include -DREGISTRATION.
#    see GOD_ONLY_PCREATE above.
# To cause netmud to detach itself from the terminal on startup, include
#   -DDETACH.  The log file appears on LOG_FILE, set in config.h.
# To add the @count & @recycle command, include -DRECYCLE
# To disable core dump on errors, include -DNODUMPCORE
# To add the ROBOT flag (allowing robots to be excluded from some rooms
#   at each player's request), include -DROBOT_MODE
# To use Tinker instead of Wizard, Bobble instead of Toad, and
#    donate instead of sacrifice, include -DTINKER
# To prevent users from using confusing names
#   (currently A, An, The, You, Your, Going, Huh?), include -DNOFAKES
# To include code for marking all things with a timestamp/usecnt,
#   include -DTIMESTAMPS
#
# To Use Islandia values in config.h, include -DISLANDIA
# To Use TinyHELL values in config.h, include -DTINYHELL

#DEFS= -DGOD_PRIV -DCOMPRESS -DQUIET_WHISPER -DGENDER -DHOST_NAME \
#      -DCONNECT_MESSAGES -DPLAYER_LIST -DDETACH -DREGISTRATION \
#      -DGOD_ONLY_PCREATE -DROBOT_MODE -DRECYCLE -DNOFAKES \
#      -DTINYHELL

DEFS= -DGOD_PRIV -DCOMPRESS -DQUIET_WHISPER -DGENDER -DHOST_NAME \
      -DCONNECT_MESSAGES -DPLAYER_LIST -DROBOT_MODE \
      -DRECYCLE -DTINKER -DNOFAKES -DTIMESTAMPS

CFLAGS= $(OPTIM) $(DEFS)
LDFLAGS = -g 

# Everything needed to use db.c
DBFILES= db.c compress.c player_list.c stringutil.c
DBOFILES= db.o compress.o player_list.o stringutil.o

# Everything except interface.c --- allows for multiple interfaces
CFILES= create.c game.c help.c look.c match.c move.c player.c predicates.c \
	rob.c set.c speech.c utils.c wiz.c \
	boolexp.c unparse.c os.c $(DBFILES)

# .o versions of above
OFILES= create.o game.o help.o look.o match.o move.o player.o predicates.o \
	rob.o set.o speech.o utils.o wiz.o boolexp.o \
	unparse.o $(DBOFILES)

# Files in the standard distribution
DISTFILES= $(CFILES) config.h db.h externs.h interface.h match.h \
	interface.c sanity-check.c extract.c dump.c decompress.c \
	help.txt small.db minimal.db restart-cmu do_gripes \
	restart-day restart-night tiny.docs tinymud.ps tinymud.tex \
 	README small.db.README \
	CHANGES copyright.h \
	Makefile Makefile.bor Makefile.dgm Makefile.vc Makefile.lcc \
	CHANGELOG os.h INSTALL_NOTES

PDIST= $(patsubst %,tinymud-1.5.4/%,$(DISTFILES))

RELEASE=dist

OUTFILES= netmud$(EXE) dump$(EXE) decompress$(EXE) sanity-check$(EXE) \
	extract$(EXE) 

all: $(OUTFILES)

netmud$(EXE): interface.o $(OFILES)
	$(CC) $(LDFLAGS) -o $@ $^ 

dump$(EXE): dump.o unparse.o $(DBOFILES)
	$(CC) $(LDFLAGS) -o $@ $^ 

sanity-check$(EXE): sanity-check.o utils.o $(DBOFILES) 
	$(CC) $(LDFLAGS) -o $@ $^ 

extract$(EXE): extract.o utils.o $(DBOFILES) 
	$(CC) $(LDFLAGS) -o $@ $^ 

decompress$(EXE): decompress.o compress.o
	$(CC) $(LDFLAGS) -o $@ $^ 

clean:
	-rm -f *.o *.d a.out core gmon.out $(OUTFILES)

dist:
	ln -s ./ tinymud-1.5.4
	tar czvf tinymud-1.5.4-$(RELEASE).tar.gz $(PDIST)
	rm tinymud-1.5.4

# pull in dependency info for *existing* .o files
OBJDEPENDS := $(OFILES) game.o interface.o dump.o \
	sanity-check.o extract.o paths.o decompress.o
-include $(OBJDEPENDS:.o=.d)

# compile and generate dependency info;
# more complicated dependency computation, so all prereqs listed
# will also become command-less, prereq-less targets
#   sed:    append directory to object target. (gcc bug?)
#   sed:    strip the target (everything before colon)
#   sed:    remove any continuation backslashes
#   fmt -1: list words one per line
#   sed:    strip leading spaces
#   sed:    add trailing colons
%.o: %.c
	$(CC) -c $(CFLAGS) $*.c -o $*.o
	@$(CC) -MM $(CFLAGS) $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp
