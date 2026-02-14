@echo off
set PROGRAMM="%~1"
set OUT_LOGS="%TEMP%\test-out.txt"
set OUT_RES="out.txt"

(echo temp )> %OUT_RES%

echo.
echo ====Test1====
echo Appeal Help
echo.

%PROGRAMM% -h > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\text-help-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test2====
echo Empty file
echo.

%PROGRAMM% "tests\in\empty.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\empty.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test3====
echo Not existed file
echo.

%PROGRAMM% "tests\in\not-existed.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\not-existed.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test4====
echo Without A
echo.

%PROGRAMM% "tests\in\without-A.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\without-A.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test5====
echo Without B
echo.

%PROGRAMM% "tests\in\without-B.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\without-B.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test6====
echo 2 A
echo.

%PROGRAMM% "tests\in\A-twice.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\A-twice.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test7====
echo 2 B
echo.

%PROGRAMM% "tests\in\B-twice.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\B-twice.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test8====
echo column overflow
echo.

%PROGRAMM% "tests\in\column-count-overflow.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\column-count-overflow.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test9====
echo row column overflow
echo.

%PROGRAMM% "tests\in\column-row-count-overflow.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\column-row-count-overflow.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test10====
echo row overflow
echo.

%PROGRAMM% "tests\in\row-overflow.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\row-overflow.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test11====
echo just walls
echo.

%PROGRAMM% "tests\in\just-walls.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\just-walls.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test12====
echo unrecognized char
echo.

%PROGRAMM% "tests\in\unrecognized-char.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_LOGS% "tests\out\unrecognized-char.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test13====
echo Without walls
echo.

%PROGRAMM% "tests\in\without-wals.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_RES% "tests\out\without-wals.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test14====
echo Spiral 
echo.

%PROGRAMM% "tests\in\spiral.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_RES% "tests\out\spiral.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test15====
echo Without Path 
echo.

%PROGRAMM% "tests\in\without-path.txt" %OUT_RES% > %OUT_LOGS%
fc %OUT_RES% "tests\out\without-path.txt" || (
	echo Test failed!
	exit /b 1
)

echo All Tests Passed!!!!   ;)
exit /b 0