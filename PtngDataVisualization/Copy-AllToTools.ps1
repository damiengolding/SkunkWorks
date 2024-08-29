Write-Host "Copying libparser libraries and executables to the deploy directory:"

Write-Host "Copying libraries to the deploy directory:"
if (-not(Test-Path "C:\Tools\GoldingsGymStatic\libparser\inc")) {
        mkdir "C:\Tools\GoldingsGymStatic\libparser\inc" -Force
}
cp "C:\Users\damie\source\repos\PtngDataVisualization\libparser\inc\*.hpp" "C:\Tools\GoldingsGymStatic\libparser\inc" -Force
cp "C:\Users\damie\source\repos\PtngDataVisualizationOutputStatic\libparser\debug\libparserd.lib" "C:\Tools\GoldingsGymStatic\libparser" -Force
cp "C:\Users\damie\source\repos\PtngDataVisualizationOutputStatic\libparser\release\libparser.lib" "C:\Tools\GoldingsGymStatic\libparser" -Force

Write-Host "Copying executables to the deploy and tools directory:"

cp "C:\Users\damie\source\repos\PtngDataVisualizationOutputStatic\ifident\release\ifident.exe"  "C:\Tools\GoldingsGymStatic"
cp "C:\Users\damie\source\repos\PtngDataVisualizationOutputStatic\ifident\debug\ifidentd.exe" "C:\Tools\GoldingsGymStatic"

cp "C:\Users\damie\source\repos\PtngDataVisualizationOutputStatic\ndgml\release\ndgml.exe" "C:\Tools\GoldingsGymStatic"
cp "C:\Users\damie\source\repos\PtngDataVisualizationOutputStatic\ndgml\debug\ndgmld.exe" "C:\Tools\GoldingsGymStatic"

cp "C:\Users\damie\source\repos\PtngDataVisualizationOutputStatic\ntxt\release\ntxt.exe"  "C:\Tools\GoldingsGymStatic"
cp "C:\Users\damie\source\repos\PtngDataVisualizationOutputStatic\ntxt\debug\ntxtd.exe" "C:\Tools\GoldingsGymStatic"

cp "C:\Users\damie\source\repos\PtngDataVisualizationOutputStatic\nviz\release\nviz.exe"  "C:\Tools\GoldingsGymStatic"
cp "C:\Users\damie\source\repos\PtngDataVisualizationOutputStatic\nviz\debug\nvizd.exe" "C:\Tools\GoldingsGymStatic"

cp "C:\Users\damie\source\repos\PtngDataVisualizationOutputStatic\ztest\release\ztest.exe"  "C:\Tools\GoldingsGymStatic"
cp "C:\Users\damie\source\repos\PtngDataVisualizationOutputStatic\ztest\debug\ztestd.exe" "C:\Tools\GoldingsGymStatic"

Write-Host "Completed copying library and executables"