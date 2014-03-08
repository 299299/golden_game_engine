:: set env NAGA_DIR to current directory.
@echo off
set "naga_dir=%cd%\"
set NAGA_DIR = wmic ENVIRONMENT where "name='NAGA_DIR'" get VariableValue
echo "env dir = %NAGA_DIR%"

if %NAGA_DIR% == "" goto createenv
if not %NAGA_DIR% == "" goto setenv 

:createenv
echo "create env NAGA_DIR"
wmic ENVIRONMENT create name="NAGA_DIR",username="%username%",VariableValue="%naga_dir%"
goto exithere

:setenv
echo "set env NAGA_DIR"
::wmic ENVIRONMENT where "name='NAGA_DIR' and username='%username%'" set VariableValue="%naga_dir%"
wmic ENVIRONMENT set name="NAGA_DIR",username="%username%",VariableValue="%naga_dir%"
goto exithere


:exithere