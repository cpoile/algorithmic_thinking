@echo off

cl.exe .\src\main.c /Zi /Femain.exe /Fdmain.pdb /std:c17 /link /DEBUG:FULL
