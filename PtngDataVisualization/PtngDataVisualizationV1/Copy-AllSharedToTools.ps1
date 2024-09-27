Write-Host "Copying (shared) libraries to the deploy directory:"
if (-not(Test-Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc")) {
        mkdir "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc" -Force
}
if (-not(Test-Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc")) {
        mkdir "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc" -Force
}

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\libparser\inc\*.hpp" "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc" -Force
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\libparser\inc\*.hpp" "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc" -Force

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\libparser\release\libparser.lib" "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared" -Force
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\libparser\debug\libparserd.lib" "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared" -Force

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\libparser\release\libparser.dll" "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared" -Force
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\libparser\debug\libparserd.dll" "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared" -Force

Write-Host "Copying (shared) executables to the deploy and tools directory:"
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\ifident\release\ifident.exe"  "C:\Tools\GoldingsGymShared"
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\ifident\debug\ifidentd.exe" "C:\Tools\GoldingsGymShared"

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\ndgml\release\ndgml.exe" "C:\Tools\GoldingsGymShared"
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\ndgml\debug\ndgmld.exe" "C:\Tools\GoldingsGymShared"

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\ntxt\release\ntxt.exe"  "C:\Tools\GoldingsGymShared"
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\ntxt\debug\ntxtd.exe" "C:\Tools\GoldingsGymShared"

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\nviz\release\nviz.exe"  "C:\Tools\GoldingsGymShared"
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\nviz\debug\nvizd.exe" "C:\Tools\GoldingsGymShared"

cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\ztest\release\ztest.exe"  "C:\Tools\GoldingsGymShared"
cp "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualizationOutputShared\ztest\debug\ztestd.exe" "C:\Tools\GoldingsGymShared"

Write-Host "Completed copying library and executables"