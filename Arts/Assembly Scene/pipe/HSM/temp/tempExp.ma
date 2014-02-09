//Maya ASCII 2014 scene
//Name: tempExp.ma
//Last modified: Thu, Feb 06, 2014 02:48:05 PM
//Codeset: 936
requires maya "2014";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2014";
fileInfo "version" "2014 x64";
fileInfo "cutIdentifier" "201303010241-864206";
fileInfo "osv" "Microsoft Windows 7 Ultimate Edition, 64-bit Windows 7 Service Pack 1 (Build 7601)\n";
createNode transform -n "ConcreteBarrier01";
createNode mesh -n "ConcreteBarrier01Shape" -p "ConcreteBarrier01";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 8 ".vt[0:7]"  -32.36529922 -2.3841858e-007 -517.8447876
		 32.36529922 -2.3841858e-007 -517.8447876 32.36529922 -2.3841858e-007 7.6293945e-006
		 -32.36529922 -2.3841858e-007 7.6293945e-006 -32.36529922 128.16659546 -517.8447876
		 -32.36529922 128.16659546 7.6293945e-006 32.36529922 128.16659546 7.6293945e-006
		 32.36529922 128.16659546 -517.8447876;
	setAttr -s 12 ".ed[0:11]"  0 1 0 1 2 0 2 3 0 3 0 0 4 5 0 5 6 0 6 7 0
		 7 4 0 2 6 0 5 3 0 4 0 0 7 1 0;
	setAttr -s 6 -ch 24 ".fc[0:5]" -type "polyFaces" 
		f 4 0 1 2 3
		f 4 4 5 6 7
		f 4 -3 8 -6 9
		f 4 -4 -10 -5 10
		f 4 -11 -8 11 -1
		f 4 -12 -7 -9 -2;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
	setAttr ".hfd" -type "dataPolyComponent" Index_Data Face 0 ;
createNode materialInfo -n "materialInfo45";
createNode shadingEngine -n "BBoxShadingGroup1";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode lambert -n "BBoxLambert1";
	setAttr ".c" -type "float3" 0.5 0.5 0.69999999 ;
createNode lightLinker -s -n "lightLinker1";
	setAttr -s 47 ".lnk";
	setAttr -s 47 ".slnk";
select -ne :time1;
	setAttr ".o" 1;
	setAttr ".unw" 1;
select -ne :renderPartition;
	setAttr -s 47 ".st";
select -ne :initialShadingGroup;
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultShaderList1;
	setAttr -s 9 ".s";
select -ne :defaultTextureList1;
	setAttr -s 6 ".tx";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 8 ".u";
select -ne :defaultRenderingList1;
select -ne :renderGlobalsList1;
select -ne :defaultResolution;
	setAttr ".pa" 1;
select -ne :hardwareRenderGlobals;
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
select -ne :hardwareRenderingGlobals;
	setAttr ".otfna" -type "stringArray" 18 "NURBS Curves" "NURBS Surfaces" "Polygons" "Subdiv Surfaces" "Particles" "Fluids" "Image Planes" "UI:" "Lights" "Cameras" "Locators" "Joints" "IK Handles" "Deformers" "Motion Trails" "Components" "Misc. UI" "Ornaments"  ;
	setAttr ".otfva" -type "Int32Array" 18 0 1 1 1 1 1
		 1 0 0 0 0 0 0 0 0 0 0 0 ;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
connectAttr "BBoxShadingGroup1.msg" "materialInfo45.sg";
connectAttr "BBoxLambert1.msg" "materialInfo45.m";
connectAttr "BBoxLambert1.oc" "BBoxShadingGroup1.ss";
connectAttr "ConcreteBarrier01Shape.iog" "BBoxShadingGroup1.dsm" -na;
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BBoxShadingGroup1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BBoxShadingGroup1.message" ":defaultLightSet.message";
connectAttr "BBoxShadingGroup1.pa" ":renderPartition.st" -na;
connectAttr "BBoxLambert1.msg" ":defaultShaderList1.s" -na;
// End of tempExp.ma
