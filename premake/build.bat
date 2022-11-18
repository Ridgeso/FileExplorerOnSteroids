@echo off
pushd %~dp0\..\

if [%*%]==[] call premake\premake5.exe vs2022

if [%*%]==[] goto end_building
premake\premake5.exe %*

:end_building
popd
pause