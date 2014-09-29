//Maya ASCII 2015 scene
//Name: Level_Test.ma
//Last modified: Mon, Sep 29, 2014 10:03:28 PM
//Codeset: 936
requires maya "2015";
requires -nodeType "mentalrayFramebuffer" -nodeType "mentalrayOptions" -nodeType "mentalrayGlobals"
		 -nodeType "mentalrayItemsList" -dataType "byteArray" "Mayatomr" "2015.0 - 3.12.1.18 ";
requires -nodeType "assemblyDefinition" "sceneAssembly" "1.0";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2015";
fileInfo "version" "2015";
fileInfo "cutIdentifier" "201408201531-928694";
fileInfo "osv" "Microsoft Windows 7 Ultimate Edition, 64-bit Windows 7 Service Pack 1 (Build 7601)\n";
createNode transform -s -n "persp";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 5096.8768790545537 890.09883526498106 362.05071840056314 ;
	setAttr ".r" -type "double3" -4.5218466210805959 -2431.8000000000097 1.2657106891047461e-014 ;
createNode camera -s -n "perspShape" -p "persp";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".fcp" 990000;
	setAttr ".coi" 4166.7048593959889;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 1832.8721303305524 200.09999999999974 1172.0851140115403 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 200.10000000000002;
	setAttr ".ow" 315.91657106507444;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
createNode transform -s -n "front";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 0 200.10000000000002 ;
createNode camera -s -n "frontShape" -p "front";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 200.10000000000002;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
createNode transform -s -n "side";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 2679.4189070502403 816.58914420458041 1586.0482127782791 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 200.10000000000002;
	setAttr ".ow" 1935.7919760379148;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode assemblyDefinition -n "AD_Gotham_GroundFloor_Shop_OlddB5_512";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/15 22:17:41";
	setAttr ".t" -type "double3" -227.71881865117575 0 -363.19090511114956 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_GroundFloor_Shop_OlddB5_512.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_GroundFloor_Shop_OlddB5_512.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham2/Gotham_GroundFloor_Shop_OlddB5_512.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_Groundfloor_Shop_OldB2";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/15 22:17:41";
	setAttr ".t" -type "double3" 309.85100072950115 0 -363.19090511114956 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_Groundfloor_Shop_OldB2.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_Groundfloor_Shop_OldB2.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham2/Gotham_Groundfloor_Shop_OldB2.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_OZ_Gotham_GroundFloor_Shop_OldA_03";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/15 22:17:41";
	setAttr ".t" -type "double3" 1348.17296694997 0 -363.19090511114956 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "OZ_Gotham_GroundFloor_Shop_OldA_03.mb";
	setAttr ".rep[0].rla" -type "string" "OZ_Gotham_GroundFloor_Shop_OldA_03.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham2/OZ_Gotham_GroundFloor_Shop_OldA_03.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_ARCH_Classic_BigWinx2";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/13 22:44:07";
	setAttr ".t" -type "double3" 1807.1874005733416 -8.5265128291212022e-014 1221.988311342102 ;
	setAttr ".r" -type "double3" 180 180 0 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_ARCH_Classic_BigWinx2.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_ARCH_Classic_BigWinx2.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/Gotham_ARCH_Classic_BigWinx2.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_ARCH_Classic_BigWinx3";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/13 22:44:07";
	setAttr ".t" -type "double3" 1807.1874005733416 767.79575881492337 1221.988311342102 ;
	setAttr ".r" -type "double3" 180 180 0 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_ARCH_Classic_BigWinx2.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_ARCH_Classic_BigWinx2.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/Gotham_ARCH_Classic_BigWinx2.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_ARCH_Classic_WinBCorner";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/13 22:44:07";
	setAttr ".t" -type "double3" 2319.0203817558977 -1.9895196601282805e-013 1718.1728113582853 ;
	setAttr ".r" -type "double3" 180 90 0 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_ARCH_Classic_WinBCorner.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_ARCH_Classic_WinBCorner.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/Gotham_ARCH_Classic_WinBCorner.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_ARCH_Classic_WinBCorner1";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/13 22:44:07";
	setAttr ".t" -type "double3" 2319.0203817558977 767.7602130373582 1718.1728113582853 ;
	setAttr ".r" -type "double3" 180 89.999999999999986 0 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_ARCH_Classic_WinBCorner.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_ARCH_Classic_WinBCorner.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/Gotham_ARCH_Classic_WinBCorner.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_Fences_Mall768";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/15 09:20:52";
	setAttr ".t" -type "double3" 1581.450877456391 0 1029.1509922906728 ;
	setAttr ".r" -type "double3" 0 90 0 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_Fences_Mall768.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_Fences_Mall768.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/Gotham_Fences_Mall768.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_Fences_Mall769";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/15 09:20:52";
	setAttr ".t" -type "double3" 2349.6488854313693 0 1029.1509922906728 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_Fences_Mall768.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_Fences_Mall768.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/Gotham_Fences_Mall768.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_Fences_PoleSolid_128C";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/15 09:20:52";
	setAttr ".t" -type "double3" 2349.4063757158419 0 982.37647316968105 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_Fences_PoleSolid_128C.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_Fences_PoleSolid_128C.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/Gotham_Fences_PoleSolid_128C.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_Fences_PoleSolid_512";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/15 09:20:52";
	setAttr ".t" -type "double3" 1837.6805463228472 0 982.47459618927633 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_Fences_PoleSolid_512.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_Fences_PoleSolid_512.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/Gotham_Fences_PoleSolid_512.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_Fences_PoleSolid_513";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/15 09:20:52";
	setAttr ".t" -type "double3" 1325.4346235433959 0 982.47459618927633 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_Fences_PoleSolid_512.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_Fences_PoleSolid_512.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/Gotham_Fences_PoleSolid_512.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_ARCH_GCPD_EntranceRoof_04";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/13 22:44:07";
	setAttr ".t" -type "double3" 1141.9377892572409 1526.6771139518823 2981.1094913643574 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "ARCH_GCPD_EntranceRoof_04.mb";
	setAttr ".rep[0].rla" -type "string" "ARCH_GCPD_EntranceRoof_04.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/ARCH_GCPD_EntranceRoof_04.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_Arch_Classic_BigWiny2";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/13 22:44:07";
	setAttr ".t" -type "double3" 784.24511246304041 0 1222.2457439274781 ;
	setAttr ".r" -type "double3" 180 -180 0 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_Arch_Classic_BigWiny2.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_Arch_Classic_BigWiny2.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/Gotham_Arch_Classic_BigWiny2.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_BridgeRoad_Destroyed_2048_Custom_02";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "feng.yu";
	setAttr ".cdat" -type "string" "2014/02/13 16:31:40";
	setAttr ".t" -type "double3" 128.73718000362123 0 363.4523101124712 ;
	setAttr ".r" -type "double3" 0 -90 0 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "BridgeRoad_Destroyed_2048_Custom_02.mb";
	setAttr ".rep[0].rla" -type "string" "BridgeRoad_Destroyed_2048_Custom_02";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Bridge/BridgeRoad_Destroyed_2048_Custom_02.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_ConcreteBarrier01";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "feng.yu";
	setAttr ".cdat" -type "string" "2014/02/13 16:31:40";
	setAttr ".t" -type "double3" 359.82006483717771 -40.966015818205165 1204.0750870623856 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "ConcreteBarrier01.mb";
	setAttr ".rep[0].rla" -type "string" "ConcreteBarrier01";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Bridge/ConcreteBarrier01.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_ConcreteBarrier02";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "feng.yu";
	setAttr ".cdat" -type "string" "2014/02/13 16:31:40";
	setAttr ".t" -type "double3" 359.82006483717771 -40.966015818205165 688.38752908664333 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "ConcreteBarrier01.mb";
	setAttr ".rep[0].rla" -type "string" "ConcreteBarrier01";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Bridge/ConcreteBarrier01.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Bridge_Rail_01_1024";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "feng.yu";
	setAttr ".cdat" -type "string" "2014/02/13 16:31:40";
	setAttr ".t" -type "double3" 2285.5543732270999 -43.265805988647912 622.08735252530801 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Bridge_Rail_01_1024.mb";
	setAttr ".rep[0].rla" -type "string" "Bridge_Rail_01_1024";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Bridge/Bridge_Rail_01_1024.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_GCPD_Window1024";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/15 09:20:52";
	setAttr ".t" -type "double3" -231.3088582787712 513.52318819232437 -384.73841723698871 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_GCPD_Window1024.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_GCPD_Window1024.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/Gotham_GCPD_Window1024.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_GCPD_Window1025";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/15 09:20:52";
	setAttr ".t" -type "double3" 795.387229222516 513.52318819232437 -384.73841723698871 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_GCPD_Window1024.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_GCPD_Window1024.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/Gotham_GCPD_Window1024.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode assemblyDefinition -n "AD_Gotham_Fences_PoleSolid_514";
	setAttr ".isc" yes;
	setAttr ".icn" -type "string" "out_assemblyDefinition.png";
	setAttr ".ctor" -type "string" "ryoma";
	setAttr ".cdat" -type "string" "2014/02/15 09:20:52";
	setAttr ".t" -type "double3" 815.546069703135 0 982.47459618927633 ;
	setAttr -s 2 ".rep";
	setAttr ".rep[0].rna" -type "string" "Gotham_Fences_PoleSolid_512.mb";
	setAttr ".rep[0].rla" -type "string" "Gotham_Fences_PoleSolid_512.mb";
	setAttr ".rep[0].rty" -type "string" "Scene";
	setAttr ".rep[0].rda" -type "string" "LevelData/Gotham/Gotham_Fences_PoleSolid_512.mb";
	setAttr ".rep[1].rna" -type "string" "Locator";
	setAttr ".rep[1].rla" -type "string" "Locator";
	setAttr ".rep[1].rty" -type "string" "Locator";
	setAttr ".rep[1].rda" -type "string" "Locator";
createNode transform -n "SkyDome";
	setAttr ".s" -type "double3" 50 50 50 ;
createNode mesh -n "SkyDomeShape" -p "SkyDome";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".sdt" 0;
	setAttr ".ugsdt" no;
	setAttr ".ndt" 0;
createNode transform -n "sun_light";
	setAttr ".t" -type "double3" 0 1085.7540651415889 -2.4868995751603507e-014 ;
	setAttr ".r" -type "double3" -150.04039409139907 -40.166940998610627 92.634470203581998 ;
	setAttr ".s" -type "double3" 323.93682138016857 522.80899775650823 323.93682138016857 ;
createNode directionalLight -n "sun_lightShape" -p "sun_light";
	setAttr -k off ".v";
	setAttr ".urs" no;
	setAttr ".phi" 8000;
createNode mentalrayItemsList -s -n "mentalrayItemsList";
createNode mentalrayGlobals -s -n "mentalrayGlobals";
	setAttr ".rvb" 3;
	setAttr ".ivb" no;
createNode mentalrayOptions -s -n "miDefaultOptions";
	addAttr -ci true -m -sn "stringOptions" -ln "stringOptions" -at "compound" -nc 
		3;
	addAttr -ci true -sn "name" -ln "name" -dt "string" -p "stringOptions";
	addAttr -ci true -sn "value" -ln "value" -dt "string" -p "stringOptions";
	addAttr -ci true -sn "type" -ln "type" -dt "string" -p "stringOptions";
	setAttr -s 45 ".stringOptions";
	setAttr ".stringOptions[0].name" -type "string" "rast motion factor";
	setAttr ".stringOptions[0].value" -type "string" "1.0";
	setAttr ".stringOptions[0].type" -type "string" "scalar";
	setAttr ".stringOptions[1].name" -type "string" "rast transparency depth";
	setAttr ".stringOptions[1].value" -type "string" "8";
	setAttr ".stringOptions[1].type" -type "string" "integer";
	setAttr ".stringOptions[2].name" -type "string" "rast useopacity";
	setAttr ".stringOptions[2].value" -type "string" "true";
	setAttr ".stringOptions[2].type" -type "string" "boolean";
	setAttr ".stringOptions[3].name" -type "string" "importon";
	setAttr ".stringOptions[3].value" -type "string" "false";
	setAttr ".stringOptions[3].type" -type "string" "boolean";
	setAttr ".stringOptions[4].name" -type "string" "importon density";
	setAttr ".stringOptions[4].value" -type "string" "1.0";
	setAttr ".stringOptions[4].type" -type "string" "scalar";
	setAttr ".stringOptions[5].name" -type "string" "importon merge";
	setAttr ".stringOptions[5].value" -type "string" "0.0";
	setAttr ".stringOptions[5].type" -type "string" "scalar";
	setAttr ".stringOptions[6].name" -type "string" "importon trace depth";
	setAttr ".stringOptions[6].value" -type "string" "0";
	setAttr ".stringOptions[6].type" -type "string" "integer";
	setAttr ".stringOptions[7].name" -type "string" "importon traverse";
	setAttr ".stringOptions[7].value" -type "string" "true";
	setAttr ".stringOptions[7].type" -type "string" "boolean";
	setAttr ".stringOptions[8].name" -type "string" "shadowmap pixel samples";
	setAttr ".stringOptions[8].value" -type "string" "3";
	setAttr ".stringOptions[8].type" -type "string" "integer";
	setAttr ".stringOptions[9].name" -type "string" "ambient occlusion";
	setAttr ".stringOptions[9].value" -type "string" "false";
	setAttr ".stringOptions[9].type" -type "string" "boolean";
	setAttr ".stringOptions[10].name" -type "string" "ambient occlusion rays";
	setAttr ".stringOptions[10].value" -type "string" "256";
	setAttr ".stringOptions[10].type" -type "string" "integer";
	setAttr ".stringOptions[11].name" -type "string" "ambient occlusion cache";
	setAttr ".stringOptions[11].value" -type "string" "false";
	setAttr ".stringOptions[11].type" -type "string" "boolean";
	setAttr ".stringOptions[12].name" -type "string" "ambient occlusion cache density";
	setAttr ".stringOptions[12].value" -type "string" "1.0";
	setAttr ".stringOptions[12].type" -type "string" "scalar";
	setAttr ".stringOptions[13].name" -type "string" "ambient occlusion cache points";
	setAttr ".stringOptions[13].value" -type "string" "64";
	setAttr ".stringOptions[13].type" -type "string" "integer";
	setAttr ".stringOptions[14].name" -type "string" "irradiance particles";
	setAttr ".stringOptions[14].value" -type "string" "false";
	setAttr ".stringOptions[14].type" -type "string" "boolean";
	setAttr ".stringOptions[15].name" -type "string" "irradiance particles rays";
	setAttr ".stringOptions[15].value" -type "string" "256";
	setAttr ".stringOptions[15].type" -type "string" "integer";
	setAttr ".stringOptions[16].name" -type "string" "irradiance particles interpolate";
	setAttr ".stringOptions[16].value" -type "string" "1";
	setAttr ".stringOptions[16].type" -type "string" "integer";
	setAttr ".stringOptions[17].name" -type "string" "irradiance particles interppoints";
	setAttr ".stringOptions[17].value" -type "string" "64";
	setAttr ".stringOptions[17].type" -type "string" "integer";
	setAttr ".stringOptions[18].name" -type "string" "irradiance particles indirect passes";
	setAttr ".stringOptions[18].value" -type "string" "0";
	setAttr ".stringOptions[18].type" -type "string" "integer";
	setAttr ".stringOptions[19].name" -type "string" "irradiance particles scale";
	setAttr ".stringOptions[19].value" -type "string" "1.0";
	setAttr ".stringOptions[19].type" -type "string" "scalar";
	setAttr ".stringOptions[20].name" -type "string" "irradiance particles env";
	setAttr ".stringOptions[20].value" -type "string" "true";
	setAttr ".stringOptions[20].type" -type "string" "boolean";
	setAttr ".stringOptions[21].name" -type "string" "irradiance particles env rays";
	setAttr ".stringOptions[21].value" -type "string" "256";
	setAttr ".stringOptions[21].type" -type "string" "integer";
	setAttr ".stringOptions[22].name" -type "string" "irradiance particles env scale";
	setAttr ".stringOptions[22].value" -type "string" "1";
	setAttr ".stringOptions[22].type" -type "string" "integer";
	setAttr ".stringOptions[23].name" -type "string" "irradiance particles rebuild";
	setAttr ".stringOptions[23].value" -type "string" "true";
	setAttr ".stringOptions[23].type" -type "string" "boolean";
	setAttr ".stringOptions[24].name" -type "string" "irradiance particles file";
	setAttr ".stringOptions[24].value" -type "string" "";
	setAttr ".stringOptions[24].type" -type "string" "string";
	setAttr ".stringOptions[25].name" -type "string" "geom displace motion factor";
	setAttr ".stringOptions[25].value" -type "string" "1.0";
	setAttr ".stringOptions[25].type" -type "string" "scalar";
	setAttr ".stringOptions[26].name" -type "string" "contrast all buffers";
	setAttr ".stringOptions[26].value" -type "string" "true";
	setAttr ".stringOptions[26].type" -type "string" "boolean";
	setAttr ".stringOptions[27].name" -type "string" "finalgather normal tolerance";
	setAttr ".stringOptions[27].value" -type "string" "25.842";
	setAttr ".stringOptions[27].type" -type "string" "scalar";
	setAttr ".stringOptions[28].name" -type "string" "trace camera clip";
	setAttr ".stringOptions[28].value" -type "string" "false";
	setAttr ".stringOptions[28].type" -type "string" "boolean";
	setAttr ".stringOptions[29].name" -type "string" "unified sampling";
	setAttr ".stringOptions[29].value" -type "string" "true";
	setAttr ".stringOptions[29].type" -type "string" "boolean";
	setAttr ".stringOptions[30].name" -type "string" "samples quality";
	setAttr ".stringOptions[30].value" -type "string" "0.5 0.5 0.5 0.5";
	setAttr ".stringOptions[30].type" -type "string" "color";
	setAttr ".stringOptions[31].name" -type "string" "samples min";
	setAttr ".stringOptions[31].value" -type "string" "1.0";
	setAttr ".stringOptions[31].type" -type "string" "scalar";
	setAttr ".stringOptions[32].name" -type "string" "samples max";
	setAttr ".stringOptions[32].value" -type "string" "100.0";
	setAttr ".stringOptions[32].type" -type "string" "scalar";
	setAttr ".stringOptions[33].name" -type "string" "samples error cutoff";
	setAttr ".stringOptions[33].value" -type "string" "0.0 0.0 0.0 0.0";
	setAttr ".stringOptions[33].type" -type "string" "color";
	setAttr ".stringOptions[34].name" -type "string" "samples per object";
	setAttr ".stringOptions[34].value" -type "string" "false";
	setAttr ".stringOptions[34].type" -type "string" "boolean";
	setAttr ".stringOptions[35].name" -type "string" "progressive";
	setAttr ".stringOptions[35].value" -type "string" "false";
	setAttr ".stringOptions[35].type" -type "string" "boolean";
	setAttr ".stringOptions[36].name" -type "string" "progressive max time";
	setAttr ".stringOptions[36].value" -type "string" "0";
	setAttr ".stringOptions[36].type" -type "string" "integer";
	setAttr ".stringOptions[37].name" -type "string" "progressive subsampling size";
	setAttr ".stringOptions[37].value" -type "string" "1";
	setAttr ".stringOptions[37].type" -type "string" "integer";
	setAttr ".stringOptions[38].name" -type "string" "iray";
	setAttr ".stringOptions[38].value" -type "string" "false";
	setAttr ".stringOptions[38].type" -type "string" "boolean";
	setAttr ".stringOptions[39].name" -type "string" "light relative scale";
	setAttr ".stringOptions[39].value" -type "string" "0.31831";
	setAttr ".stringOptions[39].type" -type "string" "scalar";
	setAttr ".stringOptions[40].name" -type "string" "trace camera motion vectors";
	setAttr ".stringOptions[40].value" -type "string" "false";
	setAttr ".stringOptions[40].type" -type "string" "boolean";
	setAttr ".stringOptions[41].name" -type "string" "ray differentials";
	setAttr ".stringOptions[41].value" -type "string" "true";
	setAttr ".stringOptions[41].type" -type "string" "boolean";
	setAttr ".stringOptions[42].name" -type "string" "environment lighting mode";
	setAttr ".stringOptions[42].value" -type "string" "off";
	setAttr ".stringOptions[42].type" -type "string" "string";
	setAttr ".stringOptions[43].name" -type "string" "environment lighting quality";
	setAttr ".stringOptions[43].value" -type "string" "0.167";
	setAttr ".stringOptions[43].type" -type "string" "scalar";
	setAttr ".stringOptions[44].name" -type "string" "environment lighting shadow";
	setAttr ".stringOptions[44].value" -type "string" "transparent";
	setAttr ".stringOptions[44].type" -type "string" "string";
createNode mentalrayFramebuffer -s -n "miDefaultFramebuffer";
createNode lightLinker -s -n "lightLinker1";
	setAttr -s 801 ".lnk";
	setAttr -s 801 ".slnk";
createNode displayLayerManager -n "layerManager";
	setAttr ".cdl" 2;
	setAttr -s 3 ".dli[1:2]"  1 2;
	setAttr -s 3 ".dli";
createNode displayLayer -n "defaultLayer";
createNode renderLayerManager -n "renderLayerManager";
createNode renderLayer -n "defaultRenderLayer";
	setAttr ".g" yes;
createNode script -n "uiConfigurationScriptNode";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"top\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n"
		+ "                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n"
		+ "                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n"
		+ "                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n            modelEditor -e \n                -pluginObjects \"gpuCacheDisplayFilter\" 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n"
		+ "            -rendererName \"base_OpenGL_Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n"
		+ "            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"side\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n"
		+ "                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n"
		+ "                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n            modelEditor -e \n"
		+ "                -pluginObjects \"gpuCacheDisplayFilter\" 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n"
		+ "            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"base_OpenGL_Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n"
		+ "            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"front\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n"
		+ "                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n"
		+ "                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n"
		+ "                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n            modelEditor -e \n                -pluginObjects \"gpuCacheDisplayFilter\" 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n"
		+ "            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"base_OpenGL_Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n"
		+ "            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n"
		+ "            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 1\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n"
		+ "                -useDefaultMaterial 1\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 1\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n"
		+ "                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n"
		+ "                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n            modelEditor -e \n                -pluginObjects \"gpuCacheDisplayFilter\" 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n"
		+ "            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 1\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 1\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n"
		+ "            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n"
		+ "            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            outlinerEditor -e \n"
		+ "                -showShapes 0\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 0\n                -showConnected 0\n                -showAnimCurvesOnly 0\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 1\n                -showAssets 1\n                -showContainedOnly 1\n                -showPublishedAsConnected 0\n                -showContainerContents 1\n                -ignoreDagHierarchy 0\n                -expandConnections 0\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 0\n                -highlightActive 1\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"defaultSetFilter\" \n"
		+ "                -showSetMembers 1\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 0\n                -ignoreHiddenAttribute 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n"
		+ "            -showShapes 0\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n"
		+ "            -directSelect 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"graphEditor\" -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n"
		+ "            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n"
		+ "                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n"
		+ "                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -classicMode 1\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n"
		+ "                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n"
		+ "                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n"
		+ "                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -classicMode 1\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dopeSheetPanel\" -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n"
		+ "            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n"
		+ "                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n"
		+ "                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n"
		+ "                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n"
		+ "                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"clipEditorPanel\" -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n"
		+ "                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"sequenceEditorPanel\" (localizedPanelLabel(\"Camera Sequencer\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"sequenceEditorPanel\" -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n"
		+ "                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperGraphPanel\" -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n"
		+ "                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n"
		+ "                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperShadePanel\" -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"visorPanel\" -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"nodeEditorPanel\" (localizedPanelLabel(\"Node Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"nodeEditorPanel\" -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n"
		+ "                -defaultPinnedState 0\n                -ignoreAssets 1\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -keyReleaseCommand \"nodeEdKeyReleaseCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                $editorName;\n\t\t\tif (`objExists nodeEditorPanel1Info`) nodeEditor -e -restoreInfo nodeEditorPanel1Info $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n"
		+ "            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -defaultPinnedState 0\n                -ignoreAssets 1\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -keyReleaseCommand \"nodeEdKeyReleaseCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                $editorName;\n\t\t\tif (`objExists nodeEditorPanel1Info`) nodeEditor -e -restoreInfo nodeEditorPanel1Info $editorName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"createNodePanel\" (localizedPanelLabel(\"Create Node\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"createNodePanel\" -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Texture Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"polyTexturePlacementPanel\" -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"renderWindowPanel\" -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"blendShapePanel\" (localizedPanelLabel(\"Blend Shape\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\tblendShapePanel -unParent -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tblendShapePanel -edit -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynRelEdPanel\" -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"relationshipPanel\" -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"referenceEditorPanel\" -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"componentEditorPanel\" -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynPaintScriptedPanelType\" -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"scriptEditorPanel\" -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\tif ($useSceneConfig) {\n\t\tscriptedPanel -e -to $panelName;\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-defaultImage \"\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"vertical2\\\" -ps 1 31 100 -ps 2 69 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Outliner\")) \n\t\t\t\t\t\"outlinerPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\\\"Outliner\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\noutlinerEditor -e \\n    -showShapes 0\\n    -showReferenceNodes 0\\n    -showReferenceMembers 0\\n    -showAttributes 0\\n    -showConnected 0\\n    -showAnimCurvesOnly 0\\n    -showMuteInfo 0\\n    -organizeByLayer 1\\n    -showAnimLayerWeight 1\\n    -autoExpandLayers 1\\n    -autoExpand 0\\n    -showDagOnly 1\\n    -showAssets 1\\n    -showContainedOnly 1\\n    -showPublishedAsConnected 0\\n    -showContainerContents 1\\n    -ignoreDagHierarchy 0\\n    -expandConnections 0\\n    -showUpstreamCurves 1\\n    -showUnitlessCurves 1\\n    -showCompounds 1\\n    -showLeafs 1\\n    -showNumericAttrsOnly 0\\n    -highlightActive 1\\n    -autoSelectNewObjects 0\\n    -doNotSelectNewObjects 0\\n    -dropIsParent 1\\n    -transmitFilters 0\\n    -setFilter \\\"defaultSetFilter\\\" \\n    -showSetMembers 1\\n    -allowMultiSelection 1\\n    -alwaysToggleSelect 0\\n    -directSelect 0\\n    -displayMode \\\"DAG\\\" \\n    -expandObjects 0\\n    -setsIgnoreFilters 1\\n    -containersIgnoreFilters 0\\n    -editAttrName 0\\n    -showAttrValues 0\\n    -highlightSecondary 0\\n    -showUVAttrsOnly 0\\n    -showTextureNodesOnly 0\\n    -attrAlphaOrder \\\"default\\\" \\n    -animLayerFilterOptions \\\"allAffecting\\\" \\n    -sortOrder \\\"none\\\" \\n    -longNames 0\\n    -niceNames 1\\n    -showNamespace 1\\n    -showPinIcons 0\\n    -mapMotionTrails 0\\n    -ignoreHiddenAttribute 0\\n    $editorName\"\n"
		+ "\t\t\t\t\t\"outlinerPanel -edit -l (localizedPanelLabel(\\\"Outliner\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\noutlinerEditor -e \\n    -showShapes 0\\n    -showReferenceNodes 0\\n    -showReferenceMembers 0\\n    -showAttributes 0\\n    -showConnected 0\\n    -showAnimCurvesOnly 0\\n    -showMuteInfo 0\\n    -organizeByLayer 1\\n    -showAnimLayerWeight 1\\n    -autoExpandLayers 1\\n    -autoExpand 0\\n    -showDagOnly 1\\n    -showAssets 1\\n    -showContainedOnly 1\\n    -showPublishedAsConnected 0\\n    -showContainerContents 1\\n    -ignoreDagHierarchy 0\\n    -expandConnections 0\\n    -showUpstreamCurves 1\\n    -showUnitlessCurves 1\\n    -showCompounds 1\\n    -showLeafs 1\\n    -showNumericAttrsOnly 0\\n    -highlightActive 1\\n    -autoSelectNewObjects 0\\n    -doNotSelectNewObjects 0\\n    -dropIsParent 1\\n    -transmitFilters 0\\n    -setFilter \\\"defaultSetFilter\\\" \\n    -showSetMembers 1\\n    -allowMultiSelection 1\\n    -alwaysToggleSelect 0\\n    -directSelect 0\\n    -displayMode \\\"DAG\\\" \\n    -expandObjects 0\\n    -setsIgnoreFilters 1\\n    -containersIgnoreFilters 0\\n    -editAttrName 0\\n    -showAttrValues 0\\n    -highlightSecondary 0\\n    -showUVAttrsOnly 0\\n    -showTextureNodesOnly 0\\n    -attrAlphaOrder \\\"default\\\" \\n    -animLayerFilterOptions \\\"allAffecting\\\" \\n    -sortOrder \\\"none\\\" \\n    -longNames 0\\n    -niceNames 1\\n    -showNamespace 1\\n    -showPinIcons 0\\n    -mapMotionTrails 0\\n    -ignoreHiddenAttribute 0\\n    $editorName\"\n"
		+ "\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 1\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 1\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 1\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 1\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 1\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 1\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        setFocus `paneLayout -q -p1 $gMainPane`;\n        sceneUIReplacement -deleteRemaining;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 5 -size 12 -divisions 5 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 24 -ast 1 -aet 48 ";
	setAttr ".st" 6;
createNode shadingEngine -n "Gotham_GroundFloor_Shop_OlddB5_512_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo1";
createNode file -n "Gotham_GroundFloor_Shop_OlddB5_512_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_02_D.tga";
createNode place2dTexture -n "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1";
createNode file -n "Gotham_GroundFloor_Shop_OlddB5_512_file2";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_N.tga";
createNode place2dTexture -n "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2";
createNode bump2d -n "Gotham_GroundFloor_Shop_OlddB5_512_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode phong -n "Gotham_GroundFloor_Shop_OlddB5_512_phong1";
createNode file -n "Gotham_GroundFloor_Shop_OlddB5_512_file3";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_S.tga";
createNode place2dTexture -n "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3";
createNode hyperGraphInfo -n "Gotham_GroundFloor_Shop_OlddB5_512_nodeEditorPanel1Info";
createNode hyperView -n "Gotham_GroundFloor_Shop_OlddB5_512_hyperView1";
	setAttr ".vl" -type "double2" -622.82040259566259 33.402662687684803 ;
	setAttr ".vh" -type "double2" 142.70380841117435 220.53080315602273 ;
	setAttr ".dag" no;
createNode hyperLayout -n "Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 15 ".hyp";
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".hyp[5].nvs" 1920;
	setAttr ".hyp[6].nvs" 1920;
	setAttr ".hyp[7].nvs" 1920;
	setAttr ".hyp[8].nvs" 1920;
	setAttr ".hyp[9].nvs" 1920;
	setAttr ".hyp[10].nvs" 1920;
	setAttr ".hyp[11].nvs" 1920;
	setAttr ".hyp[12].nvs" 1920;
	setAttr ".hyp[13].nvs" 1920;
	setAttr ".hyp[14].nvs" 1920;
	setAttr ".anf" yes;
createNode shadingEngine -n "Gotham_GroundFloor_Shop_OlddB5_512_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo2";
createNode shadingEngine -n "Gotham_GroundFloor_Shop_OlddB5_512_material_2";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo3";
createNode shadingEngine -n "Gotham_GroundFloor_Shop_OlddB5_512_material_3";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo4";
createNode shadingEngine -n "Gotham_GroundFloor_Shop_OlddB5_512_material_4";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo5";
createNode shadingEngine -n "Gotham_GroundFloor_Shop_OlddB5_512_material_5";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo6";
createNode file -n "Gotham_GroundFloor_Shop_OlddB5_512_file4";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_D.tga";
createNode place2dTexture -n "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4";
createNode file -n "Gotham_GroundFloor_Shop_OlddB5_512_file5";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_N.tga";
createNode place2dTexture -n "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5";
createNode bump2d -n "Gotham_GroundFloor_Shop_OlddB5_512_bump2d2";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode blinn -n "Gotham_GroundFloor_Shop_OlddB5_512_blinn1";
createNode shadingEngine -n "Gotham_GroundFloor_Shop_OlddB5_512_blinn1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo7";
createNode file -n "Gotham_GroundFloor_Shop_OlddB5_512_file6";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_D.tga";
createNode place2dTexture -n "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6";
createNode phong -n "Gotham_GroundFloor_Shop_OlddB5_512_phong2";
createNode file -n "Gotham_GroundFloor_Shop_OlddB5_512_file7";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_E.tga";
createNode place2dTexture -n "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7";
createNode file -n "file8";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_N.tga";
createNode place2dTexture -n "place2dTexture8";
createNode bump2d -n "bump2d3";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode shadingEngine -n "material_6";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo8";
createNode shadingEngine -n "material_7";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo9";
createNode shadingEngine -n "material_8";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo10";
createNode shadingEngine -n "material_9";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo11";
createNode lambert -n "material_0_lambert";
createNode shadingEngine -n "material_10";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo12";
createNode hyperLayout -n "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 108 ".hyp";
createNode shadingEngine -n "Gotham_Groundfloor_Shop_OldB2_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Groundfloor_Shop_OldB2_materialInfo1";
createNode file -n "Gotham_Groundfloor_Shop_OldB2_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_02_D.tga";
createNode place2dTexture -n "Gotham_Groundfloor_Shop_OldB2_place2dTexture1";
createNode file -n "Gotham_Groundfloor_Shop_OldB2_file2";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_N.tga";
createNode place2dTexture -n "Gotham_Groundfloor_Shop_OldB2_place2dTexture2";
createNode bump2d -n "Gotham_Groundfloor_Shop_OldB2_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode phong -n "Gotham_Groundfloor_Shop_OldB2_phong1";
createNode file -n "Gotham_Groundfloor_Shop_OldB2_file3";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_S.tga";
createNode place2dTexture -n "Gotham_Groundfloor_Shop_OldB2_place2dTexture3";
createNode hyperGraphInfo -n "Gotham_Groundfloor_Shop_OldB2_nodeEditorPanel1Info";
createNode hyperView -n "Gotham_Groundfloor_Shop_OldB2_hyperView1";
	setAttr ".vl" -type "double2" -622.82040259566259 33.402662687684803 ;
	setAttr ".vh" -type "double2" 142.70380841117435 220.53080315602273 ;
	setAttr ".dag" no;
createNode hyperLayout -n "Gotham_Groundfloor_Shop_OldB2_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 15 ".hyp";
	setAttr ".hyp[0].x" -498.92855834960937;
	setAttr ".hyp[0].y" 102.38095092773437;
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].x" -301.78570556640625;
	setAttr ".hyp[1].y" 125.59523773193359;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].x" -498.92855834960937;
	setAttr ".hyp[2].y" 173.80952453613281;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].x" -498.92855834960937;
	setAttr ".hyp[3].y" 252.38095092773438;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].x" -301.78570556640625;
	setAttr ".hyp[4].y" 220.23809814453125;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".hyp[5].x" -104.64286041259766;
	setAttr ".hyp[5].y" 141.66667175292969;
	setAttr ".hyp[5].nvs" 1920;
	setAttr ".hyp[6].x" -104.64286041259766;
	setAttr ".hyp[6].y" 220.23809814453125;
	setAttr ".hyp[6].nvs" 1920;
	setAttr ".hyp[7].x" 92.5;
	setAttr ".hyp[7].y" 102.38095092773437;
	setAttr ".hyp[7].nvs" 1920;
	setAttr ".hyp[8].x" -301.78570556640625;
	setAttr ".hyp[8].y" 125.59523773193359;
	setAttr ".hyp[8].nvs" 1920;
	setAttr ".hyp[9].x" -301.78570556640625;
	setAttr ".hyp[9].y" 125.59523773193359;
	setAttr ".hyp[9].nvs" 1920;
	setAttr ".hyp[10].x" 92.5;
	setAttr ".hyp[10].y" 173.80952453613281;
	setAttr ".hyp[10].nvs" 1920;
	setAttr ".hyp[11].x" -301.78570556640625;
	setAttr ".hyp[11].y" 125.59523773193359;
	setAttr ".hyp[11].nvs" 1920;
	setAttr ".hyp[12].x" -301.78570556640625;
	setAttr ".hyp[12].y" 125.59523773193359;
	setAttr ".hyp[12].nvs" 1920;
	setAttr ".hyp[13].x" -301.78570556640625;
	setAttr ".hyp[13].y" 125.59523773193359;
	setAttr ".hyp[13].nvs" 1920;
	setAttr ".hyp[14].x" 289.64285278320313;
	setAttr ".hyp[14].y" 220.23809814453125;
	setAttr ".hyp[14].nvs" 1920;
	setAttr ".anf" yes;
createNode shadingEngine -n "Gotham_Groundfloor_Shop_OldB2_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Groundfloor_Shop_OldB2_materialInfo2";
createNode shadingEngine -n "Gotham_Groundfloor_Shop_OldB2_material_2";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Groundfloor_Shop_OldB2_materialInfo3";
createNode shadingEngine -n "Gotham_Groundfloor_Shop_OldB2_material_3";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Groundfloor_Shop_OldB2_materialInfo4";
createNode shadingEngine -n "Gotham_Groundfloor_Shop_OldB2_material_4";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Groundfloor_Shop_OldB2_materialInfo5";
createNode shadingEngine -n "Gotham_Groundfloor_Shop_OldB2_material_5";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Groundfloor_Shop_OldB2_materialInfo6";
createNode file -n "Gotham_Groundfloor_Shop_OldB2_file4";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_D.tga";
createNode place2dTexture -n "Gotham_Groundfloor_Shop_OldB2_place2dTexture4";
createNode file -n "Gotham_Groundfloor_Shop_OldB2_file5";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_N.tga";
createNode place2dTexture -n "Gotham_Groundfloor_Shop_OldB2_place2dTexture5";
createNode bump2d -n "Gotham_Groundfloor_Shop_OldB2_bump2d2";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode blinn -n "Gotham_Groundfloor_Shop_OldB2_blinn1";
createNode shadingEngine -n "Gotham_Groundfloor_Shop_OldB2_blinn1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Groundfloor_Shop_OldB2_materialInfo7";
createNode file -n "Gotham_Groundfloor_Shop_OldB2_file6";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_D.tga";
createNode place2dTexture -n "Gotham_Groundfloor_Shop_OldB2_place2dTexture6";
createNode phong -n "Gotham_Groundfloor_Shop_OldB2_phong2";
createNode file -n "Gotham_Groundfloor_Shop_OldB2_file7";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_E.tga";
createNode place2dTexture -n "Gotham_Groundfloor_Shop_OldB2_place2dTexture7";
createNode file -n "Gotham_Groundfloor_Shop_OldB2_file8";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_N.tga";
createNode place2dTexture -n "Gotham_Groundfloor_Shop_OldB2_place2dTexture8";
createNode bump2d -n "Gotham_Groundfloor_Shop_OldB2_bump2d3";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode hyperLayout -n "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 86 ".hyp";
createNode shadingEngine -n "OZ_Gotham_GroundFloor_Shop_OldA_03_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo1";
createNode file -n "OZ_Gotham_GroundFloor_Shop_OldA_03_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/OZ_Gotham_Groundfloor_Shop_Old_D.tga";
createNode place2dTexture -n "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1";
createNode file -n "OZ_Gotham_GroundFloor_Shop_OldA_03_file2";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/OZ_Gotham_Groundfloor_Shop_Old_N.tga";
createNode place2dTexture -n "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2";
createNode bump2d -n "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode phong -n "OZ_Gotham_GroundFloor_Shop_OldA_03_phong1";
createNode file -n "OZ_Gotham_GroundFloor_Shop_OldA_03_file3";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_S.tga";
createNode place2dTexture -n "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3";
createNode hyperGraphInfo -n "OZ_Gotham_GroundFloor_Shop_OldA_03_nodeEditorPanel1Info";
createNode hyperView -n "OZ_Gotham_GroundFloor_Shop_OldA_03_hyperView1";
	setAttr ".vl" -type "double2" -700.47747623748171 13.960777963701666 ;
	setAttr ".vh" -type "double2" 219.1457642577445 238.75757008475694 ;
	setAttr ".dag" no;
createNode hyperLayout -n "OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 15 ".hyp";
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".hyp[5].nvs" 1920;
	setAttr ".hyp[6].nvs" 1920;
	setAttr ".hyp[7].nvs" 1920;
	setAttr ".hyp[8].nvs" 1920;
	setAttr ".hyp[9].nvs" 1920;
	setAttr ".hyp[10].nvs" 1920;
	setAttr ".hyp[11].nvs" 1920;
	setAttr ".hyp[12].nvs" 1920;
	setAttr ".hyp[13].nvs" 1920;
	setAttr ".hyp[14].nvs" 1920;
	setAttr ".anf" yes;
createNode shadingEngine -n "OZ_Gotham_GroundFloor_Shop_OldA_03_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo2";
createNode shadingEngine -n "OZ_Gotham_GroundFloor_Shop_OldA_03_material_2";
	setAttr ".ro" yes;
createNode materialInfo -n "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo3";
createNode shadingEngine -n "OZ_Gotham_GroundFloor_Shop_OldA_03_material_3";
	setAttr ".ro" yes;
createNode materialInfo -n "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo4";
createNode shadingEngine -n "OZ_Gotham_GroundFloor_Shop_OldA_03_material_4";
	setAttr ".ro" yes;
createNode materialInfo -n "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo5";
createNode shadingEngine -n "OZ_Gotham_GroundFloor_Shop_OldA_03_material_5";
	setAttr ".ro" yes;
createNode materialInfo -n "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo6";
createNode file -n "OZ_Gotham_GroundFloor_Shop_OldA_03_file4";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_D.tga";
createNode place2dTexture -n "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4";
createNode file -n "OZ_Gotham_GroundFloor_Shop_OldA_03_file5";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_N.tga";
createNode place2dTexture -n "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5";
createNode bump2d -n "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d2";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode blinn -n "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1";
createNode shadingEngine -n "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo7";
createNode file -n "OZ_Gotham_GroundFloor_Shop_OldA_03_file6";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_D.tga";
createNode place2dTexture -n "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6";
createNode phong -n "OZ_Gotham_GroundFloor_Shop_OldA_03_phong2";
createNode file -n "OZ_Gotham_GroundFloor_Shop_OldA_03_file7";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_E.tga";
createNode place2dTexture -n "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7";
createNode file -n "OZ_Gotham_GroundFloor_Shop_OldA_03_file8";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_N.tga";
createNode place2dTexture -n "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8";
createNode bump2d -n "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d3";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode shadingEngine -n "OZ_Gotham_GroundFloor_Shop_OldA_03_material_6";
	setAttr ".ro" yes;
createNode materialInfo -n "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo8";
createNode shadingEngine -n "OZ_Gotham_GroundFloor_Shop_OldA_03_material_7";
	setAttr ".ro" yes;
createNode materialInfo -n "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo9";
createNode shadingEngine -n "OZ_Gotham_GroundFloor_Shop_OldA_03_material_8";
	setAttr ".ro" yes;
createNode materialInfo -n "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo10";
createNode shadingEngine -n "OZ_Gotham_GroundFloor_Shop_OldA_03_material_9";
	setAttr ".ro" yes;
createNode materialInfo -n "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo11";
createNode shadingEngine -n "OZ_Gotham_GroundFloor_Shop_OldA_03_material_10";
	setAttr ".ro" yes;
createNode materialInfo -n "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo12";
createNode shadingEngine -n "material_11";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo13";
createNode shadingEngine -n "material_12";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo14";
createNode shadingEngine -n "material_13";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo15";
createNode hyperLayout -n "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 118 ".hyp";
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo1";
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo2";
createNode lambert -n "material_0_lambert2";
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_2";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo3";
createNode file -n "Gotham_ARCH_Classic_BigWinx2_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Gotham_ARCH_Classic_Fence_d.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_BigWinx2_place2dTexture1";
createNode file -n "Gotham_ARCH_Classic_BigWinx2_file2";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Gotham_ARCH_Classic_Fence_N.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_BigWinx2_place2dTexture2";
createNode bump2d -n "Gotham_ARCH_Classic_BigWinx2_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_3";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo4";
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_4";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo5";
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_5";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo6";
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_6";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo7";
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_7";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo8";
createNode file -n "Gotham_ARCH_Classic_BigWinx2_file3";
createNode place2dTexture -n "Gotham_ARCH_Classic_BigWinx2_place2dTexture3";
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_8";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo9";
createNode file -n "Gotham_ARCH_Classic_BigWinx2_file4";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_D.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_BigWinx2_place2dTexture4";
createNode file -n "Gotham_ARCH_Classic_BigWinx2_file5";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_N_New.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_BigWinx2_place2dTexture5";
createNode bump2d -n "Gotham_ARCH_Classic_BigWinx2_bump2d2";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 2.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_9";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo10";
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_10";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo11";
createNode file -n "Gotham_ARCH_Classic_BigWinx2_file6";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main02_D.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_BigWinx2_place2dTexture6";
createNode file -n "Gotham_ARCH_Classic_BigWinx2_file7";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_N_New.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_BigWinx2_place2dTexture7";
createNode bump2d -n "Gotham_ARCH_Classic_BigWinx2_bump2d3";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode file -n "Gotham_ARCH_Classic_BigWinx2_file8";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_D.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_BigWinx2_place2dTexture8";
createNode file -n "file9";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_N.tga";
createNode place2dTexture -n "place2dTexture9";
createNode bump2d -n "bump2d4";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode hyperGraphInfo -n "Gotham_ARCH_Classic_BigWinx2_nodeEditorPanel1Info";
createNode hyperView -n "Gotham_ARCH_Classic_BigWinx2_hyperView1";
	setAttr ".vl" -type "double2" -587.25454701690671 -81.703512257011226 ;
	setAttr ".vh" -type "double2" 325.53946266031306 314.23570752505555 ;
	setAttr ".dag" no;
createNode hyperLayout -n "Gotham_ARCH_Classic_BigWinx2_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 10 ".hyp";
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".hyp[5].nvs" 1920;
	setAttr ".hyp[6].nvs" 1920;
	setAttr ".hyp[7].nvs" 1920;
	setAttr ".hyp[8].nvs" 1920;
	setAttr ".hyp[9].nvs" 1920;
	setAttr ".anf" yes;
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_11";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo12";
createNode phong -n "Gotham_ARCH_Classic_BigWinx2_phong1";
createNode file -n "file10";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main02_S.tga";
createNode place2dTexture -n "place2dTexture10";
createNode blinn -n "Gotham_ARCH_Classic_BigWinx2_blinn1";
createNode file -n "file11";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_S.tga";
createNode place2dTexture -n "place2dTexture11";
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_12";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo13";
createNode shadingEngine -n "Gotham_ARCH_Classic_BigWinx2_material_13";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo14";
createNode shadingEngine -n "material_14";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_BigWinx2_materialInfo15";
createNode shadingEngine -n "material_15";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo16";
createNode shadingEngine -n "material_16";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo17";
createNode hyperLayout -n "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 140 ".hyp";
createNode hyperLayout -n "hyperLayout2";
	setAttr ".ihi" 0;
	setAttr -s 74 ".hyp";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo1";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo2";
createNode lambert -n "Gotham_ARCH_Classic_WinBCorner_material_0_lambert2";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_2";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo3";
createNode file -n "Gotham_ARCH_Classic_WinBCorner_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Gotham_ARCH_Classic_Fence_d.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_WinBCorner_place2dTexture1";
createNode file -n "Gotham_ARCH_Classic_WinBCorner_file2";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Gotham_ARCH_Classic_Fence_N.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_WinBCorner_place2dTexture2";
createNode bump2d -n "Gotham_ARCH_Classic_WinBCorner_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_3";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo4";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_4";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo5";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_5";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo6";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_6";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo7";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_7";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo8";
createNode file -n "Gotham_ARCH_Classic_WinBCorner_file3";
createNode place2dTexture -n "Gotham_ARCH_Classic_WinBCorner_place2dTexture3";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_8";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo9";
createNode file -n "Gotham_ARCH_Classic_WinBCorner_file4";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_D.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_WinBCorner_place2dTexture4";
createNode file -n "Gotham_ARCH_Classic_WinBCorner_file5";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_N_New.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_WinBCorner_place2dTexture5";
createNode bump2d -n "Gotham_ARCH_Classic_WinBCorner_bump2d2";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 2.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_9";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo10";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_10";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo11";
createNode file -n "Gotham_ARCH_Classic_WinBCorner_file6";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main02_D.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_WinBCorner_place2dTexture6";
createNode file -n "Gotham_ARCH_Classic_WinBCorner_file7";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_N_New.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_WinBCorner_place2dTexture7";
createNode bump2d -n "Gotham_ARCH_Classic_WinBCorner_bump2d3";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode file -n "Gotham_ARCH_Classic_WinBCorner_file8";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_D.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_WinBCorner_place2dTexture8";
createNode file -n "Gotham_ARCH_Classic_WinBCorner_file9";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_N.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_WinBCorner_place2dTexture9";
createNode bump2d -n "Gotham_ARCH_Classic_WinBCorner_bump2d4";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode hyperGraphInfo -n "Gotham_ARCH_Classic_WinBCorner_nodeEditorPanel1Info";
createNode hyperView -n "Gotham_ARCH_Classic_WinBCorner_hyperView1";
	setAttr ".vl" -type "double2" -599.41678150790187 -55.844275857488256 ;
	setAttr ".vh" -type "double2" 336.07902984307839 289.24973455198455 ;
	setAttr ".dag" no;
createNode hyperLayout -n "Gotham_ARCH_Classic_WinBCorner_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 10 ".hyp";
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".hyp[5].nvs" 1920;
	setAttr ".hyp[6].nvs" 1920;
	setAttr ".hyp[7].nvs" 1920;
	setAttr ".hyp[8].nvs" 1920;
	setAttr ".hyp[9].nvs" 1920;
	setAttr ".anf" yes;
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_11";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo12";
createNode phong -n "Gotham_ARCH_Classic_WinBCorner_phong1";
createNode file -n "Gotham_ARCH_Classic_WinBCorner_file10";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main02_S.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_WinBCorner_place2dTexture10";
createNode blinn -n "Gotham_ARCH_Classic_WinBCorner_blinn1";
createNode file -n "Gotham_ARCH_Classic_WinBCorner_file11";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_S.tga";
createNode place2dTexture -n "Gotham_ARCH_Classic_WinBCorner_place2dTexture11";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_12";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo13";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_13";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo14";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_14";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo15";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_15";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo16";
createNode shadingEngine -n "Gotham_ARCH_Classic_WinBCorner_material_16";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_ARCH_Classic_WinBCorner_materialInfo17";
createNode shadingEngine -n "material_17";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo18";
createNode shadingEngine -n "material_18";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo19";
createNode shadingEngine -n "material_19";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo20";
createNode shadingEngine -n "material_20";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo21";
createNode shadingEngine -n "material_21";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo22";
createNode shadingEngine -n "material_22";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo23";
createNode shadingEngine -n "material_23";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo24";
createNode shadingEngine -n "material_24";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo25";
createNode shadingEngine -n "material_25";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo26";
createNode shadingEngine -n "material_26";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo27";
createNode shadingEngine -n "material_27";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo28";
createNode shadingEngine -n "material_28";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo29";
createNode shadingEngine -n "material_29";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo30";
createNode shadingEngine -n "material_30";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo31";
createNode shadingEngine -n "material_31";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo32";
createNode shadingEngine -n "material_32";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo33";
createNode shadingEngine -n "material_33";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo34";
createNode shadingEngine -n "material_34";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo35";
createNode shadingEngine -n "material_35";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo36";
createNode shadingEngine -n "material_36";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo37";
createNode shadingEngine -n "material_37";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo38";
createNode shadingEngine -n "material_38";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo39";
createNode shadingEngine -n "material_39";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo40";
createNode lambert -n "Gotham_ARCH_Classic_WinBCorner_material_0_lambert";
createNode shadingEngine -n "material_40";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo41";
createNode hyperLayout -n "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 240 ".hyp";
createNode hyperLayout -n "hyperLayout3";
	setAttr ".ihi" 0;
	setAttr -s 125 ".hyp";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo1";
createNode file -n "Gotham_Fences_Mall768_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_D.tga";
createNode place2dTexture -n "Gotham_Fences_Mall768_place2dTexture1";
createNode file -n "Gotham_Fences_Mall768_file2";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_O.tga";
createNode place2dTexture -n "Gotham_Fences_Mall768_place2dTexture2";
createNode file -n "Gotham_Fences_Mall768_file3";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_N.tga";
createNode place2dTexture -n "Gotham_Fences_Mall768_place2dTexture3";
createNode bump2d -n "Gotham_Fences_Mall768_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode phong -n "Gotham_Fences_Mall768_phong1";
createNode file -n "Gotham_Fences_Mall768_file4";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_O_SDF.tga";
createNode place2dTexture -n "Gotham_Fences_Mall768_place2dTexture4";
createNode hyperGraphInfo -n "Gotham_Fences_Mall768_nodeEditorPanel1Info";
createNode hyperView -n "Gotham_Fences_Mall768_hyperView1";
	setAttr ".vl" -type "double2" -598.80952380952385 73.809523809523824 ;
	setAttr ".vh" -type "double2" 265.47619047619048 220.23809523809527 ;
	setAttr ".dag" no;
createNode hyperLayout -n "Gotham_Fences_Mall768_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 10 ".hyp";
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".hyp[5].nvs" 1920;
	setAttr ".hyp[6].nvs" 1920;
	setAttr ".hyp[7].nvs" 1920;
	setAttr ".hyp[8].nvs" 1920;
	setAttr ".hyp[9].nvs" 1920;
	setAttr ".anf" yes;
createNode shadingEngine -n "Gotham_Fences_Mall768_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo2";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_2";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo3";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_3";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo4";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_4";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo5";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_5";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo6";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_6";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo7";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_7";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo8";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_8";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo9";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_9";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo10";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_10";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo11";
createNode file -n "Gotham_Fences_Mall768_file5";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_Mall_D.tga";
createNode place2dTexture -n "Gotham_Fences_Mall768_place2dTexture5";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_11";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo12";
createNode file -n "Gotham_Fences_Mall768_file6";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Textures/Gotham_Fences_FloodBarrier_D.tga";
createNode place2dTexture -n "Gotham_Fences_Mall768_place2dTexture6";
createNode bump2d -n "Gotham_Fences_Mall768_bump2d2";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 3.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode blinn -n "Gotham_Fences_Mall768_blinn1";
createNode shadingEngine -n "Gotham_Fences_Mall768_blinn1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo13";
createNode lambert -n "Gotham_Fences_Mall768_material_0_lambert";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_12";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo14";
createNode file -n "Gotham_Fences_Mall768_file7";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_Mall_D.tga";
createNode place2dTexture -n "Gotham_Fences_Mall768_place2dTexture7";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_13";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo15";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_14";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo16";
createNode shadingEngine -n "Gotham_Fences_Mall768_material_15";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_Mall768_materialInfo17";
createNode hyperLayout -n "AD_Gotham_Fences_Mall768_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 120 ".hyp";
createNode hyperLayout -n "hyperLayout4";
	setAttr ".ihi" 0;
	setAttr -s 64 ".hyp";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo1";
createNode file -n "Gotham_Fences_PoleSolid_128C_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_D.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_128C_place2dTexture1";
createNode file -n "Gotham_Fences_PoleSolid_128C_file2";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_O.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_128C_place2dTexture2";
createNode file -n "Gotham_Fences_PoleSolid_128C_file3";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_N.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_128C_place2dTexture3";
createNode bump2d -n "Gotham_Fences_PoleSolid_128C_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode phong -n "Gotham_Fences_PoleSolid_128C_phong1";
createNode file -n "Gotham_Fences_PoleSolid_128C_file4";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_O_SDF.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_128C_place2dTexture4";
createNode hyperGraphInfo -n "Gotham_Fences_PoleSolid_128C_nodeEditorPanel1Info";
createNode hyperView -n "Gotham_Fences_PoleSolid_128C_hyperView1";
	setAttr ".vl" -type "double2" -598.80952380952385 73.809523809523824 ;
	setAttr ".vh" -type "double2" 265.47619047619048 220.23809523809527 ;
	setAttr ".dag" no;
createNode hyperLayout -n "Gotham_Fences_PoleSolid_128C_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 10 ".hyp";
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".hyp[5].nvs" 1920;
	setAttr ".hyp[6].nvs" 1920;
	setAttr ".hyp[7].nvs" 1920;
	setAttr ".hyp[8].nvs" 1920;
	setAttr ".hyp[9].nvs" 1920;
	setAttr ".anf" yes;
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo2";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_2";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo3";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_3";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo4";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_4";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo5";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_5";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo6";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_6";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo7";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_7";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo8";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_8";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo9";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_9";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo10";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_10";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo11";
createNode file -n "Gotham_Fences_PoleSolid_128C_file5";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_Mall_D.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_128C_place2dTexture5";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_11";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo12";
createNode file -n "Gotham_Fences_PoleSolid_128C_file6";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Textures/Gotham_Fences_FloodBarrier_D.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_128C_place2dTexture6";
createNode bump2d -n "Gotham_Fences_PoleSolid_128C_bump2d2";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 3.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode blinn -n "Gotham_Fences_PoleSolid_128C_blinn1";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_blinn1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo13";
createNode lambert -n "Gotham_Fences_PoleSolid_128C_material_0_lambert";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_12";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo14";
createNode file -n "Gotham_Fences_PoleSolid_128C_file7";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_Mall_D.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_128C_place2dTexture7";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_13";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo15";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_14";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo16";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_15";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo17";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_16";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo18";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_17";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo19";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_18";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo20";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_19";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo21";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_20";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo22";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_128C_material_21";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_128C_materialInfo23";
createNode hyperLayout -n "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 144 ".hyp";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo1";
createNode file -n "Gotham_Fences_PoleSolid_512_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_D.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_512_place2dTexture1";
createNode file -n "Gotham_Fences_PoleSolid_512_file2";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_O.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_512_place2dTexture2";
createNode file -n "Gotham_Fences_PoleSolid_512_file3";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_N.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_512_place2dTexture3";
createNode bump2d -n "Gotham_Fences_PoleSolid_512_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode phong -n "Gotham_Fences_PoleSolid_512_phong1";
createNode file -n "Gotham_Fences_PoleSolid_512_file4";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_O_SDF.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_512_place2dTexture4";
createNode hyperGraphInfo -n "Gotham_Fences_PoleSolid_512_nodeEditorPanel1Info";
createNode hyperView -n "Gotham_Fences_PoleSolid_512_hyperView1";
	setAttr ".vl" -type "double2" -598.80952380952385 73.809523809523824 ;
	setAttr ".vh" -type "double2" 265.47619047619048 220.23809523809527 ;
	setAttr ".dag" no;
createNode hyperLayout -n "Gotham_Fences_PoleSolid_512_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 10 ".hyp";
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".hyp[5].nvs" 1920;
	setAttr ".hyp[6].nvs" 1920;
	setAttr ".hyp[7].nvs" 1920;
	setAttr ".hyp[8].nvs" 1920;
	setAttr ".hyp[9].nvs" 1920;
	setAttr ".anf" yes;
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo2";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_2";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo3";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_3";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo4";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_4";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo5";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_5";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo6";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_6";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo7";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_7";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo8";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_8";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo9";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_9";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo10";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_10";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo11";
createNode file -n "Gotham_Fences_PoleSolid_512_file5";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_Mall_D.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_512_place2dTexture5";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_11";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo12";
createNode file -n "Gotham_Fences_PoleSolid_512_file6";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Textures/Gotham_Fences_FloodBarrier_D.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_512_place2dTexture6";
createNode bump2d -n "Gotham_Fences_PoleSolid_512_bump2d2";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 3.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode blinn -n "Gotham_Fences_PoleSolid_512_blinn1";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_blinn1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo13";
createNode lambert -n "Gotham_Fences_PoleSolid_512_material_0_lambert";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_12";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo14";
createNode file -n "Gotham_Fences_PoleSolid_512_file7";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_Mall_D.tga";
createNode place2dTexture -n "Gotham_Fences_PoleSolid_512_place2dTexture7";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_13";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo15";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_14";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo16";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_15";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo17";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_16";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo18";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_17";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo19";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_18";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo20";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_19";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo21";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_20";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo22";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_21";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo23";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_22";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo24";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_23";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo25";
createNode lambert -n "Gotham_Fences_PoleSolid_512_material_0_lambert1";
createNode shadingEngine -n "Gotham_Fences_PoleSolid_512_material_24";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Fences_PoleSolid_512_materialInfo26";
createNode hyperLayout -n "AD_Gotham_Fences_PoleSolid_512_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 158 ".hyp";
createNode hyperLayout -n "hyperLayout5";
	setAttr ".ihi" 0;
	setAttr -s 83 ".hyp";
createNode lambert -n "ARCH_GCPD_EntranceRoof_04_material_0_lambert";
createNode shadingEngine -n "ARCH_GCPD_EntranceRoof_04_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "ARCH_GCPD_EntranceRoof_04_materialInfo1";
createNode file -n "ARCH_GCPD_EntranceRoof_04_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Roof_D.tga";
createNode place2dTexture -n "ARCH_GCPD_EntranceRoof_04_place2dTexture1";
createNode file -n "ARCH_GCPD_EntranceRoof_04_file2";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Roof_N.tga";
createNode place2dTexture -n "ARCH_GCPD_EntranceRoof_04_place2dTexture2";
createNode bump2d -n "ARCH_GCPD_EntranceRoof_04_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode hyperGraphInfo -n "ARCH_GCPD_EntranceRoof_04_nodeEditorPanel1Info";
createNode hyperView -n "ARCH_GCPD_EntranceRoof_04_hyperView1";
	setAttr ".vl" -type "double2" -598.80952380952385 -82.142857142857153 ;
	setAttr ".vh" -type "double2" 78.571428571428569 220.23809523809527 ;
	setAttr ".dag" no;
createNode hyperLayout -n "ARCH_GCPD_EntranceRoof_04_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 5 ".hyp";
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".anf" yes;
createNode lambert -n "ARCH_GCPD_EntranceRoof_04_material_0_lambert1";
createNode shadingEngine -n "ARCH_GCPD_EntranceRoof_04_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "ARCH_GCPD_EntranceRoof_04_materialInfo2";
createNode hyperLayout -n "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 36 ".hyp";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo1";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo2";
createNode lambert -n "Gotham_Arch_Classic_BigWiny2_material_0_lambert2";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_2";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo3";
createNode file -n "Gotham_Arch_Classic_BigWiny2_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Gotham_ARCH_Classic_Fence_d.tga";
createNode place2dTexture -n "Gotham_Arch_Classic_BigWiny2_place2dTexture1";
createNode file -n "Gotham_Arch_Classic_BigWiny2_file2";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Gotham_ARCH_Classic_Fence_N.tga";
createNode place2dTexture -n "Gotham_Arch_Classic_BigWiny2_place2dTexture2";
createNode bump2d -n "Gotham_Arch_Classic_BigWiny2_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_3";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo4";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_4";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo5";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_5";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo6";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_6";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo7";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_7";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo8";
createNode file -n "Gotham_Arch_Classic_BigWiny2_file3";
createNode place2dTexture -n "Gotham_Arch_Classic_BigWiny2_place2dTexture3";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_8";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo9";
createNode file -n "Gotham_Arch_Classic_BigWiny2_file4";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_D.tga";
createNode place2dTexture -n "Gotham_Arch_Classic_BigWiny2_place2dTexture4";
createNode file -n "Gotham_Arch_Classic_BigWiny2_file5";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_N_New.tga";
createNode place2dTexture -n "Gotham_Arch_Classic_BigWiny2_place2dTexture5";
createNode bump2d -n "Gotham_Arch_Classic_BigWiny2_bump2d2";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 2.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_9";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo10";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_10";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo11";
createNode file -n "Gotham_Arch_Classic_BigWiny2_file6";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main02_D.tga";
createNode place2dTexture -n "Gotham_Arch_Classic_BigWiny2_place2dTexture6";
createNode file -n "Gotham_Arch_Classic_BigWiny2_file7";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_N_New.tga";
createNode place2dTexture -n "Gotham_Arch_Classic_BigWiny2_place2dTexture7";
createNode bump2d -n "Gotham_Arch_Classic_BigWiny2_bump2d3";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode file -n "Gotham_Arch_Classic_BigWiny2_file8";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_D.tga";
createNode place2dTexture -n "Gotham_Arch_Classic_BigWiny2_place2dTexture8";
createNode file -n "Gotham_Arch_Classic_BigWiny2_file9";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_N.tga";
createNode place2dTexture -n "Gotham_Arch_Classic_BigWiny2_place2dTexture9";
createNode bump2d -n "Gotham_Arch_Classic_BigWiny2_bump2d4";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode hyperGraphInfo -n "Gotham_Arch_Classic_BigWiny2_nodeEditorPanel1Info";
createNode hyperView -n "Gotham_Arch_Classic_BigWiny2_hyperView1";
	setAttr ".vl" -type "double2" -587.25454701690671 -81.703512257011226 ;
	setAttr ".vh" -type "double2" 325.53946266031306 314.23570752505555 ;
	setAttr ".dag" no;
createNode hyperLayout -n "Gotham_Arch_Classic_BigWiny2_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 10 ".hyp";
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".hyp[5].nvs" 1920;
	setAttr ".hyp[6].nvs" 1920;
	setAttr ".hyp[7].nvs" 1920;
	setAttr ".hyp[8].nvs" 1920;
	setAttr ".hyp[9].nvs" 1920;
	setAttr ".anf" yes;
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_11";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo12";
createNode phong -n "Gotham_Arch_Classic_BigWiny2_phong1";
createNode file -n "Gotham_Arch_Classic_BigWiny2_file10";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main02_S.tga";
createNode place2dTexture -n "Gotham_Arch_Classic_BigWiny2_place2dTexture10";
createNode blinn -n "Gotham_Arch_Classic_BigWiny2_blinn1";
createNode file -n "Gotham_Arch_Classic_BigWiny2_file11";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_S.tga";
createNode place2dTexture -n "Gotham_Arch_Classic_BigWiny2_place2dTexture11";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_12";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo13";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_13";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo14";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_14";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo15";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_15";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo16";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_16";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo17";
createNode lambert -n "Gotham_Arch_Classic_BigWiny2_material_0_lambert";
createNode shadingEngine -n "Gotham_Arch_Classic_BigWiny2_material_17";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_Arch_Classic_BigWiny2_materialInfo18";
createNode hyperLayout -n "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 146 ".hyp";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo1";
createNode file -n "BridgeRoad_Destroyed_2048_Custom_02_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_D.tga";
createNode place2dTexture -n "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1";
createNode file -n "BridgeRoad_Destroyed_2048_Custom_02_file2";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_N.tga";
createNode place2dTexture -n "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2";
createNode bump2d -n "BridgeRoad_Destroyed_2048_Custom_02_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode phong -n "BridgeRoad_Destroyed_2048_Custom_02_phong1";
createNode file -n "BridgeRoad_Destroyed_2048_Custom_02_file3";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_S.tga";
createNode place2dTexture -n "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3";
createNode hyperGraphInfo -n "BridgeRoad_Destroyed_2048_Custom_02_nodeEditorPanel1Info";
createNode hyperView -n "BridgeRoad_Destroyed_2048_Custom_02_hyperView1";
	setAttr ".vl" -type "double2" -598.80952380952385 110.71428571428572 ;
	setAttr ".vh" -type "double2" 91.6666666666667 217.85714285714286 ;
	setAttr ".dag" no;
createNode hyperLayout -n "BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 8 ".hyp";
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".hyp[5].nvs" 1920;
	setAttr ".hyp[6].nvs" 1920;
	setAttr ".hyp[7].nvs" 1920;
	setAttr ".anf" yes;
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo2";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_2";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo3";
createNode file -n "BridgeRoad_Destroyed_2048_Custom_02_file4";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_D.tga";
createNode place2dTexture -n "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4";
createNode file -n "BridgeRoad_Destroyed_2048_Custom_02_file5";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_N.tga";
createNode place2dTexture -n "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5";
createNode bump2d -n "BridgeRoad_Destroyed_2048_Custom_02_bump2d2";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode phong -n "BridgeRoad_Destroyed_2048_Custom_02_phong2";
createNode file -n "BridgeRoad_Destroyed_2048_Custom_02_file6";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_S.tga";
createNode place2dTexture -n "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_3";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo4";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_4";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo5";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_5";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo6";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_6";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo7";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_7";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo8";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_8";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo9";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_9";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo10";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_10";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo11";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_11";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo12";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_12";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo13";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_13";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo14";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_14";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo15";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_15";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo16";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_16";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo17";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_17";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo18";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_18";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo19";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_19";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo20";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_20";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo21";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_21";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo22";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_22";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo23";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_23";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo24";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_24";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo25";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_25";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo26";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_26";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo27";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_27";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo28";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_28";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo29";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_29";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo30";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_30";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo31";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_31";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo32";
createNode lambert -n "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_32";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo33";
createNode lambert -n "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert1";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_33";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo34";
createNode lambert -n "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert2";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_34";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo35";
createNode lambert -n "material_0_lambert3";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_35";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo36";
createNode lambert -n "material_0_lambert4";
createNode shadingEngine -n "BridgeRoad_Destroyed_2048_Custom_02_material_36";
	setAttr ".ro" yes;
createNode materialInfo -n "BridgeRoad_Destroyed_2048_Custom_02_materialInfo37";
createNode hyperLayout -n "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 204 ".hyp";
createNode shadingEngine -n "ConcreteBarrier01_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo1";
createNode file -n "ConcreteBarrier01_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_D.tga";
createNode place2dTexture -n "ConcreteBarrier01_place2dTexture1";
createNode file -n "ConcreteBarrier01_file2";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_N.tga";
createNode place2dTexture -n "ConcreteBarrier01_place2dTexture2";
createNode bump2d -n "ConcreteBarrier01_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode phong -n "ConcreteBarrier01_phong1";
createNode file -n "ConcreteBarrier01_file3";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_S.tga";
createNode place2dTexture -n "ConcreteBarrier01_place2dTexture3";
createNode hyperGraphInfo -n "ConcreteBarrier01_nodeEditorPanel1Info";
createNode hyperView -n "ConcreteBarrier01_hyperView1";
	setAttr ".vl" -type "double2" -598.80952380952385 110.71428571428572 ;
	setAttr ".vh" -type "double2" 91.6666666666667 217.85714285714286 ;
	setAttr ".dag" no;
createNode hyperLayout -n "ConcreteBarrier01_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 8 ".hyp";
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".hyp[5].nvs" 1920;
	setAttr ".hyp[6].nvs" 1920;
	setAttr ".hyp[7].nvs" 1920;
	setAttr ".anf" yes;
createNode shadingEngine -n "ConcreteBarrier01_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo2";
createNode shadingEngine -n "ConcreteBarrier01_material_2";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo3";
createNode file -n "ConcreteBarrier01_file4";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_D.tga";
createNode place2dTexture -n "ConcreteBarrier01_place2dTexture4";
createNode file -n "ConcreteBarrier01_file5";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_N.tga";
createNode place2dTexture -n "ConcreteBarrier01_place2dTexture5";
createNode bump2d -n "ConcreteBarrier01_bump2d2";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode phong -n "ConcreteBarrier01_phong2";
createNode file -n "ConcreteBarrier01_file6";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_S.tga";
createNode place2dTexture -n "ConcreteBarrier01_place2dTexture6";
createNode shadingEngine -n "ConcreteBarrier01_material_3";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo4";
createNode shadingEngine -n "ConcreteBarrier01_material_4";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo5";
createNode shadingEngine -n "ConcreteBarrier01_material_5";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo6";
createNode shadingEngine -n "ConcreteBarrier01_material_6";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo7";
createNode shadingEngine -n "ConcreteBarrier01_material_7";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo8";
createNode shadingEngine -n "ConcreteBarrier01_material_8";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo9";
createNode shadingEngine -n "ConcreteBarrier01_material_9";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo10";
createNode shadingEngine -n "ConcreteBarrier01_material_10";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo11";
createNode shadingEngine -n "ConcreteBarrier01_material_11";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo12";
createNode shadingEngine -n "ConcreteBarrier01_material_12";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo13";
createNode shadingEngine -n "ConcreteBarrier01_material_13";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo14";
createNode shadingEngine -n "ConcreteBarrier01_material_14";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo15";
createNode shadingEngine -n "ConcreteBarrier01_material_15";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo16";
createNode shadingEngine -n "ConcreteBarrier01_material_16";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo17";
createNode shadingEngine -n "ConcreteBarrier01_material_17";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo18";
createNode shadingEngine -n "ConcreteBarrier01_material_18";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo19";
createNode shadingEngine -n "ConcreteBarrier01_material_19";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo20";
createNode shadingEngine -n "ConcreteBarrier01_material_20";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo21";
createNode shadingEngine -n "ConcreteBarrier01_material_21";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo22";
createNode shadingEngine -n "ConcreteBarrier01_material_22";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo23";
createNode shadingEngine -n "ConcreteBarrier01_material_23";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo24";
createNode shadingEngine -n "ConcreteBarrier01_material_24";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo25";
createNode shadingEngine -n "ConcreteBarrier01_material_25";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo26";
createNode shadingEngine -n "ConcreteBarrier01_material_26";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo27";
createNode shadingEngine -n "ConcreteBarrier01_material_27";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo28";
createNode shadingEngine -n "ConcreteBarrier01_material_28";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo29";
createNode shadingEngine -n "ConcreteBarrier01_material_29";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo30";
createNode shadingEngine -n "ConcreteBarrier01_material_30";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo31";
createNode shadingEngine -n "ConcreteBarrier01_material_31";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo32";
createNode shadingEngine -n "ConcreteBarrier01_material_32";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo33";
createNode shadingEngine -n "ConcreteBarrier01_material_33";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo34";
createNode shadingEngine -n "ConcreteBarrier01_material_34";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo35";
createNode shadingEngine -n "ConcreteBarrier01_material_35";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo36";
createNode shadingEngine -n "ConcreteBarrier01_material_36";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo37";
createNode shadingEngine -n "ConcreteBarrier01_material_37";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo38";
createNode shadingEngine -n "ConcreteBarrier01_material_38";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo39";
createNode shadingEngine -n "ConcreteBarrier01_material_39";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo40";
createNode lambert -n "ConcreteBarrier01_material_0_lambert";
createNode shadingEngine -n "ConcreteBarrier01_material_40";
	setAttr ".ro" yes;
createNode materialInfo -n "ConcreteBarrier01_materialInfo41";
createNode lambert -n "ConcreteBarrier01_material_0_lambert1";
createNode shadingEngine -n "material_41";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo42";
createNode lambert -n "ConcreteBarrier01_material_0_lambert2";
createNode shadingEngine -n "material_42";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo43";
createNode lambert -n "ConcreteBarrier01_material_0_lambert3";
createNode shadingEngine -n "material_43";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo44";
createNode hyperLayout -n "AD_ConcreteBarrier01_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 230 ".hyp";
createNode hyperLayout -n "hyperLayout6";
	setAttr ".ihi" 0;
	setAttr -s 119 ".hyp";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo1";
createNode file -n "Bridge_Rail_01_1024_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_D.tga";
createNode place2dTexture -n "Bridge_Rail_01_1024_place2dTexture1";
createNode file -n "Bridge_Rail_01_1024_file2";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_N.tga";
createNode place2dTexture -n "Bridge_Rail_01_1024_place2dTexture2";
createNode bump2d -n "Bridge_Rail_01_1024_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode phong -n "Bridge_Rail_01_1024_phong1";
createNode file -n "Bridge_Rail_01_1024_file3";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_S.tga";
createNode place2dTexture -n "Bridge_Rail_01_1024_place2dTexture3";
createNode hyperGraphInfo -n "Bridge_Rail_01_1024_nodeEditorPanel1Info";
createNode hyperView -n "Bridge_Rail_01_1024_hyperView1";
	setAttr ".vl" -type "double2" -598.80952380952385 110.71428571428572 ;
	setAttr ".vh" -type "double2" 597.61904761904759 217.85714285714286 ;
	setAttr ".dag" no;
createNode hyperLayout -n "Bridge_Rail_01_1024_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 8 ".hyp";
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".hyp[5].nvs" 1920;
	setAttr ".hyp[6].nvs" 1920;
	setAttr ".hyp[7].nvs" 1920;
	setAttr ".anf" yes;
createNode shadingEngine -n "Bridge_Rail_01_1024_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo2";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_2";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo3";
createNode file -n "Bridge_Rail_01_1024_file4";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_D.tga";
createNode place2dTexture -n "Bridge_Rail_01_1024_place2dTexture4";
createNode file -n "Bridge_Rail_01_1024_file5";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_N.tga";
createNode place2dTexture -n "Bridge_Rail_01_1024_place2dTexture5";
createNode bump2d -n "Bridge_Rail_01_1024_bump2d2";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode phong -n "Bridge_Rail_01_1024_phong2";
createNode file -n "Bridge_Rail_01_1024_file6";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_S.tga";
createNode place2dTexture -n "Bridge_Rail_01_1024_place2dTexture6";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_3";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo4";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_4";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo5";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_5";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo6";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_6";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo7";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_7";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo8";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_8";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo9";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_9";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo10";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_10";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo11";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_11";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo12";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_12";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo13";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_13";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo14";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_14";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo15";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_15";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo16";
createNode shadingEngine -n "Bridge_Rail_01_1024_material_16";
	setAttr ".ro" yes;
createNode materialInfo -n "Bridge_Rail_01_1024_materialInfo17";
createNode hyperLayout -n "AD_Bridge_Rail_01_1024_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 114 ".hyp";
createNode lambert -n "Gotham_GCPD_Window1024_material_0_lambert";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_0";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo1";
createNode file -n "Gotham_GCPD_Window1024_file1";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Roof_D.tga";
createNode place2dTexture -n "Gotham_GCPD_Window1024_place2dTexture1";
createNode file -n "Gotham_GCPD_Window1024_file2";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Roof_N.tga";
createNode place2dTexture -n "Gotham_GCPD_Window1024_place2dTexture2";
createNode bump2d -n "Gotham_GCPD_Window1024_bump2d1";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode hyperGraphInfo -n "Gotham_GCPD_Window1024_nodeEditorPanel1Info";
createNode hyperView -n "Gotham_GCPD_Window1024_hyperView1";
	setAttr ".vl" -type "double2" -598.80952380952385 -82.142857142857153 ;
	setAttr ".vh" -type "double2" 157.14285714285722 220.23809523809527 ;
	setAttr ".dag" no;
createNode hyperLayout -n "Gotham_GCPD_Window1024_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 8 ".hyp";
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".hyp[1].nvs" 1920;
	setAttr ".hyp[2].nvs" 1920;
	setAttr ".hyp[3].nvs" 1920;
	setAttr ".hyp[4].nvs" 1920;
	setAttr ".hyp[5].nvs" 1920;
	setAttr ".hyp[6].nvs" 1920;
	setAttr ".hyp[7].nvs" 1920;
	setAttr ".anf" yes;
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_1";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo2";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_2";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo3";
createNode file -n "Gotham_GCPD_Window1024_file3";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Main_D.tga";
createNode place2dTexture -n "Gotham_GCPD_Window1024_place2dTexture3";
createNode file -n "Gotham_GCPD_Window1024_file4";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Main_N.tga";
createNode place2dTexture -n "Gotham_GCPD_Window1024_place2dTexture4";
createNode bump2d -n "Gotham_GCPD_Window1024_bump2d2";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 1.9999999e-005 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-006 9.9999997e-006 0 ;
createNode phong -n "Gotham_GCPD_Window1024_phong1";
createNode file -n "Gotham_GCPD_Window1024_file5";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Main_S.tga";
createNode place2dTexture -n "Gotham_GCPD_Window1024_place2dTexture5";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_3";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo4";
createNode file -n "Gotham_GCPD_Window1024_file6";
	setAttr ".ftn" -type "string" "L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_ARCH_GCPD_Main_E.tga";
createNode place2dTexture -n "Gotham_GCPD_Window1024_place2dTexture6";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_4";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo5";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_5";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo6";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_6";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo7";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_7";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo8";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_8";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo9";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_9";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo10";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_10";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo11";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_11";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo12";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_12";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo13";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_13";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo14";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_14";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo15";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_15";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo16";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_16";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo17";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_17";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo18";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_18";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo19";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_19";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo20";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_20";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo21";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_21";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo22";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_22";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo23";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_23";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo24";
createNode shadingEngine -n "Gotham_GCPD_Window1024_material_24";
	setAttr ".ro" yes;
createNode materialInfo -n "Gotham_GCPD_Window1024_materialInfo25";
createNode hyperLayout -n "AD_Gotham_GCPD_Window1024_hyperLayout1";
	setAttr ".ihi" 0;
	setAttr -s 146 ".hyp";
createNode hyperLayout -n "hyperLayout7";
	setAttr ".ihi" 0;
	setAttr -s 77 ".hyp";
createNode hyperLayout -n "hyperLayout8";
	setAttr ".ihi" 0;
	setAttr -s 83 ".hyp";
createNode polySphere -n "polySphere1";
	setAttr ".r" 1786.587518582518;
createNode shadingEngine -n "blinn2SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo45";
createNode file -n "SkyFile";
	setAttr ".ftn" -type "string" "C:/Project/NagaGame/Arts/LevelProject//LevelData/Level_Combine/Texture/sky.jpg";
createNode place2dTexture -n "place2dTexture12";
createNode surfaceShader -n "surfaceShader1";
createNode animCurveTU -n "surfaceShader1_materialAlphaGain";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 1;
createNode polyNormal -n "polyNormal1";
	setAttr ".ics" -type "componentList" 1 "f[*]";
	setAttr ".unm" no;
createNode displayLayer -n "sky";
	setAttr ".c" 18;
	setAttr ".do" 1;
createNode displayLayer -n "layer1";
	setAttr ".dt" 2;
	setAttr ".v" no;
	setAttr ".do" 2;
select -ne :time1;
	setAttr ".o" 1;
	setAttr ".unw" 1;
select -ne :renderPartition;
	setAttr -s 801 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 129 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 354 ".u";
select -ne :defaultRenderingList1;
select -ne :lightList1;
select -ne :defaultTextureList1;
	setAttr -s 264 ".tx";
select -ne :initialShadingGroup;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	setAttr ".ren" -type "string" "mentalRay";
	setAttr -k on ".mbf";
select -ne :defaultResolution;
	setAttr ".pa" 1;
select -ne :defaultLightSet;
select -ne :hardwareRenderGlobals;
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
select -ne :hardwareRenderingGlobals;
	setAttr ".otfna" -type "stringArray" 18 "NURBS Curves" "NURBS Surfaces" "Polygons" "Subdiv Surfaces" "Particles" "Fluids" "Image Planes" "UI:" "Lights" "Cameras" "Locators" "Joints" "IK Handles" "Deformers" "Motion Trails" "Components" "Misc. UI" "Ornaments"  ;
	setAttr ".otfva" -type "Int32Array" 18 0 1 1 1 1 1
		 1 0 0 0 0 0 0 0 0 0 0 0 ;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
connectAttr "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512.hl"
		;
connectAttr "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.msg" "AD_Gotham_Groundfloor_Shop_OldB2.hl"
		;
connectAttr "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03.hl"
		;
connectAttr "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.msg" "AD_Gotham_ARCH_Classic_BigWinx2.hl"
		;
connectAttr "hyperLayout2.msg" "AD_Gotham_ARCH_Classic_BigWinx3.hl";
connectAttr "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.msg" "AD_Gotham_ARCH_Classic_WinBCorner.hl"
		;
connectAttr "hyperLayout3.msg" "AD_Gotham_ARCH_Classic_WinBCorner1.hl";
connectAttr "AD_Gotham_Fences_Mall768_hyperLayout1.msg" "AD_Gotham_Fences_Mall768.hl"
		;
connectAttr "hyperLayout4.msg" "AD_Gotham_Fences_Mall769.hl";
connectAttr "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.msg" "AD_Gotham_Fences_PoleSolid_128C.hl"
		;
connectAttr "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.msg" "AD_Gotham_Fences_PoleSolid_512.hl"
		;
connectAttr "hyperLayout5.msg" "AD_Gotham_Fences_PoleSolid_513.hl";
connectAttr "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.msg" "AD_ARCH_GCPD_EntranceRoof_04.hl"
		;
connectAttr "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.msg" "AD_Gotham_Arch_Classic_BigWiny2.hl"
		;
connectAttr "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02.hl"
		;
connectAttr "AD_ConcreteBarrier01_hyperLayout1.msg" "AD_ConcreteBarrier01.hl";
connectAttr "hyperLayout6.msg" "AD_ConcreteBarrier02.hl";
connectAttr "AD_Bridge_Rail_01_1024_hyperLayout1.msg" "AD_Bridge_Rail_01_1024.hl"
		;
connectAttr "AD_Gotham_GCPD_Window1024_hyperLayout1.msg" "AD_Gotham_GCPD_Window1024.hl"
		;
connectAttr "hyperLayout7.msg" "AD_Gotham_GCPD_Window1025.hl";
connectAttr "hyperLayout8.msg" "AD_Gotham_Fences_PoleSolid_514.hl";
connectAttr "sky.di" "SkyDome.do";
connectAttr "polyNormal1.out" "SkyDomeShape.i";
connectAttr ":mentalrayGlobals.msg" ":mentalrayItemsList.glb";
connectAttr ":miDefaultOptions.msg" ":mentalrayItemsList.opt" -na;
connectAttr ":miDefaultFramebuffer.msg" ":mentalrayItemsList.fb" -na;
connectAttr ":miDefaultOptions.msg" ":mentalrayGlobals.opt";
connectAttr ":miDefaultFramebuffer.msg" ":mentalrayGlobals.fb";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_material_2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_material_3.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_material_4.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_material_5.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_blinn1SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_6.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_7.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_8.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_9.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_10.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_material_2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_material_3.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_material_4.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_material_5.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_blinn1SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_3.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_4.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_5.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_6.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_7.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_8.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_9.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_10.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_11.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_12.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_13.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_3.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_4.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_5.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_6.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_7.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_8.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_9.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_10.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_11.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_12.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_13.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_14.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_15.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_16.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_3.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_4.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_5.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_6.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_7.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_8.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_9.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_10.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_11.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_12.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_13.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_14.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_15.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_16.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_17.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_18.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_19.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_20.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_21.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_22.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_23.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_24.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_25.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_26.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_27.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_28.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_29.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_30.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_31.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_32.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_33.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_34.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_35.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_36.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_37.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_38.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_39.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_40.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_3.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_4.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_5.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_6.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_7.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_8.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_9.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_10.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_11.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_blinn1SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_12.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_13.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_14.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_Mall768_material_15.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_3.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_4.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_5.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_6.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_7.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_8.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_9.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_10.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_11.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_blinn1SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_12.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_13.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_14.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_15.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_16.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_17.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_18.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_19.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_20.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_21.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_3.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_4.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_5.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_6.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_7.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_8.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_9.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_10.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_11.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_blinn1SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_12.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_13.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_14.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_15.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_16.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_17.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_18.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_19.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_20.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_21.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_22.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_23.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_24.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ARCH_GCPD_EntranceRoof_04_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ARCH_GCPD_EntranceRoof_04_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_3.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_4.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_5.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_6.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_7.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_8.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_9.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_10.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_11.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_12.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_13.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_14.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_15.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_16.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_17.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "blinn2SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_3.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_4.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_5.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_6.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_7.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_8.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_9.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_10.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_11.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_12.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_13.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_14.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_15.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_16.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_17.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_18.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_19.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_20.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_21.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_22.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_23.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_24.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_25.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_26.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_27.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_28.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_29.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_30.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_31.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_32.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_33.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_34.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_35.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_36.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_3.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_4.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_5.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_6.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_7.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_8.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_9.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_10.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_11.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_12.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_13.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_14.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_15.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_16.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_17.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_18.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_19.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_20.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_21.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_22.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_23.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_24.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_25.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_26.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_27.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_28.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_29.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_30.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_31.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_32.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_33.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_34.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_35.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_36.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_37.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_38.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_39.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "ConcreteBarrier01_material_40.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_41.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_42.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "material_43.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_3.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_4.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_5.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_6.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_7.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_8.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_9.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_10.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_11.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_12.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_13.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_14.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_15.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Bridge_Rail_01_1024_material_16.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_0.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_3.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_4.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_5.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_6.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_7.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_8.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_9.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_10.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_11.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_12.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_13.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_14.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_15.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_16.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_17.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_18.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_19.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_20.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_21.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_22.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_23.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Gotham_GCPD_Window1024_material_24.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_material_2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_material_3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_material_4.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_material_5.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GroundFloor_Shop_OlddB5_512_blinn1SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_6.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_7.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_8.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_9.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_10.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_material_2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_material_3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_material_4.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_material_5.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Groundfloor_Shop_OldB2_blinn1SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_4.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_5.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_6.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_7.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_8.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_9.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_10.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_11.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_12.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_13.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_4.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_5.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_6.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_7.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_8.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_9.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_10.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_11.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_12.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_BigWinx2_material_13.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_14.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_15.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_16.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_4.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_5.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_6.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_7.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_8.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_9.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_10.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_11.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_12.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_13.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_14.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_15.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_ARCH_Classic_WinBCorner_material_16.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_17.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_18.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_19.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_20.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_21.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_22.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_23.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_24.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_25.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_26.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_27.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_28.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_29.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_30.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_31.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_32.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_33.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_34.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_35.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_36.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_37.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_38.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_39.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_40.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_4.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_5.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_6.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_7.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_8.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_9.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_10.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_11.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_blinn1SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_12.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_13.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_14.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_Mall768_material_15.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_4.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_5.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_6.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_7.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_8.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_9.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_10.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_11.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_blinn1SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_12.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_13.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_14.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_15.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_16.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_17.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_18.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_19.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_20.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_128C_material_21.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_4.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_5.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_6.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_7.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_8.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_9.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_10.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_11.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_blinn1SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_12.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_13.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_14.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_15.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_16.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_17.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_18.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_19.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_20.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_21.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_22.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_23.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Fences_PoleSolid_512_material_24.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ARCH_GCPD_EntranceRoof_04_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ARCH_GCPD_EntranceRoof_04_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_4.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_5.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_6.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_7.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_8.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_9.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_10.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_11.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_12.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_13.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_14.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_15.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_16.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_Arch_Classic_BigWiny2_material_17.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "blinn2SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_4.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_5.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_6.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_7.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_8.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_9.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_10.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_11.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_12.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_13.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_14.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_15.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_16.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_17.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_18.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_19.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_20.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_21.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_22.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_23.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_24.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_25.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_26.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_27.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_28.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_29.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_30.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_31.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_32.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_33.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_34.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_35.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BridgeRoad_Destroyed_2048_Custom_02_material_36.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_4.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_5.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_6.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_7.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_8.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_9.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_10.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_11.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_12.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_13.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_14.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_15.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_16.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_17.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_18.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_19.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_20.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_21.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_22.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_23.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_24.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_25.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_26.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_27.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_28.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_29.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_30.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_31.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_32.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_33.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_34.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_35.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_36.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_37.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_38.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_39.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "ConcreteBarrier01_material_40.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_41.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_42.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "material_43.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_4.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_5.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_6.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_7.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_8.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_9.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_10.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_11.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_12.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_13.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_14.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_15.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Bridge_Rail_01_1024_material_16.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_0.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_4.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_5.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_6.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_7.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_8.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_9.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_10.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_11.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_12.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_13.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_14.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_15.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_16.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_17.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_18.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_19.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_20.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_21.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_22.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_23.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Gotham_GCPD_Window1024_material_24.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_phong1.oc" "Gotham_GroundFloor_Shop_OlddB5_512_material_0.ss"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_phong1.msg" "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo1.m"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_0.msg" "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo1.sg"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file1.msg" "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo1.t"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.c" "Gotham_GroundFloor_Shop_OlddB5_512_file1.c"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.tf" "Gotham_GroundFloor_Shop_OlddB5_512_file1.tf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.rf" "Gotham_GroundFloor_Shop_OlddB5_512_file1.rf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.mu" "Gotham_GroundFloor_Shop_OlddB5_512_file1.mu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.mv" "Gotham_GroundFloor_Shop_OlddB5_512_file1.mv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.s" "Gotham_GroundFloor_Shop_OlddB5_512_file1.s"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.wu" "Gotham_GroundFloor_Shop_OlddB5_512_file1.wu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.wv" "Gotham_GroundFloor_Shop_OlddB5_512_file1.wv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.re" "Gotham_GroundFloor_Shop_OlddB5_512_file1.re"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.of" "Gotham_GroundFloor_Shop_OlddB5_512_file1.of"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.r" "Gotham_GroundFloor_Shop_OlddB5_512_file1.ro"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.n" "Gotham_GroundFloor_Shop_OlddB5_512_file1.n"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.vt1" "Gotham_GroundFloor_Shop_OlddB5_512_file1.vt1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.vt2" "Gotham_GroundFloor_Shop_OlddB5_512_file1.vt2"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.vt3" "Gotham_GroundFloor_Shop_OlddB5_512_file1.vt3"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.vc1" "Gotham_GroundFloor_Shop_OlddB5_512_file1.vc1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.o" "Gotham_GroundFloor_Shop_OlddB5_512_file1.uv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.ofs" "Gotham_GroundFloor_Shop_OlddB5_512_file1.fs"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.c" "Gotham_GroundFloor_Shop_OlddB5_512_file2.c"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.tf" "Gotham_GroundFloor_Shop_OlddB5_512_file2.tf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.rf" "Gotham_GroundFloor_Shop_OlddB5_512_file2.rf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.mu" "Gotham_GroundFloor_Shop_OlddB5_512_file2.mu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.mv" "Gotham_GroundFloor_Shop_OlddB5_512_file2.mv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.s" "Gotham_GroundFloor_Shop_OlddB5_512_file2.s"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.wu" "Gotham_GroundFloor_Shop_OlddB5_512_file2.wu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.wv" "Gotham_GroundFloor_Shop_OlddB5_512_file2.wv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.re" "Gotham_GroundFloor_Shop_OlddB5_512_file2.re"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.of" "Gotham_GroundFloor_Shop_OlddB5_512_file2.of"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.r" "Gotham_GroundFloor_Shop_OlddB5_512_file2.ro"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.n" "Gotham_GroundFloor_Shop_OlddB5_512_file2.n"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.vt1" "Gotham_GroundFloor_Shop_OlddB5_512_file2.vt1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.vt2" "Gotham_GroundFloor_Shop_OlddB5_512_file2.vt2"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.vt3" "Gotham_GroundFloor_Shop_OlddB5_512_file2.vt3"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.vc1" "Gotham_GroundFloor_Shop_OlddB5_512_file2.vc1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.o" "Gotham_GroundFloor_Shop_OlddB5_512_file2.uv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.ofs" "Gotham_GroundFloor_Shop_OlddB5_512_file2.fs"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file2.oa" "Gotham_GroundFloor_Shop_OlddB5_512_bump2d1.bv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file1.oc" "Gotham_GroundFloor_Shop_OlddB5_512_phong1.c"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_bump2d1.o" "Gotham_GroundFloor_Shop_OlddB5_512_phong1.n"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file3.oc" "Gotham_GroundFloor_Shop_OlddB5_512_phong1.sc"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.c" "Gotham_GroundFloor_Shop_OlddB5_512_file3.c"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.tf" "Gotham_GroundFloor_Shop_OlddB5_512_file3.tf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.rf" "Gotham_GroundFloor_Shop_OlddB5_512_file3.rf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.mu" "Gotham_GroundFloor_Shop_OlddB5_512_file3.mu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.mv" "Gotham_GroundFloor_Shop_OlddB5_512_file3.mv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.s" "Gotham_GroundFloor_Shop_OlddB5_512_file3.s"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.wu" "Gotham_GroundFloor_Shop_OlddB5_512_file3.wu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.wv" "Gotham_GroundFloor_Shop_OlddB5_512_file3.wv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.re" "Gotham_GroundFloor_Shop_OlddB5_512_file3.re"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.of" "Gotham_GroundFloor_Shop_OlddB5_512_file3.of"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.r" "Gotham_GroundFloor_Shop_OlddB5_512_file3.ro"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.n" "Gotham_GroundFloor_Shop_OlddB5_512_file3.n"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.vt1" "Gotham_GroundFloor_Shop_OlddB5_512_file3.vt1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.vt2" "Gotham_GroundFloor_Shop_OlddB5_512_file3.vt2"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.vt3" "Gotham_GroundFloor_Shop_OlddB5_512_file3.vt3"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.vc1" "Gotham_GroundFloor_Shop_OlddB5_512_file3.vc1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.o" "Gotham_GroundFloor_Shop_OlddB5_512_file3.uv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.ofs" "Gotham_GroundFloor_Shop_OlddB5_512_file3.fs"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_hyperView1.msg" "Gotham_GroundFloor_Shop_OlddB5_512_nodeEditorPanel1Info.b[0]"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.msg" "Gotham_GroundFloor_Shop_OlddB5_512_hyperView1.hl"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_1.msg" "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo2.sg"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_2.msg" "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo3.sg"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_3.msg" "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo4.sg"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_4.msg" "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo5.sg"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_phong2.oc" "Gotham_GroundFloor_Shop_OlddB5_512_material_5.ss"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_phong2.msg" "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo6.m"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_5.msg" "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo6.sg"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file4.msg" "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo6.t"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.c" "Gotham_GroundFloor_Shop_OlddB5_512_file4.c"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.tf" "Gotham_GroundFloor_Shop_OlddB5_512_file4.tf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.rf" "Gotham_GroundFloor_Shop_OlddB5_512_file4.rf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.mu" "Gotham_GroundFloor_Shop_OlddB5_512_file4.mu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.mv" "Gotham_GroundFloor_Shop_OlddB5_512_file4.mv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.s" "Gotham_GroundFloor_Shop_OlddB5_512_file4.s"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.wu" "Gotham_GroundFloor_Shop_OlddB5_512_file4.wu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.wv" "Gotham_GroundFloor_Shop_OlddB5_512_file4.wv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.re" "Gotham_GroundFloor_Shop_OlddB5_512_file4.re"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.of" "Gotham_GroundFloor_Shop_OlddB5_512_file4.of"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.r" "Gotham_GroundFloor_Shop_OlddB5_512_file4.ro"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.n" "Gotham_GroundFloor_Shop_OlddB5_512_file4.n"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.vt1" "Gotham_GroundFloor_Shop_OlddB5_512_file4.vt1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.vt2" "Gotham_GroundFloor_Shop_OlddB5_512_file4.vt2"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.vt3" "Gotham_GroundFloor_Shop_OlddB5_512_file4.vt3"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.vc1" "Gotham_GroundFloor_Shop_OlddB5_512_file4.vc1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.o" "Gotham_GroundFloor_Shop_OlddB5_512_file4.uv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.ofs" "Gotham_GroundFloor_Shop_OlddB5_512_file4.fs"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.c" "Gotham_GroundFloor_Shop_OlddB5_512_file5.c"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.tf" "Gotham_GroundFloor_Shop_OlddB5_512_file5.tf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.rf" "Gotham_GroundFloor_Shop_OlddB5_512_file5.rf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.mu" "Gotham_GroundFloor_Shop_OlddB5_512_file5.mu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.mv" "Gotham_GroundFloor_Shop_OlddB5_512_file5.mv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.s" "Gotham_GroundFloor_Shop_OlddB5_512_file5.s"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.wu" "Gotham_GroundFloor_Shop_OlddB5_512_file5.wu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.wv" "Gotham_GroundFloor_Shop_OlddB5_512_file5.wv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.re" "Gotham_GroundFloor_Shop_OlddB5_512_file5.re"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.of" "Gotham_GroundFloor_Shop_OlddB5_512_file5.of"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.r" "Gotham_GroundFloor_Shop_OlddB5_512_file5.ro"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.n" "Gotham_GroundFloor_Shop_OlddB5_512_file5.n"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.vt1" "Gotham_GroundFloor_Shop_OlddB5_512_file5.vt1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.vt2" "Gotham_GroundFloor_Shop_OlddB5_512_file5.vt2"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.vt3" "Gotham_GroundFloor_Shop_OlddB5_512_file5.vt3"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.vc1" "Gotham_GroundFloor_Shop_OlddB5_512_file5.vc1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.o" "Gotham_GroundFloor_Shop_OlddB5_512_file5.uv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.ofs" "Gotham_GroundFloor_Shop_OlddB5_512_file5.fs"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file5.oa" "Gotham_GroundFloor_Shop_OlddB5_512_bump2d2.bv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file6.oc" "Gotham_GroundFloor_Shop_OlddB5_512_blinn1.c"
		;
connectAttr "bump2d3.o" "Gotham_GroundFloor_Shop_OlddB5_512_blinn1.n";
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_blinn1.oc" "Gotham_GroundFloor_Shop_OlddB5_512_blinn1SG.ss"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_blinn1SG.msg" "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo7.sg"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_blinn1.msg" "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo7.m"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file6.msg" "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo7.t"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.c" "Gotham_GroundFloor_Shop_OlddB5_512_file6.c"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.tf" "Gotham_GroundFloor_Shop_OlddB5_512_file6.tf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.rf" "Gotham_GroundFloor_Shop_OlddB5_512_file6.rf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.mu" "Gotham_GroundFloor_Shop_OlddB5_512_file6.mu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.mv" "Gotham_GroundFloor_Shop_OlddB5_512_file6.mv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.s" "Gotham_GroundFloor_Shop_OlddB5_512_file6.s"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.wu" "Gotham_GroundFloor_Shop_OlddB5_512_file6.wu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.wv" "Gotham_GroundFloor_Shop_OlddB5_512_file6.wv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.re" "Gotham_GroundFloor_Shop_OlddB5_512_file6.re"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.of" "Gotham_GroundFloor_Shop_OlddB5_512_file6.of"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.r" "Gotham_GroundFloor_Shop_OlddB5_512_file6.ro"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.n" "Gotham_GroundFloor_Shop_OlddB5_512_file6.n"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.vt1" "Gotham_GroundFloor_Shop_OlddB5_512_file6.vt1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.vt2" "Gotham_GroundFloor_Shop_OlddB5_512_file6.vt2"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.vt3" "Gotham_GroundFloor_Shop_OlddB5_512_file6.vt3"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.vc1" "Gotham_GroundFloor_Shop_OlddB5_512_file6.vc1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.o" "Gotham_GroundFloor_Shop_OlddB5_512_file6.uv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.ofs" "Gotham_GroundFloor_Shop_OlddB5_512_file6.fs"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file4.oc" "Gotham_GroundFloor_Shop_OlddB5_512_phong2.c"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_bump2d2.o" "Gotham_GroundFloor_Shop_OlddB5_512_phong2.n"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file7.oc" "Gotham_GroundFloor_Shop_OlddB5_512_phong2.sc"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.c" "Gotham_GroundFloor_Shop_OlddB5_512_file7.c"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.tf" "Gotham_GroundFloor_Shop_OlddB5_512_file7.tf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.rf" "Gotham_GroundFloor_Shop_OlddB5_512_file7.rf"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.mu" "Gotham_GroundFloor_Shop_OlddB5_512_file7.mu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.mv" "Gotham_GroundFloor_Shop_OlddB5_512_file7.mv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.s" "Gotham_GroundFloor_Shop_OlddB5_512_file7.s"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.wu" "Gotham_GroundFloor_Shop_OlddB5_512_file7.wu"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.wv" "Gotham_GroundFloor_Shop_OlddB5_512_file7.wv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.re" "Gotham_GroundFloor_Shop_OlddB5_512_file7.re"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.of" "Gotham_GroundFloor_Shop_OlddB5_512_file7.of"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.r" "Gotham_GroundFloor_Shop_OlddB5_512_file7.ro"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.n" "Gotham_GroundFloor_Shop_OlddB5_512_file7.n"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.vt1" "Gotham_GroundFloor_Shop_OlddB5_512_file7.vt1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.vt2" "Gotham_GroundFloor_Shop_OlddB5_512_file7.vt2"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.vt3" "Gotham_GroundFloor_Shop_OlddB5_512_file7.vt3"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.vc1" "Gotham_GroundFloor_Shop_OlddB5_512_file7.vc1"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.o" "Gotham_GroundFloor_Shop_OlddB5_512_file7.uv"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.ofs" "Gotham_GroundFloor_Shop_OlddB5_512_file7.fs"
		;
connectAttr "place2dTexture8.c" "file8.c";
connectAttr "place2dTexture8.tf" "file8.tf";
connectAttr "place2dTexture8.rf" "file8.rf";
connectAttr "place2dTexture8.mu" "file8.mu";
connectAttr "place2dTexture8.mv" "file8.mv";
connectAttr "place2dTexture8.s" "file8.s";
connectAttr "place2dTexture8.wu" "file8.wu";
connectAttr "place2dTexture8.wv" "file8.wv";
connectAttr "place2dTexture8.re" "file8.re";
connectAttr "place2dTexture8.of" "file8.of";
connectAttr "place2dTexture8.r" "file8.ro";
connectAttr "place2dTexture8.n" "file8.n";
connectAttr "place2dTexture8.vt1" "file8.vt1";
connectAttr "place2dTexture8.vt2" "file8.vt2";
connectAttr "place2dTexture8.vt3" "file8.vt3";
connectAttr "place2dTexture8.vc1" "file8.vc1";
connectAttr "place2dTexture8.o" "file8.uv";
connectAttr "place2dTexture8.ofs" "file8.fs";
connectAttr "file8.oa" "bump2d3.bv";
connectAttr "material_6.msg" "materialInfo8.sg";
connectAttr "material_7.msg" "materialInfo9.sg";
connectAttr "material_8.msg" "materialInfo10.sg";
connectAttr "material_9.msg" "materialInfo11.sg";
connectAttr "material_0_lambert.oc" "material_10.ss";
connectAttr "material_0_lambert.msg" "materialInfo12.m";
connectAttr "material_10.msg" "materialInfo12.sg";
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_0.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[6].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo1.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[7].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file1.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[8].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[9].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file2.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[10].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[11].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_bump2d1.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[12].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_phong1.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[13].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file3.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[14].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[15].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_nodeEditorPanel1Info.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[16].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_hyperView1.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[17].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[18].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_1.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[21].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo2.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[22].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_2.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[23].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo3.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[24].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_3.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[25].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo4.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[26].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_4.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[27].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo5.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[28].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_5.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[29].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo6.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[30].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file4.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[31].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[32].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file5.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[33].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[34].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_bump2d2.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[35].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_blinn1.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[36].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_blinn1SG.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[37].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_materialInfo7.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[38].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file6.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[39].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[40].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_phong2.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[41].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file7.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[42].dn"
		;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[43].dn"
		;
connectAttr "file8.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[44].dn"
		;
connectAttr "place2dTexture8.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[45].dn"
		;
connectAttr "bump2d3.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[46].dn"
		;
connectAttr "material_6.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[47].dn"
		;
connectAttr "materialInfo8.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[48].dn"
		;
connectAttr "material_7.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[49].dn"
		;
connectAttr "materialInfo9.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[50].dn"
		;
connectAttr "material_8.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[51].dn"
		;
connectAttr "materialInfo10.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[52].dn"
		;
connectAttr "material_9.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[53].dn"
		;
connectAttr "materialInfo11.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[54].dn"
		;
connectAttr "material_0_lambert.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[55].dn"
		;
connectAttr "material_10.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[56].dn"
		;
connectAttr "materialInfo12.msg" "AD_Gotham_GroundFloor_Shop_OlddB5_512_hyperLayout1.hyp[57].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_phong1.oc" "Gotham_Groundfloor_Shop_OldB2_material_0.ss"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_phong1.msg" "Gotham_Groundfloor_Shop_OldB2_materialInfo1.m"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_0.msg" "Gotham_Groundfloor_Shop_OldB2_materialInfo1.sg"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file1.msg" "Gotham_Groundfloor_Shop_OldB2_materialInfo1.t"
		 -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.c" "Gotham_Groundfloor_Shop_OldB2_file1.c"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.tf" "Gotham_Groundfloor_Shop_OldB2_file1.tf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.rf" "Gotham_Groundfloor_Shop_OldB2_file1.rf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.mu" "Gotham_Groundfloor_Shop_OldB2_file1.mu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.mv" "Gotham_Groundfloor_Shop_OldB2_file1.mv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.s" "Gotham_Groundfloor_Shop_OldB2_file1.s"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.wu" "Gotham_Groundfloor_Shop_OldB2_file1.wu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.wv" "Gotham_Groundfloor_Shop_OldB2_file1.wv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.re" "Gotham_Groundfloor_Shop_OldB2_file1.re"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.of" "Gotham_Groundfloor_Shop_OldB2_file1.of"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.r" "Gotham_Groundfloor_Shop_OldB2_file1.ro"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.n" "Gotham_Groundfloor_Shop_OldB2_file1.n"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.vt1" "Gotham_Groundfloor_Shop_OldB2_file1.vt1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.vt2" "Gotham_Groundfloor_Shop_OldB2_file1.vt2"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.vt3" "Gotham_Groundfloor_Shop_OldB2_file1.vt3"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.vc1" "Gotham_Groundfloor_Shop_OldB2_file1.vc1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.o" "Gotham_Groundfloor_Shop_OldB2_file1.uv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.ofs" "Gotham_Groundfloor_Shop_OldB2_file1.fs"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.c" "Gotham_Groundfloor_Shop_OldB2_file2.c"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.tf" "Gotham_Groundfloor_Shop_OldB2_file2.tf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.rf" "Gotham_Groundfloor_Shop_OldB2_file2.rf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.mu" "Gotham_Groundfloor_Shop_OldB2_file2.mu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.mv" "Gotham_Groundfloor_Shop_OldB2_file2.mv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.s" "Gotham_Groundfloor_Shop_OldB2_file2.s"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.wu" "Gotham_Groundfloor_Shop_OldB2_file2.wu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.wv" "Gotham_Groundfloor_Shop_OldB2_file2.wv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.re" "Gotham_Groundfloor_Shop_OldB2_file2.re"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.of" "Gotham_Groundfloor_Shop_OldB2_file2.of"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.r" "Gotham_Groundfloor_Shop_OldB2_file2.ro"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.n" "Gotham_Groundfloor_Shop_OldB2_file2.n"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.vt1" "Gotham_Groundfloor_Shop_OldB2_file2.vt1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.vt2" "Gotham_Groundfloor_Shop_OldB2_file2.vt2"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.vt3" "Gotham_Groundfloor_Shop_OldB2_file2.vt3"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.vc1" "Gotham_Groundfloor_Shop_OldB2_file2.vc1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.o" "Gotham_Groundfloor_Shop_OldB2_file2.uv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.ofs" "Gotham_Groundfloor_Shop_OldB2_file2.fs"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file2.oa" "Gotham_Groundfloor_Shop_OldB2_bump2d1.bv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file1.oc" "Gotham_Groundfloor_Shop_OldB2_phong1.c"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_bump2d1.o" "Gotham_Groundfloor_Shop_OldB2_phong1.n"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file3.oc" "Gotham_Groundfloor_Shop_OldB2_phong1.sc"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.c" "Gotham_Groundfloor_Shop_OldB2_file3.c"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.tf" "Gotham_Groundfloor_Shop_OldB2_file3.tf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.rf" "Gotham_Groundfloor_Shop_OldB2_file3.rf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.mu" "Gotham_Groundfloor_Shop_OldB2_file3.mu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.mv" "Gotham_Groundfloor_Shop_OldB2_file3.mv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.s" "Gotham_Groundfloor_Shop_OldB2_file3.s"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.wu" "Gotham_Groundfloor_Shop_OldB2_file3.wu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.wv" "Gotham_Groundfloor_Shop_OldB2_file3.wv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.re" "Gotham_Groundfloor_Shop_OldB2_file3.re"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.of" "Gotham_Groundfloor_Shop_OldB2_file3.of"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.r" "Gotham_Groundfloor_Shop_OldB2_file3.ro"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.n" "Gotham_Groundfloor_Shop_OldB2_file3.n"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.vt1" "Gotham_Groundfloor_Shop_OldB2_file3.vt1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.vt2" "Gotham_Groundfloor_Shop_OldB2_file3.vt2"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.vt3" "Gotham_Groundfloor_Shop_OldB2_file3.vt3"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.vc1" "Gotham_Groundfloor_Shop_OldB2_file3.vc1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.o" "Gotham_Groundfloor_Shop_OldB2_file3.uv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.ofs" "Gotham_Groundfloor_Shop_OldB2_file3.fs"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_hyperView1.msg" "Gotham_Groundfloor_Shop_OldB2_nodeEditorPanel1Info.b[0]"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.msg" "Gotham_Groundfloor_Shop_OldB2_hyperView1.hl"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file4.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[0].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[1].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file5.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[2].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[3].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_bump2d2.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[4].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_blinn1.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[5].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_blinn1SG.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[6].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file6.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[7].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[8].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_phong2.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[9].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file7.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[10].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[11].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file8.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[12].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[13].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_bump2d3.msg" "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[14].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_1.msg" "Gotham_Groundfloor_Shop_OldB2_materialInfo2.sg"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_2.msg" "Gotham_Groundfloor_Shop_OldB2_materialInfo3.sg"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_3.msg" "Gotham_Groundfloor_Shop_OldB2_materialInfo4.sg"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_4.msg" "Gotham_Groundfloor_Shop_OldB2_materialInfo5.sg"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_phong2.oc" "Gotham_Groundfloor_Shop_OldB2_material_5.ss"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_phong2.msg" "Gotham_Groundfloor_Shop_OldB2_materialInfo6.m"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_5.msg" "Gotham_Groundfloor_Shop_OldB2_materialInfo6.sg"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file4.msg" "Gotham_Groundfloor_Shop_OldB2_materialInfo6.t"
		 -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.c" "Gotham_Groundfloor_Shop_OldB2_file4.c"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.tf" "Gotham_Groundfloor_Shop_OldB2_file4.tf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.rf" "Gotham_Groundfloor_Shop_OldB2_file4.rf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.mu" "Gotham_Groundfloor_Shop_OldB2_file4.mu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.mv" "Gotham_Groundfloor_Shop_OldB2_file4.mv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.s" "Gotham_Groundfloor_Shop_OldB2_file4.s"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.wu" "Gotham_Groundfloor_Shop_OldB2_file4.wu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.wv" "Gotham_Groundfloor_Shop_OldB2_file4.wv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.re" "Gotham_Groundfloor_Shop_OldB2_file4.re"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.of" "Gotham_Groundfloor_Shop_OldB2_file4.of"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.r" "Gotham_Groundfloor_Shop_OldB2_file4.ro"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.n" "Gotham_Groundfloor_Shop_OldB2_file4.n"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.vt1" "Gotham_Groundfloor_Shop_OldB2_file4.vt1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.vt2" "Gotham_Groundfloor_Shop_OldB2_file4.vt2"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.vt3" "Gotham_Groundfloor_Shop_OldB2_file4.vt3"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.vc1" "Gotham_Groundfloor_Shop_OldB2_file4.vc1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.o" "Gotham_Groundfloor_Shop_OldB2_file4.uv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.ofs" "Gotham_Groundfloor_Shop_OldB2_file4.fs"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.c" "Gotham_Groundfloor_Shop_OldB2_file5.c"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.tf" "Gotham_Groundfloor_Shop_OldB2_file5.tf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.rf" "Gotham_Groundfloor_Shop_OldB2_file5.rf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.mu" "Gotham_Groundfloor_Shop_OldB2_file5.mu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.mv" "Gotham_Groundfloor_Shop_OldB2_file5.mv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.s" "Gotham_Groundfloor_Shop_OldB2_file5.s"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.wu" "Gotham_Groundfloor_Shop_OldB2_file5.wu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.wv" "Gotham_Groundfloor_Shop_OldB2_file5.wv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.re" "Gotham_Groundfloor_Shop_OldB2_file5.re"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.of" "Gotham_Groundfloor_Shop_OldB2_file5.of"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.r" "Gotham_Groundfloor_Shop_OldB2_file5.ro"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.n" "Gotham_Groundfloor_Shop_OldB2_file5.n"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.vt1" "Gotham_Groundfloor_Shop_OldB2_file5.vt1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.vt2" "Gotham_Groundfloor_Shop_OldB2_file5.vt2"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.vt3" "Gotham_Groundfloor_Shop_OldB2_file5.vt3"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.vc1" "Gotham_Groundfloor_Shop_OldB2_file5.vc1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.o" "Gotham_Groundfloor_Shop_OldB2_file5.uv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.ofs" "Gotham_Groundfloor_Shop_OldB2_file5.fs"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file5.oa" "Gotham_Groundfloor_Shop_OldB2_bump2d2.bv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file6.oc" "Gotham_Groundfloor_Shop_OldB2_blinn1.c"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_bump2d3.o" "Gotham_Groundfloor_Shop_OldB2_blinn1.n"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_blinn1.oc" "Gotham_Groundfloor_Shop_OldB2_blinn1SG.ss"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_blinn1SG.msg" "Gotham_Groundfloor_Shop_OldB2_materialInfo7.sg"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_blinn1.msg" "Gotham_Groundfloor_Shop_OldB2_materialInfo7.m"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file6.msg" "Gotham_Groundfloor_Shop_OldB2_materialInfo7.t"
		 -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.c" "Gotham_Groundfloor_Shop_OldB2_file6.c"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.tf" "Gotham_Groundfloor_Shop_OldB2_file6.tf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.rf" "Gotham_Groundfloor_Shop_OldB2_file6.rf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.mu" "Gotham_Groundfloor_Shop_OldB2_file6.mu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.mv" "Gotham_Groundfloor_Shop_OldB2_file6.mv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.s" "Gotham_Groundfloor_Shop_OldB2_file6.s"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.wu" "Gotham_Groundfloor_Shop_OldB2_file6.wu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.wv" "Gotham_Groundfloor_Shop_OldB2_file6.wv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.re" "Gotham_Groundfloor_Shop_OldB2_file6.re"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.of" "Gotham_Groundfloor_Shop_OldB2_file6.of"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.r" "Gotham_Groundfloor_Shop_OldB2_file6.ro"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.n" "Gotham_Groundfloor_Shop_OldB2_file6.n"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.vt1" "Gotham_Groundfloor_Shop_OldB2_file6.vt1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.vt2" "Gotham_Groundfloor_Shop_OldB2_file6.vt2"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.vt3" "Gotham_Groundfloor_Shop_OldB2_file6.vt3"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.vc1" "Gotham_Groundfloor_Shop_OldB2_file6.vc1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.o" "Gotham_Groundfloor_Shop_OldB2_file6.uv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.ofs" "Gotham_Groundfloor_Shop_OldB2_file6.fs"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file4.oc" "Gotham_Groundfloor_Shop_OldB2_phong2.c"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_bump2d2.o" "Gotham_Groundfloor_Shop_OldB2_phong2.n"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file7.oc" "Gotham_Groundfloor_Shop_OldB2_phong2.sc"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.c" "Gotham_Groundfloor_Shop_OldB2_file7.c"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.tf" "Gotham_Groundfloor_Shop_OldB2_file7.tf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.rf" "Gotham_Groundfloor_Shop_OldB2_file7.rf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.mu" "Gotham_Groundfloor_Shop_OldB2_file7.mu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.mv" "Gotham_Groundfloor_Shop_OldB2_file7.mv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.s" "Gotham_Groundfloor_Shop_OldB2_file7.s"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.wu" "Gotham_Groundfloor_Shop_OldB2_file7.wu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.wv" "Gotham_Groundfloor_Shop_OldB2_file7.wv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.re" "Gotham_Groundfloor_Shop_OldB2_file7.re"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.of" "Gotham_Groundfloor_Shop_OldB2_file7.of"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.r" "Gotham_Groundfloor_Shop_OldB2_file7.ro"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.n" "Gotham_Groundfloor_Shop_OldB2_file7.n"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.vt1" "Gotham_Groundfloor_Shop_OldB2_file7.vt1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.vt2" "Gotham_Groundfloor_Shop_OldB2_file7.vt2"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.vt3" "Gotham_Groundfloor_Shop_OldB2_file7.vt3"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.vc1" "Gotham_Groundfloor_Shop_OldB2_file7.vc1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.o" "Gotham_Groundfloor_Shop_OldB2_file7.uv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.ofs" "Gotham_Groundfloor_Shop_OldB2_file7.fs"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.c" "Gotham_Groundfloor_Shop_OldB2_file8.c"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.tf" "Gotham_Groundfloor_Shop_OldB2_file8.tf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.rf" "Gotham_Groundfloor_Shop_OldB2_file8.rf"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.mu" "Gotham_Groundfloor_Shop_OldB2_file8.mu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.mv" "Gotham_Groundfloor_Shop_OldB2_file8.mv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.s" "Gotham_Groundfloor_Shop_OldB2_file8.s"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.wu" "Gotham_Groundfloor_Shop_OldB2_file8.wu"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.wv" "Gotham_Groundfloor_Shop_OldB2_file8.wv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.re" "Gotham_Groundfloor_Shop_OldB2_file8.re"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.of" "Gotham_Groundfloor_Shop_OldB2_file8.of"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.r" "Gotham_Groundfloor_Shop_OldB2_file8.ro"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.n" "Gotham_Groundfloor_Shop_OldB2_file8.n"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.vt1" "Gotham_Groundfloor_Shop_OldB2_file8.vt1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.vt2" "Gotham_Groundfloor_Shop_OldB2_file8.vt2"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.vt3" "Gotham_Groundfloor_Shop_OldB2_file8.vt3"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.vc1" "Gotham_Groundfloor_Shop_OldB2_file8.vc1"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.o" "Gotham_Groundfloor_Shop_OldB2_file8.uv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.ofs" "Gotham_Groundfloor_Shop_OldB2_file8.fs"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file8.oa" "Gotham_Groundfloor_Shop_OldB2_bump2d3.bv"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_0.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[6].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_materialInfo1.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[7].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file1.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[8].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[9].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file2.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[10].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[11].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_bump2d1.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[12].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_phong1.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[13].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file3.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[14].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[15].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_nodeEditorPanel1Info.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[16].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_hyperView1.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[17].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_hyperLayout1.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[18].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_1.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[21].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_materialInfo2.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[22].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_2.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[23].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_materialInfo3.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[24].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_3.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[25].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_materialInfo4.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[26].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_4.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[27].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_materialInfo5.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[28].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_5.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[29].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_materialInfo6.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[30].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file4.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[31].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[32].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file5.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[33].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[34].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_bump2d2.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[35].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_blinn1.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[36].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_blinn1SG.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[37].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_materialInfo7.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[38].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file6.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[39].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[40].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_phong2.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[41].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file7.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[42].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[43].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file8.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[44].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[45].dn"
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_bump2d3.msg" "AD_Gotham_Groundfloor_Shop_OldB2_hyperLayout1.hyp[46].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_phong1.oc" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_0.ss"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_phong1.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo1.m"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_0.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo1.sg"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo1.t"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.c" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.c"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.tf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.tf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.rf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.rf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.mu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.mu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.mv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.mv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.s" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.s"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.wu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.wu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.wv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.wv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.re" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.re"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.of" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.of"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.r" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.ro"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.n" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.n"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.vt1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.vt1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.vt2" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.vt2"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.vt3" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.vt3"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.vc1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.vc1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.o" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.uv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.ofs" "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.fs"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.c" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.c"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.tf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.tf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.rf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.rf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.mu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.mu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.mv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.mv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.s" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.s"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.wu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.wu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.wv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.wv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.re" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.re"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.of" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.of"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.r" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.ro"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.n" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.n"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.vt1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.vt1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.vt2" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.vt2"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.vt3" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.vt3"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.vc1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.vc1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.o" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.uv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.ofs" "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.fs"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.oa" "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d1.bv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.oc" "OZ_Gotham_GroundFloor_Shop_OldA_03_phong1.c"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d1.o" "OZ_Gotham_GroundFloor_Shop_OldA_03_phong1.n"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.oc" "OZ_Gotham_GroundFloor_Shop_OldA_03_phong1.sc"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.c" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.c"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.tf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.tf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.rf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.rf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.mu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.mu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.mv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.mv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.s" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.s"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.wu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.wu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.wv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.wv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.re" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.re"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.of" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.of"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.r" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.ro"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.n" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.n"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.vt1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.vt1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.vt2" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.vt2"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.vt3" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.vt3"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.vc1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.vc1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.o" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.uv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.ofs" "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.fs"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_hyperView1.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_nodeEditorPanel1Info.b[0]"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_hyperView1.hl"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_1.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo2.sg"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_2.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo3.sg"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_3.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo4.sg"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_4.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo5.sg"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_phong2.oc" "OZ_Gotham_GroundFloor_Shop_OldA_03_material_5.ss"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_phong2.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo6.m"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_5.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo6.sg"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo6.t"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.c" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.c"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.tf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.tf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.rf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.rf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.mu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.mu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.mv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.mv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.s" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.s"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.wu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.wu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.wv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.wv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.re" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.re"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.of" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.of"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.r" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.ro"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.n" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.n"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.vt1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.vt1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.vt2" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.vt2"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.vt3" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.vt3"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.vc1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.vc1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.o" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.uv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.ofs" "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.fs"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.c" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.c"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.tf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.tf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.rf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.rf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.mu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.mu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.mv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.mv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.s" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.s"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.wu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.wu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.wv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.wv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.re" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.re"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.of" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.of"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.r" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.ro"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.n" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.n"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.vt1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.vt1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.vt2" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.vt2"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.vt3" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.vt3"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.vc1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.vc1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.o" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.uv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.ofs" "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.fs"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.oa" "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d2.bv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.oc" "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1.c"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d3.o" "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1.n"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1.oc" "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1SG.ss"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1SG.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo7.sg"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo7.m"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo7.t"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.c" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.c"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.tf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.tf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.rf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.rf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.mu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.mu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.mv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.mv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.s" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.s"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.wu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.wu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.wv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.wv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.re" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.re"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.of" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.of"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.r" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.ro"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.n" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.n"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.vt1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.vt1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.vt2" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.vt2"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.vt3" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.vt3"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.vc1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.vc1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.o" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.uv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.ofs" "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.fs"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.oc" "OZ_Gotham_GroundFloor_Shop_OldA_03_phong2.c"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d2.o" "OZ_Gotham_GroundFloor_Shop_OldA_03_phong2.n"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.oc" "OZ_Gotham_GroundFloor_Shop_OldA_03_phong2.sc"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.c" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.c"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.tf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.tf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.rf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.rf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.mu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.mu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.mv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.mv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.s" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.s"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.wu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.wu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.wv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.wv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.re" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.re"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.of" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.of"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.r" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.ro"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.n" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.n"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.vt1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.vt1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.vt2" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.vt2"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.vt3" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.vt3"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.vc1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.vc1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.o" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.uv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.ofs" "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.fs"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.c" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.c"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.tf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.tf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.rf" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.rf"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.mu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.mu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.mv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.mv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.s" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.s"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.wu" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.wu"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.wv" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.wv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.re" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.re"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.of" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.of"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.r" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.ro"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.n" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.n"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.vt1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.vt1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.vt2" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.vt2"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.vt3" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.vt3"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.vc1" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.vc1"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.o" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.uv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.ofs" "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.fs"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.oa" "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d3.bv"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_6.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo8.sg"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_7.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo9.sg"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_8.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo10.sg"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_9.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo11.sg"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_10.msg" "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo12.sg"
		;
connectAttr "material_11.msg" "materialInfo13.sg";
connectAttr "material_12.msg" "materialInfo14.sg";
connectAttr "material_13.msg" "materialInfo15.sg";
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_0.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[6].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo1.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[7].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[8].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[9].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[10].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[11].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d1.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[12].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_phong1.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[13].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[14].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[15].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_nodeEditorPanel1Info.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[16].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_hyperView1.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[17].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[18].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_1.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[21].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo2.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[22].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_2.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[23].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo3.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[24].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_3.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[25].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo4.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[26].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_4.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[27].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo5.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[28].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_5.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[29].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo6.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[30].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[31].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[32].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[33].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[34].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d2.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[35].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[36].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1SG.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[37].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo7.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[38].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[39].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[40].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_phong2.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[41].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[42].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[43].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[44].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[45].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d3.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[46].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_6.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[47].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo8.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[48].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_7.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[49].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo9.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[50].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_8.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[51].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo10.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[52].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_9.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[53].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo11.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[54].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_10.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[55].dn"
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_materialInfo12.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[56].dn"
		;
connectAttr "material_11.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[57].dn"
		;
connectAttr "materialInfo13.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[58].dn"
		;
connectAttr "material_12.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[59].dn"
		;
connectAttr "materialInfo14.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[60].dn"
		;
connectAttr "material_13.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[61].dn"
		;
connectAttr "materialInfo15.msg" "AD_OZ_Gotham_GroundFloor_Shop_OldA_03_hyperLayout1.hyp[62].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_0.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo1.sg"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_1.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo2.sg"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file1.oc" "material_0_lambert2.c";
connectAttr "Gotham_ARCH_Classic_BigWinx2_bump2d1.o" "material_0_lambert2.n";
connectAttr "material_0_lambert2.oc" "Gotham_ARCH_Classic_BigWinx2_material_2.ss"
		;
connectAttr "material_0_lambert2.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo3.m"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_2.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo3.sg"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file1.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo3.t"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.c" "Gotham_ARCH_Classic_BigWinx2_file1.c"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.tf" "Gotham_ARCH_Classic_BigWinx2_file1.tf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.rf" "Gotham_ARCH_Classic_BigWinx2_file1.rf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.mu" "Gotham_ARCH_Classic_BigWinx2_file1.mu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.mv" "Gotham_ARCH_Classic_BigWinx2_file1.mv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.s" "Gotham_ARCH_Classic_BigWinx2_file1.s"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.wu" "Gotham_ARCH_Classic_BigWinx2_file1.wu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.wv" "Gotham_ARCH_Classic_BigWinx2_file1.wv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.re" "Gotham_ARCH_Classic_BigWinx2_file1.re"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.of" "Gotham_ARCH_Classic_BigWinx2_file1.of"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.r" "Gotham_ARCH_Classic_BigWinx2_file1.ro"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.n" "Gotham_ARCH_Classic_BigWinx2_file1.n"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.vt1" "Gotham_ARCH_Classic_BigWinx2_file1.vt1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.vt2" "Gotham_ARCH_Classic_BigWinx2_file1.vt2"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.vt3" "Gotham_ARCH_Classic_BigWinx2_file1.vt3"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.vc1" "Gotham_ARCH_Classic_BigWinx2_file1.vc1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.o" "Gotham_ARCH_Classic_BigWinx2_file1.uv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.ofs" "Gotham_ARCH_Classic_BigWinx2_file1.fs"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.c" "Gotham_ARCH_Classic_BigWinx2_file2.c"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.tf" "Gotham_ARCH_Classic_BigWinx2_file2.tf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.rf" "Gotham_ARCH_Classic_BigWinx2_file2.rf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.mu" "Gotham_ARCH_Classic_BigWinx2_file2.mu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.mv" "Gotham_ARCH_Classic_BigWinx2_file2.mv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.s" "Gotham_ARCH_Classic_BigWinx2_file2.s"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.wu" "Gotham_ARCH_Classic_BigWinx2_file2.wu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.wv" "Gotham_ARCH_Classic_BigWinx2_file2.wv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.re" "Gotham_ARCH_Classic_BigWinx2_file2.re"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.of" "Gotham_ARCH_Classic_BigWinx2_file2.of"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.r" "Gotham_ARCH_Classic_BigWinx2_file2.ro"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.n" "Gotham_ARCH_Classic_BigWinx2_file2.n"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.vt1" "Gotham_ARCH_Classic_BigWinx2_file2.vt1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.vt2" "Gotham_ARCH_Classic_BigWinx2_file2.vt2"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.vt3" "Gotham_ARCH_Classic_BigWinx2_file2.vt3"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.vc1" "Gotham_ARCH_Classic_BigWinx2_file2.vc1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.o" "Gotham_ARCH_Classic_BigWinx2_file2.uv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.ofs" "Gotham_ARCH_Classic_BigWinx2_file2.fs"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file2.oa" "Gotham_ARCH_Classic_BigWinx2_bump2d1.bv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_3.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo4.sg"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_4.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo5.sg"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_5.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo6.sg"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_6.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo7.sg"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_7.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo8.sg"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.c" "Gotham_ARCH_Classic_BigWinx2_file3.c"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.tf" "Gotham_ARCH_Classic_BigWinx2_file3.tf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.rf" "Gotham_ARCH_Classic_BigWinx2_file3.rf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.mu" "Gotham_ARCH_Classic_BigWinx2_file3.mu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.mv" "Gotham_ARCH_Classic_BigWinx2_file3.mv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.s" "Gotham_ARCH_Classic_BigWinx2_file3.s"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.wu" "Gotham_ARCH_Classic_BigWinx2_file3.wu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.wv" "Gotham_ARCH_Classic_BigWinx2_file3.wv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.re" "Gotham_ARCH_Classic_BigWinx2_file3.re"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.of" "Gotham_ARCH_Classic_BigWinx2_file3.of"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.r" "Gotham_ARCH_Classic_BigWinx2_file3.ro"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.n" "Gotham_ARCH_Classic_BigWinx2_file3.n"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.vt1" "Gotham_ARCH_Classic_BigWinx2_file3.vt1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.vt2" "Gotham_ARCH_Classic_BigWinx2_file3.vt2"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.vt3" "Gotham_ARCH_Classic_BigWinx2_file3.vt3"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.vc1" "Gotham_ARCH_Classic_BigWinx2_file3.vc1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.o" "Gotham_ARCH_Classic_BigWinx2_file3.uv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.ofs" "Gotham_ARCH_Classic_BigWinx2_file3.fs"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_8.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo9.sg"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.c" "Gotham_ARCH_Classic_BigWinx2_file4.c"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.tf" "Gotham_ARCH_Classic_BigWinx2_file4.tf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.rf" "Gotham_ARCH_Classic_BigWinx2_file4.rf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.mu" "Gotham_ARCH_Classic_BigWinx2_file4.mu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.mv" "Gotham_ARCH_Classic_BigWinx2_file4.mv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.s" "Gotham_ARCH_Classic_BigWinx2_file4.s"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.wu" "Gotham_ARCH_Classic_BigWinx2_file4.wu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.wv" "Gotham_ARCH_Classic_BigWinx2_file4.wv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.re" "Gotham_ARCH_Classic_BigWinx2_file4.re"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.of" "Gotham_ARCH_Classic_BigWinx2_file4.of"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.r" "Gotham_ARCH_Classic_BigWinx2_file4.ro"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.n" "Gotham_ARCH_Classic_BigWinx2_file4.n"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.vt1" "Gotham_ARCH_Classic_BigWinx2_file4.vt1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.vt2" "Gotham_ARCH_Classic_BigWinx2_file4.vt2"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.vt3" "Gotham_ARCH_Classic_BigWinx2_file4.vt3"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.vc1" "Gotham_ARCH_Classic_BigWinx2_file4.vc1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.o" "Gotham_ARCH_Classic_BigWinx2_file4.uv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.ofs" "Gotham_ARCH_Classic_BigWinx2_file4.fs"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.c" "Gotham_ARCH_Classic_BigWinx2_file5.c"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.tf" "Gotham_ARCH_Classic_BigWinx2_file5.tf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.rf" "Gotham_ARCH_Classic_BigWinx2_file5.rf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.mu" "Gotham_ARCH_Classic_BigWinx2_file5.mu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.mv" "Gotham_ARCH_Classic_BigWinx2_file5.mv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.s" "Gotham_ARCH_Classic_BigWinx2_file5.s"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.wu" "Gotham_ARCH_Classic_BigWinx2_file5.wu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.wv" "Gotham_ARCH_Classic_BigWinx2_file5.wv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.re" "Gotham_ARCH_Classic_BigWinx2_file5.re"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.of" "Gotham_ARCH_Classic_BigWinx2_file5.of"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.r" "Gotham_ARCH_Classic_BigWinx2_file5.ro"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.n" "Gotham_ARCH_Classic_BigWinx2_file5.n"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.vt1" "Gotham_ARCH_Classic_BigWinx2_file5.vt1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.vt2" "Gotham_ARCH_Classic_BigWinx2_file5.vt2"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.vt3" "Gotham_ARCH_Classic_BigWinx2_file5.vt3"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.vc1" "Gotham_ARCH_Classic_BigWinx2_file5.vc1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.o" "Gotham_ARCH_Classic_BigWinx2_file5.uv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.ofs" "Gotham_ARCH_Classic_BigWinx2_file5.fs"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file5.oa" "Gotham_ARCH_Classic_BigWinx2_bump2d2.bv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_phong1.oc" "Gotham_ARCH_Classic_BigWinx2_material_9.ss"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_phong1.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo10.m"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_9.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo10.sg"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file6.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo10.t"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_blinn1.oc" "Gotham_ARCH_Classic_BigWinx2_material_10.ss"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_blinn1.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo11.m"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_10.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo11.sg"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file8.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo11.t"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.c" "Gotham_ARCH_Classic_BigWinx2_file6.c"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.tf" "Gotham_ARCH_Classic_BigWinx2_file6.tf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.rf" "Gotham_ARCH_Classic_BigWinx2_file6.rf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.mu" "Gotham_ARCH_Classic_BigWinx2_file6.mu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.mv" "Gotham_ARCH_Classic_BigWinx2_file6.mv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.s" "Gotham_ARCH_Classic_BigWinx2_file6.s"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.wu" "Gotham_ARCH_Classic_BigWinx2_file6.wu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.wv" "Gotham_ARCH_Classic_BigWinx2_file6.wv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.re" "Gotham_ARCH_Classic_BigWinx2_file6.re"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.of" "Gotham_ARCH_Classic_BigWinx2_file6.of"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.r" "Gotham_ARCH_Classic_BigWinx2_file6.ro"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.n" "Gotham_ARCH_Classic_BigWinx2_file6.n"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.vt1" "Gotham_ARCH_Classic_BigWinx2_file6.vt1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.vt2" "Gotham_ARCH_Classic_BigWinx2_file6.vt2"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.vt3" "Gotham_ARCH_Classic_BigWinx2_file6.vt3"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.vc1" "Gotham_ARCH_Classic_BigWinx2_file6.vc1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.o" "Gotham_ARCH_Classic_BigWinx2_file6.uv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.ofs" "Gotham_ARCH_Classic_BigWinx2_file6.fs"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.c" "Gotham_ARCH_Classic_BigWinx2_file7.c"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.tf" "Gotham_ARCH_Classic_BigWinx2_file7.tf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.rf" "Gotham_ARCH_Classic_BigWinx2_file7.rf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.mu" "Gotham_ARCH_Classic_BigWinx2_file7.mu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.mv" "Gotham_ARCH_Classic_BigWinx2_file7.mv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.s" "Gotham_ARCH_Classic_BigWinx2_file7.s"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.wu" "Gotham_ARCH_Classic_BigWinx2_file7.wu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.wv" "Gotham_ARCH_Classic_BigWinx2_file7.wv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.re" "Gotham_ARCH_Classic_BigWinx2_file7.re"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.of" "Gotham_ARCH_Classic_BigWinx2_file7.of"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.r" "Gotham_ARCH_Classic_BigWinx2_file7.ro"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.n" "Gotham_ARCH_Classic_BigWinx2_file7.n"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.vt1" "Gotham_ARCH_Classic_BigWinx2_file7.vt1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.vt2" "Gotham_ARCH_Classic_BigWinx2_file7.vt2"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.vt3" "Gotham_ARCH_Classic_BigWinx2_file7.vt3"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.vc1" "Gotham_ARCH_Classic_BigWinx2_file7.vc1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.o" "Gotham_ARCH_Classic_BigWinx2_file7.uv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.ofs" "Gotham_ARCH_Classic_BigWinx2_file7.fs"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file7.oa" "Gotham_ARCH_Classic_BigWinx2_bump2d3.bv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.c" "Gotham_ARCH_Classic_BigWinx2_file8.c"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.tf" "Gotham_ARCH_Classic_BigWinx2_file8.tf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.rf" "Gotham_ARCH_Classic_BigWinx2_file8.rf"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.mu" "Gotham_ARCH_Classic_BigWinx2_file8.mu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.mv" "Gotham_ARCH_Classic_BigWinx2_file8.mv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.s" "Gotham_ARCH_Classic_BigWinx2_file8.s"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.wu" "Gotham_ARCH_Classic_BigWinx2_file8.wu"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.wv" "Gotham_ARCH_Classic_BigWinx2_file8.wv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.re" "Gotham_ARCH_Classic_BigWinx2_file8.re"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.of" "Gotham_ARCH_Classic_BigWinx2_file8.of"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.r" "Gotham_ARCH_Classic_BigWinx2_file8.ro"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.n" "Gotham_ARCH_Classic_BigWinx2_file8.n"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.vt1" "Gotham_ARCH_Classic_BigWinx2_file8.vt1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.vt2" "Gotham_ARCH_Classic_BigWinx2_file8.vt2"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.vt3" "Gotham_ARCH_Classic_BigWinx2_file8.vt3"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.vc1" "Gotham_ARCH_Classic_BigWinx2_file8.vc1"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.o" "Gotham_ARCH_Classic_BigWinx2_file8.uv"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.ofs" "Gotham_ARCH_Classic_BigWinx2_file8.fs"
		;
connectAttr "place2dTexture9.c" "file9.c";
connectAttr "place2dTexture9.tf" "file9.tf";
connectAttr "place2dTexture9.rf" "file9.rf";
connectAttr "place2dTexture9.mu" "file9.mu";
connectAttr "place2dTexture9.mv" "file9.mv";
connectAttr "place2dTexture9.s" "file9.s";
connectAttr "place2dTexture9.wu" "file9.wu";
connectAttr "place2dTexture9.wv" "file9.wv";
connectAttr "place2dTexture9.re" "file9.re";
connectAttr "place2dTexture9.of" "file9.of";
connectAttr "place2dTexture9.r" "file9.ro";
connectAttr "place2dTexture9.n" "file9.n";
connectAttr "place2dTexture9.vt1" "file9.vt1";
connectAttr "place2dTexture9.vt2" "file9.vt2";
connectAttr "place2dTexture9.vt3" "file9.vt3";
connectAttr "place2dTexture9.vc1" "file9.vc1";
connectAttr "place2dTexture9.o" "file9.uv";
connectAttr "place2dTexture9.ofs" "file9.fs";
connectAttr "file9.oa" "bump2d4.bv";
connectAttr "Gotham_ARCH_Classic_BigWinx2_hyperView1.msg" "Gotham_ARCH_Classic_BigWinx2_nodeEditorPanel1Info.b[0]"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_hyperLayout1.msg" "Gotham_ARCH_Classic_BigWinx2_hyperView1.hl"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_11.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo12.sg"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file6.oc" "Gotham_ARCH_Classic_BigWinx2_phong1.c"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_bump2d3.o" "Gotham_ARCH_Classic_BigWinx2_phong1.n"
		;
connectAttr "file10.oc" "Gotham_ARCH_Classic_BigWinx2_phong1.sc";
connectAttr "place2dTexture10.c" "file10.c";
connectAttr "place2dTexture10.tf" "file10.tf";
connectAttr "place2dTexture10.rf" "file10.rf";
connectAttr "place2dTexture10.mu" "file10.mu";
connectAttr "place2dTexture10.mv" "file10.mv";
connectAttr "place2dTexture10.s" "file10.s";
connectAttr "place2dTexture10.wu" "file10.wu";
connectAttr "place2dTexture10.wv" "file10.wv";
connectAttr "place2dTexture10.re" "file10.re";
connectAttr "place2dTexture10.of" "file10.of";
connectAttr "place2dTexture10.r" "file10.ro";
connectAttr "place2dTexture10.n" "file10.n";
connectAttr "place2dTexture10.vt1" "file10.vt1";
connectAttr "place2dTexture10.vt2" "file10.vt2";
connectAttr "place2dTexture10.vt3" "file10.vt3";
connectAttr "place2dTexture10.vc1" "file10.vc1";
connectAttr "place2dTexture10.o" "file10.uv";
connectAttr "place2dTexture10.ofs" "file10.fs";
connectAttr "Gotham_ARCH_Classic_BigWinx2_file8.oc" "Gotham_ARCH_Classic_BigWinx2_blinn1.c"
		;
connectAttr "bump2d4.o" "Gotham_ARCH_Classic_BigWinx2_blinn1.n";
connectAttr "file11.oc" "Gotham_ARCH_Classic_BigWinx2_blinn1.sc";
connectAttr "place2dTexture11.c" "file11.c";
connectAttr "place2dTexture11.tf" "file11.tf";
connectAttr "place2dTexture11.rf" "file11.rf";
connectAttr "place2dTexture11.mu" "file11.mu";
connectAttr "place2dTexture11.mv" "file11.mv";
connectAttr "place2dTexture11.s" "file11.s";
connectAttr "place2dTexture11.wu" "file11.wu";
connectAttr "place2dTexture11.wv" "file11.wv";
connectAttr "place2dTexture11.re" "file11.re";
connectAttr "place2dTexture11.of" "file11.of";
connectAttr "place2dTexture11.r" "file11.ro";
connectAttr "place2dTexture11.n" "file11.n";
connectAttr "place2dTexture11.vt1" "file11.vt1";
connectAttr "place2dTexture11.vt2" "file11.vt2";
connectAttr "place2dTexture11.vt3" "file11.vt3";
connectAttr "place2dTexture11.vc1" "file11.vc1";
connectAttr "place2dTexture11.o" "file11.uv";
connectAttr "place2dTexture11.ofs" "file11.fs";
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_12.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo13.sg"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_13.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo14.sg"
		;
connectAttr "material_14.msg" "Gotham_ARCH_Classic_BigWinx2_materialInfo15.sg";
connectAttr "material_15.msg" "materialInfo16.sg";
connectAttr "material_16.msg" "materialInfo17.sg";
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_0.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[6].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo1.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[7].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_1.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[8].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo2.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[9].dn"
		;
connectAttr "material_0_lambert2.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[10].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_2.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[11].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo3.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[12].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file1.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[13].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[14].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file2.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[15].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[16].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_bump2d1.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[17].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_3.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[18].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo4.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[19].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_4.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[20].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo5.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[21].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_5.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[22].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo6.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[23].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_6.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[24].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo7.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[25].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_7.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[26].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo8.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[27].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file3.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[28].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[29].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_8.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[30].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo9.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[31].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file4.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[32].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[33].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file5.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[34].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[35].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_bump2d2.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[36].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_9.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[37].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo10.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[38].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_10.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[39].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo11.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[40].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file6.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[41].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[42].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file7.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[43].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[44].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_bump2d3.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[45].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file8.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[46].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[47].dn"
		;
connectAttr "file9.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[48].dn"
		;
connectAttr "place2dTexture9.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[49].dn"
		;
connectAttr "bump2d4.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[50].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_nodeEditorPanel1Info.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[51].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_hyperView1.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[52].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_hyperLayout1.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[53].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_11.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[56].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo12.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[57].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_phong1.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[58].dn"
		;
connectAttr "file10.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[59].dn"
		;
connectAttr "place2dTexture10.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[60].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_blinn1.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[61].dn"
		;
connectAttr "file11.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[62].dn"
		;
connectAttr "place2dTexture11.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[63].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_12.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[64].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo13.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[65].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_13.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[66].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo14.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[67].dn"
		;
connectAttr "material_14.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[68].dn"
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_materialInfo15.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[69].dn"
		;
connectAttr "material_15.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[70].dn"
		;
connectAttr "materialInfo16.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[71].dn"
		;
connectAttr "material_16.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[72].dn"
		;
connectAttr "materialInfo17.msg" "AD_Gotham_ARCH_Classic_BigWinx2_hyperLayout1.hyp[73].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_0.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo1.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_1.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo2.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file1.oc" "Gotham_ARCH_Classic_WinBCorner_material_0_lambert2.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_bump2d1.o" "Gotham_ARCH_Classic_WinBCorner_material_0_lambert2.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_0_lambert2.oc" "Gotham_ARCH_Classic_WinBCorner_material_2.ss"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_0_lambert2.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo3.m"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_2.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo3.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file1.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo3.t"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.c" "Gotham_ARCH_Classic_WinBCorner_file1.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.tf" "Gotham_ARCH_Classic_WinBCorner_file1.tf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.rf" "Gotham_ARCH_Classic_WinBCorner_file1.rf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.mu" "Gotham_ARCH_Classic_WinBCorner_file1.mu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.mv" "Gotham_ARCH_Classic_WinBCorner_file1.mv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.s" "Gotham_ARCH_Classic_WinBCorner_file1.s"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.wu" "Gotham_ARCH_Classic_WinBCorner_file1.wu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.wv" "Gotham_ARCH_Classic_WinBCorner_file1.wv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.re" "Gotham_ARCH_Classic_WinBCorner_file1.re"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.of" "Gotham_ARCH_Classic_WinBCorner_file1.of"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.r" "Gotham_ARCH_Classic_WinBCorner_file1.ro"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.n" "Gotham_ARCH_Classic_WinBCorner_file1.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.vt1" "Gotham_ARCH_Classic_WinBCorner_file1.vt1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.vt2" "Gotham_ARCH_Classic_WinBCorner_file1.vt2"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.vt3" "Gotham_ARCH_Classic_WinBCorner_file1.vt3"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.vc1" "Gotham_ARCH_Classic_WinBCorner_file1.vc1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.o" "Gotham_ARCH_Classic_WinBCorner_file1.uv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.ofs" "Gotham_ARCH_Classic_WinBCorner_file1.fs"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.c" "Gotham_ARCH_Classic_WinBCorner_file2.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.tf" "Gotham_ARCH_Classic_WinBCorner_file2.tf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.rf" "Gotham_ARCH_Classic_WinBCorner_file2.rf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.mu" "Gotham_ARCH_Classic_WinBCorner_file2.mu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.mv" "Gotham_ARCH_Classic_WinBCorner_file2.mv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.s" "Gotham_ARCH_Classic_WinBCorner_file2.s"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.wu" "Gotham_ARCH_Classic_WinBCorner_file2.wu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.wv" "Gotham_ARCH_Classic_WinBCorner_file2.wv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.re" "Gotham_ARCH_Classic_WinBCorner_file2.re"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.of" "Gotham_ARCH_Classic_WinBCorner_file2.of"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.r" "Gotham_ARCH_Classic_WinBCorner_file2.ro"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.n" "Gotham_ARCH_Classic_WinBCorner_file2.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.vt1" "Gotham_ARCH_Classic_WinBCorner_file2.vt1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.vt2" "Gotham_ARCH_Classic_WinBCorner_file2.vt2"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.vt3" "Gotham_ARCH_Classic_WinBCorner_file2.vt3"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.vc1" "Gotham_ARCH_Classic_WinBCorner_file2.vc1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.o" "Gotham_ARCH_Classic_WinBCorner_file2.uv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.ofs" "Gotham_ARCH_Classic_WinBCorner_file2.fs"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file2.oa" "Gotham_ARCH_Classic_WinBCorner_bump2d1.bv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_3.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo4.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_4.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo5.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_5.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo6.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_6.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo7.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_7.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo8.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.c" "Gotham_ARCH_Classic_WinBCorner_file3.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.tf" "Gotham_ARCH_Classic_WinBCorner_file3.tf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.rf" "Gotham_ARCH_Classic_WinBCorner_file3.rf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.mu" "Gotham_ARCH_Classic_WinBCorner_file3.mu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.mv" "Gotham_ARCH_Classic_WinBCorner_file3.mv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.s" "Gotham_ARCH_Classic_WinBCorner_file3.s"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.wu" "Gotham_ARCH_Classic_WinBCorner_file3.wu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.wv" "Gotham_ARCH_Classic_WinBCorner_file3.wv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.re" "Gotham_ARCH_Classic_WinBCorner_file3.re"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.of" "Gotham_ARCH_Classic_WinBCorner_file3.of"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.r" "Gotham_ARCH_Classic_WinBCorner_file3.ro"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.n" "Gotham_ARCH_Classic_WinBCorner_file3.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.vt1" "Gotham_ARCH_Classic_WinBCorner_file3.vt1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.vt2" "Gotham_ARCH_Classic_WinBCorner_file3.vt2"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.vt3" "Gotham_ARCH_Classic_WinBCorner_file3.vt3"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.vc1" "Gotham_ARCH_Classic_WinBCorner_file3.vc1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.o" "Gotham_ARCH_Classic_WinBCorner_file3.uv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.ofs" "Gotham_ARCH_Classic_WinBCorner_file3.fs"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_8.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo9.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.c" "Gotham_ARCH_Classic_WinBCorner_file4.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.tf" "Gotham_ARCH_Classic_WinBCorner_file4.tf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.rf" "Gotham_ARCH_Classic_WinBCorner_file4.rf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.mu" "Gotham_ARCH_Classic_WinBCorner_file4.mu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.mv" "Gotham_ARCH_Classic_WinBCorner_file4.mv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.s" "Gotham_ARCH_Classic_WinBCorner_file4.s"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.wu" "Gotham_ARCH_Classic_WinBCorner_file4.wu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.wv" "Gotham_ARCH_Classic_WinBCorner_file4.wv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.re" "Gotham_ARCH_Classic_WinBCorner_file4.re"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.of" "Gotham_ARCH_Classic_WinBCorner_file4.of"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.r" "Gotham_ARCH_Classic_WinBCorner_file4.ro"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.n" "Gotham_ARCH_Classic_WinBCorner_file4.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.vt1" "Gotham_ARCH_Classic_WinBCorner_file4.vt1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.vt2" "Gotham_ARCH_Classic_WinBCorner_file4.vt2"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.vt3" "Gotham_ARCH_Classic_WinBCorner_file4.vt3"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.vc1" "Gotham_ARCH_Classic_WinBCorner_file4.vc1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.o" "Gotham_ARCH_Classic_WinBCorner_file4.uv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.ofs" "Gotham_ARCH_Classic_WinBCorner_file4.fs"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.c" "Gotham_ARCH_Classic_WinBCorner_file5.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.tf" "Gotham_ARCH_Classic_WinBCorner_file5.tf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.rf" "Gotham_ARCH_Classic_WinBCorner_file5.rf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.mu" "Gotham_ARCH_Classic_WinBCorner_file5.mu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.mv" "Gotham_ARCH_Classic_WinBCorner_file5.mv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.s" "Gotham_ARCH_Classic_WinBCorner_file5.s"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.wu" "Gotham_ARCH_Classic_WinBCorner_file5.wu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.wv" "Gotham_ARCH_Classic_WinBCorner_file5.wv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.re" "Gotham_ARCH_Classic_WinBCorner_file5.re"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.of" "Gotham_ARCH_Classic_WinBCorner_file5.of"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.r" "Gotham_ARCH_Classic_WinBCorner_file5.ro"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.n" "Gotham_ARCH_Classic_WinBCorner_file5.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.vt1" "Gotham_ARCH_Classic_WinBCorner_file5.vt1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.vt2" "Gotham_ARCH_Classic_WinBCorner_file5.vt2"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.vt3" "Gotham_ARCH_Classic_WinBCorner_file5.vt3"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.vc1" "Gotham_ARCH_Classic_WinBCorner_file5.vc1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.o" "Gotham_ARCH_Classic_WinBCorner_file5.uv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.ofs" "Gotham_ARCH_Classic_WinBCorner_file5.fs"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file5.oa" "Gotham_ARCH_Classic_WinBCorner_bump2d2.bv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_phong1.oc" "Gotham_ARCH_Classic_WinBCorner_material_9.ss"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_phong1.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo10.m"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_9.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo10.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file6.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo10.t"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_blinn1.oc" "Gotham_ARCH_Classic_WinBCorner_material_10.ss"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_blinn1.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo11.m"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_10.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo11.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file8.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo11.t"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.c" "Gotham_ARCH_Classic_WinBCorner_file6.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.tf" "Gotham_ARCH_Classic_WinBCorner_file6.tf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.rf" "Gotham_ARCH_Classic_WinBCorner_file6.rf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.mu" "Gotham_ARCH_Classic_WinBCorner_file6.mu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.mv" "Gotham_ARCH_Classic_WinBCorner_file6.mv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.s" "Gotham_ARCH_Classic_WinBCorner_file6.s"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.wu" "Gotham_ARCH_Classic_WinBCorner_file6.wu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.wv" "Gotham_ARCH_Classic_WinBCorner_file6.wv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.re" "Gotham_ARCH_Classic_WinBCorner_file6.re"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.of" "Gotham_ARCH_Classic_WinBCorner_file6.of"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.r" "Gotham_ARCH_Classic_WinBCorner_file6.ro"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.n" "Gotham_ARCH_Classic_WinBCorner_file6.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.vt1" "Gotham_ARCH_Classic_WinBCorner_file6.vt1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.vt2" "Gotham_ARCH_Classic_WinBCorner_file6.vt2"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.vt3" "Gotham_ARCH_Classic_WinBCorner_file6.vt3"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.vc1" "Gotham_ARCH_Classic_WinBCorner_file6.vc1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.o" "Gotham_ARCH_Classic_WinBCorner_file6.uv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.ofs" "Gotham_ARCH_Classic_WinBCorner_file6.fs"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.c" "Gotham_ARCH_Classic_WinBCorner_file7.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.tf" "Gotham_ARCH_Classic_WinBCorner_file7.tf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.rf" "Gotham_ARCH_Classic_WinBCorner_file7.rf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.mu" "Gotham_ARCH_Classic_WinBCorner_file7.mu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.mv" "Gotham_ARCH_Classic_WinBCorner_file7.mv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.s" "Gotham_ARCH_Classic_WinBCorner_file7.s"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.wu" "Gotham_ARCH_Classic_WinBCorner_file7.wu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.wv" "Gotham_ARCH_Classic_WinBCorner_file7.wv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.re" "Gotham_ARCH_Classic_WinBCorner_file7.re"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.of" "Gotham_ARCH_Classic_WinBCorner_file7.of"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.r" "Gotham_ARCH_Classic_WinBCorner_file7.ro"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.n" "Gotham_ARCH_Classic_WinBCorner_file7.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.vt1" "Gotham_ARCH_Classic_WinBCorner_file7.vt1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.vt2" "Gotham_ARCH_Classic_WinBCorner_file7.vt2"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.vt3" "Gotham_ARCH_Classic_WinBCorner_file7.vt3"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.vc1" "Gotham_ARCH_Classic_WinBCorner_file7.vc1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.o" "Gotham_ARCH_Classic_WinBCorner_file7.uv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.ofs" "Gotham_ARCH_Classic_WinBCorner_file7.fs"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file7.oa" "Gotham_ARCH_Classic_WinBCorner_bump2d3.bv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.c" "Gotham_ARCH_Classic_WinBCorner_file8.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.tf" "Gotham_ARCH_Classic_WinBCorner_file8.tf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.rf" "Gotham_ARCH_Classic_WinBCorner_file8.rf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.mu" "Gotham_ARCH_Classic_WinBCorner_file8.mu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.mv" "Gotham_ARCH_Classic_WinBCorner_file8.mv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.s" "Gotham_ARCH_Classic_WinBCorner_file8.s"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.wu" "Gotham_ARCH_Classic_WinBCorner_file8.wu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.wv" "Gotham_ARCH_Classic_WinBCorner_file8.wv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.re" "Gotham_ARCH_Classic_WinBCorner_file8.re"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.of" "Gotham_ARCH_Classic_WinBCorner_file8.of"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.r" "Gotham_ARCH_Classic_WinBCorner_file8.ro"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.n" "Gotham_ARCH_Classic_WinBCorner_file8.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.vt1" "Gotham_ARCH_Classic_WinBCorner_file8.vt1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.vt2" "Gotham_ARCH_Classic_WinBCorner_file8.vt2"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.vt3" "Gotham_ARCH_Classic_WinBCorner_file8.vt3"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.vc1" "Gotham_ARCH_Classic_WinBCorner_file8.vc1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.o" "Gotham_ARCH_Classic_WinBCorner_file8.uv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.ofs" "Gotham_ARCH_Classic_WinBCorner_file8.fs"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.c" "Gotham_ARCH_Classic_WinBCorner_file9.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.tf" "Gotham_ARCH_Classic_WinBCorner_file9.tf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.rf" "Gotham_ARCH_Classic_WinBCorner_file9.rf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.mu" "Gotham_ARCH_Classic_WinBCorner_file9.mu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.mv" "Gotham_ARCH_Classic_WinBCorner_file9.mv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.s" "Gotham_ARCH_Classic_WinBCorner_file9.s"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.wu" "Gotham_ARCH_Classic_WinBCorner_file9.wu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.wv" "Gotham_ARCH_Classic_WinBCorner_file9.wv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.re" "Gotham_ARCH_Classic_WinBCorner_file9.re"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.of" "Gotham_ARCH_Classic_WinBCorner_file9.of"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.r" "Gotham_ARCH_Classic_WinBCorner_file9.ro"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.n" "Gotham_ARCH_Classic_WinBCorner_file9.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.vt1" "Gotham_ARCH_Classic_WinBCorner_file9.vt1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.vt2" "Gotham_ARCH_Classic_WinBCorner_file9.vt2"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.vt3" "Gotham_ARCH_Classic_WinBCorner_file9.vt3"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.vc1" "Gotham_ARCH_Classic_WinBCorner_file9.vc1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.o" "Gotham_ARCH_Classic_WinBCorner_file9.uv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.ofs" "Gotham_ARCH_Classic_WinBCorner_file9.fs"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file9.oa" "Gotham_ARCH_Classic_WinBCorner_bump2d4.bv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_hyperView1.msg" "Gotham_ARCH_Classic_WinBCorner_nodeEditorPanel1Info.b[0]"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_hyperLayout1.msg" "Gotham_ARCH_Classic_WinBCorner_hyperView1.hl"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_11.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo12.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file6.oc" "Gotham_ARCH_Classic_WinBCorner_phong1.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_bump2d3.o" "Gotham_ARCH_Classic_WinBCorner_phong1.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file10.oc" "Gotham_ARCH_Classic_WinBCorner_phong1.sc"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.c" "Gotham_ARCH_Classic_WinBCorner_file10.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.tf" "Gotham_ARCH_Classic_WinBCorner_file10.tf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.rf" "Gotham_ARCH_Classic_WinBCorner_file10.rf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.mu" "Gotham_ARCH_Classic_WinBCorner_file10.mu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.mv" "Gotham_ARCH_Classic_WinBCorner_file10.mv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.s" "Gotham_ARCH_Classic_WinBCorner_file10.s"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.wu" "Gotham_ARCH_Classic_WinBCorner_file10.wu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.wv" "Gotham_ARCH_Classic_WinBCorner_file10.wv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.re" "Gotham_ARCH_Classic_WinBCorner_file10.re"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.of" "Gotham_ARCH_Classic_WinBCorner_file10.of"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.r" "Gotham_ARCH_Classic_WinBCorner_file10.ro"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.n" "Gotham_ARCH_Classic_WinBCorner_file10.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.vt1" "Gotham_ARCH_Classic_WinBCorner_file10.vt1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.vt2" "Gotham_ARCH_Classic_WinBCorner_file10.vt2"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.vt3" "Gotham_ARCH_Classic_WinBCorner_file10.vt3"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.vc1" "Gotham_ARCH_Classic_WinBCorner_file10.vc1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.o" "Gotham_ARCH_Classic_WinBCorner_file10.uv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.ofs" "Gotham_ARCH_Classic_WinBCorner_file10.fs"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file8.oc" "Gotham_ARCH_Classic_WinBCorner_blinn1.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_bump2d4.o" "Gotham_ARCH_Classic_WinBCorner_blinn1.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file11.oc" "Gotham_ARCH_Classic_WinBCorner_blinn1.sc"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.c" "Gotham_ARCH_Classic_WinBCorner_file11.c"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.tf" "Gotham_ARCH_Classic_WinBCorner_file11.tf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.rf" "Gotham_ARCH_Classic_WinBCorner_file11.rf"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.mu" "Gotham_ARCH_Classic_WinBCorner_file11.mu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.mv" "Gotham_ARCH_Classic_WinBCorner_file11.mv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.s" "Gotham_ARCH_Classic_WinBCorner_file11.s"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.wu" "Gotham_ARCH_Classic_WinBCorner_file11.wu"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.wv" "Gotham_ARCH_Classic_WinBCorner_file11.wv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.re" "Gotham_ARCH_Classic_WinBCorner_file11.re"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.of" "Gotham_ARCH_Classic_WinBCorner_file11.of"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.r" "Gotham_ARCH_Classic_WinBCorner_file11.ro"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.n" "Gotham_ARCH_Classic_WinBCorner_file11.n"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.vt1" "Gotham_ARCH_Classic_WinBCorner_file11.vt1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.vt2" "Gotham_ARCH_Classic_WinBCorner_file11.vt2"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.vt3" "Gotham_ARCH_Classic_WinBCorner_file11.vt3"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.vc1" "Gotham_ARCH_Classic_WinBCorner_file11.vc1"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.o" "Gotham_ARCH_Classic_WinBCorner_file11.uv"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.ofs" "Gotham_ARCH_Classic_WinBCorner_file11.fs"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_12.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo13.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_13.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo14.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_14.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo15.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_15.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo16.sg"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_16.msg" "Gotham_ARCH_Classic_WinBCorner_materialInfo17.sg"
		;
connectAttr "material_17.msg" "materialInfo18.sg";
connectAttr "material_18.msg" "materialInfo19.sg";
connectAttr "material_19.msg" "materialInfo20.sg";
connectAttr "material_20.msg" "materialInfo21.sg";
connectAttr "material_21.msg" "materialInfo22.sg";
connectAttr "material_22.msg" "materialInfo23.sg";
connectAttr "material_23.msg" "materialInfo24.sg";
connectAttr "material_24.msg" "materialInfo25.sg";
connectAttr "material_25.msg" "materialInfo26.sg";
connectAttr "material_26.msg" "materialInfo27.sg";
connectAttr "material_27.msg" "materialInfo28.sg";
connectAttr "material_28.msg" "materialInfo29.sg";
connectAttr "material_29.msg" "materialInfo30.sg";
connectAttr "material_30.msg" "materialInfo31.sg";
connectAttr "material_31.msg" "materialInfo32.sg";
connectAttr "material_32.msg" "materialInfo33.sg";
connectAttr "material_33.msg" "materialInfo34.sg";
connectAttr "material_34.msg" "materialInfo35.sg";
connectAttr "material_35.msg" "materialInfo36.sg";
connectAttr "material_36.msg" "materialInfo37.sg";
connectAttr "material_37.msg" "materialInfo38.sg";
connectAttr "material_38.msg" "materialInfo39.sg";
connectAttr "material_39.msg" "materialInfo40.sg";
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_0_lambert.oc" "material_40.ss"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_0_lambert.msg" "materialInfo41.m"
		;
connectAttr "material_40.msg" "materialInfo41.sg";
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_0.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[6].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo1.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[7].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_1.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[8].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo2.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[9].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_0_lambert2.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[10].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_2.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[11].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo3.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[12].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file1.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[13].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[14].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file2.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[15].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[16].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_bump2d1.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[17].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_3.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[18].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo4.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[19].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_4.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[20].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo5.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[21].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_5.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[22].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo6.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[23].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_6.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[24].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo7.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[25].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_7.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[26].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo8.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[27].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file3.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[28].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[29].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_8.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[30].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo9.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[31].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file4.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[32].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[33].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file5.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[34].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[35].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_bump2d2.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[36].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_9.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[37].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo10.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[38].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_10.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[39].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo11.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[40].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file6.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[41].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[42].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file7.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[43].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[44].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_bump2d3.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[45].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file8.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[46].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[47].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file9.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[48].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[49].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_bump2d4.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[50].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_nodeEditorPanel1Info.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[51].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_hyperView1.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[52].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_hyperLayout1.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[53].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_11.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[56].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo12.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[57].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_phong1.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[58].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file10.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[59].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[60].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_blinn1.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[61].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file11.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[62].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[63].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_12.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[64].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo13.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[65].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_13.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[66].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo14.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[67].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_14.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[68].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo15.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[69].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_15.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[70].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo16.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[71].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_16.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[72].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_materialInfo17.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[73].dn"
		;
connectAttr "material_17.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[74].dn"
		;
connectAttr "materialInfo18.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[75].dn"
		;
connectAttr "material_18.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[76].dn"
		;
connectAttr "materialInfo19.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[77].dn"
		;
connectAttr "material_19.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[78].dn"
		;
connectAttr "materialInfo20.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[79].dn"
		;
connectAttr "material_20.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[80].dn"
		;
connectAttr "materialInfo21.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[81].dn"
		;
connectAttr "material_21.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[82].dn"
		;
connectAttr "materialInfo22.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[83].dn"
		;
connectAttr "material_22.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[84].dn"
		;
connectAttr "materialInfo23.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[85].dn"
		;
connectAttr "material_23.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[86].dn"
		;
connectAttr "materialInfo24.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[87].dn"
		;
connectAttr "material_24.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[88].dn"
		;
connectAttr "materialInfo25.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[89].dn"
		;
connectAttr "material_25.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[90].dn"
		;
connectAttr "materialInfo26.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[91].dn"
		;
connectAttr "material_26.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[92].dn"
		;
connectAttr "materialInfo27.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[93].dn"
		;
connectAttr "material_27.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[94].dn"
		;
connectAttr "materialInfo28.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[95].dn"
		;
connectAttr "material_28.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[96].dn"
		;
connectAttr "materialInfo29.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[97].dn"
		;
connectAttr "material_29.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[98].dn"
		;
connectAttr "materialInfo30.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[99].dn"
		;
connectAttr "material_30.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[100].dn"
		;
connectAttr "materialInfo31.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[101].dn"
		;
connectAttr "material_31.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[102].dn"
		;
connectAttr "materialInfo32.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[103].dn"
		;
connectAttr "material_32.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[104].dn"
		;
connectAttr "materialInfo33.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[105].dn"
		;
connectAttr "material_33.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[106].dn"
		;
connectAttr "materialInfo34.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[107].dn"
		;
connectAttr "material_34.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[108].dn"
		;
connectAttr "materialInfo35.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[109].dn"
		;
connectAttr "material_35.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[110].dn"
		;
connectAttr "materialInfo36.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[111].dn"
		;
connectAttr "material_36.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[112].dn"
		;
connectAttr "materialInfo37.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[113].dn"
		;
connectAttr "material_37.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[114].dn"
		;
connectAttr "materialInfo38.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[115].dn"
		;
connectAttr "material_38.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[116].dn"
		;
connectAttr "materialInfo39.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[117].dn"
		;
connectAttr "material_39.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[118].dn"
		;
connectAttr "materialInfo40.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[119].dn"
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_0_lambert.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[120].dn"
		;
connectAttr "material_40.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[121].dn"
		;
connectAttr "materialInfo41.msg" "AD_Gotham_ARCH_Classic_WinBCorner_hyperLayout1.hyp[122].dn"
		;
connectAttr "Gotham_Fences_Mall768_phong1.oc" "Gotham_Fences_Mall768_material_0.ss"
		;
connectAttr "Gotham_Fences_Mall768_phong1.msg" "Gotham_Fences_Mall768_materialInfo1.m"
		;
connectAttr "Gotham_Fences_Mall768_material_0.msg" "Gotham_Fences_Mall768_materialInfo1.sg"
		;
connectAttr "Gotham_Fences_Mall768_file1.msg" "Gotham_Fences_Mall768_materialInfo1.t"
		 -na;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.c" "Gotham_Fences_Mall768_file1.c"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.tf" "Gotham_Fences_Mall768_file1.tf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.rf" "Gotham_Fences_Mall768_file1.rf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.mu" "Gotham_Fences_Mall768_file1.mu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.mv" "Gotham_Fences_Mall768_file1.mv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.s" "Gotham_Fences_Mall768_file1.s"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.wu" "Gotham_Fences_Mall768_file1.wu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.wv" "Gotham_Fences_Mall768_file1.wv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.re" "Gotham_Fences_Mall768_file1.re"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.of" "Gotham_Fences_Mall768_file1.of"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.r" "Gotham_Fences_Mall768_file1.ro"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.n" "Gotham_Fences_Mall768_file1.n"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.vt1" "Gotham_Fences_Mall768_file1.vt1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.vt2" "Gotham_Fences_Mall768_file1.vt2"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.vt3" "Gotham_Fences_Mall768_file1.vt3"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.vc1" "Gotham_Fences_Mall768_file1.vc1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.o" "Gotham_Fences_Mall768_file1.uv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.ofs" "Gotham_Fences_Mall768_file1.fs"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.c" "Gotham_Fences_Mall768_file2.c"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.tf" "Gotham_Fences_Mall768_file2.tf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.rf" "Gotham_Fences_Mall768_file2.rf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.mu" "Gotham_Fences_Mall768_file2.mu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.mv" "Gotham_Fences_Mall768_file2.mv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.s" "Gotham_Fences_Mall768_file2.s"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.wu" "Gotham_Fences_Mall768_file2.wu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.wv" "Gotham_Fences_Mall768_file2.wv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.re" "Gotham_Fences_Mall768_file2.re"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.of" "Gotham_Fences_Mall768_file2.of"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.r" "Gotham_Fences_Mall768_file2.ro"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.n" "Gotham_Fences_Mall768_file2.n"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.vt1" "Gotham_Fences_Mall768_file2.vt1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.vt2" "Gotham_Fences_Mall768_file2.vt2"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.vt3" "Gotham_Fences_Mall768_file2.vt3"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.vc1" "Gotham_Fences_Mall768_file2.vc1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.o" "Gotham_Fences_Mall768_file2.uv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.ofs" "Gotham_Fences_Mall768_file2.fs"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.c" "Gotham_Fences_Mall768_file3.c"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.tf" "Gotham_Fences_Mall768_file3.tf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.rf" "Gotham_Fences_Mall768_file3.rf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.mu" "Gotham_Fences_Mall768_file3.mu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.mv" "Gotham_Fences_Mall768_file3.mv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.s" "Gotham_Fences_Mall768_file3.s"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.wu" "Gotham_Fences_Mall768_file3.wu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.wv" "Gotham_Fences_Mall768_file3.wv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.re" "Gotham_Fences_Mall768_file3.re"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.of" "Gotham_Fences_Mall768_file3.of"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.r" "Gotham_Fences_Mall768_file3.ro"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.n" "Gotham_Fences_Mall768_file3.n"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.vt1" "Gotham_Fences_Mall768_file3.vt1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.vt2" "Gotham_Fences_Mall768_file3.vt2"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.vt3" "Gotham_Fences_Mall768_file3.vt3"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.vc1" "Gotham_Fences_Mall768_file3.vc1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.o" "Gotham_Fences_Mall768_file3.uv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.ofs" "Gotham_Fences_Mall768_file3.fs"
		;
connectAttr "Gotham_Fences_Mall768_file3.oa" "Gotham_Fences_Mall768_bump2d1.bv";
connectAttr "Gotham_Fences_Mall768_file1.oc" "Gotham_Fences_Mall768_phong1.c";
connectAttr "Gotham_Fences_Mall768_file2.ot" "Gotham_Fences_Mall768_phong1.it";
connectAttr "Gotham_Fences_Mall768_bump2d1.o" "Gotham_Fences_Mall768_phong1.n";
connectAttr "Gotham_Fences_Mall768_file4.oc" "Gotham_Fences_Mall768_phong1.sc";
connectAttr "Gotham_Fences_Mall768_place2dTexture4.c" "Gotham_Fences_Mall768_file4.c"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.tf" "Gotham_Fences_Mall768_file4.tf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.rf" "Gotham_Fences_Mall768_file4.rf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.mu" "Gotham_Fences_Mall768_file4.mu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.mv" "Gotham_Fences_Mall768_file4.mv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.s" "Gotham_Fences_Mall768_file4.s"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.wu" "Gotham_Fences_Mall768_file4.wu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.wv" "Gotham_Fences_Mall768_file4.wv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.re" "Gotham_Fences_Mall768_file4.re"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.of" "Gotham_Fences_Mall768_file4.of"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.r" "Gotham_Fences_Mall768_file4.ro"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.n" "Gotham_Fences_Mall768_file4.n"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.vt1" "Gotham_Fences_Mall768_file4.vt1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.vt2" "Gotham_Fences_Mall768_file4.vt2"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.vt3" "Gotham_Fences_Mall768_file4.vt3"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.vc1" "Gotham_Fences_Mall768_file4.vc1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.o" "Gotham_Fences_Mall768_file4.uv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.ofs" "Gotham_Fences_Mall768_file4.fs"
		;
connectAttr "Gotham_Fences_Mall768_hyperView1.msg" "Gotham_Fences_Mall768_nodeEditorPanel1Info.b[0]"
		;
connectAttr "Gotham_Fences_Mall768_hyperLayout1.msg" "Gotham_Fences_Mall768_hyperView1.hl"
		;
connectAttr "Gotham_Fences_Mall768_material_1.msg" "Gotham_Fences_Mall768_materialInfo2.sg"
		;
connectAttr "Gotham_Fences_Mall768_material_2.msg" "Gotham_Fences_Mall768_materialInfo3.sg"
		;
connectAttr "Gotham_Fences_Mall768_material_3.msg" "Gotham_Fences_Mall768_materialInfo4.sg"
		;
connectAttr "Gotham_Fences_Mall768_material_4.msg" "Gotham_Fences_Mall768_materialInfo5.sg"
		;
connectAttr "Gotham_Fences_Mall768_material_5.msg" "Gotham_Fences_Mall768_materialInfo6.sg"
		;
connectAttr "Gotham_Fences_Mall768_material_6.msg" "Gotham_Fences_Mall768_materialInfo7.sg"
		;
connectAttr "Gotham_Fences_Mall768_material_7.msg" "Gotham_Fences_Mall768_materialInfo8.sg"
		;
connectAttr "Gotham_Fences_Mall768_material_8.msg" "Gotham_Fences_Mall768_materialInfo9.sg"
		;
connectAttr "Gotham_Fences_Mall768_material_9.msg" "Gotham_Fences_Mall768_materialInfo10.sg"
		;
connectAttr "Gotham_Fences_Mall768_material_10.msg" "Gotham_Fences_Mall768_materialInfo11.sg"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.c" "Gotham_Fences_Mall768_file5.c"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.tf" "Gotham_Fences_Mall768_file5.tf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.rf" "Gotham_Fences_Mall768_file5.rf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.mu" "Gotham_Fences_Mall768_file5.mu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.mv" "Gotham_Fences_Mall768_file5.mv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.s" "Gotham_Fences_Mall768_file5.s"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.wu" "Gotham_Fences_Mall768_file5.wu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.wv" "Gotham_Fences_Mall768_file5.wv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.re" "Gotham_Fences_Mall768_file5.re"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.of" "Gotham_Fences_Mall768_file5.of"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.r" "Gotham_Fences_Mall768_file5.ro"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.n" "Gotham_Fences_Mall768_file5.n"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.vt1" "Gotham_Fences_Mall768_file5.vt1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.vt2" "Gotham_Fences_Mall768_file5.vt2"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.vt3" "Gotham_Fences_Mall768_file5.vt3"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.vc1" "Gotham_Fences_Mall768_file5.vc1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.o" "Gotham_Fences_Mall768_file5.uv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.ofs" "Gotham_Fences_Mall768_file5.fs"
		;
connectAttr "Gotham_Fences_Mall768_material_11.msg" "Gotham_Fences_Mall768_materialInfo12.sg"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.c" "Gotham_Fences_Mall768_file6.c"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.tf" "Gotham_Fences_Mall768_file6.tf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.rf" "Gotham_Fences_Mall768_file6.rf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.mu" "Gotham_Fences_Mall768_file6.mu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.mv" "Gotham_Fences_Mall768_file6.mv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.s" "Gotham_Fences_Mall768_file6.s"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.wu" "Gotham_Fences_Mall768_file6.wu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.wv" "Gotham_Fences_Mall768_file6.wv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.re" "Gotham_Fences_Mall768_file6.re"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.of" "Gotham_Fences_Mall768_file6.of"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.r" "Gotham_Fences_Mall768_file6.ro"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.n" "Gotham_Fences_Mall768_file6.n"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.vt1" "Gotham_Fences_Mall768_file6.vt1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.vt2" "Gotham_Fences_Mall768_file6.vt2"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.vt3" "Gotham_Fences_Mall768_file6.vt3"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.vc1" "Gotham_Fences_Mall768_file6.vc1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.o" "Gotham_Fences_Mall768_file6.uv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.ofs" "Gotham_Fences_Mall768_file6.fs"
		;
connectAttr "Gotham_Fences_Mall768_file6.oa" "Gotham_Fences_Mall768_bump2d2.bv";
connectAttr "Gotham_Fences_Mall768_blinn1.oc" "Gotham_Fences_Mall768_blinn1SG.ss"
		;
connectAttr "Gotham_Fences_Mall768_blinn1SG.msg" "Gotham_Fences_Mall768_materialInfo13.sg"
		;
connectAttr "Gotham_Fences_Mall768_blinn1.msg" "Gotham_Fences_Mall768_materialInfo13.m"
		;
connectAttr "Gotham_Fences_Mall768_file7.oc" "Gotham_Fences_Mall768_material_0_lambert.c"
		;
connectAttr "Gotham_Fences_Mall768_material_0_lambert.oc" "Gotham_Fences_Mall768_material_12.ss"
		;
connectAttr "Gotham_Fences_Mall768_material_0_lambert.msg" "Gotham_Fences_Mall768_materialInfo14.m"
		;
connectAttr "Gotham_Fences_Mall768_material_12.msg" "Gotham_Fences_Mall768_materialInfo14.sg"
		;
connectAttr "Gotham_Fences_Mall768_file7.msg" "Gotham_Fences_Mall768_materialInfo14.t"
		 -na;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.c" "Gotham_Fences_Mall768_file7.c"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.tf" "Gotham_Fences_Mall768_file7.tf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.rf" "Gotham_Fences_Mall768_file7.rf"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.mu" "Gotham_Fences_Mall768_file7.mu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.mv" "Gotham_Fences_Mall768_file7.mv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.s" "Gotham_Fences_Mall768_file7.s"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.wu" "Gotham_Fences_Mall768_file7.wu"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.wv" "Gotham_Fences_Mall768_file7.wv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.re" "Gotham_Fences_Mall768_file7.re"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.of" "Gotham_Fences_Mall768_file7.of"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.r" "Gotham_Fences_Mall768_file7.ro"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.n" "Gotham_Fences_Mall768_file7.n"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.vt1" "Gotham_Fences_Mall768_file7.vt1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.vt2" "Gotham_Fences_Mall768_file7.vt2"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.vt3" "Gotham_Fences_Mall768_file7.vt3"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.vc1" "Gotham_Fences_Mall768_file7.vc1"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.o" "Gotham_Fences_Mall768_file7.uv"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.ofs" "Gotham_Fences_Mall768_file7.fs"
		;
connectAttr "Gotham_Fences_Mall768_material_13.msg" "Gotham_Fences_Mall768_materialInfo15.sg"
		;
connectAttr "Gotham_Fences_Mall768_material_14.msg" "Gotham_Fences_Mall768_materialInfo16.sg"
		;
connectAttr "Gotham_Fences_Mall768_material_15.msg" "Gotham_Fences_Mall768_materialInfo17.sg"
		;
connectAttr "Gotham_Fences_Mall768_material_0.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[6].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo1.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[7].dn"
		;
connectAttr "Gotham_Fences_Mall768_file1.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[8].dn"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[9].dn"
		;
connectAttr "Gotham_Fences_Mall768_file2.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[10].dn"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[11].dn"
		;
connectAttr "Gotham_Fences_Mall768_file3.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[12].dn"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[13].dn"
		;
connectAttr "Gotham_Fences_Mall768_bump2d1.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[14].dn"
		;
connectAttr "Gotham_Fences_Mall768_phong1.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[15].dn"
		;
connectAttr "Gotham_Fences_Mall768_file4.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[16].dn"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[17].dn"
		;
connectAttr "Gotham_Fences_Mall768_nodeEditorPanel1Info.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[18].dn"
		;
connectAttr "Gotham_Fences_Mall768_hyperView1.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[19].dn"
		;
connectAttr "Gotham_Fences_Mall768_hyperLayout1.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[20].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_1.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[23].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo2.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[24].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_2.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[25].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo3.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[26].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_3.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[27].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo4.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[28].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_4.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[29].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo5.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[30].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_5.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[31].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo6.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[32].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_6.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[33].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo7.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[34].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_7.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[35].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo8.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[36].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_8.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[37].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo9.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[38].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_9.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[39].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo10.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[40].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_10.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[41].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo11.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[42].dn"
		;
connectAttr "Gotham_Fences_Mall768_file5.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[43].dn"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[44].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_11.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[45].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo12.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[46].dn"
		;
connectAttr "Gotham_Fences_Mall768_file6.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[47].dn"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[48].dn"
		;
connectAttr "Gotham_Fences_Mall768_bump2d2.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[49].dn"
		;
connectAttr "Gotham_Fences_Mall768_blinn1.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[50].dn"
		;
connectAttr "Gotham_Fences_Mall768_blinn1SG.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[51].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo13.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[52].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_0_lambert.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[53].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_12.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[54].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo14.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[55].dn"
		;
connectAttr "Gotham_Fences_Mall768_file7.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[56].dn"
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[57].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_13.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[58].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo15.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[59].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_14.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[60].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo16.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[61].dn"
		;
connectAttr "Gotham_Fences_Mall768_material_15.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[62].dn"
		;
connectAttr "Gotham_Fences_Mall768_materialInfo17.msg" "AD_Gotham_Fences_Mall768_hyperLayout1.hyp[63].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_phong1.oc" "Gotham_Fences_PoleSolid_128C_material_0.ss"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_phong1.msg" "Gotham_Fences_PoleSolid_128C_materialInfo1.m"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_0.msg" "Gotham_Fences_PoleSolid_128C_materialInfo1.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file1.msg" "Gotham_Fences_PoleSolid_128C_materialInfo1.t"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.c" "Gotham_Fences_PoleSolid_128C_file1.c"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.tf" "Gotham_Fences_PoleSolid_128C_file1.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.rf" "Gotham_Fences_PoleSolid_128C_file1.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.mu" "Gotham_Fences_PoleSolid_128C_file1.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.mv" "Gotham_Fences_PoleSolid_128C_file1.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.s" "Gotham_Fences_PoleSolid_128C_file1.s"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.wu" "Gotham_Fences_PoleSolid_128C_file1.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.wv" "Gotham_Fences_PoleSolid_128C_file1.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.re" "Gotham_Fences_PoleSolid_128C_file1.re"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.of" "Gotham_Fences_PoleSolid_128C_file1.of"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.r" "Gotham_Fences_PoleSolid_128C_file1.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.n" "Gotham_Fences_PoleSolid_128C_file1.n"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.vt1" "Gotham_Fences_PoleSolid_128C_file1.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.vt2" "Gotham_Fences_PoleSolid_128C_file1.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.vt3" "Gotham_Fences_PoleSolid_128C_file1.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.vc1" "Gotham_Fences_PoleSolid_128C_file1.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.o" "Gotham_Fences_PoleSolid_128C_file1.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.ofs" "Gotham_Fences_PoleSolid_128C_file1.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.c" "Gotham_Fences_PoleSolid_128C_file2.c"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.tf" "Gotham_Fences_PoleSolid_128C_file2.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.rf" "Gotham_Fences_PoleSolid_128C_file2.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.mu" "Gotham_Fences_PoleSolid_128C_file2.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.mv" "Gotham_Fences_PoleSolid_128C_file2.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.s" "Gotham_Fences_PoleSolid_128C_file2.s"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.wu" "Gotham_Fences_PoleSolid_128C_file2.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.wv" "Gotham_Fences_PoleSolid_128C_file2.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.re" "Gotham_Fences_PoleSolid_128C_file2.re"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.of" "Gotham_Fences_PoleSolid_128C_file2.of"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.r" "Gotham_Fences_PoleSolid_128C_file2.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.n" "Gotham_Fences_PoleSolid_128C_file2.n"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.vt1" "Gotham_Fences_PoleSolid_128C_file2.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.vt2" "Gotham_Fences_PoleSolid_128C_file2.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.vt3" "Gotham_Fences_PoleSolid_128C_file2.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.vc1" "Gotham_Fences_PoleSolid_128C_file2.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.o" "Gotham_Fences_PoleSolid_128C_file2.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.ofs" "Gotham_Fences_PoleSolid_128C_file2.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.c" "Gotham_Fences_PoleSolid_128C_file3.c"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.tf" "Gotham_Fences_PoleSolid_128C_file3.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.rf" "Gotham_Fences_PoleSolid_128C_file3.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.mu" "Gotham_Fences_PoleSolid_128C_file3.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.mv" "Gotham_Fences_PoleSolid_128C_file3.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.s" "Gotham_Fences_PoleSolid_128C_file3.s"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.wu" "Gotham_Fences_PoleSolid_128C_file3.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.wv" "Gotham_Fences_PoleSolid_128C_file3.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.re" "Gotham_Fences_PoleSolid_128C_file3.re"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.of" "Gotham_Fences_PoleSolid_128C_file3.of"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.r" "Gotham_Fences_PoleSolid_128C_file3.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.n" "Gotham_Fences_PoleSolid_128C_file3.n"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.vt1" "Gotham_Fences_PoleSolid_128C_file3.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.vt2" "Gotham_Fences_PoleSolid_128C_file3.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.vt3" "Gotham_Fences_PoleSolid_128C_file3.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.vc1" "Gotham_Fences_PoleSolid_128C_file3.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.o" "Gotham_Fences_PoleSolid_128C_file3.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.ofs" "Gotham_Fences_PoleSolid_128C_file3.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file3.oa" "Gotham_Fences_PoleSolid_128C_bump2d1.bv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file1.oc" "Gotham_Fences_PoleSolid_128C_phong1.c"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file2.ot" "Gotham_Fences_PoleSolid_128C_phong1.it"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_bump2d1.o" "Gotham_Fences_PoleSolid_128C_phong1.n"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file4.oc" "Gotham_Fences_PoleSolid_128C_phong1.sc"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.c" "Gotham_Fences_PoleSolid_128C_file4.c"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.tf" "Gotham_Fences_PoleSolid_128C_file4.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.rf" "Gotham_Fences_PoleSolid_128C_file4.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.mu" "Gotham_Fences_PoleSolid_128C_file4.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.mv" "Gotham_Fences_PoleSolid_128C_file4.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.s" "Gotham_Fences_PoleSolid_128C_file4.s"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.wu" "Gotham_Fences_PoleSolid_128C_file4.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.wv" "Gotham_Fences_PoleSolid_128C_file4.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.re" "Gotham_Fences_PoleSolid_128C_file4.re"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.of" "Gotham_Fences_PoleSolid_128C_file4.of"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.r" "Gotham_Fences_PoleSolid_128C_file4.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.n" "Gotham_Fences_PoleSolid_128C_file4.n"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.vt1" "Gotham_Fences_PoleSolid_128C_file4.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.vt2" "Gotham_Fences_PoleSolid_128C_file4.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.vt3" "Gotham_Fences_PoleSolid_128C_file4.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.vc1" "Gotham_Fences_PoleSolid_128C_file4.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.o" "Gotham_Fences_PoleSolid_128C_file4.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.ofs" "Gotham_Fences_PoleSolid_128C_file4.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_hyperView1.msg" "Gotham_Fences_PoleSolid_128C_nodeEditorPanel1Info.b[0]"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_hyperLayout1.msg" "Gotham_Fences_PoleSolid_128C_hyperView1.hl"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_1.msg" "Gotham_Fences_PoleSolid_128C_materialInfo2.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_2.msg" "Gotham_Fences_PoleSolid_128C_materialInfo3.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_3.msg" "Gotham_Fences_PoleSolid_128C_materialInfo4.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_4.msg" "Gotham_Fences_PoleSolid_128C_materialInfo5.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_5.msg" "Gotham_Fences_PoleSolid_128C_materialInfo6.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_6.msg" "Gotham_Fences_PoleSolid_128C_materialInfo7.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_7.msg" "Gotham_Fences_PoleSolid_128C_materialInfo8.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_8.msg" "Gotham_Fences_PoleSolid_128C_materialInfo9.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_9.msg" "Gotham_Fences_PoleSolid_128C_materialInfo10.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_10.msg" "Gotham_Fences_PoleSolid_128C_materialInfo11.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.c" "Gotham_Fences_PoleSolid_128C_file5.c"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.tf" "Gotham_Fences_PoleSolid_128C_file5.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.rf" "Gotham_Fences_PoleSolid_128C_file5.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.mu" "Gotham_Fences_PoleSolid_128C_file5.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.mv" "Gotham_Fences_PoleSolid_128C_file5.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.s" "Gotham_Fences_PoleSolid_128C_file5.s"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.wu" "Gotham_Fences_PoleSolid_128C_file5.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.wv" "Gotham_Fences_PoleSolid_128C_file5.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.re" "Gotham_Fences_PoleSolid_128C_file5.re"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.of" "Gotham_Fences_PoleSolid_128C_file5.of"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.r" "Gotham_Fences_PoleSolid_128C_file5.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.n" "Gotham_Fences_PoleSolid_128C_file5.n"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.vt1" "Gotham_Fences_PoleSolid_128C_file5.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.vt2" "Gotham_Fences_PoleSolid_128C_file5.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.vt3" "Gotham_Fences_PoleSolid_128C_file5.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.vc1" "Gotham_Fences_PoleSolid_128C_file5.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.o" "Gotham_Fences_PoleSolid_128C_file5.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.ofs" "Gotham_Fences_PoleSolid_128C_file5.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_11.msg" "Gotham_Fences_PoleSolid_128C_materialInfo12.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.c" "Gotham_Fences_PoleSolid_128C_file6.c"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.tf" "Gotham_Fences_PoleSolid_128C_file6.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.rf" "Gotham_Fences_PoleSolid_128C_file6.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.mu" "Gotham_Fences_PoleSolid_128C_file6.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.mv" "Gotham_Fences_PoleSolid_128C_file6.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.s" "Gotham_Fences_PoleSolid_128C_file6.s"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.wu" "Gotham_Fences_PoleSolid_128C_file6.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.wv" "Gotham_Fences_PoleSolid_128C_file6.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.re" "Gotham_Fences_PoleSolid_128C_file6.re"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.of" "Gotham_Fences_PoleSolid_128C_file6.of"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.r" "Gotham_Fences_PoleSolid_128C_file6.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.n" "Gotham_Fences_PoleSolid_128C_file6.n"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.vt1" "Gotham_Fences_PoleSolid_128C_file6.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.vt2" "Gotham_Fences_PoleSolid_128C_file6.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.vt3" "Gotham_Fences_PoleSolid_128C_file6.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.vc1" "Gotham_Fences_PoleSolid_128C_file6.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.o" "Gotham_Fences_PoleSolid_128C_file6.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.ofs" "Gotham_Fences_PoleSolid_128C_file6.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file6.oa" "Gotham_Fences_PoleSolid_128C_bump2d2.bv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_blinn1.oc" "Gotham_Fences_PoleSolid_128C_blinn1SG.ss"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_blinn1SG.msg" "Gotham_Fences_PoleSolid_128C_materialInfo13.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_blinn1.msg" "Gotham_Fences_PoleSolid_128C_materialInfo13.m"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file7.oc" "Gotham_Fences_PoleSolid_128C_material_0_lambert.c"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_0_lambert.oc" "Gotham_Fences_PoleSolid_128C_material_12.ss"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_0_lambert.msg" "Gotham_Fences_PoleSolid_128C_materialInfo14.m"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_12.msg" "Gotham_Fences_PoleSolid_128C_materialInfo14.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file7.msg" "Gotham_Fences_PoleSolid_128C_materialInfo14.t"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.c" "Gotham_Fences_PoleSolid_128C_file7.c"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.tf" "Gotham_Fences_PoleSolid_128C_file7.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.rf" "Gotham_Fences_PoleSolid_128C_file7.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.mu" "Gotham_Fences_PoleSolid_128C_file7.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.mv" "Gotham_Fences_PoleSolid_128C_file7.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.s" "Gotham_Fences_PoleSolid_128C_file7.s"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.wu" "Gotham_Fences_PoleSolid_128C_file7.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.wv" "Gotham_Fences_PoleSolid_128C_file7.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.re" "Gotham_Fences_PoleSolid_128C_file7.re"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.of" "Gotham_Fences_PoleSolid_128C_file7.of"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.r" "Gotham_Fences_PoleSolid_128C_file7.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.n" "Gotham_Fences_PoleSolid_128C_file7.n"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.vt1" "Gotham_Fences_PoleSolid_128C_file7.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.vt2" "Gotham_Fences_PoleSolid_128C_file7.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.vt3" "Gotham_Fences_PoleSolid_128C_file7.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.vc1" "Gotham_Fences_PoleSolid_128C_file7.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.o" "Gotham_Fences_PoleSolid_128C_file7.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.ofs" "Gotham_Fences_PoleSolid_128C_file7.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_13.msg" "Gotham_Fences_PoleSolid_128C_materialInfo15.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_14.msg" "Gotham_Fences_PoleSolid_128C_materialInfo16.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_15.msg" "Gotham_Fences_PoleSolid_128C_materialInfo17.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_16.msg" "Gotham_Fences_PoleSolid_128C_materialInfo18.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_17.msg" "Gotham_Fences_PoleSolid_128C_materialInfo19.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_18.msg" "Gotham_Fences_PoleSolid_128C_materialInfo20.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_19.msg" "Gotham_Fences_PoleSolid_128C_materialInfo21.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_20.msg" "Gotham_Fences_PoleSolid_128C_materialInfo22.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_21.msg" "Gotham_Fences_PoleSolid_128C_materialInfo23.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_0.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[6].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo1.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[7].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file1.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[8].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[9].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file2.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[10].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[11].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file3.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[12].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[13].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_bump2d1.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[14].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_phong1.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[15].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file4.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[16].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[17].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_nodeEditorPanel1Info.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[18].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_hyperView1.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[19].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_hyperLayout1.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[20].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_1.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[23].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo2.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[24].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_2.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[25].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo3.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[26].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_3.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[27].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo4.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[28].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_4.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[29].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo5.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[30].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_5.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[31].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo6.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[32].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_6.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[33].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo7.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[34].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_7.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[35].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo8.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[36].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_8.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[37].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo9.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[38].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_9.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[39].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo10.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[40].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_10.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[41].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo11.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[42].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file5.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[43].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[44].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_11.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[45].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo12.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[46].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file6.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[47].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[48].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_bump2d2.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[49].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_blinn1.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[50].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_blinn1SG.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[51].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo13.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[52].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_0_lambert.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[53].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_12.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[54].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo14.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[55].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file7.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[56].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[57].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_13.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[58].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo15.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[59].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_14.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[60].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo16.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[61].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_15.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[62].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo17.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[63].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_16.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[64].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo18.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[65].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_17.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[66].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo19.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[67].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_18.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[68].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo20.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[69].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_19.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[70].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo21.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[71].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_20.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[72].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo22.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[73].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_21.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[74].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_128C_materialInfo23.msg" "AD_Gotham_Fences_PoleSolid_128C_hyperLayout1.hyp[75].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_phong1.oc" "Gotham_Fences_PoleSolid_512_material_0.ss"
		;
connectAttr "Gotham_Fences_PoleSolid_512_phong1.msg" "Gotham_Fences_PoleSolid_512_materialInfo1.m"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_0.msg" "Gotham_Fences_PoleSolid_512_materialInfo1.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file1.msg" "Gotham_Fences_PoleSolid_512_materialInfo1.t"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.c" "Gotham_Fences_PoleSolid_512_file1.c"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.tf" "Gotham_Fences_PoleSolid_512_file1.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.rf" "Gotham_Fences_PoleSolid_512_file1.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.mu" "Gotham_Fences_PoleSolid_512_file1.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.mv" "Gotham_Fences_PoleSolid_512_file1.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.s" "Gotham_Fences_PoleSolid_512_file1.s"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.wu" "Gotham_Fences_PoleSolid_512_file1.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.wv" "Gotham_Fences_PoleSolid_512_file1.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.re" "Gotham_Fences_PoleSolid_512_file1.re"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.of" "Gotham_Fences_PoleSolid_512_file1.of"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.r" "Gotham_Fences_PoleSolid_512_file1.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.n" "Gotham_Fences_PoleSolid_512_file1.n"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.vt1" "Gotham_Fences_PoleSolid_512_file1.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.vt2" "Gotham_Fences_PoleSolid_512_file1.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.vt3" "Gotham_Fences_PoleSolid_512_file1.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.vc1" "Gotham_Fences_PoleSolid_512_file1.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.o" "Gotham_Fences_PoleSolid_512_file1.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.ofs" "Gotham_Fences_PoleSolid_512_file1.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.c" "Gotham_Fences_PoleSolid_512_file2.c"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.tf" "Gotham_Fences_PoleSolid_512_file2.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.rf" "Gotham_Fences_PoleSolid_512_file2.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.mu" "Gotham_Fences_PoleSolid_512_file2.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.mv" "Gotham_Fences_PoleSolid_512_file2.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.s" "Gotham_Fences_PoleSolid_512_file2.s"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.wu" "Gotham_Fences_PoleSolid_512_file2.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.wv" "Gotham_Fences_PoleSolid_512_file2.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.re" "Gotham_Fences_PoleSolid_512_file2.re"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.of" "Gotham_Fences_PoleSolid_512_file2.of"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.r" "Gotham_Fences_PoleSolid_512_file2.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.n" "Gotham_Fences_PoleSolid_512_file2.n"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.vt1" "Gotham_Fences_PoleSolid_512_file2.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.vt2" "Gotham_Fences_PoleSolid_512_file2.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.vt3" "Gotham_Fences_PoleSolid_512_file2.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.vc1" "Gotham_Fences_PoleSolid_512_file2.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.o" "Gotham_Fences_PoleSolid_512_file2.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.ofs" "Gotham_Fences_PoleSolid_512_file2.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.c" "Gotham_Fences_PoleSolid_512_file3.c"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.tf" "Gotham_Fences_PoleSolid_512_file3.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.rf" "Gotham_Fences_PoleSolid_512_file3.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.mu" "Gotham_Fences_PoleSolid_512_file3.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.mv" "Gotham_Fences_PoleSolid_512_file3.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.s" "Gotham_Fences_PoleSolid_512_file3.s"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.wu" "Gotham_Fences_PoleSolid_512_file3.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.wv" "Gotham_Fences_PoleSolid_512_file3.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.re" "Gotham_Fences_PoleSolid_512_file3.re"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.of" "Gotham_Fences_PoleSolid_512_file3.of"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.r" "Gotham_Fences_PoleSolid_512_file3.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.n" "Gotham_Fences_PoleSolid_512_file3.n"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.vt1" "Gotham_Fences_PoleSolid_512_file3.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.vt2" "Gotham_Fences_PoleSolid_512_file3.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.vt3" "Gotham_Fences_PoleSolid_512_file3.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.vc1" "Gotham_Fences_PoleSolid_512_file3.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.o" "Gotham_Fences_PoleSolid_512_file3.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.ofs" "Gotham_Fences_PoleSolid_512_file3.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file3.oa" "Gotham_Fences_PoleSolid_512_bump2d1.bv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file1.oc" "Gotham_Fences_PoleSolid_512_phong1.c"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file2.ot" "Gotham_Fences_PoleSolid_512_phong1.it"
		;
connectAttr "Gotham_Fences_PoleSolid_512_bump2d1.o" "Gotham_Fences_PoleSolid_512_phong1.n"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file4.oc" "Gotham_Fences_PoleSolid_512_phong1.sc"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.c" "Gotham_Fences_PoleSolid_512_file4.c"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.tf" "Gotham_Fences_PoleSolid_512_file4.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.rf" "Gotham_Fences_PoleSolid_512_file4.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.mu" "Gotham_Fences_PoleSolid_512_file4.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.mv" "Gotham_Fences_PoleSolid_512_file4.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.s" "Gotham_Fences_PoleSolid_512_file4.s"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.wu" "Gotham_Fences_PoleSolid_512_file4.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.wv" "Gotham_Fences_PoleSolid_512_file4.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.re" "Gotham_Fences_PoleSolid_512_file4.re"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.of" "Gotham_Fences_PoleSolid_512_file4.of"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.r" "Gotham_Fences_PoleSolid_512_file4.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.n" "Gotham_Fences_PoleSolid_512_file4.n"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.vt1" "Gotham_Fences_PoleSolid_512_file4.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.vt2" "Gotham_Fences_PoleSolid_512_file4.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.vt3" "Gotham_Fences_PoleSolid_512_file4.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.vc1" "Gotham_Fences_PoleSolid_512_file4.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.o" "Gotham_Fences_PoleSolid_512_file4.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.ofs" "Gotham_Fences_PoleSolid_512_file4.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_512_hyperView1.msg" "Gotham_Fences_PoleSolid_512_nodeEditorPanel1Info.b[0]"
		;
connectAttr "Gotham_Fences_PoleSolid_512_hyperLayout1.msg" "Gotham_Fences_PoleSolid_512_hyperView1.hl"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_1.msg" "Gotham_Fences_PoleSolid_512_materialInfo2.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_2.msg" "Gotham_Fences_PoleSolid_512_materialInfo3.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_3.msg" "Gotham_Fences_PoleSolid_512_materialInfo4.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_4.msg" "Gotham_Fences_PoleSolid_512_materialInfo5.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_5.msg" "Gotham_Fences_PoleSolid_512_materialInfo6.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_6.msg" "Gotham_Fences_PoleSolid_512_materialInfo7.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_7.msg" "Gotham_Fences_PoleSolid_512_materialInfo8.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_8.msg" "Gotham_Fences_PoleSolid_512_materialInfo9.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_9.msg" "Gotham_Fences_PoleSolid_512_materialInfo10.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_10.msg" "Gotham_Fences_PoleSolid_512_materialInfo11.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.c" "Gotham_Fences_PoleSolid_512_file5.c"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.tf" "Gotham_Fences_PoleSolid_512_file5.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.rf" "Gotham_Fences_PoleSolid_512_file5.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.mu" "Gotham_Fences_PoleSolid_512_file5.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.mv" "Gotham_Fences_PoleSolid_512_file5.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.s" "Gotham_Fences_PoleSolid_512_file5.s"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.wu" "Gotham_Fences_PoleSolid_512_file5.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.wv" "Gotham_Fences_PoleSolid_512_file5.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.re" "Gotham_Fences_PoleSolid_512_file5.re"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.of" "Gotham_Fences_PoleSolid_512_file5.of"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.r" "Gotham_Fences_PoleSolid_512_file5.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.n" "Gotham_Fences_PoleSolid_512_file5.n"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.vt1" "Gotham_Fences_PoleSolid_512_file5.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.vt2" "Gotham_Fences_PoleSolid_512_file5.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.vt3" "Gotham_Fences_PoleSolid_512_file5.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.vc1" "Gotham_Fences_PoleSolid_512_file5.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.o" "Gotham_Fences_PoleSolid_512_file5.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.ofs" "Gotham_Fences_PoleSolid_512_file5.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_11.msg" "Gotham_Fences_PoleSolid_512_materialInfo12.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.c" "Gotham_Fences_PoleSolid_512_file6.c"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.tf" "Gotham_Fences_PoleSolid_512_file6.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.rf" "Gotham_Fences_PoleSolid_512_file6.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.mu" "Gotham_Fences_PoleSolid_512_file6.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.mv" "Gotham_Fences_PoleSolid_512_file6.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.s" "Gotham_Fences_PoleSolid_512_file6.s"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.wu" "Gotham_Fences_PoleSolid_512_file6.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.wv" "Gotham_Fences_PoleSolid_512_file6.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.re" "Gotham_Fences_PoleSolid_512_file6.re"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.of" "Gotham_Fences_PoleSolid_512_file6.of"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.r" "Gotham_Fences_PoleSolid_512_file6.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.n" "Gotham_Fences_PoleSolid_512_file6.n"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.vt1" "Gotham_Fences_PoleSolid_512_file6.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.vt2" "Gotham_Fences_PoleSolid_512_file6.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.vt3" "Gotham_Fences_PoleSolid_512_file6.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.vc1" "Gotham_Fences_PoleSolid_512_file6.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.o" "Gotham_Fences_PoleSolid_512_file6.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.ofs" "Gotham_Fences_PoleSolid_512_file6.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file6.oa" "Gotham_Fences_PoleSolid_512_bump2d2.bv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_blinn1.oc" "Gotham_Fences_PoleSolid_512_blinn1SG.ss"
		;
connectAttr "Gotham_Fences_PoleSolid_512_blinn1SG.msg" "Gotham_Fences_PoleSolid_512_materialInfo13.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_blinn1.msg" "Gotham_Fences_PoleSolid_512_materialInfo13.m"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file7.oc" "Gotham_Fences_PoleSolid_512_material_0_lambert.c"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_0_lambert.oc" "Gotham_Fences_PoleSolid_512_material_12.ss"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_0_lambert.msg" "Gotham_Fences_PoleSolid_512_materialInfo14.m"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_12.msg" "Gotham_Fences_PoleSolid_512_materialInfo14.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file7.msg" "Gotham_Fences_PoleSolid_512_materialInfo14.t"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.c" "Gotham_Fences_PoleSolid_512_file7.c"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.tf" "Gotham_Fences_PoleSolid_512_file7.tf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.rf" "Gotham_Fences_PoleSolid_512_file7.rf"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.mu" "Gotham_Fences_PoleSolid_512_file7.mu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.mv" "Gotham_Fences_PoleSolid_512_file7.mv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.s" "Gotham_Fences_PoleSolid_512_file7.s"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.wu" "Gotham_Fences_PoleSolid_512_file7.wu"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.wv" "Gotham_Fences_PoleSolid_512_file7.wv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.re" "Gotham_Fences_PoleSolid_512_file7.re"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.of" "Gotham_Fences_PoleSolid_512_file7.of"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.r" "Gotham_Fences_PoleSolid_512_file7.ro"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.n" "Gotham_Fences_PoleSolid_512_file7.n"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.vt1" "Gotham_Fences_PoleSolid_512_file7.vt1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.vt2" "Gotham_Fences_PoleSolid_512_file7.vt2"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.vt3" "Gotham_Fences_PoleSolid_512_file7.vt3"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.vc1" "Gotham_Fences_PoleSolid_512_file7.vc1"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.o" "Gotham_Fences_PoleSolid_512_file7.uv"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.ofs" "Gotham_Fences_PoleSolid_512_file7.fs"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_13.msg" "Gotham_Fences_PoleSolid_512_materialInfo15.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_14.msg" "Gotham_Fences_PoleSolid_512_materialInfo16.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_15.msg" "Gotham_Fences_PoleSolid_512_materialInfo17.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_16.msg" "Gotham_Fences_PoleSolid_512_materialInfo18.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_17.msg" "Gotham_Fences_PoleSolid_512_materialInfo19.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_18.msg" "Gotham_Fences_PoleSolid_512_materialInfo20.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_19.msg" "Gotham_Fences_PoleSolid_512_materialInfo21.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_20.msg" "Gotham_Fences_PoleSolid_512_materialInfo22.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_21.msg" "Gotham_Fences_PoleSolid_512_materialInfo23.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_22.msg" "Gotham_Fences_PoleSolid_512_materialInfo24.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_23.msg" "Gotham_Fences_PoleSolid_512_materialInfo25.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_0_lambert1.oc" "Gotham_Fences_PoleSolid_512_material_24.ss"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_0_lambert1.msg" "Gotham_Fences_PoleSolid_512_materialInfo26.m"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_24.msg" "Gotham_Fences_PoleSolid_512_materialInfo26.sg"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_0.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[6].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo1.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[7].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file1.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[8].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[9].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file2.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[10].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[11].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file3.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[12].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[13].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_bump2d1.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[14].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_phong1.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[15].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file4.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[16].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[17].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_nodeEditorPanel1Info.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[18].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_hyperView1.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[19].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_hyperLayout1.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[20].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_1.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[23].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo2.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[24].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_2.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[25].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo3.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[26].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_3.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[27].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo4.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[28].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_4.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[29].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo5.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[30].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_5.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[31].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo6.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[32].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_6.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[33].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo7.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[34].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_7.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[35].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo8.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[36].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_8.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[37].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo9.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[38].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_9.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[39].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo10.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[40].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_10.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[41].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo11.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[42].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file5.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[43].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[44].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_11.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[45].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo12.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[46].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file6.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[47].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[48].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_bump2d2.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[49].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_blinn1.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[50].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_blinn1SG.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[51].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo13.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[52].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_0_lambert.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[53].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_12.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[54].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo14.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[55].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_file7.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[56].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[57].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_13.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[58].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo15.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[59].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_14.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[60].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo16.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[61].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_15.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[62].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo17.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[63].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_16.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[64].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo18.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[65].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_17.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[66].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo19.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[67].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_18.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[68].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo20.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[69].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_19.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[70].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo21.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[71].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_20.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[72].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo22.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[73].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_21.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[74].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo23.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[75].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_22.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[76].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo24.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[77].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_23.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[78].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo25.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[79].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_0_lambert1.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[80].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_24.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[81].dn"
		;
connectAttr "Gotham_Fences_PoleSolid_512_materialInfo26.msg" "AD_Gotham_Fences_PoleSolid_512_hyperLayout1.hyp[82].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_file1.oc" "ARCH_GCPD_EntranceRoof_04_material_0_lambert.c"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_bump2d1.o" "ARCH_GCPD_EntranceRoof_04_material_0_lambert.n"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_0_lambert.oc" "ARCH_GCPD_EntranceRoof_04_material_0.ss"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_0_lambert.msg" "ARCH_GCPD_EntranceRoof_04_materialInfo1.m"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_0.msg" "ARCH_GCPD_EntranceRoof_04_materialInfo1.sg"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_file1.msg" "ARCH_GCPD_EntranceRoof_04_materialInfo1.t"
		 -na;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.c" "ARCH_GCPD_EntranceRoof_04_file1.c"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.tf" "ARCH_GCPD_EntranceRoof_04_file1.tf"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.rf" "ARCH_GCPD_EntranceRoof_04_file1.rf"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.mu" "ARCH_GCPD_EntranceRoof_04_file1.mu"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.mv" "ARCH_GCPD_EntranceRoof_04_file1.mv"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.s" "ARCH_GCPD_EntranceRoof_04_file1.s"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.wu" "ARCH_GCPD_EntranceRoof_04_file1.wu"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.wv" "ARCH_GCPD_EntranceRoof_04_file1.wv"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.re" "ARCH_GCPD_EntranceRoof_04_file1.re"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.of" "ARCH_GCPD_EntranceRoof_04_file1.of"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.r" "ARCH_GCPD_EntranceRoof_04_file1.ro"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.n" "ARCH_GCPD_EntranceRoof_04_file1.n"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.vt1" "ARCH_GCPD_EntranceRoof_04_file1.vt1"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.vt2" "ARCH_GCPD_EntranceRoof_04_file1.vt2"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.vt3" "ARCH_GCPD_EntranceRoof_04_file1.vt3"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.vc1" "ARCH_GCPD_EntranceRoof_04_file1.vc1"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.o" "ARCH_GCPD_EntranceRoof_04_file1.uv"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.ofs" "ARCH_GCPD_EntranceRoof_04_file1.fs"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.c" "ARCH_GCPD_EntranceRoof_04_file2.c"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.tf" "ARCH_GCPD_EntranceRoof_04_file2.tf"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.rf" "ARCH_GCPD_EntranceRoof_04_file2.rf"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.mu" "ARCH_GCPD_EntranceRoof_04_file2.mu"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.mv" "ARCH_GCPD_EntranceRoof_04_file2.mv"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.s" "ARCH_GCPD_EntranceRoof_04_file2.s"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.wu" "ARCH_GCPD_EntranceRoof_04_file2.wu"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.wv" "ARCH_GCPD_EntranceRoof_04_file2.wv"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.re" "ARCH_GCPD_EntranceRoof_04_file2.re"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.of" "ARCH_GCPD_EntranceRoof_04_file2.of"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.r" "ARCH_GCPD_EntranceRoof_04_file2.ro"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.n" "ARCH_GCPD_EntranceRoof_04_file2.n"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.vt1" "ARCH_GCPD_EntranceRoof_04_file2.vt1"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.vt2" "ARCH_GCPD_EntranceRoof_04_file2.vt2"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.vt3" "ARCH_GCPD_EntranceRoof_04_file2.vt3"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.vc1" "ARCH_GCPD_EntranceRoof_04_file2.vc1"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.o" "ARCH_GCPD_EntranceRoof_04_file2.uv"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.ofs" "ARCH_GCPD_EntranceRoof_04_file2.fs"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_file2.oa" "ARCH_GCPD_EntranceRoof_04_bump2d1.bv"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_hyperView1.msg" "ARCH_GCPD_EntranceRoof_04_nodeEditorPanel1Info.b[0]"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_hyperLayout1.msg" "ARCH_GCPD_EntranceRoof_04_hyperView1.hl"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_0_lambert1.oc" "ARCH_GCPD_EntranceRoof_04_material_1.ss"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_0_lambert1.msg" "ARCH_GCPD_EntranceRoof_04_materialInfo2.m"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_1.msg" "ARCH_GCPD_EntranceRoof_04_materialInfo2.sg"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_0_lambert.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[6].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_0.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[7].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_materialInfo1.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[8].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_file1.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[9].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[10].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_file2.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[11].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[12].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_bump2d1.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[13].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_nodeEditorPanel1Info.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[14].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_hyperView1.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[15].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_hyperLayout1.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[16].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_0_lambert1.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[19].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_1.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[20].dn"
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_materialInfo2.msg" "AD_ARCH_GCPD_EntranceRoof_04_hyperLayout1.hyp[21].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_0.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo1.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_1.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo2.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file1.oc" "Gotham_Arch_Classic_BigWiny2_material_0_lambert2.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_bump2d1.o" "Gotham_Arch_Classic_BigWiny2_material_0_lambert2.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_0_lambert2.oc" "Gotham_Arch_Classic_BigWiny2_material_2.ss"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_0_lambert2.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo3.m"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_2.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo3.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file1.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo3.t"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.c" "Gotham_Arch_Classic_BigWiny2_file1.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.tf" "Gotham_Arch_Classic_BigWiny2_file1.tf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.rf" "Gotham_Arch_Classic_BigWiny2_file1.rf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.mu" "Gotham_Arch_Classic_BigWiny2_file1.mu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.mv" "Gotham_Arch_Classic_BigWiny2_file1.mv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.s" "Gotham_Arch_Classic_BigWiny2_file1.s"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.wu" "Gotham_Arch_Classic_BigWiny2_file1.wu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.wv" "Gotham_Arch_Classic_BigWiny2_file1.wv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.re" "Gotham_Arch_Classic_BigWiny2_file1.re"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.of" "Gotham_Arch_Classic_BigWiny2_file1.of"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.r" "Gotham_Arch_Classic_BigWiny2_file1.ro"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.n" "Gotham_Arch_Classic_BigWiny2_file1.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.vt1" "Gotham_Arch_Classic_BigWiny2_file1.vt1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.vt2" "Gotham_Arch_Classic_BigWiny2_file1.vt2"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.vt3" "Gotham_Arch_Classic_BigWiny2_file1.vt3"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.vc1" "Gotham_Arch_Classic_BigWiny2_file1.vc1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.o" "Gotham_Arch_Classic_BigWiny2_file1.uv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.ofs" "Gotham_Arch_Classic_BigWiny2_file1.fs"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.c" "Gotham_Arch_Classic_BigWiny2_file2.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.tf" "Gotham_Arch_Classic_BigWiny2_file2.tf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.rf" "Gotham_Arch_Classic_BigWiny2_file2.rf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.mu" "Gotham_Arch_Classic_BigWiny2_file2.mu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.mv" "Gotham_Arch_Classic_BigWiny2_file2.mv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.s" "Gotham_Arch_Classic_BigWiny2_file2.s"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.wu" "Gotham_Arch_Classic_BigWiny2_file2.wu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.wv" "Gotham_Arch_Classic_BigWiny2_file2.wv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.re" "Gotham_Arch_Classic_BigWiny2_file2.re"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.of" "Gotham_Arch_Classic_BigWiny2_file2.of"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.r" "Gotham_Arch_Classic_BigWiny2_file2.ro"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.n" "Gotham_Arch_Classic_BigWiny2_file2.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.vt1" "Gotham_Arch_Classic_BigWiny2_file2.vt1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.vt2" "Gotham_Arch_Classic_BigWiny2_file2.vt2"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.vt3" "Gotham_Arch_Classic_BigWiny2_file2.vt3"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.vc1" "Gotham_Arch_Classic_BigWiny2_file2.vc1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.o" "Gotham_Arch_Classic_BigWiny2_file2.uv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.ofs" "Gotham_Arch_Classic_BigWiny2_file2.fs"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file2.oa" "Gotham_Arch_Classic_BigWiny2_bump2d1.bv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_3.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo4.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_4.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo5.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_5.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo6.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_6.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo7.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_7.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo8.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.c" "Gotham_Arch_Classic_BigWiny2_file3.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.tf" "Gotham_Arch_Classic_BigWiny2_file3.tf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.rf" "Gotham_Arch_Classic_BigWiny2_file3.rf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.mu" "Gotham_Arch_Classic_BigWiny2_file3.mu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.mv" "Gotham_Arch_Classic_BigWiny2_file3.mv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.s" "Gotham_Arch_Classic_BigWiny2_file3.s"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.wu" "Gotham_Arch_Classic_BigWiny2_file3.wu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.wv" "Gotham_Arch_Classic_BigWiny2_file3.wv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.re" "Gotham_Arch_Classic_BigWiny2_file3.re"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.of" "Gotham_Arch_Classic_BigWiny2_file3.of"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.r" "Gotham_Arch_Classic_BigWiny2_file3.ro"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.n" "Gotham_Arch_Classic_BigWiny2_file3.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.vt1" "Gotham_Arch_Classic_BigWiny2_file3.vt1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.vt2" "Gotham_Arch_Classic_BigWiny2_file3.vt2"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.vt3" "Gotham_Arch_Classic_BigWiny2_file3.vt3"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.vc1" "Gotham_Arch_Classic_BigWiny2_file3.vc1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.o" "Gotham_Arch_Classic_BigWiny2_file3.uv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.ofs" "Gotham_Arch_Classic_BigWiny2_file3.fs"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_8.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo9.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.c" "Gotham_Arch_Classic_BigWiny2_file4.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.tf" "Gotham_Arch_Classic_BigWiny2_file4.tf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.rf" "Gotham_Arch_Classic_BigWiny2_file4.rf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.mu" "Gotham_Arch_Classic_BigWiny2_file4.mu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.mv" "Gotham_Arch_Classic_BigWiny2_file4.mv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.s" "Gotham_Arch_Classic_BigWiny2_file4.s"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.wu" "Gotham_Arch_Classic_BigWiny2_file4.wu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.wv" "Gotham_Arch_Classic_BigWiny2_file4.wv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.re" "Gotham_Arch_Classic_BigWiny2_file4.re"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.of" "Gotham_Arch_Classic_BigWiny2_file4.of"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.r" "Gotham_Arch_Classic_BigWiny2_file4.ro"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.n" "Gotham_Arch_Classic_BigWiny2_file4.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.vt1" "Gotham_Arch_Classic_BigWiny2_file4.vt1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.vt2" "Gotham_Arch_Classic_BigWiny2_file4.vt2"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.vt3" "Gotham_Arch_Classic_BigWiny2_file4.vt3"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.vc1" "Gotham_Arch_Classic_BigWiny2_file4.vc1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.o" "Gotham_Arch_Classic_BigWiny2_file4.uv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.ofs" "Gotham_Arch_Classic_BigWiny2_file4.fs"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.c" "Gotham_Arch_Classic_BigWiny2_file5.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.tf" "Gotham_Arch_Classic_BigWiny2_file5.tf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.rf" "Gotham_Arch_Classic_BigWiny2_file5.rf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.mu" "Gotham_Arch_Classic_BigWiny2_file5.mu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.mv" "Gotham_Arch_Classic_BigWiny2_file5.mv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.s" "Gotham_Arch_Classic_BigWiny2_file5.s"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.wu" "Gotham_Arch_Classic_BigWiny2_file5.wu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.wv" "Gotham_Arch_Classic_BigWiny2_file5.wv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.re" "Gotham_Arch_Classic_BigWiny2_file5.re"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.of" "Gotham_Arch_Classic_BigWiny2_file5.of"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.r" "Gotham_Arch_Classic_BigWiny2_file5.ro"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.n" "Gotham_Arch_Classic_BigWiny2_file5.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.vt1" "Gotham_Arch_Classic_BigWiny2_file5.vt1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.vt2" "Gotham_Arch_Classic_BigWiny2_file5.vt2"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.vt3" "Gotham_Arch_Classic_BigWiny2_file5.vt3"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.vc1" "Gotham_Arch_Classic_BigWiny2_file5.vc1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.o" "Gotham_Arch_Classic_BigWiny2_file5.uv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.ofs" "Gotham_Arch_Classic_BigWiny2_file5.fs"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file5.oa" "Gotham_Arch_Classic_BigWiny2_bump2d2.bv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_phong1.oc" "Gotham_Arch_Classic_BigWiny2_material_9.ss"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_phong1.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo10.m"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_9.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo10.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file6.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo10.t"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_blinn1.oc" "Gotham_Arch_Classic_BigWiny2_material_10.ss"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_blinn1.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo11.m"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_10.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo11.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file8.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo11.t"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.c" "Gotham_Arch_Classic_BigWiny2_file6.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.tf" "Gotham_Arch_Classic_BigWiny2_file6.tf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.rf" "Gotham_Arch_Classic_BigWiny2_file6.rf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.mu" "Gotham_Arch_Classic_BigWiny2_file6.mu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.mv" "Gotham_Arch_Classic_BigWiny2_file6.mv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.s" "Gotham_Arch_Classic_BigWiny2_file6.s"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.wu" "Gotham_Arch_Classic_BigWiny2_file6.wu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.wv" "Gotham_Arch_Classic_BigWiny2_file6.wv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.re" "Gotham_Arch_Classic_BigWiny2_file6.re"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.of" "Gotham_Arch_Classic_BigWiny2_file6.of"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.r" "Gotham_Arch_Classic_BigWiny2_file6.ro"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.n" "Gotham_Arch_Classic_BigWiny2_file6.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.vt1" "Gotham_Arch_Classic_BigWiny2_file6.vt1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.vt2" "Gotham_Arch_Classic_BigWiny2_file6.vt2"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.vt3" "Gotham_Arch_Classic_BigWiny2_file6.vt3"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.vc1" "Gotham_Arch_Classic_BigWiny2_file6.vc1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.o" "Gotham_Arch_Classic_BigWiny2_file6.uv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.ofs" "Gotham_Arch_Classic_BigWiny2_file6.fs"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.c" "Gotham_Arch_Classic_BigWiny2_file7.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.tf" "Gotham_Arch_Classic_BigWiny2_file7.tf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.rf" "Gotham_Arch_Classic_BigWiny2_file7.rf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.mu" "Gotham_Arch_Classic_BigWiny2_file7.mu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.mv" "Gotham_Arch_Classic_BigWiny2_file7.mv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.s" "Gotham_Arch_Classic_BigWiny2_file7.s"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.wu" "Gotham_Arch_Classic_BigWiny2_file7.wu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.wv" "Gotham_Arch_Classic_BigWiny2_file7.wv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.re" "Gotham_Arch_Classic_BigWiny2_file7.re"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.of" "Gotham_Arch_Classic_BigWiny2_file7.of"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.r" "Gotham_Arch_Classic_BigWiny2_file7.ro"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.n" "Gotham_Arch_Classic_BigWiny2_file7.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.vt1" "Gotham_Arch_Classic_BigWiny2_file7.vt1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.vt2" "Gotham_Arch_Classic_BigWiny2_file7.vt2"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.vt3" "Gotham_Arch_Classic_BigWiny2_file7.vt3"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.vc1" "Gotham_Arch_Classic_BigWiny2_file7.vc1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.o" "Gotham_Arch_Classic_BigWiny2_file7.uv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.ofs" "Gotham_Arch_Classic_BigWiny2_file7.fs"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file7.oa" "Gotham_Arch_Classic_BigWiny2_bump2d3.bv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.c" "Gotham_Arch_Classic_BigWiny2_file8.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.tf" "Gotham_Arch_Classic_BigWiny2_file8.tf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.rf" "Gotham_Arch_Classic_BigWiny2_file8.rf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.mu" "Gotham_Arch_Classic_BigWiny2_file8.mu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.mv" "Gotham_Arch_Classic_BigWiny2_file8.mv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.s" "Gotham_Arch_Classic_BigWiny2_file8.s"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.wu" "Gotham_Arch_Classic_BigWiny2_file8.wu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.wv" "Gotham_Arch_Classic_BigWiny2_file8.wv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.re" "Gotham_Arch_Classic_BigWiny2_file8.re"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.of" "Gotham_Arch_Classic_BigWiny2_file8.of"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.r" "Gotham_Arch_Classic_BigWiny2_file8.ro"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.n" "Gotham_Arch_Classic_BigWiny2_file8.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.vt1" "Gotham_Arch_Classic_BigWiny2_file8.vt1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.vt2" "Gotham_Arch_Classic_BigWiny2_file8.vt2"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.vt3" "Gotham_Arch_Classic_BigWiny2_file8.vt3"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.vc1" "Gotham_Arch_Classic_BigWiny2_file8.vc1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.o" "Gotham_Arch_Classic_BigWiny2_file8.uv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.ofs" "Gotham_Arch_Classic_BigWiny2_file8.fs"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.c" "Gotham_Arch_Classic_BigWiny2_file9.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.tf" "Gotham_Arch_Classic_BigWiny2_file9.tf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.rf" "Gotham_Arch_Classic_BigWiny2_file9.rf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.mu" "Gotham_Arch_Classic_BigWiny2_file9.mu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.mv" "Gotham_Arch_Classic_BigWiny2_file9.mv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.s" "Gotham_Arch_Classic_BigWiny2_file9.s"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.wu" "Gotham_Arch_Classic_BigWiny2_file9.wu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.wv" "Gotham_Arch_Classic_BigWiny2_file9.wv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.re" "Gotham_Arch_Classic_BigWiny2_file9.re"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.of" "Gotham_Arch_Classic_BigWiny2_file9.of"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.r" "Gotham_Arch_Classic_BigWiny2_file9.ro"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.n" "Gotham_Arch_Classic_BigWiny2_file9.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.vt1" "Gotham_Arch_Classic_BigWiny2_file9.vt1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.vt2" "Gotham_Arch_Classic_BigWiny2_file9.vt2"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.vt3" "Gotham_Arch_Classic_BigWiny2_file9.vt3"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.vc1" "Gotham_Arch_Classic_BigWiny2_file9.vc1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.o" "Gotham_Arch_Classic_BigWiny2_file9.uv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.ofs" "Gotham_Arch_Classic_BigWiny2_file9.fs"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file9.oa" "Gotham_Arch_Classic_BigWiny2_bump2d4.bv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_hyperView1.msg" "Gotham_Arch_Classic_BigWiny2_nodeEditorPanel1Info.b[0]"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_hyperLayout1.msg" "Gotham_Arch_Classic_BigWiny2_hyperView1.hl"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_11.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo12.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file6.oc" "Gotham_Arch_Classic_BigWiny2_phong1.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_bump2d3.o" "Gotham_Arch_Classic_BigWiny2_phong1.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file10.oc" "Gotham_Arch_Classic_BigWiny2_phong1.sc"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.c" "Gotham_Arch_Classic_BigWiny2_file10.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.tf" "Gotham_Arch_Classic_BigWiny2_file10.tf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.rf" "Gotham_Arch_Classic_BigWiny2_file10.rf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.mu" "Gotham_Arch_Classic_BigWiny2_file10.mu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.mv" "Gotham_Arch_Classic_BigWiny2_file10.mv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.s" "Gotham_Arch_Classic_BigWiny2_file10.s"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.wu" "Gotham_Arch_Classic_BigWiny2_file10.wu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.wv" "Gotham_Arch_Classic_BigWiny2_file10.wv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.re" "Gotham_Arch_Classic_BigWiny2_file10.re"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.of" "Gotham_Arch_Classic_BigWiny2_file10.of"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.r" "Gotham_Arch_Classic_BigWiny2_file10.ro"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.n" "Gotham_Arch_Classic_BigWiny2_file10.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.vt1" "Gotham_Arch_Classic_BigWiny2_file10.vt1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.vt2" "Gotham_Arch_Classic_BigWiny2_file10.vt2"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.vt3" "Gotham_Arch_Classic_BigWiny2_file10.vt3"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.vc1" "Gotham_Arch_Classic_BigWiny2_file10.vc1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.o" "Gotham_Arch_Classic_BigWiny2_file10.uv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.ofs" "Gotham_Arch_Classic_BigWiny2_file10.fs"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file8.oc" "Gotham_Arch_Classic_BigWiny2_blinn1.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_bump2d4.o" "Gotham_Arch_Classic_BigWiny2_blinn1.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file11.oc" "Gotham_Arch_Classic_BigWiny2_blinn1.sc"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.c" "Gotham_Arch_Classic_BigWiny2_file11.c"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.tf" "Gotham_Arch_Classic_BigWiny2_file11.tf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.rf" "Gotham_Arch_Classic_BigWiny2_file11.rf"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.mu" "Gotham_Arch_Classic_BigWiny2_file11.mu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.mv" "Gotham_Arch_Classic_BigWiny2_file11.mv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.s" "Gotham_Arch_Classic_BigWiny2_file11.s"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.wu" "Gotham_Arch_Classic_BigWiny2_file11.wu"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.wv" "Gotham_Arch_Classic_BigWiny2_file11.wv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.re" "Gotham_Arch_Classic_BigWiny2_file11.re"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.of" "Gotham_Arch_Classic_BigWiny2_file11.of"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.r" "Gotham_Arch_Classic_BigWiny2_file11.ro"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.n" "Gotham_Arch_Classic_BigWiny2_file11.n"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.vt1" "Gotham_Arch_Classic_BigWiny2_file11.vt1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.vt2" "Gotham_Arch_Classic_BigWiny2_file11.vt2"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.vt3" "Gotham_Arch_Classic_BigWiny2_file11.vt3"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.vc1" "Gotham_Arch_Classic_BigWiny2_file11.vc1"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.o" "Gotham_Arch_Classic_BigWiny2_file11.uv"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.ofs" "Gotham_Arch_Classic_BigWiny2_file11.fs"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_12.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo13.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_13.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo14.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_14.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo15.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_15.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo16.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_16.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo17.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_0_lambert.oc" "Gotham_Arch_Classic_BigWiny2_material_17.ss"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_0_lambert.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo18.m"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_17.msg" "Gotham_Arch_Classic_BigWiny2_materialInfo18.sg"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_0.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[6].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo1.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[7].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_1.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[8].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo2.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[9].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_0_lambert2.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[10].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_2.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[11].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo3.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[12].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file1.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[13].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[14].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file2.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[15].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[16].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_bump2d1.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[17].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_3.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[18].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo4.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[19].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_4.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[20].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo5.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[21].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_5.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[22].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo6.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[23].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_6.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[24].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo7.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[25].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_7.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[26].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo8.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[27].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file3.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[28].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[29].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_8.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[30].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo9.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[31].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file4.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[32].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[33].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file5.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[34].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[35].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_bump2d2.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[36].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_9.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[37].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo10.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[38].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_10.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[39].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo11.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[40].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file6.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[41].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[42].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file7.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[43].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[44].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_bump2d3.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[45].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file8.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[46].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[47].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file9.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[48].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[49].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_bump2d4.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[50].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_nodeEditorPanel1Info.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[51].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_hyperView1.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[52].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_hyperLayout1.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[53].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_11.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[56].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo12.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[57].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_phong1.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[58].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file10.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[59].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[60].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_blinn1.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[61].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file11.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[62].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[63].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_12.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[64].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo13.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[65].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_13.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[66].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo14.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[67].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_14.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[68].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo15.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[69].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_15.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[70].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo16.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[71].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_16.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[72].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo17.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[73].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_0_lambert.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[74].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_17.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[75].dn"
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_materialInfo18.msg" "AD_Gotham_Arch_Classic_BigWiny2_hyperLayout1.hyp[76].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_phong1.oc" "BridgeRoad_Destroyed_2048_Custom_02_material_0.ss"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_phong1.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo1.m"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo1.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file1.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo1.t"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.c" "BridgeRoad_Destroyed_2048_Custom_02_file1.c"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.tf" "BridgeRoad_Destroyed_2048_Custom_02_file1.tf"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.rf" "BridgeRoad_Destroyed_2048_Custom_02_file1.rf"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.mu" "BridgeRoad_Destroyed_2048_Custom_02_file1.mu"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.mv" "BridgeRoad_Destroyed_2048_Custom_02_file1.mv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.s" "BridgeRoad_Destroyed_2048_Custom_02_file1.s"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.wu" "BridgeRoad_Destroyed_2048_Custom_02_file1.wu"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.wv" "BridgeRoad_Destroyed_2048_Custom_02_file1.wv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.re" "BridgeRoad_Destroyed_2048_Custom_02_file1.re"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.of" "BridgeRoad_Destroyed_2048_Custom_02_file1.of"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.r" "BridgeRoad_Destroyed_2048_Custom_02_file1.ro"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.n" "BridgeRoad_Destroyed_2048_Custom_02_file1.n"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.vt1" "BridgeRoad_Destroyed_2048_Custom_02_file1.vt1"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.vt2" "BridgeRoad_Destroyed_2048_Custom_02_file1.vt2"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.vt3" "BridgeRoad_Destroyed_2048_Custom_02_file1.vt3"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.vc1" "BridgeRoad_Destroyed_2048_Custom_02_file1.vc1"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.o" "BridgeRoad_Destroyed_2048_Custom_02_file1.uv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.ofs" "BridgeRoad_Destroyed_2048_Custom_02_file1.fs"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.c" "BridgeRoad_Destroyed_2048_Custom_02_file2.c"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.tf" "BridgeRoad_Destroyed_2048_Custom_02_file2.tf"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.rf" "BridgeRoad_Destroyed_2048_Custom_02_file2.rf"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.mu" "BridgeRoad_Destroyed_2048_Custom_02_file2.mu"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.mv" "BridgeRoad_Destroyed_2048_Custom_02_file2.mv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.s" "BridgeRoad_Destroyed_2048_Custom_02_file2.s"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.wu" "BridgeRoad_Destroyed_2048_Custom_02_file2.wu"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.wv" "BridgeRoad_Destroyed_2048_Custom_02_file2.wv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.re" "BridgeRoad_Destroyed_2048_Custom_02_file2.re"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.of" "BridgeRoad_Destroyed_2048_Custom_02_file2.of"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.r" "BridgeRoad_Destroyed_2048_Custom_02_file2.ro"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.n" "BridgeRoad_Destroyed_2048_Custom_02_file2.n"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.vt1" "BridgeRoad_Destroyed_2048_Custom_02_file2.vt1"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.vt2" "BridgeRoad_Destroyed_2048_Custom_02_file2.vt2"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.vt3" "BridgeRoad_Destroyed_2048_Custom_02_file2.vt3"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.vc1" "BridgeRoad_Destroyed_2048_Custom_02_file2.vc1"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.o" "BridgeRoad_Destroyed_2048_Custom_02_file2.uv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.ofs" "BridgeRoad_Destroyed_2048_Custom_02_file2.fs"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file2.oa" "BridgeRoad_Destroyed_2048_Custom_02_bump2d1.bv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file1.oc" "BridgeRoad_Destroyed_2048_Custom_02_phong1.c"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_bump2d1.o" "BridgeRoad_Destroyed_2048_Custom_02_phong1.n"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file3.oc" "BridgeRoad_Destroyed_2048_Custom_02_phong1.sc"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.c" "BridgeRoad_Destroyed_2048_Custom_02_file3.c"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.tf" "BridgeRoad_Destroyed_2048_Custom_02_file3.tf"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.rf" "BridgeRoad_Destroyed_2048_Custom_02_file3.rf"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.mu" "BridgeRoad_Destroyed_2048_Custom_02_file3.mu"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.mv" "BridgeRoad_Destroyed_2048_Custom_02_file3.mv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.s" "BridgeRoad_Destroyed_2048_Custom_02_file3.s"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.wu" "BridgeRoad_Destroyed_2048_Custom_02_file3.wu"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.wv" "BridgeRoad_Destroyed_2048_Custom_02_file3.wv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.re" "BridgeRoad_Destroyed_2048_Custom_02_file3.re"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.of" "BridgeRoad_Destroyed_2048_Custom_02_file3.of"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.r" "BridgeRoad_Destroyed_2048_Custom_02_file3.ro"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.n" "BridgeRoad_Destroyed_2048_Custom_02_file3.n"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.vt1" "BridgeRoad_Destroyed_2048_Custom_02_file3.vt1"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.vt2" "BridgeRoad_Destroyed_2048_Custom_02_file3.vt2"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.vt3" "BridgeRoad_Destroyed_2048_Custom_02_file3.vt3"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.vc1" "BridgeRoad_Destroyed_2048_Custom_02_file3.vc1"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.o" "BridgeRoad_Destroyed_2048_Custom_02_file3.uv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.ofs" "BridgeRoad_Destroyed_2048_Custom_02_file3.fs"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_hyperView1.msg" "BridgeRoad_Destroyed_2048_Custom_02_nodeEditorPanel1Info.b[0]"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.msg" "BridgeRoad_Destroyed_2048_Custom_02_hyperView1.hl"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_1.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo2.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_phong2.oc" "BridgeRoad_Destroyed_2048_Custom_02_material_2.ss"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_phong2.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo3.m"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_2.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo3.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file4.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo3.t"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.c" "BridgeRoad_Destroyed_2048_Custom_02_file4.c"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.tf" "BridgeRoad_Destroyed_2048_Custom_02_file4.tf"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.rf" "BridgeRoad_Destroyed_2048_Custom_02_file4.rf"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.mu" "BridgeRoad_Destroyed_2048_Custom_02_file4.mu"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.mv" "BridgeRoad_Destroyed_2048_Custom_02_file4.mv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.s" "BridgeRoad_Destroyed_2048_Custom_02_file4.s"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.wu" "BridgeRoad_Destroyed_2048_Custom_02_file4.wu"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.wv" "BridgeRoad_Destroyed_2048_Custom_02_file4.wv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.re" "BridgeRoad_Destroyed_2048_Custom_02_file4.re"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.of" "BridgeRoad_Destroyed_2048_Custom_02_file4.of"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.r" "BridgeRoad_Destroyed_2048_Custom_02_file4.ro"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.n" "BridgeRoad_Destroyed_2048_Custom_02_file4.n"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.vt1" "BridgeRoad_Destroyed_2048_Custom_02_file4.vt1"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.vt2" "BridgeRoad_Destroyed_2048_Custom_02_file4.vt2"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.vt3" "BridgeRoad_Destroyed_2048_Custom_02_file4.vt3"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.vc1" "BridgeRoad_Destroyed_2048_Custom_02_file4.vc1"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.o" "BridgeRoad_Destroyed_2048_Custom_02_file4.uv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.ofs" "BridgeRoad_Destroyed_2048_Custom_02_file4.fs"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.c" "BridgeRoad_Destroyed_2048_Custom_02_file5.c"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.tf" "BridgeRoad_Destroyed_2048_Custom_02_file5.tf"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.rf" "BridgeRoad_Destroyed_2048_Custom_02_file5.rf"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.mu" "BridgeRoad_Destroyed_2048_Custom_02_file5.mu"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.mv" "BridgeRoad_Destroyed_2048_Custom_02_file5.mv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.s" "BridgeRoad_Destroyed_2048_Custom_02_file5.s"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.wu" "BridgeRoad_Destroyed_2048_Custom_02_file5.wu"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.wv" "BridgeRoad_Destroyed_2048_Custom_02_file5.wv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.re" "BridgeRoad_Destroyed_2048_Custom_02_file5.re"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.of" "BridgeRoad_Destroyed_2048_Custom_02_file5.of"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.r" "BridgeRoad_Destroyed_2048_Custom_02_file5.ro"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.n" "BridgeRoad_Destroyed_2048_Custom_02_file5.n"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.vt1" "BridgeRoad_Destroyed_2048_Custom_02_file5.vt1"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.vt2" "BridgeRoad_Destroyed_2048_Custom_02_file5.vt2"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.vt3" "BridgeRoad_Destroyed_2048_Custom_02_file5.vt3"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.vc1" "BridgeRoad_Destroyed_2048_Custom_02_file5.vc1"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.o" "BridgeRoad_Destroyed_2048_Custom_02_file5.uv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.ofs" "BridgeRoad_Destroyed_2048_Custom_02_file5.fs"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file5.oa" "BridgeRoad_Destroyed_2048_Custom_02_bump2d2.bv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file4.oc" "BridgeRoad_Destroyed_2048_Custom_02_phong2.c"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_bump2d2.o" "BridgeRoad_Destroyed_2048_Custom_02_phong2.n"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file6.oc" "BridgeRoad_Destroyed_2048_Custom_02_phong2.sc"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.c" "BridgeRoad_Destroyed_2048_Custom_02_file6.c"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.tf" "BridgeRoad_Destroyed_2048_Custom_02_file6.tf"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.rf" "BridgeRoad_Destroyed_2048_Custom_02_file6.rf"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.mu" "BridgeRoad_Destroyed_2048_Custom_02_file6.mu"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.mv" "BridgeRoad_Destroyed_2048_Custom_02_file6.mv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.s" "BridgeRoad_Destroyed_2048_Custom_02_file6.s"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.wu" "BridgeRoad_Destroyed_2048_Custom_02_file6.wu"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.wv" "BridgeRoad_Destroyed_2048_Custom_02_file6.wv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.re" "BridgeRoad_Destroyed_2048_Custom_02_file6.re"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.of" "BridgeRoad_Destroyed_2048_Custom_02_file6.of"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.r" "BridgeRoad_Destroyed_2048_Custom_02_file6.ro"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.n" "BridgeRoad_Destroyed_2048_Custom_02_file6.n"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.vt1" "BridgeRoad_Destroyed_2048_Custom_02_file6.vt1"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.vt2" "BridgeRoad_Destroyed_2048_Custom_02_file6.vt2"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.vt3" "BridgeRoad_Destroyed_2048_Custom_02_file6.vt3"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.vc1" "BridgeRoad_Destroyed_2048_Custom_02_file6.vc1"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.o" "BridgeRoad_Destroyed_2048_Custom_02_file6.uv"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.ofs" "BridgeRoad_Destroyed_2048_Custom_02_file6.fs"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_3.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo4.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_4.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo5.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_5.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo6.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_6.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo7.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_7.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo8.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_8.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo9.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_9.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo10.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_10.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo11.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_11.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo12.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_12.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo13.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_13.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo14.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_14.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo15.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_15.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo16.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_16.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo17.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_17.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo18.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_18.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo19.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_19.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo20.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_20.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo21.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_21.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo22.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_22.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo23.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_23.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo24.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_24.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo25.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_25.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo26.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_26.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo27.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_27.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo28.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_28.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo29.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_29.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo30.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_30.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo31.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_31.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo32.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert.oc" "BridgeRoad_Destroyed_2048_Custom_02_material_32.ss"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo33.m"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_32.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo33.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert1.oc" "BridgeRoad_Destroyed_2048_Custom_02_material_33.ss"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert1.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo34.m"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_33.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo34.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert2.oc" "BridgeRoad_Destroyed_2048_Custom_02_material_34.ss"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert2.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo35.m"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_34.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo35.sg"
		;
connectAttr "material_0_lambert3.oc" "BridgeRoad_Destroyed_2048_Custom_02_material_35.ss"
		;
connectAttr "material_0_lambert3.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo36.m"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_35.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo36.sg"
		;
connectAttr "material_0_lambert4.oc" "BridgeRoad_Destroyed_2048_Custom_02_material_36.ss"
		;
connectAttr "material_0_lambert4.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo37.m"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_36.msg" "BridgeRoad_Destroyed_2048_Custom_02_materialInfo37.sg"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[6].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo1.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[7].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file1.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[8].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[9].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file2.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[10].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[11].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_bump2d1.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[12].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_phong1.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[13].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file3.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[14].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[15].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_nodeEditorPanel1Info.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[16].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_hyperView1.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[17].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[18].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_1.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[21].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo2.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[22].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_2.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[23].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo3.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[24].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file4.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[25].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[26].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file5.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[27].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[28].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_bump2d2.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[29].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_phong2.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[30].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file6.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[31].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[32].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_3.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[33].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo4.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[34].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_4.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[35].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo5.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[36].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_5.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[37].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo6.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[38].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_6.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[39].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo7.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[40].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_7.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[41].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo8.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[42].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_8.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[43].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo9.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[44].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_9.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[45].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo10.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[46].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_10.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[47].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo11.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[48].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_11.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[49].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo12.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[50].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_12.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[51].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo13.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[52].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_13.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[53].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo14.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[54].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_14.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[55].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo15.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[56].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_15.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[57].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo16.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[58].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_16.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[59].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo17.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[60].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_17.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[61].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo18.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[62].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_18.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[63].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo19.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[64].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_19.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[65].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo20.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[66].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_20.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[67].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo21.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[68].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_21.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[69].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo22.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[70].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_22.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[71].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo23.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[72].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_23.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[73].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo24.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[74].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_24.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[75].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo25.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[76].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_25.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[77].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo26.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[78].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_26.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[79].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo27.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[80].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_27.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[81].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo28.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[82].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_28.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[83].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo29.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[84].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_29.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[85].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo30.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[86].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_30.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[87].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo31.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[88].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_31.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[89].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo32.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[90].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[91].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_32.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[92].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo33.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[93].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert1.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[94].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_33.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[95].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo34.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[96].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert2.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[97].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_34.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[98].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo35.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[99].dn"
		;
connectAttr "material_0_lambert3.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[100].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_35.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[101].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo36.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[102].dn"
		;
connectAttr "material_0_lambert4.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[103].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_36.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[104].dn"
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_materialInfo37.msg" "AD_BridgeRoad_Destroyed_2048_Custom_02_hyperLayout1.hyp[105].dn"
		;
connectAttr "ConcreteBarrier01_phong1.oc" "ConcreteBarrier01_material_0.ss";
connectAttr "ConcreteBarrier01_phong1.msg" "ConcreteBarrier01_materialInfo1.m";
connectAttr "ConcreteBarrier01_material_0.msg" "ConcreteBarrier01_materialInfo1.sg"
		;
connectAttr "ConcreteBarrier01_file1.msg" "ConcreteBarrier01_materialInfo1.t" -na
		;
connectAttr "ConcreteBarrier01_place2dTexture1.c" "ConcreteBarrier01_file1.c";
connectAttr "ConcreteBarrier01_place2dTexture1.tf" "ConcreteBarrier01_file1.tf";
connectAttr "ConcreteBarrier01_place2dTexture1.rf" "ConcreteBarrier01_file1.rf";
connectAttr "ConcreteBarrier01_place2dTexture1.mu" "ConcreteBarrier01_file1.mu";
connectAttr "ConcreteBarrier01_place2dTexture1.mv" "ConcreteBarrier01_file1.mv";
connectAttr "ConcreteBarrier01_place2dTexture1.s" "ConcreteBarrier01_file1.s";
connectAttr "ConcreteBarrier01_place2dTexture1.wu" "ConcreteBarrier01_file1.wu";
connectAttr "ConcreteBarrier01_place2dTexture1.wv" "ConcreteBarrier01_file1.wv";
connectAttr "ConcreteBarrier01_place2dTexture1.re" "ConcreteBarrier01_file1.re";
connectAttr "ConcreteBarrier01_place2dTexture1.of" "ConcreteBarrier01_file1.of";
connectAttr "ConcreteBarrier01_place2dTexture1.r" "ConcreteBarrier01_file1.ro";
connectAttr "ConcreteBarrier01_place2dTexture1.n" "ConcreteBarrier01_file1.n";
connectAttr "ConcreteBarrier01_place2dTexture1.vt1" "ConcreteBarrier01_file1.vt1"
		;
connectAttr "ConcreteBarrier01_place2dTexture1.vt2" "ConcreteBarrier01_file1.vt2"
		;
connectAttr "ConcreteBarrier01_place2dTexture1.vt3" "ConcreteBarrier01_file1.vt3"
		;
connectAttr "ConcreteBarrier01_place2dTexture1.vc1" "ConcreteBarrier01_file1.vc1"
		;
connectAttr "ConcreteBarrier01_place2dTexture1.o" "ConcreteBarrier01_file1.uv";
connectAttr "ConcreteBarrier01_place2dTexture1.ofs" "ConcreteBarrier01_file1.fs"
		;
connectAttr "ConcreteBarrier01_place2dTexture2.c" "ConcreteBarrier01_file2.c";
connectAttr "ConcreteBarrier01_place2dTexture2.tf" "ConcreteBarrier01_file2.tf";
connectAttr "ConcreteBarrier01_place2dTexture2.rf" "ConcreteBarrier01_file2.rf";
connectAttr "ConcreteBarrier01_place2dTexture2.mu" "ConcreteBarrier01_file2.mu";
connectAttr "ConcreteBarrier01_place2dTexture2.mv" "ConcreteBarrier01_file2.mv";
connectAttr "ConcreteBarrier01_place2dTexture2.s" "ConcreteBarrier01_file2.s";
connectAttr "ConcreteBarrier01_place2dTexture2.wu" "ConcreteBarrier01_file2.wu";
connectAttr "ConcreteBarrier01_place2dTexture2.wv" "ConcreteBarrier01_file2.wv";
connectAttr "ConcreteBarrier01_place2dTexture2.re" "ConcreteBarrier01_file2.re";
connectAttr "ConcreteBarrier01_place2dTexture2.of" "ConcreteBarrier01_file2.of";
connectAttr "ConcreteBarrier01_place2dTexture2.r" "ConcreteBarrier01_file2.ro";
connectAttr "ConcreteBarrier01_place2dTexture2.n" "ConcreteBarrier01_file2.n";
connectAttr "ConcreteBarrier01_place2dTexture2.vt1" "ConcreteBarrier01_file2.vt1"
		;
connectAttr "ConcreteBarrier01_place2dTexture2.vt2" "ConcreteBarrier01_file2.vt2"
		;
connectAttr "ConcreteBarrier01_place2dTexture2.vt3" "ConcreteBarrier01_file2.vt3"
		;
connectAttr "ConcreteBarrier01_place2dTexture2.vc1" "ConcreteBarrier01_file2.vc1"
		;
connectAttr "ConcreteBarrier01_place2dTexture2.o" "ConcreteBarrier01_file2.uv";
connectAttr "ConcreteBarrier01_place2dTexture2.ofs" "ConcreteBarrier01_file2.fs"
		;
connectAttr "ConcreteBarrier01_file2.oa" "ConcreteBarrier01_bump2d1.bv";
connectAttr "ConcreteBarrier01_file1.oc" "ConcreteBarrier01_phong1.c";
connectAttr "ConcreteBarrier01_bump2d1.o" "ConcreteBarrier01_phong1.n";
connectAttr "ConcreteBarrier01_file3.oc" "ConcreteBarrier01_phong1.sc";
connectAttr "ConcreteBarrier01_place2dTexture3.c" "ConcreteBarrier01_file3.c";
connectAttr "ConcreteBarrier01_place2dTexture3.tf" "ConcreteBarrier01_file3.tf";
connectAttr "ConcreteBarrier01_place2dTexture3.rf" "ConcreteBarrier01_file3.rf";
connectAttr "ConcreteBarrier01_place2dTexture3.mu" "ConcreteBarrier01_file3.mu";
connectAttr "ConcreteBarrier01_place2dTexture3.mv" "ConcreteBarrier01_file3.mv";
connectAttr "ConcreteBarrier01_place2dTexture3.s" "ConcreteBarrier01_file3.s";
connectAttr "ConcreteBarrier01_place2dTexture3.wu" "ConcreteBarrier01_file3.wu";
connectAttr "ConcreteBarrier01_place2dTexture3.wv" "ConcreteBarrier01_file3.wv";
connectAttr "ConcreteBarrier01_place2dTexture3.re" "ConcreteBarrier01_file3.re";
connectAttr "ConcreteBarrier01_place2dTexture3.of" "ConcreteBarrier01_file3.of";
connectAttr "ConcreteBarrier01_place2dTexture3.r" "ConcreteBarrier01_file3.ro";
connectAttr "ConcreteBarrier01_place2dTexture3.n" "ConcreteBarrier01_file3.n";
connectAttr "ConcreteBarrier01_place2dTexture3.vt1" "ConcreteBarrier01_file3.vt1"
		;
connectAttr "ConcreteBarrier01_place2dTexture3.vt2" "ConcreteBarrier01_file3.vt2"
		;
connectAttr "ConcreteBarrier01_place2dTexture3.vt3" "ConcreteBarrier01_file3.vt3"
		;
connectAttr "ConcreteBarrier01_place2dTexture3.vc1" "ConcreteBarrier01_file3.vc1"
		;
connectAttr "ConcreteBarrier01_place2dTexture3.o" "ConcreteBarrier01_file3.uv";
connectAttr "ConcreteBarrier01_place2dTexture3.ofs" "ConcreteBarrier01_file3.fs"
		;
connectAttr "ConcreteBarrier01_hyperView1.msg" "ConcreteBarrier01_nodeEditorPanel1Info.b[0]"
		;
connectAttr "ConcreteBarrier01_hyperLayout1.msg" "ConcreteBarrier01_hyperView1.hl"
		;
connectAttr "ConcreteBarrier01_material_1.msg" "ConcreteBarrier01_materialInfo2.sg"
		;
connectAttr "ConcreteBarrier01_phong2.oc" "ConcreteBarrier01_material_2.ss";
connectAttr "ConcreteBarrier01_phong2.msg" "ConcreteBarrier01_materialInfo3.m";
connectAttr "ConcreteBarrier01_material_2.msg" "ConcreteBarrier01_materialInfo3.sg"
		;
connectAttr "ConcreteBarrier01_file4.msg" "ConcreteBarrier01_materialInfo3.t" -na
		;
connectAttr "ConcreteBarrier01_place2dTexture4.c" "ConcreteBarrier01_file4.c";
connectAttr "ConcreteBarrier01_place2dTexture4.tf" "ConcreteBarrier01_file4.tf";
connectAttr "ConcreteBarrier01_place2dTexture4.rf" "ConcreteBarrier01_file4.rf";
connectAttr "ConcreteBarrier01_place2dTexture4.mu" "ConcreteBarrier01_file4.mu";
connectAttr "ConcreteBarrier01_place2dTexture4.mv" "ConcreteBarrier01_file4.mv";
connectAttr "ConcreteBarrier01_place2dTexture4.s" "ConcreteBarrier01_file4.s";
connectAttr "ConcreteBarrier01_place2dTexture4.wu" "ConcreteBarrier01_file4.wu";
connectAttr "ConcreteBarrier01_place2dTexture4.wv" "ConcreteBarrier01_file4.wv";
connectAttr "ConcreteBarrier01_place2dTexture4.re" "ConcreteBarrier01_file4.re";
connectAttr "ConcreteBarrier01_place2dTexture4.of" "ConcreteBarrier01_file4.of";
connectAttr "ConcreteBarrier01_place2dTexture4.r" "ConcreteBarrier01_file4.ro";
connectAttr "ConcreteBarrier01_place2dTexture4.n" "ConcreteBarrier01_file4.n";
connectAttr "ConcreteBarrier01_place2dTexture4.vt1" "ConcreteBarrier01_file4.vt1"
		;
connectAttr "ConcreteBarrier01_place2dTexture4.vt2" "ConcreteBarrier01_file4.vt2"
		;
connectAttr "ConcreteBarrier01_place2dTexture4.vt3" "ConcreteBarrier01_file4.vt3"
		;
connectAttr "ConcreteBarrier01_place2dTexture4.vc1" "ConcreteBarrier01_file4.vc1"
		;
connectAttr "ConcreteBarrier01_place2dTexture4.o" "ConcreteBarrier01_file4.uv";
connectAttr "ConcreteBarrier01_place2dTexture4.ofs" "ConcreteBarrier01_file4.fs"
		;
connectAttr "ConcreteBarrier01_place2dTexture5.c" "ConcreteBarrier01_file5.c";
connectAttr "ConcreteBarrier01_place2dTexture5.tf" "ConcreteBarrier01_file5.tf";
connectAttr "ConcreteBarrier01_place2dTexture5.rf" "ConcreteBarrier01_file5.rf";
connectAttr "ConcreteBarrier01_place2dTexture5.mu" "ConcreteBarrier01_file5.mu";
connectAttr "ConcreteBarrier01_place2dTexture5.mv" "ConcreteBarrier01_file5.mv";
connectAttr "ConcreteBarrier01_place2dTexture5.s" "ConcreteBarrier01_file5.s";
connectAttr "ConcreteBarrier01_place2dTexture5.wu" "ConcreteBarrier01_file5.wu";
connectAttr "ConcreteBarrier01_place2dTexture5.wv" "ConcreteBarrier01_file5.wv";
connectAttr "ConcreteBarrier01_place2dTexture5.re" "ConcreteBarrier01_file5.re";
connectAttr "ConcreteBarrier01_place2dTexture5.of" "ConcreteBarrier01_file5.of";
connectAttr "ConcreteBarrier01_place2dTexture5.r" "ConcreteBarrier01_file5.ro";
connectAttr "ConcreteBarrier01_place2dTexture5.n" "ConcreteBarrier01_file5.n";
connectAttr "ConcreteBarrier01_place2dTexture5.vt1" "ConcreteBarrier01_file5.vt1"
		;
connectAttr "ConcreteBarrier01_place2dTexture5.vt2" "ConcreteBarrier01_file5.vt2"
		;
connectAttr "ConcreteBarrier01_place2dTexture5.vt3" "ConcreteBarrier01_file5.vt3"
		;
connectAttr "ConcreteBarrier01_place2dTexture5.vc1" "ConcreteBarrier01_file5.vc1"
		;
connectAttr "ConcreteBarrier01_place2dTexture5.o" "ConcreteBarrier01_file5.uv";
connectAttr "ConcreteBarrier01_place2dTexture5.ofs" "ConcreteBarrier01_file5.fs"
		;
connectAttr "ConcreteBarrier01_file5.oa" "ConcreteBarrier01_bump2d2.bv";
connectAttr "ConcreteBarrier01_file4.oc" "ConcreteBarrier01_phong2.c";
connectAttr "ConcreteBarrier01_bump2d2.o" "ConcreteBarrier01_phong2.n";
connectAttr "ConcreteBarrier01_file6.oc" "ConcreteBarrier01_phong2.sc";
connectAttr "ConcreteBarrier01_place2dTexture6.c" "ConcreteBarrier01_file6.c";
connectAttr "ConcreteBarrier01_place2dTexture6.tf" "ConcreteBarrier01_file6.tf";
connectAttr "ConcreteBarrier01_place2dTexture6.rf" "ConcreteBarrier01_file6.rf";
connectAttr "ConcreteBarrier01_place2dTexture6.mu" "ConcreteBarrier01_file6.mu";
connectAttr "ConcreteBarrier01_place2dTexture6.mv" "ConcreteBarrier01_file6.mv";
connectAttr "ConcreteBarrier01_place2dTexture6.s" "ConcreteBarrier01_file6.s";
connectAttr "ConcreteBarrier01_place2dTexture6.wu" "ConcreteBarrier01_file6.wu";
connectAttr "ConcreteBarrier01_place2dTexture6.wv" "ConcreteBarrier01_file6.wv";
connectAttr "ConcreteBarrier01_place2dTexture6.re" "ConcreteBarrier01_file6.re";
connectAttr "ConcreteBarrier01_place2dTexture6.of" "ConcreteBarrier01_file6.of";
connectAttr "ConcreteBarrier01_place2dTexture6.r" "ConcreteBarrier01_file6.ro";
connectAttr "ConcreteBarrier01_place2dTexture6.n" "ConcreteBarrier01_file6.n";
connectAttr "ConcreteBarrier01_place2dTexture6.vt1" "ConcreteBarrier01_file6.vt1"
		;
connectAttr "ConcreteBarrier01_place2dTexture6.vt2" "ConcreteBarrier01_file6.vt2"
		;
connectAttr "ConcreteBarrier01_place2dTexture6.vt3" "ConcreteBarrier01_file6.vt3"
		;
connectAttr "ConcreteBarrier01_place2dTexture6.vc1" "ConcreteBarrier01_file6.vc1"
		;
connectAttr "ConcreteBarrier01_place2dTexture6.o" "ConcreteBarrier01_file6.uv";
connectAttr "ConcreteBarrier01_place2dTexture6.ofs" "ConcreteBarrier01_file6.fs"
		;
connectAttr "ConcreteBarrier01_material_3.msg" "ConcreteBarrier01_materialInfo4.sg"
		;
connectAttr "ConcreteBarrier01_material_4.msg" "ConcreteBarrier01_materialInfo5.sg"
		;
connectAttr "ConcreteBarrier01_material_5.msg" "ConcreteBarrier01_materialInfo6.sg"
		;
connectAttr "ConcreteBarrier01_material_6.msg" "ConcreteBarrier01_materialInfo7.sg"
		;
connectAttr "ConcreteBarrier01_material_7.msg" "ConcreteBarrier01_materialInfo8.sg"
		;
connectAttr "ConcreteBarrier01_material_8.msg" "ConcreteBarrier01_materialInfo9.sg"
		;
connectAttr "ConcreteBarrier01_material_9.msg" "ConcreteBarrier01_materialInfo10.sg"
		;
connectAttr "ConcreteBarrier01_material_10.msg" "ConcreteBarrier01_materialInfo11.sg"
		;
connectAttr "ConcreteBarrier01_material_11.msg" "ConcreteBarrier01_materialInfo12.sg"
		;
connectAttr "ConcreteBarrier01_material_12.msg" "ConcreteBarrier01_materialInfo13.sg"
		;
connectAttr "ConcreteBarrier01_material_13.msg" "ConcreteBarrier01_materialInfo14.sg"
		;
connectAttr "ConcreteBarrier01_material_14.msg" "ConcreteBarrier01_materialInfo15.sg"
		;
connectAttr "ConcreteBarrier01_material_15.msg" "ConcreteBarrier01_materialInfo16.sg"
		;
connectAttr "ConcreteBarrier01_material_16.msg" "ConcreteBarrier01_materialInfo17.sg"
		;
connectAttr "ConcreteBarrier01_material_17.msg" "ConcreteBarrier01_materialInfo18.sg"
		;
connectAttr "ConcreteBarrier01_material_18.msg" "ConcreteBarrier01_materialInfo19.sg"
		;
connectAttr "ConcreteBarrier01_material_19.msg" "ConcreteBarrier01_materialInfo20.sg"
		;
connectAttr "ConcreteBarrier01_material_20.msg" "ConcreteBarrier01_materialInfo21.sg"
		;
connectAttr "ConcreteBarrier01_material_21.msg" "ConcreteBarrier01_materialInfo22.sg"
		;
connectAttr "ConcreteBarrier01_material_22.msg" "ConcreteBarrier01_materialInfo23.sg"
		;
connectAttr "ConcreteBarrier01_material_23.msg" "ConcreteBarrier01_materialInfo24.sg"
		;
connectAttr "ConcreteBarrier01_material_24.msg" "ConcreteBarrier01_materialInfo25.sg"
		;
connectAttr "ConcreteBarrier01_material_25.msg" "ConcreteBarrier01_materialInfo26.sg"
		;
connectAttr "ConcreteBarrier01_material_26.msg" "ConcreteBarrier01_materialInfo27.sg"
		;
connectAttr "ConcreteBarrier01_material_27.msg" "ConcreteBarrier01_materialInfo28.sg"
		;
connectAttr "ConcreteBarrier01_material_28.msg" "ConcreteBarrier01_materialInfo29.sg"
		;
connectAttr "ConcreteBarrier01_material_29.msg" "ConcreteBarrier01_materialInfo30.sg"
		;
connectAttr "ConcreteBarrier01_material_30.msg" "ConcreteBarrier01_materialInfo31.sg"
		;
connectAttr "ConcreteBarrier01_material_31.msg" "ConcreteBarrier01_materialInfo32.sg"
		;
connectAttr "ConcreteBarrier01_material_32.msg" "ConcreteBarrier01_materialInfo33.sg"
		;
connectAttr "ConcreteBarrier01_material_33.msg" "ConcreteBarrier01_materialInfo34.sg"
		;
connectAttr "ConcreteBarrier01_material_34.msg" "ConcreteBarrier01_materialInfo35.sg"
		;
connectAttr "ConcreteBarrier01_material_35.msg" "ConcreteBarrier01_materialInfo36.sg"
		;
connectAttr "ConcreteBarrier01_material_36.msg" "ConcreteBarrier01_materialInfo37.sg"
		;
connectAttr "ConcreteBarrier01_material_37.msg" "ConcreteBarrier01_materialInfo38.sg"
		;
connectAttr "ConcreteBarrier01_material_38.msg" "ConcreteBarrier01_materialInfo39.sg"
		;
connectAttr "ConcreteBarrier01_material_39.msg" "ConcreteBarrier01_materialInfo40.sg"
		;
connectAttr "ConcreteBarrier01_material_0_lambert.oc" "ConcreteBarrier01_material_40.ss"
		;
connectAttr "ConcreteBarrier01_material_0_lambert.msg" "ConcreteBarrier01_materialInfo41.m"
		;
connectAttr "ConcreteBarrier01_material_40.msg" "ConcreteBarrier01_materialInfo41.sg"
		;
connectAttr "ConcreteBarrier01_material_0_lambert1.oc" "material_41.ss";
connectAttr "ConcreteBarrier01_material_0_lambert1.msg" "materialInfo42.m";
connectAttr "material_41.msg" "materialInfo42.sg";
connectAttr "ConcreteBarrier01_material_0_lambert2.oc" "material_42.ss";
connectAttr "ConcreteBarrier01_material_0_lambert2.msg" "materialInfo43.m";
connectAttr "material_42.msg" "materialInfo43.sg";
connectAttr "ConcreteBarrier01_material_0_lambert3.oc" "material_43.ss";
connectAttr "ConcreteBarrier01_material_0_lambert3.msg" "materialInfo44.m";
connectAttr "material_43.msg" "materialInfo44.sg";
connectAttr "ConcreteBarrier01_material_0.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[6].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo1.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[7].dn"
		;
connectAttr "ConcreteBarrier01_file1.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[8].dn"
		;
connectAttr "ConcreteBarrier01_place2dTexture1.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[9].dn"
		;
connectAttr "ConcreteBarrier01_file2.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[10].dn"
		;
connectAttr "ConcreteBarrier01_place2dTexture2.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[11].dn"
		;
connectAttr "ConcreteBarrier01_bump2d1.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[12].dn"
		;
connectAttr "ConcreteBarrier01_phong1.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[13].dn"
		;
connectAttr "ConcreteBarrier01_file3.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[14].dn"
		;
connectAttr "ConcreteBarrier01_place2dTexture3.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[15].dn"
		;
connectAttr "ConcreteBarrier01_nodeEditorPanel1Info.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[16].dn"
		;
connectAttr "ConcreteBarrier01_hyperView1.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[17].dn"
		;
connectAttr "ConcreteBarrier01_hyperLayout1.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[18].dn"
		;
connectAttr "ConcreteBarrier01_material_1.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[21].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo2.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[22].dn"
		;
connectAttr "ConcreteBarrier01_material_2.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[23].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo3.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[24].dn"
		;
connectAttr "ConcreteBarrier01_file4.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[25].dn"
		;
connectAttr "ConcreteBarrier01_place2dTexture4.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[26].dn"
		;
connectAttr "ConcreteBarrier01_file5.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[27].dn"
		;
connectAttr "ConcreteBarrier01_place2dTexture5.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[28].dn"
		;
connectAttr "ConcreteBarrier01_bump2d2.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[29].dn"
		;
connectAttr "ConcreteBarrier01_phong2.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[30].dn"
		;
connectAttr "ConcreteBarrier01_file6.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[31].dn"
		;
connectAttr "ConcreteBarrier01_place2dTexture6.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[32].dn"
		;
connectAttr "ConcreteBarrier01_material_3.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[33].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo4.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[34].dn"
		;
connectAttr "ConcreteBarrier01_material_4.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[35].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo5.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[36].dn"
		;
connectAttr "ConcreteBarrier01_material_5.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[37].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo6.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[38].dn"
		;
connectAttr "ConcreteBarrier01_material_6.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[39].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo7.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[40].dn"
		;
connectAttr "ConcreteBarrier01_material_7.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[41].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo8.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[42].dn"
		;
connectAttr "ConcreteBarrier01_material_8.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[43].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo9.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[44].dn"
		;
connectAttr "ConcreteBarrier01_material_9.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[45].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo10.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[46].dn"
		;
connectAttr "ConcreteBarrier01_material_10.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[47].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo11.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[48].dn"
		;
connectAttr "ConcreteBarrier01_material_11.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[49].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo12.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[50].dn"
		;
connectAttr "ConcreteBarrier01_material_12.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[51].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo13.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[52].dn"
		;
connectAttr "ConcreteBarrier01_material_13.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[53].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo14.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[54].dn"
		;
connectAttr "ConcreteBarrier01_material_14.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[55].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo15.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[56].dn"
		;
connectAttr "ConcreteBarrier01_material_15.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[57].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo16.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[58].dn"
		;
connectAttr "ConcreteBarrier01_material_16.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[59].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo17.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[60].dn"
		;
connectAttr "ConcreteBarrier01_material_17.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[61].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo18.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[62].dn"
		;
connectAttr "ConcreteBarrier01_material_18.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[63].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo19.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[64].dn"
		;
connectAttr "ConcreteBarrier01_material_19.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[65].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo20.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[66].dn"
		;
connectAttr "ConcreteBarrier01_material_20.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[67].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo21.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[68].dn"
		;
connectAttr "ConcreteBarrier01_material_21.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[69].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo22.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[70].dn"
		;
connectAttr "ConcreteBarrier01_material_22.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[71].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo23.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[72].dn"
		;
connectAttr "ConcreteBarrier01_material_23.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[73].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo24.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[74].dn"
		;
connectAttr "ConcreteBarrier01_material_24.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[75].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo25.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[76].dn"
		;
connectAttr "ConcreteBarrier01_material_25.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[77].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo26.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[78].dn"
		;
connectAttr "ConcreteBarrier01_material_26.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[79].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo27.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[80].dn"
		;
connectAttr "ConcreteBarrier01_material_27.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[81].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo28.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[82].dn"
		;
connectAttr "ConcreteBarrier01_material_28.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[83].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo29.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[84].dn"
		;
connectAttr "ConcreteBarrier01_material_29.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[85].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo30.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[86].dn"
		;
connectAttr "ConcreteBarrier01_material_30.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[87].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo31.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[88].dn"
		;
connectAttr "ConcreteBarrier01_material_31.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[89].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo32.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[90].dn"
		;
connectAttr "ConcreteBarrier01_material_32.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[91].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo33.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[92].dn"
		;
connectAttr "ConcreteBarrier01_material_33.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[93].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo34.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[94].dn"
		;
connectAttr "ConcreteBarrier01_material_34.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[95].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo35.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[96].dn"
		;
connectAttr "ConcreteBarrier01_material_35.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[97].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo36.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[98].dn"
		;
connectAttr "ConcreteBarrier01_material_36.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[99].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo37.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[100].dn"
		;
connectAttr "ConcreteBarrier01_material_37.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[101].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo38.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[102].dn"
		;
connectAttr "ConcreteBarrier01_material_38.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[103].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo39.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[104].dn"
		;
connectAttr "ConcreteBarrier01_material_39.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[105].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo40.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[106].dn"
		;
connectAttr "ConcreteBarrier01_material_0_lambert.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[107].dn"
		;
connectAttr "ConcreteBarrier01_material_40.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[108].dn"
		;
connectAttr "ConcreteBarrier01_materialInfo41.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[109].dn"
		;
connectAttr "ConcreteBarrier01_material_0_lambert1.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[110].dn"
		;
connectAttr "material_41.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[111].dn";
connectAttr "materialInfo42.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[112].dn"
		;
connectAttr "ConcreteBarrier01_material_0_lambert2.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[113].dn"
		;
connectAttr "material_42.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[114].dn";
connectAttr "materialInfo43.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[115].dn"
		;
connectAttr "ConcreteBarrier01_material_0_lambert3.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[116].dn"
		;
connectAttr "material_43.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[117].dn";
connectAttr "materialInfo44.msg" "AD_ConcreteBarrier01_hyperLayout1.hyp[118].dn"
		;
connectAttr "Bridge_Rail_01_1024_phong1.oc" "Bridge_Rail_01_1024_material_0.ss";
connectAttr "Bridge_Rail_01_1024_phong1.msg" "Bridge_Rail_01_1024_materialInfo1.m"
		;
connectAttr "Bridge_Rail_01_1024_material_0.msg" "Bridge_Rail_01_1024_materialInfo1.sg"
		;
connectAttr "Bridge_Rail_01_1024_file1.msg" "Bridge_Rail_01_1024_materialInfo1.t"
		 -na;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.c" "Bridge_Rail_01_1024_file1.c"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.tf" "Bridge_Rail_01_1024_file1.tf"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.rf" "Bridge_Rail_01_1024_file1.rf"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.mu" "Bridge_Rail_01_1024_file1.mu"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.mv" "Bridge_Rail_01_1024_file1.mv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.s" "Bridge_Rail_01_1024_file1.s"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.wu" "Bridge_Rail_01_1024_file1.wu"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.wv" "Bridge_Rail_01_1024_file1.wv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.re" "Bridge_Rail_01_1024_file1.re"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.of" "Bridge_Rail_01_1024_file1.of"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.r" "Bridge_Rail_01_1024_file1.ro"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.n" "Bridge_Rail_01_1024_file1.n"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.vt1" "Bridge_Rail_01_1024_file1.vt1"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.vt2" "Bridge_Rail_01_1024_file1.vt2"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.vt3" "Bridge_Rail_01_1024_file1.vt3"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.vc1" "Bridge_Rail_01_1024_file1.vc1"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.o" "Bridge_Rail_01_1024_file1.uv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.ofs" "Bridge_Rail_01_1024_file1.fs"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.c" "Bridge_Rail_01_1024_file2.c"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.tf" "Bridge_Rail_01_1024_file2.tf"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.rf" "Bridge_Rail_01_1024_file2.rf"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.mu" "Bridge_Rail_01_1024_file2.mu"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.mv" "Bridge_Rail_01_1024_file2.mv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.s" "Bridge_Rail_01_1024_file2.s"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.wu" "Bridge_Rail_01_1024_file2.wu"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.wv" "Bridge_Rail_01_1024_file2.wv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.re" "Bridge_Rail_01_1024_file2.re"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.of" "Bridge_Rail_01_1024_file2.of"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.r" "Bridge_Rail_01_1024_file2.ro"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.n" "Bridge_Rail_01_1024_file2.n"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.vt1" "Bridge_Rail_01_1024_file2.vt1"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.vt2" "Bridge_Rail_01_1024_file2.vt2"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.vt3" "Bridge_Rail_01_1024_file2.vt3"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.vc1" "Bridge_Rail_01_1024_file2.vc1"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.o" "Bridge_Rail_01_1024_file2.uv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.ofs" "Bridge_Rail_01_1024_file2.fs"
		;
connectAttr "Bridge_Rail_01_1024_file2.oa" "Bridge_Rail_01_1024_bump2d1.bv";
connectAttr "Bridge_Rail_01_1024_file1.oc" "Bridge_Rail_01_1024_phong1.c";
connectAttr "Bridge_Rail_01_1024_bump2d1.o" "Bridge_Rail_01_1024_phong1.n";
connectAttr "Bridge_Rail_01_1024_file3.oc" "Bridge_Rail_01_1024_phong1.sc";
connectAttr "Bridge_Rail_01_1024_place2dTexture3.c" "Bridge_Rail_01_1024_file3.c"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.tf" "Bridge_Rail_01_1024_file3.tf"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.rf" "Bridge_Rail_01_1024_file3.rf"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.mu" "Bridge_Rail_01_1024_file3.mu"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.mv" "Bridge_Rail_01_1024_file3.mv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.s" "Bridge_Rail_01_1024_file3.s"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.wu" "Bridge_Rail_01_1024_file3.wu"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.wv" "Bridge_Rail_01_1024_file3.wv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.re" "Bridge_Rail_01_1024_file3.re"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.of" "Bridge_Rail_01_1024_file3.of"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.r" "Bridge_Rail_01_1024_file3.ro"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.n" "Bridge_Rail_01_1024_file3.n"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.vt1" "Bridge_Rail_01_1024_file3.vt1"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.vt2" "Bridge_Rail_01_1024_file3.vt2"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.vt3" "Bridge_Rail_01_1024_file3.vt3"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.vc1" "Bridge_Rail_01_1024_file3.vc1"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.o" "Bridge_Rail_01_1024_file3.uv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.ofs" "Bridge_Rail_01_1024_file3.fs"
		;
connectAttr "Bridge_Rail_01_1024_hyperView1.msg" "Bridge_Rail_01_1024_nodeEditorPanel1Info.b[0]"
		;
connectAttr "Bridge_Rail_01_1024_hyperLayout1.msg" "Bridge_Rail_01_1024_hyperView1.hl"
		;
connectAttr "Bridge_Rail_01_1024_material_1.msg" "Bridge_Rail_01_1024_materialInfo2.sg"
		;
connectAttr "Bridge_Rail_01_1024_phong2.oc" "Bridge_Rail_01_1024_material_2.ss";
connectAttr "Bridge_Rail_01_1024_phong2.msg" "Bridge_Rail_01_1024_materialInfo3.m"
		;
connectAttr "Bridge_Rail_01_1024_material_2.msg" "Bridge_Rail_01_1024_materialInfo3.sg"
		;
connectAttr "Bridge_Rail_01_1024_file4.msg" "Bridge_Rail_01_1024_materialInfo3.t"
		 -na;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.c" "Bridge_Rail_01_1024_file4.c"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.tf" "Bridge_Rail_01_1024_file4.tf"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.rf" "Bridge_Rail_01_1024_file4.rf"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.mu" "Bridge_Rail_01_1024_file4.mu"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.mv" "Bridge_Rail_01_1024_file4.mv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.s" "Bridge_Rail_01_1024_file4.s"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.wu" "Bridge_Rail_01_1024_file4.wu"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.wv" "Bridge_Rail_01_1024_file4.wv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.re" "Bridge_Rail_01_1024_file4.re"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.of" "Bridge_Rail_01_1024_file4.of"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.r" "Bridge_Rail_01_1024_file4.ro"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.n" "Bridge_Rail_01_1024_file4.n"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.vt1" "Bridge_Rail_01_1024_file4.vt1"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.vt2" "Bridge_Rail_01_1024_file4.vt2"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.vt3" "Bridge_Rail_01_1024_file4.vt3"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.vc1" "Bridge_Rail_01_1024_file4.vc1"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.o" "Bridge_Rail_01_1024_file4.uv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.ofs" "Bridge_Rail_01_1024_file4.fs"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.c" "Bridge_Rail_01_1024_file5.c"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.tf" "Bridge_Rail_01_1024_file5.tf"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.rf" "Bridge_Rail_01_1024_file5.rf"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.mu" "Bridge_Rail_01_1024_file5.mu"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.mv" "Bridge_Rail_01_1024_file5.mv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.s" "Bridge_Rail_01_1024_file5.s"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.wu" "Bridge_Rail_01_1024_file5.wu"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.wv" "Bridge_Rail_01_1024_file5.wv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.re" "Bridge_Rail_01_1024_file5.re"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.of" "Bridge_Rail_01_1024_file5.of"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.r" "Bridge_Rail_01_1024_file5.ro"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.n" "Bridge_Rail_01_1024_file5.n"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.vt1" "Bridge_Rail_01_1024_file5.vt1"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.vt2" "Bridge_Rail_01_1024_file5.vt2"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.vt3" "Bridge_Rail_01_1024_file5.vt3"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.vc1" "Bridge_Rail_01_1024_file5.vc1"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.o" "Bridge_Rail_01_1024_file5.uv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.ofs" "Bridge_Rail_01_1024_file5.fs"
		;
connectAttr "Bridge_Rail_01_1024_file5.oa" "Bridge_Rail_01_1024_bump2d2.bv";
connectAttr "Bridge_Rail_01_1024_file4.oc" "Bridge_Rail_01_1024_phong2.c";
connectAttr "Bridge_Rail_01_1024_bump2d2.o" "Bridge_Rail_01_1024_phong2.n";
connectAttr "Bridge_Rail_01_1024_file6.oc" "Bridge_Rail_01_1024_phong2.sc";
connectAttr "Bridge_Rail_01_1024_place2dTexture6.c" "Bridge_Rail_01_1024_file6.c"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.tf" "Bridge_Rail_01_1024_file6.tf"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.rf" "Bridge_Rail_01_1024_file6.rf"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.mu" "Bridge_Rail_01_1024_file6.mu"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.mv" "Bridge_Rail_01_1024_file6.mv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.s" "Bridge_Rail_01_1024_file6.s"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.wu" "Bridge_Rail_01_1024_file6.wu"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.wv" "Bridge_Rail_01_1024_file6.wv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.re" "Bridge_Rail_01_1024_file6.re"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.of" "Bridge_Rail_01_1024_file6.of"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.r" "Bridge_Rail_01_1024_file6.ro"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.n" "Bridge_Rail_01_1024_file6.n"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.vt1" "Bridge_Rail_01_1024_file6.vt1"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.vt2" "Bridge_Rail_01_1024_file6.vt2"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.vt3" "Bridge_Rail_01_1024_file6.vt3"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.vc1" "Bridge_Rail_01_1024_file6.vc1"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.o" "Bridge_Rail_01_1024_file6.uv"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.ofs" "Bridge_Rail_01_1024_file6.fs"
		;
connectAttr "Bridge_Rail_01_1024_material_3.msg" "Bridge_Rail_01_1024_materialInfo4.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_4.msg" "Bridge_Rail_01_1024_materialInfo5.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_5.msg" "Bridge_Rail_01_1024_materialInfo6.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_6.msg" "Bridge_Rail_01_1024_materialInfo7.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_7.msg" "Bridge_Rail_01_1024_materialInfo8.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_8.msg" "Bridge_Rail_01_1024_materialInfo9.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_9.msg" "Bridge_Rail_01_1024_materialInfo10.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_10.msg" "Bridge_Rail_01_1024_materialInfo11.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_11.msg" "Bridge_Rail_01_1024_materialInfo12.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_12.msg" "Bridge_Rail_01_1024_materialInfo13.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_13.msg" "Bridge_Rail_01_1024_materialInfo14.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_14.msg" "Bridge_Rail_01_1024_materialInfo15.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_15.msg" "Bridge_Rail_01_1024_materialInfo16.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_16.msg" "Bridge_Rail_01_1024_materialInfo17.sg"
		;
connectAttr "Bridge_Rail_01_1024_material_0.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[6].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo1.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[7].dn"
		;
connectAttr "Bridge_Rail_01_1024_file1.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[8].dn"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[9].dn"
		;
connectAttr "Bridge_Rail_01_1024_file2.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[10].dn"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[11].dn"
		;
connectAttr "Bridge_Rail_01_1024_bump2d1.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[12].dn"
		;
connectAttr "Bridge_Rail_01_1024_phong1.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[13].dn"
		;
connectAttr "Bridge_Rail_01_1024_file3.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[14].dn"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[15].dn"
		;
connectAttr "Bridge_Rail_01_1024_nodeEditorPanel1Info.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[16].dn"
		;
connectAttr "Bridge_Rail_01_1024_hyperView1.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[17].dn"
		;
connectAttr "Bridge_Rail_01_1024_hyperLayout1.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[18].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_1.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[21].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo2.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[22].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_2.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[23].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo3.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[24].dn"
		;
connectAttr "Bridge_Rail_01_1024_file4.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[25].dn"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[26].dn"
		;
connectAttr "Bridge_Rail_01_1024_file5.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[27].dn"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[28].dn"
		;
connectAttr "Bridge_Rail_01_1024_bump2d2.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[29].dn"
		;
connectAttr "Bridge_Rail_01_1024_phong2.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[30].dn"
		;
connectAttr "Bridge_Rail_01_1024_file6.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[31].dn"
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[32].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_3.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[33].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo4.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[34].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_4.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[35].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo5.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[36].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_5.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[37].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo6.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[38].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_6.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[39].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo7.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[40].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_7.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[41].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo8.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[42].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_8.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[43].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo9.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[44].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_9.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[45].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo10.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[46].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_10.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[47].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo11.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[48].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_11.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[49].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo12.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[50].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_12.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[51].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo13.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[52].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_13.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[53].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo14.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[54].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_14.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[55].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo15.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[56].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_15.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[57].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo16.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[58].dn"
		;
connectAttr "Bridge_Rail_01_1024_material_16.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[59].dn"
		;
connectAttr "Bridge_Rail_01_1024_materialInfo17.msg" "AD_Bridge_Rail_01_1024_hyperLayout1.hyp[60].dn"
		;
connectAttr "Gotham_GCPD_Window1024_file1.oc" "Gotham_GCPD_Window1024_material_0_lambert.c"
		;
connectAttr "Gotham_GCPD_Window1024_bump2d1.o" "Gotham_GCPD_Window1024_material_0_lambert.n"
		;
connectAttr "Gotham_GCPD_Window1024_material_0_lambert.oc" "Gotham_GCPD_Window1024_material_0.ss"
		;
connectAttr "Gotham_GCPD_Window1024_material_0_lambert.msg" "Gotham_GCPD_Window1024_materialInfo1.m"
		;
connectAttr "Gotham_GCPD_Window1024_material_0.msg" "Gotham_GCPD_Window1024_materialInfo1.sg"
		;
connectAttr "Gotham_GCPD_Window1024_file1.msg" "Gotham_GCPD_Window1024_materialInfo1.t"
		 -na;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.c" "Gotham_GCPD_Window1024_file1.c"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.tf" "Gotham_GCPD_Window1024_file1.tf"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.rf" "Gotham_GCPD_Window1024_file1.rf"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.mu" "Gotham_GCPD_Window1024_file1.mu"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.mv" "Gotham_GCPD_Window1024_file1.mv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.s" "Gotham_GCPD_Window1024_file1.s"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.wu" "Gotham_GCPD_Window1024_file1.wu"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.wv" "Gotham_GCPD_Window1024_file1.wv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.re" "Gotham_GCPD_Window1024_file1.re"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.of" "Gotham_GCPD_Window1024_file1.of"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.r" "Gotham_GCPD_Window1024_file1.ro"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.n" "Gotham_GCPD_Window1024_file1.n"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.vt1" "Gotham_GCPD_Window1024_file1.vt1"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.vt2" "Gotham_GCPD_Window1024_file1.vt2"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.vt3" "Gotham_GCPD_Window1024_file1.vt3"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.vc1" "Gotham_GCPD_Window1024_file1.vc1"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.o" "Gotham_GCPD_Window1024_file1.uv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.ofs" "Gotham_GCPD_Window1024_file1.fs"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.c" "Gotham_GCPD_Window1024_file2.c"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.tf" "Gotham_GCPD_Window1024_file2.tf"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.rf" "Gotham_GCPD_Window1024_file2.rf"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.mu" "Gotham_GCPD_Window1024_file2.mu"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.mv" "Gotham_GCPD_Window1024_file2.mv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.s" "Gotham_GCPD_Window1024_file2.s"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.wu" "Gotham_GCPD_Window1024_file2.wu"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.wv" "Gotham_GCPD_Window1024_file2.wv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.re" "Gotham_GCPD_Window1024_file2.re"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.of" "Gotham_GCPD_Window1024_file2.of"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.r" "Gotham_GCPD_Window1024_file2.ro"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.n" "Gotham_GCPD_Window1024_file2.n"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.vt1" "Gotham_GCPD_Window1024_file2.vt1"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.vt2" "Gotham_GCPD_Window1024_file2.vt2"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.vt3" "Gotham_GCPD_Window1024_file2.vt3"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.vc1" "Gotham_GCPD_Window1024_file2.vc1"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.o" "Gotham_GCPD_Window1024_file2.uv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.ofs" "Gotham_GCPD_Window1024_file2.fs"
		;
connectAttr "Gotham_GCPD_Window1024_file2.oa" "Gotham_GCPD_Window1024_bump2d1.bv"
		;
connectAttr "Gotham_GCPD_Window1024_hyperView1.msg" "Gotham_GCPD_Window1024_nodeEditorPanel1Info.b[0]"
		;
connectAttr "Gotham_GCPD_Window1024_hyperLayout1.msg" "Gotham_GCPD_Window1024_hyperView1.hl"
		;
connectAttr "Gotham_GCPD_Window1024_phong1.oc" "Gotham_GCPD_Window1024_material_1.ss"
		;
connectAttr "Gotham_GCPD_Window1024_phong1.msg" "Gotham_GCPD_Window1024_materialInfo2.m"
		;
connectAttr "Gotham_GCPD_Window1024_material_1.msg" "Gotham_GCPD_Window1024_materialInfo2.sg"
		;
connectAttr "Gotham_GCPD_Window1024_file3.msg" "Gotham_GCPD_Window1024_materialInfo2.t"
		 -na;
connectAttr "Gotham_GCPD_Window1024_material_2.msg" "Gotham_GCPD_Window1024_materialInfo3.sg"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.c" "Gotham_GCPD_Window1024_file3.c"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.tf" "Gotham_GCPD_Window1024_file3.tf"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.rf" "Gotham_GCPD_Window1024_file3.rf"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.mu" "Gotham_GCPD_Window1024_file3.mu"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.mv" "Gotham_GCPD_Window1024_file3.mv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.s" "Gotham_GCPD_Window1024_file3.s"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.wu" "Gotham_GCPD_Window1024_file3.wu"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.wv" "Gotham_GCPD_Window1024_file3.wv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.re" "Gotham_GCPD_Window1024_file3.re"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.of" "Gotham_GCPD_Window1024_file3.of"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.r" "Gotham_GCPD_Window1024_file3.ro"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.n" "Gotham_GCPD_Window1024_file3.n"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.vt1" "Gotham_GCPD_Window1024_file3.vt1"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.vt2" "Gotham_GCPD_Window1024_file3.vt2"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.vt3" "Gotham_GCPD_Window1024_file3.vt3"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.vc1" "Gotham_GCPD_Window1024_file3.vc1"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.o" "Gotham_GCPD_Window1024_file3.uv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.ofs" "Gotham_GCPD_Window1024_file3.fs"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.c" "Gotham_GCPD_Window1024_file4.c"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.tf" "Gotham_GCPD_Window1024_file4.tf"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.rf" "Gotham_GCPD_Window1024_file4.rf"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.mu" "Gotham_GCPD_Window1024_file4.mu"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.mv" "Gotham_GCPD_Window1024_file4.mv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.s" "Gotham_GCPD_Window1024_file4.s"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.wu" "Gotham_GCPD_Window1024_file4.wu"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.wv" "Gotham_GCPD_Window1024_file4.wv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.re" "Gotham_GCPD_Window1024_file4.re"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.of" "Gotham_GCPD_Window1024_file4.of"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.r" "Gotham_GCPD_Window1024_file4.ro"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.n" "Gotham_GCPD_Window1024_file4.n"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.vt1" "Gotham_GCPD_Window1024_file4.vt1"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.vt2" "Gotham_GCPD_Window1024_file4.vt2"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.vt3" "Gotham_GCPD_Window1024_file4.vt3"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.vc1" "Gotham_GCPD_Window1024_file4.vc1"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.o" "Gotham_GCPD_Window1024_file4.uv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.ofs" "Gotham_GCPD_Window1024_file4.fs"
		;
connectAttr "Gotham_GCPD_Window1024_file4.oa" "Gotham_GCPD_Window1024_bump2d2.bv"
		;
connectAttr "Gotham_GCPD_Window1024_file3.oc" "Gotham_GCPD_Window1024_phong1.c";
connectAttr "Gotham_GCPD_Window1024_bump2d2.o" "Gotham_GCPD_Window1024_phong1.n"
		;
connectAttr "Gotham_GCPD_Window1024_file5.oc" "Gotham_GCPD_Window1024_phong1.sc"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.c" "Gotham_GCPD_Window1024_file5.c"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.tf" "Gotham_GCPD_Window1024_file5.tf"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.rf" "Gotham_GCPD_Window1024_file5.rf"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.mu" "Gotham_GCPD_Window1024_file5.mu"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.mv" "Gotham_GCPD_Window1024_file5.mv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.s" "Gotham_GCPD_Window1024_file5.s"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.wu" "Gotham_GCPD_Window1024_file5.wu"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.wv" "Gotham_GCPD_Window1024_file5.wv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.re" "Gotham_GCPD_Window1024_file5.re"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.of" "Gotham_GCPD_Window1024_file5.of"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.r" "Gotham_GCPD_Window1024_file5.ro"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.n" "Gotham_GCPD_Window1024_file5.n"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.vt1" "Gotham_GCPD_Window1024_file5.vt1"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.vt2" "Gotham_GCPD_Window1024_file5.vt2"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.vt3" "Gotham_GCPD_Window1024_file5.vt3"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.vc1" "Gotham_GCPD_Window1024_file5.vc1"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.o" "Gotham_GCPD_Window1024_file5.uv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.ofs" "Gotham_GCPD_Window1024_file5.fs"
		;
connectAttr "Gotham_GCPD_Window1024_material_3.msg" "Gotham_GCPD_Window1024_materialInfo4.sg"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.c" "Gotham_GCPD_Window1024_file6.c"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.tf" "Gotham_GCPD_Window1024_file6.tf"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.rf" "Gotham_GCPD_Window1024_file6.rf"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.mu" "Gotham_GCPD_Window1024_file6.mu"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.mv" "Gotham_GCPD_Window1024_file6.mv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.s" "Gotham_GCPD_Window1024_file6.s"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.wu" "Gotham_GCPD_Window1024_file6.wu"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.wv" "Gotham_GCPD_Window1024_file6.wv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.re" "Gotham_GCPD_Window1024_file6.re"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.of" "Gotham_GCPD_Window1024_file6.of"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.r" "Gotham_GCPD_Window1024_file6.ro"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.n" "Gotham_GCPD_Window1024_file6.n"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.vt1" "Gotham_GCPD_Window1024_file6.vt1"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.vt2" "Gotham_GCPD_Window1024_file6.vt2"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.vt3" "Gotham_GCPD_Window1024_file6.vt3"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.vc1" "Gotham_GCPD_Window1024_file6.vc1"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.o" "Gotham_GCPD_Window1024_file6.uv"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.ofs" "Gotham_GCPD_Window1024_file6.fs"
		;
connectAttr "Gotham_GCPD_Window1024_material_4.msg" "Gotham_GCPD_Window1024_materialInfo5.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_5.msg" "Gotham_GCPD_Window1024_materialInfo6.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_6.msg" "Gotham_GCPD_Window1024_materialInfo7.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_7.msg" "Gotham_GCPD_Window1024_materialInfo8.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_8.msg" "Gotham_GCPD_Window1024_materialInfo9.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_9.msg" "Gotham_GCPD_Window1024_materialInfo10.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_10.msg" "Gotham_GCPD_Window1024_materialInfo11.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_11.msg" "Gotham_GCPD_Window1024_materialInfo12.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_12.msg" "Gotham_GCPD_Window1024_materialInfo13.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_13.msg" "Gotham_GCPD_Window1024_materialInfo14.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_14.msg" "Gotham_GCPD_Window1024_materialInfo15.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_15.msg" "Gotham_GCPD_Window1024_materialInfo16.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_16.msg" "Gotham_GCPD_Window1024_materialInfo17.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_17.msg" "Gotham_GCPD_Window1024_materialInfo18.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_18.msg" "Gotham_GCPD_Window1024_materialInfo19.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_19.msg" "Gotham_GCPD_Window1024_materialInfo20.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_20.msg" "Gotham_GCPD_Window1024_materialInfo21.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_21.msg" "Gotham_GCPD_Window1024_materialInfo22.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_22.msg" "Gotham_GCPD_Window1024_materialInfo23.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_23.msg" "Gotham_GCPD_Window1024_materialInfo24.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_24.msg" "Gotham_GCPD_Window1024_materialInfo25.sg"
		;
connectAttr "Gotham_GCPD_Window1024_material_0_lambert.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[6].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_0.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[7].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo1.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[8].dn"
		;
connectAttr "Gotham_GCPD_Window1024_file1.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[9].dn"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[10].dn"
		;
connectAttr "Gotham_GCPD_Window1024_file2.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[11].dn"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[12].dn"
		;
connectAttr "Gotham_GCPD_Window1024_bump2d1.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[13].dn"
		;
connectAttr "Gotham_GCPD_Window1024_nodeEditorPanel1Info.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[14].dn"
		;
connectAttr "Gotham_GCPD_Window1024_hyperView1.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[15].dn"
		;
connectAttr "Gotham_GCPD_Window1024_hyperLayout1.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[16].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_1.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[19].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo2.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[20].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_2.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[21].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo3.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[22].dn"
		;
connectAttr "Gotham_GCPD_Window1024_file3.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[23].dn"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[24].dn"
		;
connectAttr "Gotham_GCPD_Window1024_file4.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[25].dn"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[26].dn"
		;
connectAttr "Gotham_GCPD_Window1024_bump2d2.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[27].dn"
		;
connectAttr "Gotham_GCPD_Window1024_phong1.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[28].dn"
		;
connectAttr "Gotham_GCPD_Window1024_file5.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[29].dn"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[30].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_3.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[31].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo4.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[32].dn"
		;
connectAttr "Gotham_GCPD_Window1024_file6.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[33].dn"
		;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[34].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_4.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[35].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo5.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[36].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_5.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[37].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo6.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[38].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_6.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[39].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo7.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[40].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_7.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[41].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo8.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[42].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_8.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[43].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo9.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[44].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_9.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[45].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo10.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[46].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_10.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[47].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo11.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[48].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_11.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[49].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo12.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[50].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_12.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[51].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo13.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[52].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_13.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[53].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo14.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[54].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_14.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[55].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo15.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[56].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_15.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[57].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo16.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[58].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_16.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[59].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo17.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[60].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_17.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[61].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo18.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[62].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_18.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[63].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo19.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[64].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_19.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[65].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo20.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[66].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_20.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[67].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo21.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[68].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_21.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[69].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo22.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[70].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_22.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[71].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo23.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[72].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_23.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[73].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo24.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[74].dn"
		;
connectAttr "Gotham_GCPD_Window1024_material_24.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[75].dn"
		;
connectAttr "Gotham_GCPD_Window1024_materialInfo25.msg" "AD_Gotham_GCPD_Window1024_hyperLayout1.hyp[76].dn"
		;
connectAttr "surfaceShader1.oc" "blinn2SG.ss";
connectAttr "SkyDomeShape.iog" "blinn2SG.dsm" -na;
connectAttr "blinn2SG.msg" "materialInfo45.sg";
connectAttr "surfaceShader1.msg" "materialInfo45.m";
connectAttr "SkyFile.msg" "materialInfo45.t" -na;
connectAttr "SkyFile.oc" "materialInfo45.tc";
connectAttr "place2dTexture12.c" "SkyFile.c";
connectAttr "place2dTexture12.tf" "SkyFile.tf";
connectAttr "place2dTexture12.rf" "SkyFile.rf";
connectAttr "place2dTexture12.mu" "SkyFile.mu";
connectAttr "place2dTexture12.mv" "SkyFile.mv";
connectAttr "place2dTexture12.s" "SkyFile.s";
connectAttr "place2dTexture12.wu" "SkyFile.wu";
connectAttr "place2dTexture12.wv" "SkyFile.wv";
connectAttr "place2dTexture12.re" "SkyFile.re";
connectAttr "place2dTexture12.of" "SkyFile.of";
connectAttr "place2dTexture12.r" "SkyFile.ro";
connectAttr "place2dTexture12.n" "SkyFile.n";
connectAttr "place2dTexture12.vt1" "SkyFile.vt1";
connectAttr "place2dTexture12.vt2" "SkyFile.vt2";
connectAttr "place2dTexture12.vt3" "SkyFile.vt3";
connectAttr "place2dTexture12.vc1" "SkyFile.vc1";
connectAttr "place2dTexture12.o" "SkyFile.uv";
connectAttr "place2dTexture12.ofs" "SkyFile.fs";
connectAttr "SkyFile.oc" "surfaceShader1.oc";
connectAttr "surfaceShader1_materialAlphaGain.o" "surfaceShader1.maga";
connectAttr "polySphere1.out" "polyNormal1.ip";
connectAttr "layerManager.dli[1]" "sky.id";
connectAttr "layerManager.dli[2]" "layer1.id";
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_0.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_1.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_2.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_3.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_4.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_material_5.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_blinn1SG.pa" ":renderPartition.st"
		 -na;
connectAttr "material_6.pa" ":renderPartition.st" -na;
connectAttr "material_7.pa" ":renderPartition.st" -na;
connectAttr "material_8.pa" ":renderPartition.st" -na;
connectAttr "material_9.pa" ":renderPartition.st" -na;
connectAttr "material_10.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_0.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_1.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_2.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_3.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_4.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_material_5.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_blinn1SG.pa" ":renderPartition.st" -na
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_0.pa" ":renderPartition.st"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_1.pa" ":renderPartition.st"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_2.pa" ":renderPartition.st"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_3.pa" ":renderPartition.st"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_4.pa" ":renderPartition.st"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_5.pa" ":renderPartition.st"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1SG.pa" ":renderPartition.st"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_6.pa" ":renderPartition.st"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_7.pa" ":renderPartition.st"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_8.pa" ":renderPartition.st"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_9.pa" ":renderPartition.st"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_material_10.pa" ":renderPartition.st"
		 -na;
connectAttr "material_11.pa" ":renderPartition.st" -na;
connectAttr "material_12.pa" ":renderPartition.st" -na;
connectAttr "material_13.pa" ":renderPartition.st" -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_0.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_1.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_2.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_3.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_4.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_5.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_6.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_7.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_8.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_9.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_10.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_11.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_12.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_material_13.pa" ":renderPartition.st" 
		-na;
connectAttr "material_14.pa" ":renderPartition.st" -na;
connectAttr "material_15.pa" ":renderPartition.st" -na;
connectAttr "material_16.pa" ":renderPartition.st" -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_0.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_1.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_2.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_3.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_4.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_5.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_6.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_7.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_8.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_9.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_10.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_11.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_12.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_13.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_14.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_15.pa" ":renderPartition.st"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_16.pa" ":renderPartition.st"
		 -na;
connectAttr "material_17.pa" ":renderPartition.st" -na;
connectAttr "material_18.pa" ":renderPartition.st" -na;
connectAttr "material_19.pa" ":renderPartition.st" -na;
connectAttr "material_20.pa" ":renderPartition.st" -na;
connectAttr "material_21.pa" ":renderPartition.st" -na;
connectAttr "material_22.pa" ":renderPartition.st" -na;
connectAttr "material_23.pa" ":renderPartition.st" -na;
connectAttr "material_24.pa" ":renderPartition.st" -na;
connectAttr "material_25.pa" ":renderPartition.st" -na;
connectAttr "material_26.pa" ":renderPartition.st" -na;
connectAttr "material_27.pa" ":renderPartition.st" -na;
connectAttr "material_28.pa" ":renderPartition.st" -na;
connectAttr "material_29.pa" ":renderPartition.st" -na;
connectAttr "material_30.pa" ":renderPartition.st" -na;
connectAttr "material_31.pa" ":renderPartition.st" -na;
connectAttr "material_32.pa" ":renderPartition.st" -na;
connectAttr "material_33.pa" ":renderPartition.st" -na;
connectAttr "material_34.pa" ":renderPartition.st" -na;
connectAttr "material_35.pa" ":renderPartition.st" -na;
connectAttr "material_36.pa" ":renderPartition.st" -na;
connectAttr "material_37.pa" ":renderPartition.st" -na;
connectAttr "material_38.pa" ":renderPartition.st" -na;
connectAttr "material_39.pa" ":renderPartition.st" -na;
connectAttr "material_40.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_0.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_1.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_2.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_3.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_4.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_5.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_6.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_7.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_8.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_9.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_10.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_11.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_blinn1SG.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_12.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_13.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_14.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_Mall768_material_15.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_PoleSolid_128C_material_0.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_1.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_2.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_3.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_4.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_5.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_6.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_7.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_8.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_9.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_10.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Fences_PoleSolid_128C_material_11.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Fences_PoleSolid_128C_blinn1SG.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_12.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Fences_PoleSolid_128C_material_13.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Fences_PoleSolid_128C_material_14.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Fences_PoleSolid_128C_material_15.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Fences_PoleSolid_128C_material_16.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Fences_PoleSolid_128C_material_17.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Fences_PoleSolid_128C_material_18.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Fences_PoleSolid_128C_material_19.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Fences_PoleSolid_128C_material_20.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Fences_PoleSolid_128C_material_21.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Fences_PoleSolid_512_material_0.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_1.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_2.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_3.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_4.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_5.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_6.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_7.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_8.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_9.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_10.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_11.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_blinn1SG.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Fences_PoleSolid_512_material_12.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_13.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_14.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_15.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_16.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_17.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_18.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_19.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_20.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_21.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_22.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_23.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_24.pa" ":renderPartition.st" -na
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_0.pa" ":renderPartition.st" -na;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_1.pa" ":renderPartition.st" -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_0.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_1.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_2.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_3.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_4.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_5.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_6.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_7.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_8.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_9.pa" ":renderPartition.st" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_10.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_11.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_12.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_13.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_14.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_15.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_16.pa" ":renderPartition.st" 
		-na;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_17.pa" ":renderPartition.st" 
		-na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_1.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_2.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_3.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_4.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_5.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_6.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_7.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_8.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_9.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_10.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_11.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_12.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_13.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_14.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_15.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_16.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_17.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_18.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_19.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_20.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_21.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_22.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_23.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_24.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_25.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_26.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_27.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_28.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_29.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_30.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_31.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_32.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_33.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_34.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_35.pa" ":renderPartition.st"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_36.pa" ":renderPartition.st"
		 -na;
connectAttr "ConcreteBarrier01_material_0.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_1.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_2.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_3.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_4.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_5.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_6.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_7.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_8.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_9.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_10.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_11.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_12.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_13.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_14.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_15.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_16.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_17.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_18.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_19.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_20.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_21.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_22.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_23.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_24.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_25.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_26.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_27.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_28.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_29.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_30.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_31.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_32.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_33.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_34.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_35.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_36.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_37.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_38.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_39.pa" ":renderPartition.st" -na;
connectAttr "ConcreteBarrier01_material_40.pa" ":renderPartition.st" -na;
connectAttr "material_41.pa" ":renderPartition.st" -na;
connectAttr "material_42.pa" ":renderPartition.st" -na;
connectAttr "material_43.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_0.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_1.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_2.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_3.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_4.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_5.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_6.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_7.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_8.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_9.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_10.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_11.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_12.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_13.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_14.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_15.pa" ":renderPartition.st" -na;
connectAttr "Bridge_Rail_01_1024_material_16.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_0.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_1.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_2.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_3.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_4.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_5.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_6.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_7.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_8.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_9.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_10.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_11.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_12.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_13.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_14.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_15.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_16.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_17.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_18.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_19.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_20.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_21.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_22.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_23.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GCPD_Window1024_material_24.pa" ":renderPartition.st" -na;
connectAttr "blinn2SG.pa" ":renderPartition.st" -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_phong1.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_phong2.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_blinn1.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "material_0_lambert.msg" ":defaultShaderList1.s" -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_phong1.msg" ":defaultShaderList1.s" -na
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_phong2.msg" ":defaultShaderList1.s" -na
		;
connectAttr "Gotham_Groundfloor_Shop_OldB2_blinn1.msg" ":defaultShaderList1.s" -na
		;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_phong1.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_phong2.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_blinn1.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_phong1.msg" ":defaultShaderList1.s" -na
		;
connectAttr "material_0_lambert2.msg" ":defaultShaderList1.s" -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_blinn1.msg" ":defaultShaderList1.s" -na
		;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_0_lambert.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_phong1.msg" ":defaultShaderList1.s" 
		-na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_material_0_lambert2.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_blinn1.msg" ":defaultShaderList1.s" 
		-na;
connectAttr "Gotham_Fences_Mall768_phong1.msg" ":defaultShaderList1.s" -na;
connectAttr "Gotham_Fences_Mall768_material_0_lambert.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "Gotham_Fences_Mall768_blinn1.msg" ":defaultShaderList1.s" -na;
connectAttr "Gotham_Fences_PoleSolid_128C_phong1.msg" ":defaultShaderList1.s" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_material_0_lambert.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_128C_blinn1.msg" ":defaultShaderList1.s" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_phong1.msg" ":defaultShaderList1.s" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_material_0_lambert.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_512_material_0_lambert1.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_512_blinn1.msg" ":defaultShaderList1.s" -na
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_0_lambert.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "ARCH_GCPD_EntranceRoof_04_material_0_lambert1.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_0_lambert.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_phong1.msg" ":defaultShaderList1.s" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_material_0_lambert2.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_blinn1.msg" ":defaultShaderList1.s" -na
		;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_phong1.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_phong2.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert1.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_material_0_lambert2.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "material_0_lambert3.msg" ":defaultShaderList1.s" -na;
connectAttr "material_0_lambert4.msg" ":defaultShaderList1.s" -na;
connectAttr "ConcreteBarrier01_phong1.msg" ":defaultShaderList1.s" -na;
connectAttr "ConcreteBarrier01_material_0_lambert.msg" ":defaultShaderList1.s" -na
		;
connectAttr "ConcreteBarrier01_phong2.msg" ":defaultShaderList1.s" -na;
connectAttr "ConcreteBarrier01_material_0_lambert1.msg" ":defaultShaderList1.s" 
		-na;
connectAttr "ConcreteBarrier01_material_0_lambert2.msg" ":defaultShaderList1.s" 
		-na;
connectAttr "ConcreteBarrier01_material_0_lambert3.msg" ":defaultShaderList1.s" 
		-na;
connectAttr "Bridge_Rail_01_1024_phong1.msg" ":defaultShaderList1.s" -na;
connectAttr "Bridge_Rail_01_1024_phong2.msg" ":defaultShaderList1.s" -na;
connectAttr "Gotham_GCPD_Window1024_material_0_lambert.msg" ":defaultShaderList1.s"
		 -na;
connectAttr "Gotham_GCPD_Window1024_phong1.msg" ":defaultShaderList1.s" -na;
connectAttr "surfaceShader1.msg" ":defaultShaderList1.s" -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_bump2d1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture5.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_bump2d2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture6.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_place2dTexture7.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "place2dTexture8.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "bump2d3.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_bump2d1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture5.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_bump2d2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture6.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture7.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_place2dTexture8.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_bump2d3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture5.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture6.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture7.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_place2dTexture8.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_bump2d3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_bump2d1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture5.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_bump2d2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture6.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture7.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_bump2d3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_place2dTexture8.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "place2dTexture9.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "bump2d4.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture10.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture11.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_bump2d1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture5.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_bump2d2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture6.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture7.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_bump2d3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture8.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture9.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_bump2d4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture10.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_place2dTexture11.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_Mall768_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_Mall768_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_Mall768_place2dTexture3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_Mall768_bump2d1.msg" ":defaultRenderUtilityList1.u" -na
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_Mall768_place2dTexture5.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_Mall768_place2dTexture6.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_Mall768_bump2d2.msg" ":defaultRenderUtilityList1.u" -na
		;
connectAttr "Gotham_Fences_Mall768_place2dTexture7.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_128C_bump2d1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture5.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture6.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_128C_bump2d2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_128C_place2dTexture7.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_512_bump2d1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture5.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture6.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_512_bump2d2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Fences_PoleSolid_512_place2dTexture7.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "ARCH_GCPD_EntranceRoof_04_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "ARCH_GCPD_EntranceRoof_04_bump2d1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_bump2d1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture5.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_bump2d2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture6.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture7.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_bump2d3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture8.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture9.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_bump2d4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture10.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_place2dTexture11.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_bump2d1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture5.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_bump2d2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_place2dTexture6.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "ConcreteBarrier01_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "ConcreteBarrier01_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "ConcreteBarrier01_bump2d1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "ConcreteBarrier01_place2dTexture3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "ConcreteBarrier01_place2dTexture4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "ConcreteBarrier01_place2dTexture5.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "ConcreteBarrier01_bump2d2.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "ConcreteBarrier01_place2dTexture6.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Bridge_Rail_01_1024_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Bridge_Rail_01_1024_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Bridge_Rail_01_1024_bump2d1.msg" ":defaultRenderUtilityList1.u" -na
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Bridge_Rail_01_1024_place2dTexture4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Bridge_Rail_01_1024_place2dTexture5.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Bridge_Rail_01_1024_bump2d2.msg" ":defaultRenderUtilityList1.u" -na
		;
connectAttr "Bridge_Rail_01_1024_place2dTexture6.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GCPD_Window1024_place2dTexture1.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GCPD_Window1024_place2dTexture2.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GCPD_Window1024_bump2d1.msg" ":defaultRenderUtilityList1.u" 
		-na;
connectAttr "Gotham_GCPD_Window1024_place2dTexture3.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GCPD_Window1024_place2dTexture4.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GCPD_Window1024_bump2d2.msg" ":defaultRenderUtilityList1.u" 
		-na;
connectAttr "Gotham_GCPD_Window1024_place2dTexture5.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "Gotham_GCPD_Window1024_place2dTexture6.msg" ":defaultRenderUtilityList1.u"
		 -na;
connectAttr "place2dTexture12.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "sun_lightShape.ltd" ":lightList1.l" -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file1.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file2.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file3.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file4.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file5.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file6.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_GroundFloor_Shop_OlddB5_512_file7.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "file8.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file1.msg" ":defaultTextureList1.tx" 
		-na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file2.msg" ":defaultTextureList1.tx" 
		-na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file3.msg" ":defaultTextureList1.tx" 
		-na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file4.msg" ":defaultTextureList1.tx" 
		-na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file5.msg" ":defaultTextureList1.tx" 
		-na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file6.msg" ":defaultTextureList1.tx" 
		-na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file7.msg" ":defaultTextureList1.tx" 
		-na;
connectAttr "Gotham_Groundfloor_Shop_OldB2_file8.msg" ":defaultTextureList1.tx" 
		-na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file1.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file2.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file3.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file4.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file5.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file6.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file7.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "OZ_Gotham_GroundFloor_Shop_OldA_03_file8.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file1.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file2.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file3.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file4.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file5.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file6.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file7.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_ARCH_Classic_BigWinx2_file8.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "file9.msg" ":defaultTextureList1.tx" -na;
connectAttr "file10.msg" ":defaultTextureList1.tx" -na;
connectAttr "file11.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file1.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file2.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file3.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file4.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file5.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file6.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file7.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file8.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file9.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file10.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_ARCH_Classic_WinBCorner_file11.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "Gotham_Fences_Mall768_file1.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_Fences_Mall768_file2.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_Fences_Mall768_file3.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_Fences_Mall768_file4.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_Fences_Mall768_file5.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_Fences_Mall768_file6.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_Fences_Mall768_file7.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_Fences_PoleSolid_128C_file1.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file2.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file3.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file4.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file5.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file6.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Fences_PoleSolid_128C_file7.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_file1.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_file2.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_file3.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_file4.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_file5.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_file6.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Fences_PoleSolid_512_file7.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "ARCH_GCPD_EntranceRoof_04_file1.msg" ":defaultTextureList1.tx" -na;
connectAttr "ARCH_GCPD_EntranceRoof_04_file2.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_Arch_Classic_BigWiny2_file1.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file2.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file3.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file4.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file5.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file6.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file7.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file8.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file9.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "Gotham_Arch_Classic_BigWiny2_file10.msg" ":defaultTextureList1.tx" 
		-na;
connectAttr "Gotham_Arch_Classic_BigWiny2_file11.msg" ":defaultTextureList1.tx" 
		-na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file1.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file2.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file3.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file4.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file5.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "BridgeRoad_Destroyed_2048_Custom_02_file6.msg" ":defaultTextureList1.tx"
		 -na;
connectAttr "ConcreteBarrier01_file1.msg" ":defaultTextureList1.tx" -na;
connectAttr "ConcreteBarrier01_file2.msg" ":defaultTextureList1.tx" -na;
connectAttr "ConcreteBarrier01_file3.msg" ":defaultTextureList1.tx" -na;
connectAttr "ConcreteBarrier01_file4.msg" ":defaultTextureList1.tx" -na;
connectAttr "ConcreteBarrier01_file5.msg" ":defaultTextureList1.tx" -na;
connectAttr "ConcreteBarrier01_file6.msg" ":defaultTextureList1.tx" -na;
connectAttr "Bridge_Rail_01_1024_file1.msg" ":defaultTextureList1.tx" -na;
connectAttr "Bridge_Rail_01_1024_file2.msg" ":defaultTextureList1.tx" -na;
connectAttr "Bridge_Rail_01_1024_file3.msg" ":defaultTextureList1.tx" -na;
connectAttr "Bridge_Rail_01_1024_file4.msg" ":defaultTextureList1.tx" -na;
connectAttr "Bridge_Rail_01_1024_file5.msg" ":defaultTextureList1.tx" -na;
connectAttr "Bridge_Rail_01_1024_file6.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_GCPD_Window1024_file1.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_GCPD_Window1024_file2.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_GCPD_Window1024_file3.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_GCPD_Window1024_file4.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_GCPD_Window1024_file5.msg" ":defaultTextureList1.tx" -na;
connectAttr "Gotham_GCPD_Window1024_file6.msg" ":defaultTextureList1.tx" -na;
connectAttr "SkyFile.msg" ":defaultTextureList1.tx" -na;
connectAttr ":perspShape.msg" ":defaultRenderGlobals.sc";
connectAttr "sun_light.iog" ":defaultLightSet.dsm" -na;
dataStructure -fmt "raw" -as "name=externalContentTable:string=node:string=key:string=upath:uint32=upathcrc:string=rpath:string=roles";
applyMetadata -fmt "raw" -v "channel\nname externalContentTable\nstream\nname v1.0\nindexType numeric\nstructure externalContentTable\n0\n\"|AD_Gotham_GroundFloor_Shop_OlddB5_512\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n1\n\"|AD_Gotham_GroundFloor_Shop_OlddB5_512\" \"representations[0].repData\" \"LevelData/Gotham2/Gotham_GroundFloor_Shop_OlddB5_512.mb\" 2489887621 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham2/Gotham_GroundFloor_Shop_OlddB5_512.mb\" \"\"\n2\n\"|AD_Gotham_Groundfloor_Shop_OldB2\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n3\n\"|AD_Gotham_Groundfloor_Shop_OldB2\" \"representations[0].repData\" \"LevelData/Gotham2/Gotham_Groundfloor_Shop_OldB2.mb\" 1360868314 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham2/Gotham_Groundfloor_Shop_OldB2.mb\" \"\"\n4\n\"|AD_OZ_Gotham_GroundFloor_Shop_OldA_03\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n5\n\"|AD_OZ_Gotham_GroundFloor_Shop_OldA_03\" \"representations[0].repData\" \"LevelData/Gotham2/OZ_Gotham_GroundFloor_Shop_OldA_03.mb\" 2274961572 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham2/OZ_Gotham_GroundFloor_Shop_OldA_03.mb\" \"\"\n6\n\"|AD_Gotham_ARCH_Classic_BigWinx2\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n7\n\"|AD_Gotham_ARCH_Classic_BigWinx2\" \"representations[0].repData\" \"LevelData/Gotham/Gotham_ARCH_Classic_BigWinx2.mb\" 3753359945 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/Gotham_ARCH_Classic_BigWinx2.mb\" \"\"\n8\n\"|AD_Gotham_ARCH_Classic_BigWinx3\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n9\n\"|AD_Gotham_ARCH_Classic_BigWinx3\" \"representations[0].repData\" \"LevelData/Gotham/Gotham_ARCH_Classic_BigWinx2.mb\" 3753359945 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/Gotham_ARCH_Classic_BigWinx2.mb\" \"\"\n10\n\"|AD_Gotham_ARCH_Classic_WinBCorner\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n11\n\"|AD_Gotham_ARCH_Classic_WinBCorner\" \"representations[0].repData\" \"LevelData/Gotham/Gotham_ARCH_Classic_WinBCorner.mb\" 1900794556 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/Gotham_ARCH_Classic_WinBCorner.mb\" \"\"\n12\n\"|AD_Gotham_ARCH_Classic_WinBCorner1\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n13\n\"|AD_Gotham_ARCH_Classic_WinBCorner1\" \"representations[0].repData\" \"LevelData/Gotham/Gotham_ARCH_Classic_WinBCorner.mb\" 1900794556 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/Gotham_ARCH_Classic_WinBCorner.mb\" \"\"\n14\n\"|AD_Gotham_Fences_Mall768\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n15\n\"|AD_Gotham_Fences_Mall768\" \"representations[0].repData\" \"LevelData/Gotham/Gotham_Fences_Mall768.mb\" 1799560506 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/Gotham_Fences_Mall768.mb\" \"\"\n16\n\"|AD_Gotham_Fences_Mall769\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n17\n\"|AD_Gotham_Fences_Mall769\" \"representations[0].repData\" \"LevelData/Gotham/Gotham_Fences_Mall768.mb\" 1799560506 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/Gotham_Fences_Mall768.mb\" \"\"\n18\n\"|AD_Gotham_Fences_PoleSolid_128C\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n19\n\"|AD_Gotham_Fences_PoleSolid_128C\" \"representations[0].repData\" \"LevelData/Gotham/Gotham_Fences_PoleSolid_128C.mb\" 568374597 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/Gotham_Fences_PoleSolid_128C.mb\" \"\"\n20\n\"|AD_Gotham_Fences_PoleSolid_512\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n21\n\"|AD_Gotham_Fences_PoleSolid_512\" \"representations[0].repData\" \"LevelData/Gotham/Gotham_Fences_PoleSolid_512.mb\" 3812819446 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/Gotham_Fences_PoleSolid_512.mb\" \"\"\n22\n\"|AD_Gotham_Fences_PoleSolid_513\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n23\n\"|AD_Gotham_Fences_PoleSolid_513\" \"representations[0].repData\" \"LevelData/Gotham/Gotham_Fences_PoleSolid_512.mb\" 3812819446 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/Gotham_Fences_PoleSolid_512.mb\" \"\"\n24\n\"|AD_ARCH_GCPD_EntranceRoof_04\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n25\n\"|AD_ARCH_GCPD_EntranceRoof_04\" \"representations[0].repData\" \"LevelData/Gotham/ARCH_GCPD_EntranceRoof_04.mb\" 4273868373 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/ARCH_GCPD_EntranceRoof_04.mb\" \"\"\n26\n\"|AD_Gotham_Arch_Classic_BigWiny2\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n27\n\"|AD_Gotham_Arch_Classic_BigWiny2\" \"representations[0].repData\" \"LevelData/Gotham/Gotham_Arch_Classic_BigWiny2.mb\" 4284819578 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/Gotham_Arch_Classic_BigWiny2.mb\" \"\"\n28\n\"|AD_BridgeRoad_Destroyed_2048_Custom_02\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n29\n\"|AD_BridgeRoad_Destroyed_2048_Custom_02\" \"representations[0].repData\" \"LevelData/Bridge/BridgeRoad_Destroyed_2048_Custom_02.mb\" 830170048 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Bridge/BridgeRoad_Destroyed_2048_Custom_02.mb\" \"\"\n30\n\"|AD_ConcreteBarrier01\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n31\n\"|AD_ConcreteBarrier01\" \"representations[0].repData\" \"LevelData/Bridge/ConcreteBarrier01.mb\" 2120712365 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Bridge/ConcreteBarrier01.mb\" \"\"\n32\n\"|AD_ConcreteBarrier02\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n33\n\"|AD_ConcreteBarrier02\" \"representations[0].repData\" \"LevelData/Bridge/ConcreteBarrier01.mb\" 2120712365 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Bridge/ConcreteBarrier01.mb\" \"\"\n34\n\"|AD_Bridge_Rail_01_1024\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n35\n\"|AD_Bridge_Rail_01_1024\" \"representations[0].repData\" \"LevelData/Bridge/Bridge_Rail_01_1024.mb\" 118358252 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Bridge/Bridge_Rail_01_1024.mb\" \"\"\n36\n\"|AD_Gotham_GCPD_Window1024\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n37\n\"|AD_Gotham_GCPD_Window1024\" \"representations[0].repData\" \"LevelData/Gotham/Gotham_GCPD_Window1024.mb\" 916622624 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/Gotham_GCPD_Window1024.mb\" \"\"\n38\n\"|AD_Gotham_GCPD_Window1025\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n39\n\"|AD_Gotham_GCPD_Window1025\" \"representations[0].repData\" \"LevelData/Gotham/Gotham_GCPD_Window1024.mb\" 916622624 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/Gotham_GCPD_Window1024.mb\" \"\"\n40\n\"|AD_Gotham_Fences_PoleSolid_514\" \"iconName\" \"out_assemblyDefinition.png\" 4223031819 \"\" \"ui\"\n41\n\"|AD_Gotham_Fences_PoleSolid_514\" \"representations[0].repData\" \"LevelData/Gotham/Gotham_Fences_PoleSolid_512.mb\" 3812819446 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Gotham/Gotham_Fences_PoleSolid_512.mb\" \"\"\n42\n\"|sun_light|sun_lightShape\" \"dmapName\" \"depthmap\" 2097411553 \"\" \"sourceImages\"\n43\n\"Gotham_GroundFloor_Shop_OlddB5_512_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_02_D.tga\" 2689655935 \"\" \"sourceImages\"\n44\n\"Gotham_GroundFloor_Shop_OlddB5_512_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_N.tga\" 39221344 \"\" \"sourceImages\"\n45\n\"Gotham_GroundFloor_Shop_OlddB5_512_file3\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_S.tga\" 2586192723 \"\" \"sourceImages\"\n46\n\"Gotham_GroundFloor_Shop_OlddB5_512_file4\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_D.tga\" 2272928930 \"\" \"sourceImages\"\n47\n\"Gotham_GroundFloor_Shop_OlddB5_512_file5\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_N.tga\" 3452582915 \"\" \"sourceImages\"\n48\n\"Gotham_GroundFloor_Shop_OlddB5_512_file6\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_D.tga\" 1418502102 \"\" \"sourceImages\"\n49\n\"Gotham_GroundFloor_Shop_OlddB5_512_file7\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_E.tga\" 3122269458 \"\" \"sourceImages\"\n50\n\"file8\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_N.tga\" 507283319 \"\" \"sourceImages\"\n51\n\"Gotham_Groundfloor_Shop_OldB2_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_02_D.tga\" 2689655935 \"\" \"sourceImages\"\n52\n\"Gotham_Groundfloor_Shop_OldB2_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_N.tga\" 39221344 \"\" \"sourceImages\"\n53\n\"Gotham_Groundfloor_Shop_OldB2_file3\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_S.tga\" 2586192723 \"\" \"sourceImages\"\n54\n\"Gotham_Groundfloor_Shop_OldB2_file4\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_D.tga\" 2272928930 \"\" \"sourceImages\"\n55\n\"Gotham_Groundfloor_Shop_OldB2_file5\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_N.tga\" 3452582915 \"\" \"sourceImages\"\n56\n\"Gotham_Groundfloor_Shop_OldB2_file6\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_D.tga\" 1418502102 \"\" \"sourceImages\"\n57\n\"Gotham_Groundfloor_Shop_OldB2_file7\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_E.tga\" 3122269458 \"\" \"sourceImages\"\n58\n\"Gotham_Groundfloor_Shop_OldB2_file8\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_N.tga\" 507283319 \"\" \"sourceImages\"\n59\n\"OZ_Gotham_GroundFloor_Shop_OldA_03_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/OZ_Gotham_Groundfloor_Shop_Old_D.tga\" 4056168653 \"\" \"sourceImages\"\n60\n\"OZ_Gotham_GroundFloor_Shop_OldA_03_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/OZ_Gotham_Groundfloor_Shop_Old_N.tga\" 3144949868 \"\" \"sourceImages\"\n61\n\"OZ_Gotham_GroundFloor_Shop_OldA_03_file3\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_Old_S.tga\" 2586192723 \"\" \"sourceImages\"\n62\n\"OZ_Gotham_GroundFloor_Shop_OldA_03_file4\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_D.tga\" 2272928930 \"\" \"sourceImages\"\n63\n\"OZ_Gotham_GroundFloor_Shop_OldA_03_file5\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_N.tga\" 3452582915 \"\" \"sourceImages\"\n64\n\"OZ_Gotham_GroundFloor_Shop_OldA_03_file6\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_D.tga\" 1418502102 \"\" \"sourceImages\"\n65\n\"OZ_Gotham_GroundFloor_Shop_OldA_03_file7\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_02_E.tga\" 3122269458 \"\" \"sourceImages\"\n66\n\"OZ_Gotham_GroundFloor_Shop_OldA_03_file8\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Groundfloor/Shop/Gotham_Groundfloor_Shop_OldB_N.tga\" 507283319 \"\" \"sourceImages\"\n67\n\"Gotham_ARCH_Classic_BigWinx2_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Gotham_ARCH_Classic_Fence_d.tga\" 1537557673 \"\" \"sourceImages\"\n68\n\"Gotham_ARCH_Classic_BigWinx2_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Gotham_ARCH_Classic_Fence_N.tga\" 3503584012 \"\" \"sourceImages\"\n69\n\"Gotham_ARCH_Classic_BigWinx2_file4\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_D.tga\" 895219309 \"\" \"sourceImages\"\n70\n\"Gotham_ARCH_Classic_BigWinx2_file5\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_N_New.tga\" 235809174 \"\" \"sourceImages\"\n71\n\"Gotham_ARCH_Classic_BigWinx2_file6\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main02_D.tga\" 3464531457 \"\" \"sourceImages\"\n72\n\"Gotham_ARCH_Classic_BigWinx2_file7\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_N_New.tga\" 235809174 \"\" \"sourceImages\"\n73\n\"Gotham_ARCH_Classic_BigWinx2_file8\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_D.tga\" 1668251090 \"\" \"sourceImages\"\n74\n\"file9\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_N.tga\" 702506355 \"\" \"sourceImages\"\n75\n\"file10\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main02_S.tga\" 474006931 \"\" \"sourceImages\"\n76\n\"file11\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_S.tga\" 2981049920 \"\" \"sourceImages\"\n77\n\"Gotham_ARCH_Classic_WinBCorner_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Gotham_ARCH_Classic_Fence_d.tga\" 1537557673 \"\" \"sourceImages\"\n78\n\"Gotham_ARCH_Classic_WinBCorner_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Gotham_ARCH_Classic_Fence_N.tga\" 3503584012 \"\" \"sourceImages\"\n79\n\"Gotham_ARCH_Classic_WinBCorner_file4\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_D.tga\" 895219309 \"\" \"sourceImages\"\n80\n\"Gotham_ARCH_Classic_WinBCorner_file5\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_N_New.tga\" 235809174 \"\" \"sourceImages\"\n81\n\"Gotham_ARCH_Classic_WinBCorner_file6\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main02_D.tga\" 3464531457 \"\" \"sourceImages\"\n82\n\"Gotham_ARCH_Classic_WinBCorner_file7\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_N_New.tga\" 235809174 \"\" \"sourceImages\"\n83\n\"Gotham_ARCH_Classic_WinBCorner_file8\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_D.tga\" 1668251090 \"\" \"sourceImages\"\n84\n\"Gotham_ARCH_Classic_WinBCorner_file9\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_N.tga\" 702506355 \"\" \"sourceImages\"\n85\n\"Gotham_ARCH_Classic_WinBCorner_file10\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main02_S.tga\" 474006931 \"\" \"sourceImages\"\n86\n\"Gotham_ARCH_Classic_WinBCorner_file11\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_S.tga\" 2981049920 \"\" \"sourceImages\"\n87\n\"Gotham_Fences_Mall768_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_D.tga\" 3590571595 \"\" \"sourceImages\"\n88\n\"Gotham_Fences_Mall768_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_O.tga\" 2715023194 \"\" \"sourceImages\"\n89\n\"Gotham_Fences_Mall768_file3\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_N.tga\" 2629033706 \"\" \"sourceImages\"\n90\n\"Gotham_Fences_Mall768_file4\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_O_SDF.tga\" 2778658450 \"\" \"sourceImages\"\n91\n\"Gotham_Fences_Mall768_file5\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_Mall_D.tga\" 1535523530 \"\" \"sourceImages\"\n92\n\"Gotham_Fences_Mall768_file6\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Textures/Gotham_Fences_FloodBarrier_D.tga\" 1475522209 \"\" \"sourceImages\"\n93\n\"Gotham_Fences_Mall768_file7\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_Mall_D.tga\" 1535523530 \"\" \"sourceImages\"\n94\n\"Gotham_Fences_PoleSolid_128C_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_D.tga\" 3590571595 \"\" \"sourceImages\"\n95\n\"Gotham_Fences_PoleSolid_128C_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_O.tga\" 2715023194 \"\" \"sourceImages\"\n96\n\"Gotham_Fences_PoleSolid_128C_file3\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_N.tga\" 2629033706 \"\" \"sourceImages\"\n97\n\"Gotham_Fences_PoleSolid_128C_file4\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_O_SDF.tga\" 2778658450 \"\" \"sourceImages\"\n98\n\"Gotham_Fences_PoleSolid_128C_file5\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_Mall_D.tga\" 1535523530 \"\" \"sourceImages\"\n99\n\"Gotham_Fences_PoleSolid_128C_file6\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Textures/Gotham_Fences_FloodBarrier_D.tga\" 1475522209 \"\" \"sourceImages\"\n100\n\"Gotham_Fences_PoleSolid_128C_file7\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_Mall_D.tga\" 1535523530 \"\" \"sourceImages\"\n101\n\"Gotham_Fences_PoleSolid_512_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_D.tga\" 3590571595 \"\" \"sourceImages\"\n102\n\"Gotham_Fences_PoleSolid_512_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_O.tga\" 2715023194 \"\" \"sourceImages\"\n103\n\"Gotham_Fences_PoleSolid_512_file3\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_N.tga\" 2629033706 \"\" \"sourceImages\"\n104\n\"Gotham_Fences_PoleSolid_512_file4\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_3BarGate_O_SDF.tga\" 2778658450 \"\" \"sourceImages\"\n105\n\"Gotham_Fences_PoleSolid_512_file5\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_Mall_D.tga\" 1535523530 \"\" \"sourceImages\"\n106\n\"Gotham_Fences_PoleSolid_512_file6\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Textures/Gotham_Fences_FloodBarrier_D.tga\" 1475522209 \"\" \"sourceImages\"\n107\n\"Gotham_Fences_PoleSolid_512_file7\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Fences/Gotham_Fences_Mall_D.tga\" 1535523530 \"\" \"sourceImages\"\n108\n\"ARCH_GCPD_EntranceRoof_04_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Roof_D.tga\" 3861339948 \"\" \"sourceImages\"\n109\n\"ARCH_GCPD_EntranceRoof_04_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Roof_N.tga\" 2895595405 \"\" \"sourceImages\"\n110\n\"Gotham_Arch_Classic_BigWiny2_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Gotham_ARCH_Classic_Fence_d.tga\" 1537557673 \"\" \"sourceImages\"\n111\n\"Gotham_Arch_Classic_BigWiny2_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Gotham_ARCH_Classic_Fence_N.tga\" 3503584012 \"\" \"sourceImages\"\n112\n\"Gotham_Arch_Classic_BigWiny2_file4\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_D.tga\" 895219309 \"\" \"sourceImages\"\n113\n\"Gotham_Arch_Classic_BigWiny2_file5\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_N_New.tga\" 235809174 \"\" \"sourceImages\"\n114\n\"Gotham_Arch_Classic_BigWiny2_file6\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main02_D.tga\" 3464531457 \"\" \"sourceImages\"\n115\n\"Gotham_Arch_Classic_BigWiny2_file7\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main_N_New.tga\" 235809174 \"\" \"sourceImages\"\n116\n\"Gotham_Arch_Classic_BigWiny2_file8\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_D.tga\" 1668251090 \"\" \"sourceImages\"\n117\n\"Gotham_Arch_Classic_BigWiny2_file9\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_N.tga\" 702506355 \"\" \"sourceImages\"\n118\n\"Gotham_Arch_Classic_BigWiny2_file10\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Main02_S.tga\" 474006931 \"\" \"sourceImages\"\n119\n\"Gotham_Arch_Classic_BigWiny2_file11\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_Arch/Classic/Gotham_ARCH_Hotel_Ornate_S.tga\" 2981049920 \"\" \"sourceImages\"\n120\n\"BridgeRoad_Destroyed_2048_Custom_02_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_D.tga\" 140519586 \"\" \"sourceImages\"\n121\n\"BridgeRoad_Destroyed_2048_Custom_02_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_N.tga\" 1120940035 \"\" \"sourceImages\"\n122\n\"BridgeRoad_Destroyed_2048_Custom_02_file3\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_S.tga\" 3667944240 \"\" \"sourceImages\"\n123\n\"BridgeRoad_Destroyed_2048_Custom_02_file4\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_D.tga\" 2920751894 \"\" \"sourceImages\"\n124\n\"BridgeRoad_Destroyed_2048_Custom_02_file5\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_N.tga\" 3836165047 \"\" \"sourceImages\"\n125\n\"BridgeRoad_Destroyed_2048_Custom_02_file6\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_S.tga\" 2094491780 \"\" \"sourceImages\"\n126\n\"ConcreteBarrier01_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_D.tga\" 140519586 \"\" \"sourceImages\"\n127\n\"ConcreteBarrier01_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_N.tga\" 1120940035 \"\" \"sourceImages\"\n128\n\"ConcreteBarrier01_file3\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_S.tga\" 3667944240 \"\" \"sourceImages\"\n129\n\"ConcreteBarrier01_file4\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_D.tga\" 2920751894 \"\" \"sourceImages\"\n130\n\"ConcreteBarrier01_file5\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_N.tga\" 3836165047 \"\" \"sourceImages\"\n131\n\"ConcreteBarrier01_file6\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_S.tga\" 2094491780 \"\" \"sourceImages\"\n132\n\"Bridge_Rail_01_1024_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_D.tga\" 140519586 \"\" \"sourceImages\"\n133\n\"Bridge_Rail_01_1024_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_N.tga\" 1120940035 \"\" \"sourceImages\"\n134\n\"Bridge_Rail_01_1024_file3\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_03_S.tga\" 3667944240 \"\" \"sourceImages\"\n135\n\"Bridge_Rail_01_1024_file4\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_D.tga\" 2920751894 \"\" \"sourceImages\"\n136\n\"Bridge_Rail_01_1024_file5\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_N.tga\" 3836165047 \"\" \"sourceImages\"\n137\n\"Bridge_Rail_01_1024_file6\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Bridge/Bridge_Roads/Mesh/Bridge_Road_02_S.tga\" 2094491780 \"\" \"sourceImages\"\n138\n\"Gotham_GCPD_Window1024_file1\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Roof_D.tga\" 3861339948 \"\" \"sourceImages\"\n139\n\"Gotham_GCPD_Window1024_file2\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Roof_N.tga\" 2895595405 \"\" \"sourceImages\"\n140\n\"Gotham_GCPD_Window1024_file3\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Main_D.tga\" 230693179 \"\" \"sourceImages\"\n141\n\"Gotham_GCPD_Window1024_file4\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Main_N.tga\" 1198522778 \"\" \"sourceImages\"\n142\n\"Gotham_GCPD_Window1024_file5\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_GCPD_Main_S.tga\" 3741340329 \"\" \"sourceImages\"\n143\n\"Gotham_GCPD_Window1024_file6\" \"fileTextureName\" \"L:/Umodel_BatmanOG/Gotham/Gotham_GCPD/Gotham_ARCH_GCPD_Main_E.tga\" 334878717 \"\" \"sourceImages\"\n144\n\"SkyFile\" \"fileTextureName\" \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Level_Combine/Texture/sky.jpg\" 718479912 \"C:/Project/NagaGame/Arts/LevelProject/LevelData/Level_Combine/Texture/sky.jpg\" \"sourceImages\"\nendStream\nendChannel\nendAssociations\n" 
		-scn;
// End of Level_Test.ma
