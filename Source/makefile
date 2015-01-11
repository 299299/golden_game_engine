
UNAME := $(shell uname)
ifeq ($(UNAME), $(filter $(UNAME), Linux))
    OS=linux
else
    OS=windows
endif

GENIE=C:/Project/bx/tools/bin/$(OS)/genie

vs2010-build:
	$(GENIE) --file=Genie\genie.lua vs2010
vs2010-debug32: vs2010-build
	devenv .build/projects/vs2010/game.sln /Build "Debug|Win32"
vs2010-release32: vs2010-build
	devenv .build/projects/vs2010/game.sln /Build "Release|Win32"

.PHONY: docs
docs:

clean:
	@echo Cleaning...
	-@rm -rf .build