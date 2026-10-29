@echo off
title PBL2 - Quan Ly Ban Giay
cls
echo ====================================================
echo   DANG BIEN DICH HE THONG QUAN LY BAN GIAY (PBL2)
echo ====================================================
echo.

g++ -std=c++11 -Wall -Wextra main.cpp Shoes/*.cpp Payment/*.cpp Customer/*.cpp Order/*.cpp OrderDetail/*.cpp StockTransaction/*.cpp -I Shoes -I Payment -I Customer -I Order -I OrderDetail -I StockTransaction -o RunTests.exe

if %errorlevel% equ 0 (
    echo.
    echo [THANH CONG] Bien dich hoan tat khong co loi!
    echo ====================================================
    echo   DANG KHOI CHAY CHUONG TRINH...
    echo ====================================================
    echo.
    RunTests.exe
) else (
    echo.
    echo [LOI] Co loi xay ra trong qua trinh bien dich!
)

echo.
pause

