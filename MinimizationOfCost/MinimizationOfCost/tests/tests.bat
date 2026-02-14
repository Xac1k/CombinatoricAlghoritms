@echo off
echo ==============================
echo Minimization of Manufacture Placing Tests with Expected Results
echo ==============================


set TEST_COUNT=0
set FAIL_COUNT=0

echo.
echo ==============================
echo TEST 1: Not Existed File
echo ================
echo Expected: 
echo - Error(Cannot to open File)
echo.
echo Sources/Test1/NotExistedFile.txt Sources/Test1/NotExistedFile.txt > temp.txt
Sources\Executable\MinimizationOfCost.exe < temp.txt	
del temp.txt
set /a TEST_COUNT+=1

echo.
echo ==============================
echo TEST 2: File is Empty
echo ================
echo Expected: 
echo - Error(Empty files)
echo.

echo Sources/Test2/Cost.txt Sources/Test2/Demanding.txt > temp.txt
Sources\Executable\MinimizationOfCost.exe < temp.txt
del temp.txt
set /a TEST_COUNT+=1

echo.
echo ==============================
echo TEST 3: File isn't squared
echo ================
echo Expected: 
echo - Error(matrix isn't square)
echo.
echo Sources/Test3/Cost.txt Sources/Test3/Demanding.txt > temp.txt
Sources\Executable\MinimizationOfCost.exe < temp.txt
del temp.txt
set /a TEST_COUNT+=1

echo.
echo ==============================
echo TEST 4: File hasn't right format
echo ================
echo Expected: 
echo - Error(Invalid stoi argument)
echo.
echo Sources/Test4/Cost.txt Sources/Test4/Demanding.txt > temp.txt
Sources\Executable\MinimizationOfCost.exe < temp.txt
del temp.txt
set /a TEST_COUNT+=1

echo.
echo ==============================
echo TEST 5: Matrix Demension isn't equal
echo ================
echo Expected: 
echo - Error(Demension of graphOfCost and graphOfDemanding isn't equal)
echo.
echo Sources/Test5/Cost.txt Sources/Test5/Demanding.txt > temp.txt
Sources\Executable\MinimizationOfCost.exe < temp.txt
del temp.txt
set /a TEST_COUNT+=1

echo.
echo ==============================
echo TEST 6: Not Oriented FullConnected Matrix 3x3 
echo ================
echo Expected: 
echo - 105500
echo.
echo Sources/Test6/Cost.txt Sources/Test6/Demanding.txt > temp.txt
Sources\Executable\MinimizationOfCost.exe < temp.txt
del temp.txt
set /a TEST_COUNT+=1

echo.
echo ==============================
echo TEST 7: Not Oriented FullConnected Matrix 10x10
echo ================
echo.
echo Sources/Test7/Cost.txt Sources/Test7/Demanding.txt > temp.txt
Sources\Executable\MinimizationOfCost.exe < temp.txt
del temp.txt
set /a TEST_COUNT+=1

pause

