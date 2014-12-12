@ECHO OFF

IF [%1] == [] (
        "%~dp0NagaGame" Scripts/Editor.as -w -s
        )

IF NOT [%1] == [] (
        "%~dp0NagaGame" Scripts/Editor.as %*
        )
