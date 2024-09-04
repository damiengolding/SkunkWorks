Write-Host "Copying libparser libraries and executables to the deploy directory:"

Write-Host "Copying libraries to the deploy directory:"
if (-not(Test-Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc")) {
        mkdir "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc" -Force
}
if (-not(Test-Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc")) {
        mkdir "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc" -Force
}

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\libparser\inc\*.hpp" "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc" -Force
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\libparser\inc\*.hpp" "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc" -Force

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\libparser\release\libparser.lib" "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static" -Force
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\libparser\debug\libparserd.lib" "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static" -Force

Write-Host "Copying executables to the deploy and tools directory:"



Write-Host "Completed copying library and executables"