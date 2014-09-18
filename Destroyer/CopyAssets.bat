@echo off

:: Android asset copy.
robocopy /NJS /NJH /S assets UtHEngine/android/assets

::Update your Project folder/assets here.
robocopy /NJS /NJH /S assets Destroyer/assets

pause