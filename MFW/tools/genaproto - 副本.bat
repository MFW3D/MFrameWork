@echo off  
rem ÕýÔÚËÑË÷...  
for /f "delims=" %%s in ('dir "../proto" /b /a-d /s "*.proto"') do ( 
echo %%s

protoc -I=../proto --cpp_out=../protofiles/cpp ../proto/%%~ns.proto
protoc -I=../proto --cpp_out=./src/cpp ../proto/%%~ns.proto
protoc -I=../proto --cpp_out=../MFW_Proto ../proto/%%~ns.proto

protoc -I=../proto --csharp_out=../protofiles/cs ../proto/%%~ns.proto
protoc -I=../proto --csharp_out=./src/cs ../proto/%%~ns.proto

protoc -I=../proto --js_out=../protofiles/js ../proto/%%~ns.proto
protoc -I=../proto --js_out=./src/js ../proto/%%~ns.proto

protoc -I=../proto --java_out=../protofiles/java ../proto/%%~ns.proto
protoc -I=../proto --java_out=./src/java ../proto/%%~ns.proto

protoc -I=../proto --python_out=../protofiles/python ../proto/%%~ns.proto
protoc -I=../proto --python_out=./src/python ../proto/%%~ns.proto

) 

pause