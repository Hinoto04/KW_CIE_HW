@echo off
echo 2024 Assembly Language Programming Lecture
echo Term Project - Bilinear Interpolation
echo Program by Jiwoon Lee, 2024-11-23

set /p input_number=Please enter a number: 

echo Start translating HEX dump to image...
"utils\python-3.12.7-embed-amd64\python.exe" ".\utils\hex-decoder.py"
if errorlevel 1 (
    echo Error running hex-decoder.py
    pause
    exit /b 1
)

echo Start calculating PSNR of the ground truth and the interpolated image...
"utils\python-3.12.7-embed-amd64\python.exe" ".\utils\psnr.py" %input_number%
if errorlevel 1 (
    echo Error running psnr.py
    pause
    exit /b 1
)

echo All programs have finished executing successfully.
pause
