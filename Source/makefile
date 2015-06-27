
UNAME := $(shell uname)
ifeq ($(UNAME), $(filter $(UNAME), Linux))
    OS=linux
    GENIE=/home/lixin/work/bx/tools/bin/linux/genie
else
    OS=windows
    GENIE=F:/Project/bx/tools/bin/windows/genie
endif

vs2010-build:
	$(GENIE) --file=Genie/genie.lua --os=$(OS) vs2010
vs2010-debug32: vs2010-build
	devenv .build/projects/vs2010/game.sln /Build "Debug|Win32"
vs2010-release32: vs2010-build
	devenv .build/projects/vs2010/game.sln /Build "Release|Win32"
	
vs2008-build:
	$(GENIE) --file=Genie/genie.lua --os=$(OS) vs2008
vs2008-debug32: vs2008-build
	devenv .build/projects/vs2008/game.sln /Build "Debug|Win32"
vs2008-release32: vs2008-build
	devenv .build/projects/vs2008/game.sln /Build "Release|Win32"

linux-build:
	$(GENIE) --file=Genie/genie.lua --gcc=linux-gcc --os=$(OS) gmake
linux-debug32: linux-build
	make -R -C .build/projects/linux config=debug32
linux-release32: linux-build
	make -R -C .build/projects/linux config=release32

.PHONY: docs
docs:

clean:
	@echo Cleaning...
	-@rm -rf .build