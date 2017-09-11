@echo off 

for /R "./proto/" %%s in (.,*) do ( 
echo %%s 
flatc -c -o ../protos/cpp %%s
flatc -c -o ./src/cpp %%s
flatc -c -o ../MFW_Proto %%s

flatc -n -o ../protos/cs %%s
flatc -n -o ./src/cs %%s

flatc -s -o ../protos/js %%s
flatc -s -o ./src/js %%s

flatc -j -o ../protos/java %%s
flatc -j -o ./src/java %%s

flatc -p -o ../protos/python %%s
flatc -p -o ./src/python %%s

) 

pause