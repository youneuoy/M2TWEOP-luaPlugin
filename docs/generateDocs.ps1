#remove old lua doc files
Remove-item generatedLuaDocs -recurse

#.\luarocks\ldoc.lua.bat . -c ../luaPlugin/config.ld
.\luarocks\lua.exe ./luarocks/rocks/ldoc/1.4.6-2/bin/ldoc.lua . -c ../luaPlugin/config.ld

Remove-item EOPDocs/source/_static/LuaLib/* -recurse
Remove-item EOPDocs/build/* -recurse
Copy-Item -Path "generatedLuaDocs/*" -Destination "EOPDocs/source/_static/LuaLib" -recurse
.\EOPDocs\WPy32-3890\scripts\cmdEOPDOCS.bat
pause