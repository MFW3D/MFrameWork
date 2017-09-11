@echo off  
rem ÕýÔÚËÑË÷...  
for /f "delims=" %%s in ('dir "../proto" /b /a-d /s "*.proto"') do ( 
echo %%s

protoc -I=../proto --cpp_out=../protofiles/cpp ../proto/%%~ns.proto
protoc -I=../proto --cpp_out=./src/cpp ../proto/%%~ns.proto
protoc -I=../proto --cpp_out=../MFW_Proto ../proto/%%~ns.proto

protoc -I=../proto --csharp_out=../protofiles/cs ../proto/%%~ns.proto
protoc -I=../proto --csharp_out=./src/cs ../proto/%%~ns.proto
protoc -I=../proto --csharp_out=../ClientTest/Protos ../proto/%%~ns.proto

) 

pause