Write-Host "Deploying PtngDataVisualization libraries and headers"

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static" -ItemType Directory
}

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc" -ItemType Directory
}

##### Libraries #####
if( Test-Path -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\StaticOutput\libparser\release\libparser.lib" ){
    Write-Host "Copying release (static) build library to C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static"
    Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\StaticOutput\libparser\release\libparser.lib" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static"
}
else{
    Write-Host "Omitting release (static) build library; library does not exist"
}

if( Test-Path -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\StaticOutput\libparser\debug\libparserd.lib" ){
    Write-Host "Copying debug (static) build library to C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static"
    Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\StaticOutput\libparser\debug\libparserd.lib" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static"
}
else{
    Write-Host "Omitting debug (static) build library; library does not exist"
}

##### Headers #####
###### Create directories ######
if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\inc" ) ){ # This is for libparser_global.hpp and similar structural files
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\inc" -ItemType Directory
}

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\utils" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\utils" -ItemType Directory
}

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io" -ItemType Directory
}

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\data" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\data" -ItemType Directory
}

###### Copy headers ######
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\inc\libparser_global.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\inc"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\utils\ptngenums.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\utils"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\utils\ptngstylesheet.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\utils"

