@echo off
set PROGRAMM="%~1"
set OUT_LOGS="%TEMP%\test-out.txt"
set OUT_RES="test-out_res.txt"

echo.
echo ====Test1====
echo Without arguments
echo expected: error message
echo.

%PROGRAMM% > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test1-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test2====
echo Wrong path to file
echo expected: error message
echo.

%PROGRAMM% "test_data\test2.txt" %OUT_RES% 0 0 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test2-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test3====
echo Negative values of parameters
echo expected: error message
echo.

%PROGRAMM% "test_data\test3.txt" %OUT_RES% -9 -25 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test3-out.txt" || (
	echo Test failed!OUT_RES
	exit /b 1
)

echo.
echo ====Test4====
echo position overflow
echo expected: error message
echo.

%PROGRAMM% "test_data\test3.txt" %OUT_RES% 0 70 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test4-out.txt" || (
	echo Test failed!OUT_RES
	exit /b 1
)

echo.
echo ====Test5====
echo successful test
echo expected: copied file
echo.

%PROGRAMM% "test_data\test3.txt" %OUT_RES% 0 5 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test5-out.txt" || (
	echo Test failed!OUT_RES
	exit /b 1
)

echo.
echo ====Test6====
echo too much arguments
echo expected: error message
echo.

%PROGRAMM% -h 0 2 4 5 6 7 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test6-out.txt" || (
	echo Test failed!
	exit /b 1
)

fc "test_data\test5-res.txt" %OUT_RES% || (
	echo Test failed!OUT_RES
	exit /b 1
)