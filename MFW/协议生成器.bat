@echo off  
rem ÕýÔÚËÑË÷...  
for /f "delims=" %%s in ('dir "./proto" /b /a-d /s "*.proto"') do ( 
echo %%s

tools\protoc -I=./proto --cpp_out=./protofiles/cpp ./proto/%%~ns.proto
tools\protoc -I=./proto --cpp_out=./tools/src/cpp ./proto/%%~ns.proto
tools\protoc -I=./proto --cpp_out=./MFW_Proto ./proto/%%~ns.proto

tools\protoc -I=./proto --csharp_out=./protofiles/cs ./proto/%%~ns.proto
tools\protoc -I=./proto --csharp_out=./tools/src/cs ./proto/%%~ns.proto

tools\protoc -I=./proto --js_out=./protofiles/js ./proto/%%~ns.proto
tools\protoc -I=./proto --js_out=./tools/src/js ./proto/%%~ns.proto

tools\protoc -I=./proto --java_out=./protofiles/java ./proto/%%~ns.proto
tools\protoc -I=./proto --java_out=./tools/src/java ./proto/%%~ns.proto

tools\protoc -I=./proto --python_out=./protofiles/python ./proto/%%~ns.proto
tools\protoc -I=./proto --python_out=./tools/src/python ./proto/%%~ns.proto

) 

pause