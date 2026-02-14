@echo off
set PROGRAMM="%~1"
set IN="%TEMP%\test-in.txt"
set OUT_LOGS="%TEMP%\test-out.txt"
set OUT_RES="out.txt"

(echo temp )> %OUT_RES%

echo.
echo ====Test1====
echo Appeal Help
echo.

%PROGRAMM% -h > %OUT_RES%
fc %OUT_RES% "test\out\text-help-out.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test2====
echo too much argc
echo.

%PROGRAMM% 0 1 2 3 4 5 > %OUT_RES%
fc %OUT_RES% "test\out\too-much-arguments.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test3====
echo unrecognized char
echo.

(
	echo 5 g 6
	echo 0 a g
	echo 1 2 5
) > IN

%PROGRAMM% < IN > %OUT_RES%
fc %OUT_RES% "test\out\unrecognized.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test4====
echo wrong file path
echo.

%PROGRAMM% "test\in\not-existed.txt"  > %OUT_LOGS%
fc %OUT_LOGS% "test\out\not-existed.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test5====
echo identitac return
echo.

%PROGRAMM% "test\in\identity.txt"  > %OUT_LOGS%
fc %OUT_LOGS% "test\out\identity.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test6====
echo regular return
echo.

%PROGRAMM% "test\in\regular.txt"  > %OUT_LOGS%
fc %OUT_LOGS% "test\out\regular.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test6====
echo singular error
echo.

%PROGRAMM% "test\in\singular.txt"  > %OUT_LOGS%
fc %OUT_LOGS% "test\out\singular.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test7====
echo float input
echo.

%PROGRAMM% "test\in\float.txt"  > %OUT_LOGS%
fc %OUT_LOGS% "test\out\float.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test8====
echo float\int input
echo.

%PROGRAMM% "test\in\floatint.txt"  > %OUT_LOGS%
fc %OUT_LOGS% "test\out\floatint.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test9====
echo diagonal
echo.

%PROGRAMM% "test\in\diagonal.txt"  > %OUT_LOGS%
fc %OUT_LOGS% "test\out\diagonal.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test10====
echo nsquare
echo.

%PROGRAMM% "test\in\nsquare.txt"  > %OUT_LOGS%
fc %OUT_LOGS% "test\out\nsquare.txt" || (
	echo Test failed!
	exit /b 1
)

echo.
echo ====Test11====
echo nsquare_column
echo.

%PROGRAMM% "test\in\nsquare_column.txt"  > %OUT_LOGS%
fc %OUT_LOGS% "test\out\nsquare_column.txt" || (
	echo Test failed!
	exit /b 1
)