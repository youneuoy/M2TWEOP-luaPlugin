#remove old lua doc files
Remove-item generatedLuaDocs -recurse

#create folder for temporary place scripting docs
new-item ./generatedLuaDocs -itemtype directory

#.\luarocks\ldoc.lua.bat . -c ../luaPlugin/config.ld
.\luarocks\lua.exe ./luarocks/rocks/ldoc/1.4.6-2/bin/ldoc.lua . -c config.ld

#remove old scripting files in main docs path
Remove-item EOPDocs/source/_static/LuaLib/* -recurse
#erase build path
Remove-item EOPDocs/build/* -recurse
#copy created scripting docs to main docs source folder
Copy-Item -Path "generatedLuaDocs/*" -Destination "EOPDocs/source/_static/LuaLib" -recurse
.\EOPDocs\WPy32-3890\scripts\cmdEOPDOCS.bat
pause