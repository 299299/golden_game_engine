set "maya_user_dir=C:\Users\%username%\Documents\maya\"
set "maya_script_dir=%maya_user_dir%scripts\"
set "maya_shelf_dir=%maya_user_dir%2014-x64\prefs\shelves\"
set "fbx_presets_dir=%maya_user_dir%FBX\Presets\2015.0\export\"

::copy python scirpts
copy *.py                       %maya_script_dir%
copy *.mel                      %maya_script_dir%
copy *.fbxexportpreset          %fbx_presets_dir%
