set "maya_user_dir=C:\Users\%username%\Documents\maya\"
set "maya_script_dir=%maya_user_dir%scripts\"
set "maya_shelf_dir=%maya_user_dir%2014-x64\prefs\shelves\"

::copy python scirpts
copy *.py                       %maya_script_dir%
copy shelf_Custom.mel           %maya_script_dir%
