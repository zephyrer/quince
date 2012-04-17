rem @echo off

rem compile bjam
start bootstrap.bat

rem a minute wait compiling bjam
SET SLEEP=ping 127.0.0.1 -n
%SLEEP% 60 > nul

rem use bjam to compile boost
rem compile vs2010 x86 boost library files


rem vs2010 win32 library files
md stage\lib\win32\vs10_0\


rem ******************************************************************
rem delete all files in the lib
del stage\lib\*.* /Q



rem compile vs2010 win32 library file
bjam --toolset=msvc-10.0 architecture=x86 --with-graph --with-iostreams --with-program_options --with-signals --with-system --with-thread --with-date_time --with-filesystem --with-serialization --with-timer --with-log variant=release link=shared runtime-link=shared threading=multi stage
bjam --toolset=msvc-10.0 architecture=x86 --with-graph --with-iostreams --with-program_options --with-signals --with-system --with-thread --with-date_time --with-filesystem --with-serialization --with-timer --with-log variant=debug link=shared runtime-link=shared threading=multi stage

rem copy to \stage\lib\win32\vs10_0
copy stage\lib\*.* stage\lib\win32\vs10_0\*.* /Y
rem ##################################################################


#####################################################################
#     Runtime configure     variant	threading 	runtime-link
#	/MT		    release 	multi		static
#	/MTd		    debug	multi		shared
#	/MD		    release	multi		static
#	/MDd		    debug	multi		shared
#####################################################################
