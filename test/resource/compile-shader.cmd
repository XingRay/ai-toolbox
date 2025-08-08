@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

:: ================ 配置参数 ================
set INPUT_DIR=shader
set OUTPUT_DIR=spv
set SHADER_EXTS=*.vert *.frag *.comp *.geom *.tesc *.tese
set COMPILER=glslc

:: ================ 验证编译器 ================
where %COMPILER% >nul 2>&1
if !errorlevel! neq 0 (
    echo [错误] 未找到 %COMPILER% 编译器
    echo 请安装 Vulkan SDK 或 Google Shaderc
    exit /b 1
)
%COMPILER% --version >nul || (
    echo [错误] %COMPILER% 无法执行，请检查安装
    exit /b 1
)

:: ================ 验证输入目录 ================
if not exist "%INPUT_DIR%" (
    echo [错误] 输入目录不存在: %INPUT_DIR%
    exit /b 1
)

:: ================ 准备输出目录 ================
if exist "%OUTPUT_DIR%" (
    robocopy "%OUTPUT_DIR%" "%OUTPUT_DIR%" /purge /mir >nul 2>&1
) else (
    mkdir "%OUTPUT_DIR%" >nul 2>&1
)

:: ===== 替换原“收集着色器文件”部分 =====
echo 扫描着色器文件...
:: 使用直接遍历代替 dir /s
setlocal enabledelayedexpansion
set file_count=0
for %%f in ("%INPUT_DIR%\*.vert" "%INPUT_DIR%\*.frag" "%INPUT_DIR%\*.comp") do (
    set /a file_count+=1
    set "input_path=%%f"
    set "filename=%%~nxf"
    set "output_path=%OUTPUT_DIR%\!filename!.spv"

    echo [编译] !filename!
    %COMPILER% "%%f" -o "!output_path!"
    if !errorlevel! equ 0 (
        echo   [✓] 成功: !output_path!
        set /a success_count+=1
    ) else (
        echo   [×] 失败: !filename!
    )
)
endlocal

:: ================ 清理与统计 ================
del shader_list.txt >nul 2>&1
echo.
echo ================ 编译统计 ================
echo 成功: !success_count! / !file_count! 个着色器
echo 输出目录: %OUTPUT_DIR%\
echo ========================================
endlocal