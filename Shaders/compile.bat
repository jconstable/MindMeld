forfiles /s /m *.vert /c "cmd /c C:\VulkanSDK\1.1.82.0\Bin32\glslangValidator.exe -V @relpath -o ..\BinShaders\\@relpath.spv"
forfiles /s /m *.frag /c "cmd /c C:\VulkanSDK\1.1.82.0\Bin32\glslangValidator.exe -V @relpath -o ..\BinShaders\\@relpath.spv"
pause