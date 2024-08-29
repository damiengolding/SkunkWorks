Write-Host "Copying PtngWidgets to Qt directories:"

if (-not(Test-Path "C:\Users\damie\source\repos\PtngDesignerWidgets\Deploy\inc")) {
        mkdir "C:\Users\damie\source\repos\PtngDesignerWidgets\Deploy\inc" -Force
}

cp "C:\Users\damie\source\repos\PtngDesignerWidgets\PtngWidgets\inc\*.hpp" "C:\Users\damie\source\repos\PtngDesignerWidgets\Deploy\inc" -Force
cp "C:\Users\damie\source\repos\PtngDesignerWidgets\PtngWidgetsOutput\release\PtngWidgets.lib" "C:\Users\damie\source\repos\PtngDesignerWidgets\Deploy" -Force

