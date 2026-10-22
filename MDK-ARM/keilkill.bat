@echo off
:: 一键清理 Keil MDK 编译生成文件与垃圾文件
cd /d "%~dp0"
del /Q /S *.bak 2>nul
del /Q /S *.ddk 2>nul
del /Q /S *.edk 2>nul
del /Q /S *.lst 2>nul
del /Q /S *.lnp 2>nul
del /Q /S *.mpf 2>nul
del /Q /S *.mpj 2>nul
del /Q /S *.obj 2>nul
del /Q /S *.tags 2>nul
del /Q /S *.crf 2>nul
del /Q /S *.d 2>nul
del /Q /S *.o 2>nul
del /Q /S *.axf 2>nul
del /Q /S *.dep 2>nul
del /Q /S *.htm 2>nul
del /Q /S *.map 2>nul
del /Q /S *.iex 2>nul
del /Q /S *.__i 2>nul
del /Q /S JLinkLog.txt 2>nul
del /Q /S *.uvguix.* 2>nul
del /Q /S *.uvgui.* 2>nul
del /Q /S *.orig 2>nul
if exist firmware (
    rd /s /q firmware
)
echo Clean completed!
