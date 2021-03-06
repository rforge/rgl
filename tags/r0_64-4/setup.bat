@echo off
REM  RGL windows setup build tool
REM This file is part of the RGL software
REM (c) 2003 D.Adler

set SRC=src
set DEST=src
set CFG=config.mk

REM === SETUP build tool =====================================================

set TARGET=x%1
if %TARGET% == xclean goto clean
if %TARGET% == xinfo  goto dump
if %TARGET% == x      goto usage

REM jump to build routine
goto %1

REM === dump usage ===========================================================

:usage
echo usage: %0 [tool]
echo supported build tools:
echo   mingw    MinGW
echo   vc       Microsoft Visual C++
echo   clean    clean source package (maintainer)
goto return

REM === build tool: mingw ====================================================

:mingw
echo include build/mingw/Makefile >%SRC%\Makefile.win
echo include build/mingw/Makefile >%SRC%\Makefile
copy src\build\mingw\configure.win configure.win
goto done

REM === build tool: vc =======================================================

:vc
echo include build/vc/Makefile >%SRC%\Makefile.win
echo include build/vc/Makefile >%SRC%\Makefile
copy src\build\vc\configure.win configure.win
goto done

REM === SETUP CLEAN ==========================================================

:clean
del %CFG%
goto return

REM === SETUP DONE ===========================================================

:done
echo setup.bat: configured for build tool '%1'
echo BUILD_TOOL=%1 >config.status

:return
