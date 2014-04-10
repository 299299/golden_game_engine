set "maya_user_dir=C:\Users\Administrator\Documents\maya\"
set "maya_script_dir=%maya_user_dir%scripts\"

::copy python scirpts
copy monk_rig.txt 				%maya_script_dir%
copy NagaMayaPipeline.py 		%maya_script_dir%
copy MayaWebSocket.py 			%maya_script_dir%
copy websocket.py 				%maya_script_dir%
copy MyTimer.py 				%maya_script_dir%
copy FixTexturePath.py 			%maya_script_dir%

::copy env
copy Maya.env 					%maya_user_dir%2014-x64

