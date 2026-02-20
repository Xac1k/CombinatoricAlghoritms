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
fc %OUT_LOGS% "tests\out\test1-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test2====
echo Wrong path to file
echo expected: error message
echo.

%PROGRAMM% pack  "tests\in\not-existed.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\test2-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test3====
echo Wrong mode of rle converstion
echo expected: error message
echo.

%PROGRAMM% inpack  "tests\in\test3.bin" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\test3-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test4====
echo Wrong fromat of file for decoding
echo expected: error message
echo.

%PROGRAMM% unpack  "tests\in\test4.bin" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\test4-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test5====
echo Help message
echo expected: error message
echo.

%PROGRAMM% -h > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\test5-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test6====
echo File only from 0xFF
echo.

%PROGRAMM% pack  "tests\in\test6.bin" %OUT_RES% > %OUT_LOGS%
fc %OUT_RES% "tests\out\test6-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test7====
echo File from 300 symbols "A"
echo.

%PROGRAMM% pack  "tests\in\test7.bin" %OUT_RES% > %OUT_LOGS%
fc %OUT_RES% "tests\out\test7-out.bin" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test8====
echo File from 255 symbols "A"
echo.

%PROGRAMM% pack  "tests\in\test8.bin" %OUT_RES% > %OUT_LOGS%
fc %OUT_RES% "tests\out\test8-out.bin" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test9====
echo Random Text File Encode
echo.

%PROGRAMM% pack  "tests\in\test9.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_RES% "tests\out\test9-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test10====
echo Random Text File Decode
echo.

%PROGRAMM% unpack  "tests\out\test9-out.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_RES% "tests\out\test10-out.txt" || (
	echo Test failed!
	exit /b 1
)