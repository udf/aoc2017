@echo off
setlocal EnableDelayedExpansion

set i=0
for /F %%a in (input.txt) do (
   set offsets[!i!]=%%a
   set /A i+=1
)
set length=%i%
set ptr=0

:while
set jmp=!offsets[%ptr%]!
if %jmp%=="" (
    goto end
)
set /A offsets[!ptr!]=jmp + 1
set /A ptr=ptr + jmp
set /A steps+=1
goto while

:end
echo took %steps% steps