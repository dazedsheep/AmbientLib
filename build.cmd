call npapi_activex_plugin\firebreath-1.5.2\prep2010.cmd %CD%\npapi_activex_plugin\firebreath-1.5.2\projects npapi_activex_plugin\firebreath-1.5.2\build

msbuild AmbientLib.sln /p:Configuration=Release

devenv AmbientLib.sln /build release

