Write-Host "Copying (static) libraries to the deploy directory:"
if (-not(Test-Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc")) {
        mkdir "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc" -Force
}

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\libparser\inc\*.hpp" "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc" -Force
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\libparser\release\libparser.lib" "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static" -Force
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\libparser\debug\libparserd.lib" "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static" -Force

Write-Host "Copying (static) executables to the deploy and tools directory:"
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\ifident\release\ifident.exe"  "C:\Tools\GoldingsGymStatic"
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\ifident\debug\ifidentd.exe" "C:\Tools\GoldingsGymStatic"

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\ndgml\release\ndgml.exe" "C:\Tools\GoldingsGymStatic"
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\ndgml\debug\ndgmld.exe" "C:\Tools\GoldingsGymStatic"

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\ntxt\release\ntxt.exe"  "C:\Tools\GoldingsGymStatic"
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\ntxt\debug\ntxtd.exe" "C:\Tools\GoldingsGymStatic"

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\nviz\release\nviz.exe"  "C:\Tools\GoldingsGymStatic"
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\nviz\debug\nvizd.exe" "C:\Tools\GoldingsGymStatic"

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\ztest\release\ztest.exe"  "C:\Tools\GoldingsGymStatic"
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputStatic\ztest\debug\ztestd.exe" "C:\Tools\GoldingsGymStatic"

Write-Host "Completed copying library and executables"