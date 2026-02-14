@echo off
set PROGRAMM="%~1"
set OUT_LOGS="%TEMP%\test-out.txt"

echo.
echo ====Test1====
echo With 0-vector
echo expected: error message
echo.

%PROGRAMM% < "test_data\test1-in.txt" > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test1-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test2====
echo With 1-vector with wrong Limitations
echo expected: error message
echo.

%PROGRAMM% < "test_data\test2-in.txt" > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test2-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test3====
echo With 5-vector with correct data
echo.

%PROGRAMM% < "test_data\test3-in.txt" > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test3-out.txt" || (
	echo Test failed!
	exit /b 1
)


echo.
echo ====Test4====
echo With 13-vector with correct data
echo.

%PROGRAMM% < "test_data\test4-in.txt" > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test4-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test5====
echo With 8-vector with correct data. All occurence.
echo.

%PROGRAMM% < "test_data\test5-in.txt" > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test5-out.txt" || (
	echo Test failed!
	exit /b 1
)
