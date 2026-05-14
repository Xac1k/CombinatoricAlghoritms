#!/bin/sh

PROGRAM="$1"
OUT_LOGS="$(mktemp)"

echo
echo "====Test1===="
echo "With 0-vector"
echo "expected: error message"
echo

"$PROGRAM" < "test1-in.txt" > "$OUT_LOGS"
if ! cmp -s "$OUT_LOGS" "test1-out.txt"; then
    echo "Test failed!"
    rm -f "$OUT_LOGS"
    exit 1
fi

echo
echo "====Test2===="
echo "With 1-vector with wrong Limitations"
echo "expected: error message"
echo

"$PROGRAM" < "test2-in.txt" > "$OUT_LOGS"
if ! cmp -s "$OUT_LOGS" "test2-out.txt"; then
    echo "Test failed!"
    rm -f "$OUT_LOGS"
    exit 1
fi

echo
echo "====Test3===="
echo "With 5-vector with correct data"
echo

"$PROGRAM" < "test3-in.txt" > "$OUT_LOGS"
if ! cmp -s "$OUT_LOGS" "test3-out.txt"; then
    echo "Test failed!"
    rm -f "$OUT_LOGS"
    exit 1
fi

echo
echo "====Test4===="
echo "With 13-vector with correct data"
echo

"$PROGRAM" < "test4-in.txt" > "$OUT_LOGS"
if ! cmp -s "$OUT_LOGS" "test4-out.txt"; then
    echo "Test failed!"
    rm -f "$OUT_LOGS"
    exit 1
fi

echo
echo "====Test5===="
echo "With 8-vector with correct data. All occurence."
echo

"$PROGRAM" < "test5-in.txt" > "$OUT_LOGS"
if ! cmp -s "$OUT_LOGS" "test5-out.txt"; then
    echo "Test failed!"
    rm -f "$OUT_LOGS"
    exit 1
fi

rm -f "$OUT_LOGS"
echo "All tests passed."
exit 0