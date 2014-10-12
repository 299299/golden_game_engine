set "bgfx_dir=F:\Code\other_engine\bgfx\"
set "bgfx_inc_dir=%bgfx_dir%include\"
set "bgfx_src_dir=%bgfx_dir%src\"
set "bgfx_dest_dir=C:\Project\NagaGame\Source\ThirdParty\bgfx\"

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
