#remove old lua doc files
Remove-item generatedLuaDocs -recurse

.\luaTech\ldoc.lua.bat . -c E:/codes/m2tw\plugins/luaPlugin/luaPlugin/config.ld

Remove-item EOPDocs/source/_static/LuaLib/* -recurse
Remove-item EOPDocs/build/* -recurse
Copy-Item -Path "generatedLuaDocs/*" -Destination "EOPDocs/source/_static/LuaLib" -recurse
.\EOPDocs\WPy32-3890\scripts\cmdEOPDOCS.bat
pause