set "bgfx_dir=F:\Code\other_engine\bgfx\"
set "bgfx_inc_dir=%bgfx_dir%include\"
set "bgfx_src_dir=%bgfx_dir%src\"
set "dest_proj_dir=C:\Project\NagaGame\Source\ThirdParty\"
set "bgfx_dest_dir=%dest_proj_dir%bgfx\"

set "imgui_src_dir=%bgfx_dir%examples\common\imgui\"
set "imgui_dest_dir=%dest_proj_dir%imgui\"

set "nanovg_src_dir=%bgfx_dir%examples\common\nanovg\"
set "nanovg_dest_dir=%dest_proj_dir%nanovg\"

::copy python scirpts
copy %bgfx_inc_dir%*.h                      %bgfx_dest_dir%
copy %bgfx_src_dir%*.bin.h                  %bgfx_dest_dir%
copy %bgfx_src_dir%bgfx.cpp                 %bgfx_dest_dir%
copy %bgfx_src_dir%bgfx_p.h                 %bgfx_dest_dir%
copy %bgfx_src_dir%config.h                 %bgfx_dest_dir%
copy %bgfx_src_dir%vertexdecl.h             %bgfx_dest_dir%
copy %bgfx_src_dir%vertexdecl.cpp           %bgfx_dest_dir%
copy %bgfx_src_dir%renderer_d3d.h           %bgfx_dest_dir%
copy %bgfx_src_dir%renderer_d3d11.h         %bgfx_dest_dir%
copy %bgfx_src_dir%renderer_d3d11.cpp       %bgfx_dest_dir%
copy %bgfx_src_dir%charset.h                %bgfx_dest_dir%
copy %bgfx_src_dir%image.h                  %bgfx_dest_dir%
copy %bgfx_src_dir%image.cpp                %bgfx_dest_dir%
copy %bgfx_src_dir%renderer_null.cpp        %bgfx_dest_dir%
copy %bgfx_inc_dir%*.h                      %bgfx_dest_dir%

copy %imgui_src_dir%*.bin.h                 %imgui_dest_dir%
copy %imgui_src_dir%*.h                 	%imgui_dest_dir%
copy %imgui_src_dir%*.cpp                 	%imgui_dest_dir%

copy %nanovg_src_dir%*.bin.h                %nanovg_dest_dir%
copy %nanovg_src_dir%*.h                 	%nanovg_dest_dir%
copy %nanovg_src_dir%*.cpp                 	%nanovg_dest_dir%