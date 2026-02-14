@echo off
set PROGRAMM="%~1"
set OUT_LOGS="%TEMP%\test-out.txt"
set OUT_RES="test-out_res.txt"

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
echo Wrong sourceNotation or destinationNotation(unrecognized char)
echo expected: error message
echo.

%PROGRAMM% 1+ 16 10 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test2-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test3====
echo Wrong sourceNotation or destinationNotation(The char doesn't match with sourceNotation)
echo expected: error message
echo.

%PROGRAMM% 10 16 1F > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test3-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test4====
echo Wrong sourceNotation or destinationNotation(Notation is more then 36 or less then 2)
echo expected: error message
echo.

%PROGRAMM% 1 16 0 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test4-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test5====
echo Correct input
echo expected: FF
echo.

%PROGRAMM% 2 16 11111111 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test5-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test6====
echo Wrong sourceNotation
echo expected: error
echo.

%PROGRAMM% 37 10 11111111 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test6-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test7====
echo Wrong sourceNotation
echo expected: 73
echo.

%PROGRAMM% 2 36 11111111 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test7-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test8====
echo MAX INT test
echo expected: ZIK0ZJ
echo.

%PROGRAMM% 10 36 2147483647 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test8-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test9====
echo MAX INT overflow test
echo expected: String to Int overflow conversation.
echo.

%PROGRAMM% 10 36 2147483648 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test9-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test10====
echo Negative number test
echo expected: 
echo.

%PROGRAMM% 10 36 -368 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test10-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test11====
echo Negative MIN_INT + 1 number test
echo expected: 
echo.

%PROGRAMM% 10 36 -2147483647 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test11-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test12====
echo Negative MIN_INT number test
echo expected: 
echo.

%PROGRAMM% 10 36 -2147483648 > %OUT_LOGS%
fc %OUT_LOGS% "test_data\test12-out.txt" || (
	echo Test failed!
	exit /b 1
)