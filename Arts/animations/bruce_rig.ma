//Maya ASCII 2015 scene
//Name: bruce_rig.ma
//Last modified: Wed, Jan 28, 2015 09:02:48 PM
//Codeset: 936
requires maya "2015";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2015";
fileInfo "version" "2015";
fileInfo "cutIdentifier" "201410051530-933320";
fileInfo "osv" "Microsoft Windows 7 Ultimate Edition, 64-bit Windows 7 Service Pack 1 (Build 7601)\n";
createNode transform -s -n "persp";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 267.62968785521986 734.8170731226453 1079.3082142730216 ;
	setAttr ".r" -type "double3" -22.538352729602376 15.800000000000047 -8.2636021744866581e-016 ;
createNode camera -s -n "perspShape" -p "persp";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 1329.4580950804398;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 100.1 0 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
createNode transform -s -n "front";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 0 100.1 ;
createNode camera -s -n "frontShape" -p "front";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
createNode transform -s -n "side";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 100.1 0 0 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode joint -n "Bip01";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 0 277.86429916381837 0 ;
	setAttr ".r" -type "double3" 0 0 -89.999921452826385 ;
	setAttr ".s" -type "double3" 2.5399998486065893 2.5399998486065893 2.54 ;
	setAttr ".jo" -type "double3" -89.999999999999986 0 0 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 3.48210305817104e-006 -7.0499157861686183e-016 2.5399998486042024 0
		 2.5399998486042024 0 -3.482103058312038e-006 0 1.4099832412739488e-016 2.54 5.6399329650957953e-016 0
		 0 277.86429916381837 0 1;
	setAttr ".radi" 0;
	setAttr -k on ".MaxHandle" 1;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_Pelvis" -p "Bip01";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".r" -type "double3" -89.999935113205538 -90 0 ;
	setAttr ".s" -type "double3" 0.99999994039613904 0.99999994039681228 0.99999994039599827 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0 2.54 0 0 6.3586200000000001e-006 0 2.54 0 2.54 0 -6.3586200000000001e-006 0
		 0 277.86429900000002 0 1;
	setAttr ".radi" 1.844965925216675;
	setAttr -k on ".MaxHandle" 2;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_Spine" -p "Bip01_Pelvis";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 8.7855453491210937 -0.010490705259144306 1.3066653536952799e-006 ;
	setAttr ".r" -type "double3" -0.0001399169273737591 -1.8457955760328241e-005 -1.5704593926002834 ;
	setAttr ".s" -type "double3" 1.0000000531109785 1.0000003509230919 1.0000002384214894 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 5.6418600000000007e-007 2.5390459999999999 -0.069608699999999996 0
		 -2.47394e-006 0.069608699999999996 2.5390470000000001 0 2.54 -4.9617599999999998e-007 2.48847e-006 0
		 2.5856300000000003e-006 300.17958399999998 -0.0266185 1;
	setAttr ".radi" 2.766168651580811;
	setAttr -k on ".MaxHandle" 3;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_Spine1" -p "Bip01_Spine";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 13.172225952148437 -0.010484218597412109 -2.2624572011409327e-006 ;
	setAttr ".r" -type "double3" -0.0001254340361290615 9.5406731528169878e-006 -1.6160218005934837 ;
	setAttr ".s" -type "double3" 1.0000001689446287 0.99999981119873882 1.0000000000023532 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.32471e-007 2.536073 -0.141185 0 -4.0818599999999996e-006 0.141185 2.536073 0
		 2.54 9.4622399999999994e-008 4.0829100000000002e-006 0 4.2674e-006 333.62374499999999 -0.97014100000000003 1;
	setAttr ".radi" 2.7661676502227781;
	setAttr -k on ".MaxHandle" 4;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_Spine2" -p "Bip01_Spine1";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 13.1722412109375 -0.010482311248779297 2.4398104869760573e-007 ;
	setAttr ".r" -type "double3" -4.0697133530037078e-005 -5.4176939322622899e-006 -1.7195405267021384 ;
	setAttr ".s" -type "double3" 1.0000000024905971 1.0000001811124715 0.99999988079097701 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 5.2988500000000001e-007 2.5306950000000001 -0.217222 0
		 -6.1733099999999997e-006 0.217222 2.5306950000000001 0 2.54 0 6.1960100000000003e-006 0
		 6.6870000000000005e-006 367.027985 -2.8564470000000002 1;
	setAttr ".radi" 2.7661111736297608;
	setAttr -k on ".MaxHandle" 5;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_Spine3" -p "Bip01_Spine2";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 13.171951293945313 -0.010468482971191406 -3.1250294796336675e-006 ;
	setAttr ".r" -type "double3" 8.6650658181683518e-005 2.7626377534848828e-005 -3.1990673768171125 ;
	setAttr ".s" -type "double3" 0.9999999638304804 0.99999984771845774 0.99999994039663542 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -3.0279199999999998e-007 2.5146289999999998 -0.35810900000000001 0
		 -2.9744600000000002e-006 0.35810900000000001 2.5146289999999998 0 2.54 7.1913000000000001e-007 2.9020599999999999e-006 0
		 5.8027499999999996e-006 400.35990399999997 -5.7441750000000003 1;
	setAttr ".radi" 3.3014279651641854;
	setAttr -k on ".MaxHandle" 6;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_Neck" -p "Bip01_Spine3";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 15.716537475585937 0.37741661071777344 1.0183066478930414e-006 ;
	setAttr ".r" -type "double3" -1.4250509816784579e-005 -6.6850726429924757e-005 23.260540721988864 ;
	setAttr ".s" -type "double3" 1.0000001978757871 1.000000252635032 1.0000001192099499 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.43826e-006 2.4516589999999998 0.66405800000000004 0
		 -3.08676e-006 -0.66405800000000004 2.4516589999999998 0 2.54 -2.19524e-006 2.6033800000000002e-006 0
		 2.4385200000000002e-006 440.01635900000002 -10.423356999999999 1;
	setAttr ".radi" 2.4979903507232666;
	setAttr -k on ".MaxHandle" 7;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_Head" -p "Bip01_Neck";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 11.895172119140625 -3.814697265625e-006 -1.7111306078732014e-006 ;
	setAttr ".r" -type "double3" -0.11414401974119875 1.7330198549859684e-005 -15.186279470306557 ;
	setAttr ".s" -type "double3" 0.99999993318351255 0.99999979004873008 1.0000001366613578 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0 2.54 0 0 -0.0050630500000000004 0 2.5399949999999998 0
		 2.5399949999999998 0 0.0050630500000000004 0 1.52006e-005 469.17930799999999 -2.5242770000000001 1;
	setAttr ".radi" 2.4979903507232666;
	setAttr -k on ".MaxHandle" 8;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Clavicle" -p "Bip01_Neck";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" -5.6907196044921875 0.033100128173828125 9.0506420135498047 ;
	setAttr ".r" -type "double3" -6.6332088345425948 -62.353933974738304 162.57534905119104 ;
	setAttr ".s" -type "double3" 0.9999999536490306 0.99999969835479541 0.99999984348064808 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 2.2500089999999999 -1.177659 0.046666600000000003 0
		 -0.13613900000000001 -0.359595 -2.5107279999999998 0 1.1706939999999999 2.2215780000000001 -0.38166 0
		 22.988626 426.04271599999998 -14.121126 1;
	setAttr ".radi" 3.9354291915893564;
	setAttr -k on ".MaxHandle" 9;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_UpperArm" -p "Bip01_L_Clavicle";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 18.740142822265625 -9.5367431640625e-006 3.0517578125e-005 ;
	setAttr ".r" -type "double3" 6.831328350621888 17.256333965698214 -3.648124591871313 ;
	setAttr ".s" -type "double3" 1.0000000404725218 1.0000003619287867 1.0000001257636708 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.8053650652461701 -1.7595448049522582 0.31026019746374245 0
		 0.21977011866068624 -0.21903036901645323 -2.5209783228934604 0 1.773121266412423 1.81868946809487 -0.0034389355687517442 0
		 65.15416068628636 403.97320808878175 -13.246744446295066 1;
	setAttr ".radi" 5.9889773941040048;
	setAttr -k on ".MaxHandle" 10;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Forearm" -p "Bip01_L_UpperArm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 28.518943786621094 9.5367431640625e-007 -3.0517578125e-005 ;
	setAttr ".r" -type "double3" -4.2688674026894374e-006 1.0245281085192652e-005 -22.787035072392555 ;
	setAttr ".s" -type "double3" 1.0000002605908522 1.0000001940956409 1.0000000000000071 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.5793393880435658 -1.5373825032397903 1.2624374642039844 0
		 0.90184776830119751 -0.88341951306060773 -2.2040525085469236 0 1.77312161601308 1.8186891273697892 -0.0034388740421044716 0
		 116.64121159459376 353.79279299542554 -4.3984536148449287 1;
	setAttr ".radi" 5.2235905838012711;
	setAttr -k on ".MaxHandle" 11;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Hand" -p "Bip01_L_Forearm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 24.874237060546875 1.1444091796875e-005 0 ;
	setAttr ".r" -type "double3" -87.179420416016768 4.404806101093758 1.7614798082330103 ;
	setAttr ".s" -type "double3" 0.99999971654809927 0.99999983397048497 0.99999972897809009 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.4653890000000001 -1.6988730000000001 1.190825 0 -1.8469930000000001 -1.732286 -0.198493 0
		 0.94490700000000005 -0.75140899999999999 -2.234756 0 155.926064 315.55165 27.003734000000001 1;
	setAttr ".radi" 1.1005645751953126;
	setAttr -k on ".MaxHandle" 12;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger0" -p "Bip01_L_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.8994979858398438 0.53240966796875 -4.333038330078125 ;
	setAttr ".r" -type "double3" 89.473437293653092 45.531610549485706 29.550984081037878 ;
	setAttr ".s" -type "double3" 1.0000005235781002 1.0000003346113244 1.0000006421406049 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.41944900000000002 -1.097537 2.251906 0 0.90012099999999995 -2.1968019999999999 -0.90302000000000004 0
		 2.3378299999999999 0.64890400000000004 0.751718 0 155.09727699999999 312.95936599999999 40.034146 1;
	setAttr ".radi" 1.2398516750335695;
	setAttr -k on ".MaxHandle" 13;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger01" -p "Bip01_L_Finger0";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 5.9040565490722656 -7.62939453125e-006 7.62939453125e-006 ;
	setAttr ".r" -type "double3" -1.5367935542252185e-005 2.5613217573748365e-005 10.313810058786023 ;
	setAttr ".s" -type "double3" 0.99999968039159182 0.99999935516906502 0.99999934434914295 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.25151600000000002 -1.473117 2.0538419999999999 0
		 0.960673 -1.9648030000000001 -1.291609 0 2.3378290000000002 0.64890199999999998 0.751718 0
		 152.62083899999999 306.47947099999999 53.329531000000003 1;
	setAttr ".radi" 0.63191009044647228;
	setAttr -k on ".MaxHandle" 14;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger02" -p "Bip01_L_Finger01";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.00909423828125 0 0 ;
	setAttr ".r" -type "double3" -8.5377349409956552e-007 -2.4759430770513896e-005 9.8148659367302109 ;
	setAttr ".s" -type "double3" 1.000000200763222 1.0000001782113717 1.0000002384187163 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.084072099999999997 -1.786486 1.8036080000000001 0
		 0.98948700000000001 -1.684931 -1.6228130000000001 0 2.3378299999999999 0.64890300000000001 0.75171699999999997 0
		 151.86400599999999 302.046718 59.509734999999999 1;
	setAttr ".radi" 0.63191009044647228;
	setAttr -k on ".MaxHandle" 15;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger1" -p "Bip01_L_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 12.355052947998047 -0.7883758544921875 -4.8366165161132812 ;
	setAttr ".r" -type "double3" 15.836835392154274 18.974394783981843 16.987357609715637 ;
	setAttr ".s" -type "double3" 1.0000001780715493 1.0000000916909475 0.99999994229263101 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.50777300000000003 -1.7707569999999999 1.7487680000000001 0
		 -1.790913 -1.4993080000000001 -0.99814899999999995 0 1.728119 -1.033487 -1.54826 0
		 170.91699 299.56194799999997 52.681600000000003 1;
	setAttr ".radi" 1.1010951948165895;
	setAttr -k on ".MaxHandle" 16;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger11" -p "Bip01_L_Finger1";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 5.2433128356933594 0 1.9073486328125e-006 ;
	setAttr ".r" -type "double3" 2.4759428105868841e-005 1.0245283390428765e-005 18.670866762941749 ;
	setAttr ".s" -type "double3" 1.000000035586172 1.0000003083848088 1.0000001192095183 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.092276800000000006 -2.157543 1.337197 0 -1.8592169999999999 -0.85353100000000004 -1.505457 0
		 1.7281200000000001 -1.033487 -1.5482590000000001 0 173.57940500000001 290.27732099999997 61.850929000000001 1;
	setAttr ".radi" 0.63700449943542492;
	setAttr -k on ".MaxHandle" 17;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger12" -p "Bip01_L_Finger11";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.033355712890625 -1.52587890625e-005 0 ;
	setAttr ".r" -type "double3" -2.4332550945794229e-005 -2.5613213380423062e-005 8.7860690986769665 ;
	setAttr ".s" -type "double3" 0.99999984410880671 0.99999991667053378 0.99999994039563411 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.37518000000000001 -2.2625980000000001 1.091553 0
		 -1.8233060000000001 -0.51395999999999997 -1.6920409999999999 0 1.7281200000000001 -1.0334859999999999 -1.54826 0
		 173.299519 283.73273899999998 65.907139999999998 1;
	setAttr ".radi" 0.63700449943542492;
	setAttr -k on ".MaxHandle" 18;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger2" -p "Bip01_L_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 12.988391876220703 -1.183349609375 -1.3129692077636719 ;
	setAttr ".r" -type "double3" -2.0692816769994247 5.9643036629767536 16.648704817842404 ;
	setAttr ".s" -type "double3" 1.0000001383163986 1.0000004022476627 1.0000002461959572 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.77187099999999997 -2.0343849999999999 1.310379 0
		 -2.225193 -1.1372180000000001 -0.45481199999999999 0 0.95096400000000003 -1.00976 -2.1278280000000001 0
		 175.904089 296.52248200000002 45.639690000000002 1;
	setAttr ".radi" 1.2057290983200075;
	setAttr -k on ".MaxHandle" 19;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger21" -p "Bip01_L_Finger2";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 5.7415695190429687 1.52587890625e-005 -7.62939453125e-006 ;
	setAttr ".r" -type "double3" 2.3905662470788203e-005 2.3905665245700817e-005 18.939963286513017 ;
	setAttr ".s" -type "double3" 0.99999986820465092 0.99999998428256942 0.99999958276787837 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.0078337400000000005 -2.2933560000000002 1.0918140000000001 0
		 -2.355251 -0.41533199999999998 -0.85550700000000002 0 0.95096400000000003 -1.0097609999999999 -2.1278269999999999 0
		 180.33579499999999 284.84191600000003 53.163330000000002 1;
	setAttr ".radi" 0.74868225574493419;
	setAttr -k on ".MaxHandle" 20;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger22" -p "Bip01_L_Finger21";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.565155029296875 -1.52587890625e-005 7.62939453125e-006 ;
	setAttr ".r" -type "double3" -2.5506495242260408e-005 -1.7075470700449542e-006 11.691639759427753 ;
	setAttr ".s" -type "double3" 1.0000001302794153 0.99999970358575585 1.0000000000002831 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.469607 -2.329939 0.89579699999999995 0 -2.3079719999999999 0.058020799999999997 -1.059007 0
		 0.950963 -1.0097609999999999 -2.1278280000000001 0 180.36375799999999 276.66574800000001 57.055810000000001 1;
	setAttr ".radi" 0.74868225574493419;
	setAttr -k on ".MaxHandle" 21;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger3" -p "Bip01_L_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 12.939460754394531 -0.7145538330078125 2.3609771728515625 ;
	setAttr ".r" -type "double3" -15.468617587555348 -6.8025395325295186 26.076781696496628 ;
	setAttr ".s" -type "double3" 1.0000000812367122 1.0000005685065965 1.0000002711644294 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.61270100000000005 -2.3603079999999999 0.71073600000000003 0
		 -2.4540130000000002 -0.65312099999999995 -0.0534537 0 0.23242699999999999 -0.67378099999999996 -2.4379499999999998 0
		 178.43808100000001 293.03290800000002 37.277996000000002 1;
	setAttr ".radi" 1.005283055305481;
	setAttr -k on ".MaxHandle" 22;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger31" -p "Bip01_L_Finger3";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 4.7870559692382812 7.62939453125e-006 -3.814697265625e-006 ;
	setAttr ".r" -type "double3" -1.2539801130431755e-005 -5.1226402757427212e-006 14.876065184976131 ;
	setAttr ".s" -type "double3" 1.0000003126838433 0.9999999440890931 1.0000000000000013 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.037851299999999997 -2.448874 0.67319099999999998 0
		 -2.529061 -0.025270899999999999 -0.234129 0 0.23242699999999999 -0.67378099999999996 -2.4379499999999998 0
		 181.37110000000001 281.73396600000001 40.680342000000003 1;
	setAttr ".radi" 0.68097428083419798;
	setAttr -k on ".MaxHandle" 23;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger32" -p "Bip01_L_Finger31";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.2427291870117187 -1.52587890625e-005 0 ;
	setAttr ".r" -type "double3" -1.6008256421588803e-005 1.2806610415685252e-005 13.908467538526386 ;
	setAttr ".s" -type "double3" 0.99999955320642619 0.9999999653697319 0.9999997019768776 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.64465499999999998 -2.383149 0.59717699999999996 0
		 -2.4458129999999998 0.56411 -0.38907900000000001 0 0.23242599999999999 -0.67378099999999996 -2.4379490000000001 0
		 181.24837500000001 273.79291999999998 42.863323999999999 1;
	setAttr ".radi" 0.68097428083419798;
	setAttr -k on ".MaxHandle" 24;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger4" -p "Bip01_L_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 11.267040252685547 0.47991943359375 5.7823066711425781 ;
	setAttr ".r" -type "double3" -29.280083774646346 -16.422299296015236 29.54304153013511 ;
	setAttr ".s" -type "double3" 1.0000001662727316 1.0000001676620343 1.0000002727634776 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.61643999999999999 -2.4494379999999998 0.26805800000000002 0
		 -2.4247299999999998 -0.55382699999999996 0.51532500000000003 0 -0.438504 -0.38095899999999999 -2.4726880000000002 0
		 177.01400100000001 291.23414200000002 27.403507000000001 1;
	setAttr ".radi" 0.80888405084610004;
	setAttr -k on ".MaxHandle" 25;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger41" -p "Bip01_L_Finger4";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.8518218994140625 0 -7.62939453125e-006 ;
	setAttr ".r" -type "double3" -6.0404477444745536e-005 9.391510841664724e-006 14.79338829118438 ;
	setAttr ".s" -type "double3" 0.9999999219617417 1.0000001328968116 0.99999988079120883 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.023109299999999999 -2.5096569999999998 0.39075300000000002 0
		 -2.5017550000000002 0.089956400000000006 0.42980000000000002 0 -0.43850499999999998 -0.38095899999999999 -2.4726880000000002 0
		 179.38843 281.79933 28.436039999999998 1;
	setAttr ".radi" 0.45876061677932745;
	setAttr -k on ".MaxHandle" 26;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger42" -p "Bip01_L_Finger41";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.1845703125 3.814697265625e-006 3.814697265625e-006 ;
	setAttr ".r" -type "double3" 4.1194575708550601e-005 1.1099054223921971e-005 16.48036977801052 ;
	setAttr ".s" -type "double3" 1.0000002862720332 1.0000000661031785 1.0000002384188384 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.73187500000000005 -2.3810340000000001 0.49662899999999999 0
		 -2.39242 0.79821699999999995 0.30129 0 -0.43850299999999998 -0.38096000000000002 -2.4726880000000002 0
		 179.33794900000001 276.31679700000001 29.289660999999999 1;
	setAttr ".radi" 0.45876061677932745;
	setAttr -k on ".MaxHandle" 27;
	setAttr ".fbxID" 5;
createNode joint -n "Gundummy02" -p "Bip01_L_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" -3.814697265625e-006 -3.0517578125e-005 5.7220458984375e-006 ;
	setAttr ".r" -type "double3" 5.1226400455106967e-006 1.1099054755049698e-005 -3.415093770784567e-006 ;
	setAttr ".s" -type "double3" 1.0000002384185995 1.0000003576278726 1.0000001192092913 ;
	setAttr ".ssc" no;
	setAttr ".radi" 6.8003931301063869e-006;
	setAttr -k on ".MaxHandle" 28;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Foretwist" -p "Bip01_L_UpperArm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 28.518943786621094 9.5367431640625e-007 -3.0517578125e-005 ;
	setAttr ".r" -type "double3" 0.93775617627889984 0 -22.787027201021058 ;
	setAttr ".s" -type "double3" 1.0000002028776087 0.99999978722044258 1.0000003020494674 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.579339 -1.5373829999999999 1.262435 0 0.93074599999999996 -0.85353299999999999 -2.2038129999999998 0
		 1.758124 1.8329040000000001 0.032635900000000002 0 116.641204 353.79290099999997 -4.3983530000000002 1;
	setAttr ".radi" 2.611794290542603;
	setAttr -k on ".MaxHandle" 29;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Foretwist1" -p "Bip01_L_Foretwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 12.437114715576172 -7.62939453125e-006 -1.52587890625e-005 ;
	setAttr ".r" -type "double3" 0.93775517509134076 6.3179257354144695e-005 1.451415371649874e-005 ;
	setAttr ".s" -type "double3" 0.99999988079135049 0.99999994372082024 0.99999976468765306 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.579337 -1.5373859999999999 1.2624340000000001 0 0.95939399999999997 -0.82342000000000004 -2.2029839999999998 0
		 1.742658 1.846625 0.068701100000000001 0 136.28361899999999 334.67228499999999 11.302699 1;
	setAttr ".radi" 2.611794290542603;
	setAttr -k on ".MaxHandle" 30;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_LUpArmTwist" -p "Bip01_L_Clavicle";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 18.740142822265625 -9.5367431640625e-006 3.0517578125e-005 ;
	setAttr ".r" -type "double3" 6.7762547733620186 17.256359126214932 -3.6481199033100467 ;
	setAttr ".s" -type "double3" 1.0000002342040111 1.0000000606910231 1.0000003578749088 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.8053650000000001 -1.7595460000000001 0.31025799999999998 0
		 0.21806600000000001 -0.220775 -2.5209730000000001 0 1.773333 1.8184769999999999 -0.00585937 0
		 65.154148000000006 403.97328800000003 -13.246574000000001 1;
	setAttr ".radi" 2.9944880962371827;
	setAttr -k on ".MaxHandle" 31;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_LUpArmTwist1" -p "Bip01_LUpArmTwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 14.25946044921875 -4.76837158203125e-007 -1.52587890625e-005 ;
	setAttr ".r" -type "double3" 0.027536974377171515 -3.5858503829229071e-005 -4.2688695034802134e-006 ;
	setAttr ".s" -type "double3" 0.99999970197697474 1.0000000558887645 0.99999993668315523 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.8053650000000001 -1.759544 0.31025799999999998 0
		 0.218918 -0.21990100000000001 -2.5209760000000001 0 1.7732270000000001 1.818584 -0.0046479399999999997 0
		 90.897649000000001 378.88307500000002 -8.8224619999999998 1;
	setAttr ".radi" 2.9944880962371827;
	setAttr -k on ".MaxHandle" 32;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Clavicle" -p "Bip01_Neck";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" -5.6906890869140625 0.033145904541015625 -9.0506401062011719 ;
	setAttr ".r" -type "double3" 6.6326029621776383 62.353830177642394 162.5748147467641 ;
	setAttr ".s" -type "double3" 1.000000027860952 0.99999951441406609 1.0000000223498076 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -2.2500089999999999 -1.177659 0.046672600000000002 0
		 0.136132 -0.359595 -2.5107279999999998 0 1.170695 -2.2215790000000002 0.38165700000000002 0
		 -22.988631000000002 426.04279300000002 -14.121057 1;
	setAttr ".radi" 3.9354315948486329;
	setAttr -k on ".MaxHandle" 33;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_UpperArm" -p "Bip01_R_Clavicle";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 18.740150451660156 0 0 ;
	setAttr ".r" -type "double3" -6.8313063453905816 -17.256327971298528 -3.648117463215653 ;
	setAttr ".s" -type "double3" 0.9999998749595681 1.0000004012673778 0.99999999315980681 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.8053646777966552 -1.7595441648219285 0.31026435542437619 0
		 -0.21977570921932404 -0.21903065379024034 -2.5209774590938072 0 1.7731207779000404 -1.8186900601415077 0.00343554135327101 0
		 -65.154143364958415 403.97322337599195 -13.246572504074972 1;
	setAttr ".radi" 5.9889745903015132;
	setAttr -k on ".MaxHandle" 34;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Forearm" -p "Bip01_R_UpperArm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 28.518928527832031 1.9073486328125e-006 -1.52587890625e-005 ;
	setAttr ".r" -type "double3" -3.4150950670164715e-006 -5.1226423781510633e-006 -22.787021471855638 ;
	setAttr ".s" -type "double3" 0.99999990226889646 0.99999985885898002 0.99999988079073932 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.5793366722660236 -1.5373812989960436 1.2624399872321093 0
		 -0.90185233302666346 -0.88341862268681481 -2.2040496630118871 0 1.7731206539767497 -1.8186897585400728 0.0034352967011649404 0
		 -116.64123705257856 353.79293643111163 -4.3981703877984248 1;
	setAttr ".radi" 5.2235929870605471;
	setAttr -k on ".MaxHandle" 35;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Hand" -p "Bip01_R_Forearm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 24.874259948730469 5.7220458984375e-006 3.0517578125e-005 ;
	setAttr ".r" -type "double3" 87.179394989992872 -4.4047963523296065 1.7614476135634927 ;
	setAttr ".s" -type "double3" 0.99999998520877253 0.99999999761616654 1.0000001589933782 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.465387 -1.6988719999999999 1.1908300000000001 0
		 1.846992 -1.7322869999999999 -0.19849800000000001 0 0.94491400000000003 0.75140799999999996 2.2347540000000001 0
		 -155.92597699999999 315.551669 27.004121999999999 1;
	setAttr ".radi" 1.1005664777755739;
	setAttr -k on ".MaxHandle" 36;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger0" -p "Bip01_R_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.899505615234375 0.5324249267578125 4.3330459594726562 ;
	setAttr ".r" -type "double3" -89.473431914997391 -45.531614663840671 29.551016322972661 ;
	setAttr ".s" -type "double3" 1.0000000354776202 1.0000001067088209 1.0000000531495399 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.419456 -1.097537 2.2519040000000001 0 -0.90012300000000001 -2.1968019999999999 -0.90301699999999996 0
		 2.3378269999999999 -0.64890300000000001 -0.75172399999999995 0 -155.09713199999999 312.95934699999998 40.034545000000001 1;
	setAttr ".radi" 1.2398503732681276;
	setAttr -k on ".MaxHandle" 37;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger01" -p "Bip01_R_Finger0";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 5.9040489196777344 -1.52587890625e-005 -7.62939453125e-006 ;
	setAttr ".r" -type "double3" 2.6466984578500466e-005 2.3905660814083885e-005 10.313813109994209 ;
	setAttr ".s" -type "double3" 1.0000000535840212 0.999999941636738 1.0000000000001279 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.25152000000000002 -1.473117 2.0538419999999999 0
		 -0.960677 -1.9648030000000001 -1.291606 0 2.337828 -0.64890300000000001 -0.75172300000000003 0
		 -152.620645 306.47947099999999 53.329912999999998 1;
	setAttr ".radi" 0.63190968990325924;
	setAttr -k on ".MaxHandle" 38;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger02" -p "Bip01_R_Finger01";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.00909423828125 1.52587890625e-005 -1.52587890625e-005 ;
	setAttr ".r" -type "double3" 3.4150955463087379e-006 1.1952834351356671e-005 9.8148481385913726 ;
	setAttr ".s" -type "double3" 0.99999972359407208 0.99999971851380376 0.9999998211860982 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.084076499999999998 -1.7864850000000001 1.8036080000000001 0
		 -0.98949100000000001 -1.684931 -1.6228089999999999 0 2.3378269999999999 -0.64890300000000001 -0.751722 0
		 -151.863821 302.046718 59.510112999999997 1;
	setAttr ".radi" 0.63190968990325924;
	setAttr -k on ".MaxHandle" 39;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger1" -p "Bip01_R_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 12.355060577392578 -0.788360595703125 4.8366241455078125 ;
	setAttr ".r" -type "double3" -15.836849709682806 -18.974370259230266 16.987350607413891 ;
	setAttr ".s" -type "double3" 1.0000003230899479 1.0000000596593139 1.0000002002838713 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.50777000000000005 -1.7707569999999999 1.748769 0
		 1.7909090000000001 -1.4993099999999999 -0.99815600000000004 0 1.7281249999999999 1.033485 1.5482549999999999 0
		 -170.91681500000001 299.56194799999997 52.682040999999998 1;
	setAttr ".radi" 1.1010934925079348;
	setAttr -k on ".MaxHandle" 40;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger11" -p "Bip01_R_Finger1";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 5.2432937622070312 1.52587890625e-005 -7.62939453125e-006 ;
	setAttr ".r" -type "double3" 2.8174533646395497e-005 1.5367933395279034e-005 18.670817752443298 ;
	setAttr ".s" -type "double3" 0.99999949487351614 0.99999988215987368 0.99999976158158299 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.092276499999999997 -2.1575419999999998 1.337197 0
		 1.8592139999999999 -0.85353299999999999 -1.5054590000000001 0 1.7281230000000001 1.0334859999999999 1.548257 0
		 -173.57921099999999 290.27732099999997 61.851345999999999 1;
	setAttr ".radi" 0.63700670242309565;
	setAttr -k on ".MaxHandle" 41;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger12" -p "Bip01_R_Finger11";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.0333633422851562 -1.52587890625e-005 3.814697265625e-006 ;
	setAttr ".r" -type "double3" -2.0917454314640961e-005 3.7566031379440142e-005 8.7861044594445374 ;
	setAttr ".s" -type "double3" 1.0000002410590725 1.0000000008858883 1.0000002384189792 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.37518000000000001 -2.2625989999999998 1.0915509999999999 0
		 1.8233010000000001 -0.513961 -1.692045 0 1.7281249999999999 1.0334840000000001 1.548257 0
		 -173.29932500000001 283.73271999999997 65.907576000000006 1;
	setAttr ".radi" 0.63700670242309565;
	setAttr -k on ".MaxHandle" 42;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger2" -p "Bip01_R_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 12.988407135009766 -1.183319091796875 1.3129653930664063 ;
	setAttr ".r" -type "double3" 2.0693093640608464 -5.9643314706775907 16.64876466265104 ;
	setAttr ".s" -type "double3" 0.99999993840375934 0.99999994909266843 0.99999996207735697 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.77186500000000002 -2.0343849999999999 1.3103819999999999 0
		 2.2251919999999998 -1.1372150000000001 -0.454818 0 0.95096999999999998 1.009762 2.1278250000000001 0
		 -175.903953 296.52246300000002 45.640135999999998 1;
	setAttr ".radi" 1.205727496147156;
	setAttr -k on ".MaxHandle" 43;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger21" -p "Bip01_R_Finger2";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 5.7415657043457031 7.62939453125e-006 7.62939453125e-006 ;
	setAttr ".r" -type "double3" -1.7075470093537791e-005 4.6103758040295962e-005 18.939864194372479 ;
	setAttr ".s" -type "double3" 1.0000004090186112 1.0000001658226041 1.0000000000003126 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.0078335499999999999 -2.2933569999999999 1.0918140000000001 0
		 2.3552490000000001 -0.41533399999999998 -0.85551200000000005 0 0.95096899999999995 1.00976 2.1278260000000002 0
		 -180.33564000000001 284.84191600000003 53.163780000000003 1;
	setAttr ".radi" 0.7486838579177858;
	setAttr -k on ".MaxHandle" 44;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger22" -p "Bip01_R_Finger21";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.5651702880859375 -7.62939453125e-006 -7.62939453125e-006 ;
	setAttr ".r" -type "double3" 8.8579039914891362e-006 -1.707548015144437e-005 11.691655040531368 ;
	setAttr ".s" -type "double3" 0.99999957679595675 0.99999972774277146 1.0000000000000597 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.46960800000000003 -2.329939 0.89579600000000004 0
		 2.3079700000000001 0.058019099999999997 -1.059013 0 0.95096899999999995 1.0097609999999999 2.1278250000000001 0
		 -180.363584 276.665729 57.056265000000003 1;
	setAttr ".radi" 0.7486838579177858;
	setAttr -k on ".MaxHandle" 45;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger3" -p "Bip01_R_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 12.939456939697266 -0.7145233154296875 -2.3609809875488281 ;
	setAttr ".r" -type "double3" 15.468644174246331 6.8025322632304315 26.076837105564895 ;
	setAttr ".s" -type "double3" 1.000000138399171 1.0000001595580146 1.0000000056081628 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.61269700000000005 -2.3603079999999999 0.71073799999999998 0
		 2.4540130000000002 -0.65311900000000001 -0.053460899999999999 0 0.232433 0.67378099999999996 2.4379490000000001 0
		 -178.437926 293.03288900000001 37.278436999999997 1;
	setAttr ".radi" 1.0052832555770874;
	setAttr -k on ".MaxHandle" 46;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger31" -p "Bip01_R_Finger3";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 4.7870559692382812 0 3.814697265625e-006 ;
	setAttr ".r" -type "double3" 1.2926668708602822e-005 1.8783023406571253e-005 14.875987723296889 ;
	setAttr ".s" -type "double3" 0.9999998302171178 0.9999998378681737 0.99999994039540141 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.037851299999999997 -2.4488729999999999 0.67319099999999998 0
		 2.5290599999999999 -0.025272599999999999 -0.23413500000000001 0 0.232433 0.67378000000000005 2.4379490000000001 0
		 -181.37094500000001 281.733947 40.680791999999997 1;
	setAttr ".radi" 0.68097428083419798;
	setAttr -k on ".MaxHandle" 47;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger32" -p "Bip01_R_Finger31";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.24273681640625 0 0 ;
	setAttr ".r" -type "double3" -1.8356132047578396e-005 8.537735927825254e-006 13.908471745038685 ;
	setAttr ".s" -type "double3" 1.0000000626267573 1.0000000733722449 0.99999994039537565 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.64465600000000001 -2.3831500000000001 0.59717399999999998 0
		 2.4458120000000001 0.56410800000000005 -0.38908700000000002 0 0.232434 0.67378000000000005 2.4379490000000001 0
		 -181.2482 273.79289999999997 42.863773999999999 1;
	setAttr ".radi" 0.68097428083419798;
	setAttr -k on ".MaxHandle" 48;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger4" -p "Bip01_R_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 11.267044067382812 0.47991943359375 -5.7823066711425781 ;
	setAttr ".r" -type "double3" 29.280139118999067 16.422314667267376 29.54303399332025 ;
	setAttr ".s" -type "double3" 1.0000000993654021 1.0000002219559081 1.0000000366619102 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.61644100000000002 -2.4494379999999998 0.26805899999999999 0
		 2.4247320000000001 -0.55382799999999999 0.51532100000000003 0 -0.43849900000000003 0.38095899999999999 2.4726889999999999 0
		 -177.013924 291.23418099999998 27.403952 1;
	setAttr ".radi" 0.80888665437698359;
	setAttr -k on ".MaxHandle" 49;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger41" -p "Bip01_R_Finger4";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.851837158203125 7.62939453125e-006 0 ;
	setAttr ".r" -type "double3" 7.5238810737562051e-006 -5.9764136247280099e-006 14.793380536307032 ;
	setAttr ".s" -type "double3" 1.0000003177546397 0.9999998915235363 1.0000000000000089 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.023109000000000001 -2.5096579999999999 0.39075300000000002 0
		 2.501757 0.089955099999999996 0.42979400000000001 0 -0.43849900000000003 0.38095899999999999 2.4726889999999999 0
		 -179.38833299999999 281.79933 28.436478999999999 1;
	setAttr ".radi" 0.45876216888427751;
	setAttr -k on ".MaxHandle" 50;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger42" -p "Bip01_R_Finger41";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.1845779418945312 -1.52587890625e-005 -7.62939453125e-006 ;
	setAttr ".r" -type "double3" -4.4823124561614569e-006 -1.5367927802612943e-005 16.480359216952039 ;
	setAttr ".s" -type "double3" 0.99999985879136744 0.99999981854446973 0.99999982118611352 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.73187400000000002 -2.3810340000000001 0.49662699999999999 0
		 2.3924210000000001 0.79821600000000004 0.30128700000000003 0 -0.4385 0.38095899999999999 2.4726880000000002 0
		 -179.33787100000001 276.316777 29.290096999999999 1;
	setAttr ".radi" 0.45876216888427751;
	setAttr -k on ".MaxHandle" 51;
	setAttr ".fbxID" 5;
createNode joint -n "Gundummy" -p "Bip01_R_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" -7.62939453125e-006 -4.57763671875e-005 3.814697265625e-006 ;
	setAttr ".r" -type "double3" -4.6103785141579859e-005 1.8783013500205175e-005 6.830186727347597e-006 ;
	setAttr ".s" -type "double3" 1.0000003576279295 0.99999982118638986 0.99999970197719856 ;
	setAttr ".ssc" no;
	setAttr ".radi" 1.0307666598237119e-005;
	setAttr -k on ".MaxHandle" 52;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Foretwist" -p "Bip01_R_UpperArm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 28.518928527832031 1.9073486328125e-006 -1.52587890625e-005 ;
	setAttr ".r" -type "double3" -0.9377704991548016 5.1226421274937659e-006 -22.787036963018586 ;
	setAttr ".s" -type "double3" 0.9999999512001444 0.99999998806490431 0.99999970483236988 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.5793360000000001 -1.537382 1.2624390000000001 0
		 -0.93075200000000002 -0.85353299999999999 -2.203811 0 1.7581230000000001 -1.8329040000000001 -0.032640200000000001 0
		 -116.64121400000001 353.792979 -4.3980699999999997 1;
	setAttr ".radi" 2.6117984962463385;
	setAttr -k on ".MaxHandle" 53;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Foretwist1" -p "Bip01_R_Foretwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 12.437145233154297 0 0 ;
	setAttr ".r" -type "double3" -0.93775000055293634 -6.3179227227914706e-005 5.1226400455093565e-005 ;
	setAttr ".s" -type "double3" 1.0000003576288763 1.0000000018543864 1.0000003032519997 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.5793349999999999 -1.5373859999999999 1.262437 0
		 -0.959399 -0.82342000000000004 -2.2029830000000001 0 1.7426569999999999 -1.8466260000000001 -0.068705100000000005 0
		 -136.28361899999999 334.672324 11.303048 1;
	setAttr ".radi" 2.6117984962463385;
	setAttr -k on ".MaxHandle" 54;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_RUpArmTwist" -p "Bip01_R_Clavicle";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 18.740150451660156 0 0 ;
	setAttr ".r" -type "double3" -6.7762432955420184 -17.256356515979139 -3.6481161428648923 ;
	setAttr ".s" -type "double3" 0.99999977808228757 1.000000247477846 0.99999984308453682 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.8053630000000001 -1.7595449999999999 0.31026199999999998 0
		 -0.21807199999999999 -0.220775 -2.520972 0 1.7733319999999999 -1.8184769999999999 0.0058550499999999997 0
		 -65.154143000000005 403.97328800000003 -13.246409 1;
	setAttr ".radi" 2.9944868946075447;
	setAttr -k on ".MaxHandle" 55;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_RUpArmTwist1" -p "Bip01_RUpArmTwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 14.25946044921875 1.9073486328125e-006 0 ;
	setAttr ".r" -type "double3" -0.027539317329487053 5.1226382135118261e-005 -6.4032977668914881e-007 ;
	setAttr ".s" -type "double3" 1.000000715256137 1.0000002347223746 1.0000003539209918 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.805366 -1.759544 0.31026199999999998 0 -0.21892400000000001 -0.21990100000000001 -2.520975 0
		 1.773226 -1.8185849999999999 0.0046438800000000004 0 -90.897649000000001 378.88311399999998 -8.8222419999999993 1;
	setAttr ".radi" 2.9944868946075447;
	setAttr -k on ".MaxHandle" 56;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_LThighTwist" -p "Bip01_Spine";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" -8.78253173828125 -0.23029947280883789 11.00208568572998 ;
	setAttr ".r" -type "double3" 172.4382631809905 -5.5779061205699971 -177.19596833468918 ;
	setAttr ".s" -type "double3" 1.0000001295162955 0.99999984382977225 0.99999998254859934 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.24688499999999999 -2.5273870000000001 -0.054426000000000002 0
		 0.33266800000000002 -0.0217282 2.518027 0 -2.505989 -0.25187799999999999 0.32890399999999997 0
		 27.945298000000001 277.86429900000002 -2.2416e-005 1;
	setAttr ".radi" 5.4371494102478035;
	setAttr -k on ".MaxHandle" 57;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_LThighTwist1" -p "Bip01_LThighTwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 25.891181945800781 -7.7486038208007813e-007 5.7220458984375e-006 ;
	setAttr ".r" -type "double3" 0.83393390041638338 -1.5794812455654086e-005 -7.4705194047014464e-007 ;
	setAttr ".s" -type "double3" 1.000000000000038 0.99999988389959038 0.99999976546203295 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.24688499999999999 -2.5273870000000001 -0.054426000000000002 0
		 0.29615900000000001 -0.025391799999999999 2.5225469999999999 0 -2.5105650000000002 -0.25153399999999998 0.29221999999999998 0
		 34.337434000000002 212.42724699999999 -1.4091769999999999 1;
	setAttr ".radi" 5.4371494102478035;
	setAttr -k on ".MaxHandle" 58;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_RThighTwist" -p "Bip01_Spine";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" -8.7825241088867187 -0.23027396202087402 -11.002081871032715 ;
	setAttr ".r" -type "double3" -172.43840853195854 5.5778978331235161 -177.19598154004086 ;
	setAttr ".s" -type "double3" 0.99999992422177075 0.99999969302986635 0.99999997514822248 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.24688599999999999 -2.5273870000000001 -0.054425399999999999 0
		 -0.33266000000000001 -0.0217282 2.5180280000000002 0 -2.5059900000000002 0.25187799999999999 -0.32889600000000002 0
		 -27.945292999999999 277.86431900000002 4.7642400000000003e-005 1;
	setAttr ".radi" 5.4371494102478035;
	setAttr -k on ".MaxHandle" 59;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_RThighTwist1" -p "Bip01_RThighTwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 25.891189575195313 -1.0728836059570313e-006 -5.7220458984375e-006 ;
	setAttr ".r" -type "double3" -0.83394186303036621 0 5.3360859251834732e-007 ;
	setAttr ".s" -type "double3" 0.99999988079071056 1.0000001243668135 0.99999982480278804 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.24688599999999999 -2.5273870000000001 -0.054425300000000003 0
		 -0.29615200000000003 -0.025391799999999999 2.522548 0 -2.5105659999999999 0.25153500000000001 -0.292213 0
		 -34.337451000000001 212.427266 -1.4090910000000001 1;
	setAttr ".radi" 5.4371494102478035;
	setAttr -k on ".MaxHandle" 60;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Thigh" -p "Bip01_Pelvis";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 0 1.8400081899017096e-005 11.002087593078613 ;
	setAttr ".r" -type "double3" 174.10625510207953 -5.5778730033738659 -178.76644091646233 ;
	setAttr ".s" -type "double3" 1.0000002223489739 1.0000004559471316 1.0000001738870989 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.24688419777104931 -2.5273876710322756 -0.054422840046680014 0
		 0.25958865931805891 -0.029046920910554823 2.5265340586396738 0 -2.5146098445494354 -0.25113727503822098 0.2554762451557957 0
		 27.945299155153787 277.86429916381837 -2.3221919782706393e-005 1;
	setAttr ".radi" 10.87430042266846;
	setAttr -k on ".MaxHandle" 61;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Calf" -p "Bip01_L_Thigh";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 51.782379150390625 3.5762786865234375e-007 -1.1444091796875e-005 ;
	setAttr ".r" -type "double3" -1.907651286151064e-005 1.1952829630450466e-005 -3.0928170589834152 ;
	setAttr ".s" -type "double3" 1.0000001185553529 0.9999995830959354 1.0000001192093704 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.23251939831501095 -2.5221394444070295 -0.19065932981669581 0
		 0.27253157569552305 -0.16536619920485626 2.5199165701512092 0 -2.5146100050684841 -0.25113788619375266 0.25547707483787596 0
		 40.72957916063632 146.99015538605238 -2.818169379792641 1;
	setAttr ".radi" 9.3799698257446309;
	setAttr -k on ".MaxHandle" 62;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Foot" -p "Bip01_L_Calf";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 44.666515350341797 1.1920928955078125e-006 -5.7220458984375e-006 ;
	setAttr ".r" -type "double3" -0.046556133429792784 -5.6743089942777516 3.7513631482461727 ;
	setAttr ".s" -type "double3" 0.99999991380956732 1.0000001006286001 0.99999990496362223 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0 -2.54 0 0 0.25878800000000002 0 2.5267819999999999 0
		 -2.5267819999999999 0 0.25878800000000002 0 51.115436000000003 34.335017000000001 -11.334562999999999 1;
	setAttr ".radi" 4.9470831871032717;
	setAttr -k on ".MaxHandle" 63;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Toe0" -p "Bip01_L_Foot";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 13.581253051757812 19.248559951782227 -1.1444091796875e-005 ;
	setAttr ".r" -type "double3" 2.8380092321482364e-005 1.750236183460092e-005 89.999988900941275 ;
	setAttr ".s" -type "double3" 0.99999988079077584 0.99999976158155579 1.0000000000000973 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.25878899999999999 -5.6773400000000003e-008 2.5267819999999999 0
		 -7.4725499999999995e-007 2.54 1.3360300000000001e-007 0 -2.5267819999999999 -7.5697900000000007e-007 0.25878899999999999 0
		 56.096755000000002 -0.161361 37.302366999999997 1;
	setAttr ".radi" 4.9470831871032717;
	setAttr -k on ".MaxHandle" 64;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_LCalfTwist" -p "Bip01_L_Thigh";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 51.782379150390625 3.5762786865234375e-007 -1.1444091796875e-005 ;
	setAttr ".r" -type "double3" 0.10855694186832024 3.4150951943646268e-006 -3.0928186196649996 ;
	setAttr ".s" -type "double3" 0.99999982156917622 0.99999964956450282 1.0000001259993103 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.232519 -2.522138 -0.190662 0 0.26776699999999998 -0.16584499999999999 2.5203959999999999 0
		 -2.5151219999999999 -0.25082399999999999 0.25070300000000001 0 40.729588 146.99017499999999 -2.818333 1;
	setAttr ".radi" 4.6899845123291017;
	setAttr -k on ".MaxHandle" 65;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_LCalfTwist1" -p "Bip01_LCalfTwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 22.333263397216797 4.76837158203125e-007 -9.5367431640625e-006 ;
	setAttr ".r" -type "double3" 0.10863024744330196 2.7320750166274371e-005 5.5495273775249111e-006 ;
	setAttr ".s" -type "double3" 1.0000002384186975 1.0000000091837387 0.99999988992080846 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.23252 -2.522138 -0.190662 0 0.26299299999999998 -0.16632 2.520867 0
		 -2.515625 -0.25051000000000001 0.245918 0 45.922516999999999 90.662605999999997 -7.0764490000000002 1;
	setAttr ".radi" 4.6899845123291017;
	setAttr -k on ".MaxHandle" 66;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Thigh" -p "Bip01_Pelvis";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 0 -8.8364322436973453e-006 -11.002087593078613 ;
	setAttr ".r" -type "double3" -174.1061065519385 5.577902528700748 -178.76642672492332 ;
	setAttr ".s" -type "double3" 1.0000001582045204 1.0000002407679043 1.0000002411587441 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.24688575711736527 -2.5273873682406971 -0.054422223721916296 0
		 -0.2595824601742131 -0.029046755595267724 2.5265341479951489 0 -2.5146104932366096 0.25113872603402365 -0.25547013263266405 0
		 -27.945299155092975 277.86429916381837 4.7513587011408012e-005 1;
	setAttr ".radi" 10.874301223754882;
	setAttr -k on ".MaxHandle" 67;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Calf" -p "Bip01_R_Thigh";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 51.782382965087891 -5.9604644775390625e-008 3.814697265625e-006 ;
	setAttr ".r" -type "double3" 2.0223762092271748e-005 1.707547800784626e-006 -3.0928187750462128 ;
	setAttr ".s" -type "double3" 0.99999970233252766 1.0000000570276375 0.99999976158148673 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.23252058538405612 -2.5221381561270459 -0.19065865441794855 0
		 -0.27252565618973534 -0.16536616667750959 2.5199178760745902 0 -2.5146098044430389 0.25113864936179942 -0.25547096686420728 0
		 -40.729641555775508 146.9901595202025 -2.8180660421273358 1;
	setAttr ".radi" 9.3799706268310565;
	setAttr -k on ".MaxHandle" 68;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Foot" -p "Bip01_R_Calf";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 44.666542053222656 -2.384185791015625e-007 0 ;
	setAttr ".r" -type "double3" 0.046566952705208317 5.6743099479106585 3.7513358712926386 ;
	setAttr ".s" -type "double3" 1.0000004244894483 1.0000002524345488 1.0000005871117097 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0 -2.54 0 0 -0.25878200000000001 0 2.5267840000000001 0
		 -2.5267840000000001 0 -0.25878200000000001 0 -51.115518999999999 34.334997000000001 -11.334433000000001 1;
	setAttr ".radi" 4.9470831871032717;
	setAttr -k on ".MaxHandle" 69;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Toe0" -p "Bip01_R_Foot";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 13.581240653991699 19.248565673828125 -1.9073486328125e-006 ;
	setAttr ".r" -type "double3" -1.4302654718417054e-005 -6.4033046368854159e-006 90.000041762656522 ;
	setAttr ".s" -type "double3" 0.99999964237240324 0.9999997615817019 0.99999952316285889 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.25878299999999999 1.37365e-006 2.526783 0 5.5412300000000002e-007 2.54 -1.3240799999999998e-006 0
		 -2.526783 4.1633800000000003e-007 -0.25878299999999999 0 -56.096702000000001 -0.16136900000000001 37.302520000000001 1;
	setAttr ".radi" 4.9470831871032717;
	setAttr -k on ".MaxHandle" 70;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_RCalfTwist" -p "Bip01_R_Thigh";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 51.782382965087891 -5.9604644775390625e-008 3.814697265625e-006 ;
	setAttr ".r" -type "double3" -0.10855005953718778 1.4941042373612592e-005 -3.0928181645241777 ;
	setAttr ".s" -type "double3" 0.9999997614484023 0.9999998839917692 1.0000000661698047 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.23252 -2.522138 -0.190662 0 -0.26776 -0.16584499999999999 2.520397 0
		 -2.5151219999999999 0.25082500000000002 -0.250695 0 -40.729635999999999 146.99016499999999 -2.8182299999999998 1;
	setAttr ".radi" 4.6899869155883804;
	setAttr -k on ".MaxHandle" 71;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_RCalfTwist1" -p "Bip01_RCalfTwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 22.333274841308594 -4.76837158203125e-007 3.814697265625e-006 ;
	setAttr ".r" -type "double3" -0.10863644377422846 -1.4514150256055247e-005 -4.2688677223692811e-007 ;
	setAttr ".s" -type "double3" 1.0000001192093215 0.99999994978403051 0.99999989019895941 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.23252100000000001 -2.522138 -0.190662 0 -0.26299099999999997 -0.16632 2.520867 0
		 -2.515625 0.25051000000000001 -0.245916 0 -45.922580000000004 90.662566999999996 -7.076333 1;
	setAttr ".radi" 4.6899869155883804;
	setAttr -k on ".MaxHandle" 72;
	setAttr ".fbxID" 5;
createNode lightLinker -s -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
createNode displayLayerManager -n "layerManager";
createNode displayLayer -n "defaultLayer";
createNode renderLayerManager -n "renderLayerManager";
createNode renderLayer -n "defaultRenderLayer";
	setAttr ".g" yes;
createNode phong -n "Guard_NoRain_Mat";
	setAttr ".dc" 1;
	setAttr ".ambc" -type "float3" 0.588 0.588 0.588 ;
	setAttr ".sc" -type "float3" 0 0 0 ;
	setAttr ".rfl" 1;
	setAttr ".cp" 2;
createNode shadingEngine -n "Louie_Green_Hood_on_MeshSG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo1";
createNode phong -n "Guard_A_Head_A2_FaceFX_Mat";
	setAttr ".dc" 1;
	setAttr ".ambc" -type "float3" 0.588 0.588 0.588 ;
	setAttr ".sc" -type "float3" 0 0 0 ;
	setAttr ".rfl" 1;
	setAttr ".cp" 2;
createNode shadingEngine -n "Louie_Green_Hood_on_MeshSG1";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo2";
createNode file -n "Guard_NoRain_Mat_ncl1_1";
	setAttr ".ftn" -type "string" "C:/Project/NagaGame/Arts/animations/Guard_A4_Raincoat_D.tga";
createNode place2dTexture -n "place2dTexture1";
createNode file -n "Guard_A_Head_A2_FaceFX_Mat_ncl1_1";
	setAttr ".ftn" -type "string" "Guard_A_Head_A2_FaceFX_Mat";
createNode place2dTexture -n "place2dTexture2";
createNode dagPose -n "bindPose1";
	setAttr -s 70 ".wm";
	setAttr -s 70 ".xm";
	setAttr ".xm[0]" -type "matrix" "xform" 2.5399998486065893 2.5399998486065893 2.54 0
		 -0 -1.5707949558880989 0 0 277.86429916381837 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
		 0 0 0 0 1 -0.70710678118654746 0 0 0.70710678118654768 1 1 1 no;
	setAttr ".xm[1]" -type "matrix" "xform" 0.99999994039613904 0.99999994039681228 0.99999994039599827 -1.5707951943066922
		 -1.5707963267948966 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.39370081086760178
		 0.39370081086760178 0.39370078740157477 no;
	setAttr ".xm[2]" -type "matrix" "xform" 1.0000000531109785 1.0000003509230919 1.0000002384214894 -2.442011061945879e-006
		 -3.2215210120518114e-007 -0.027409687169745216 0 8.7855453491210937 -0.010490705259144306
		 1.3066653536952799e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000596038645
		 1.0000000596031913 1.0000000596040053 no;
	setAttr ".xm[3]" -type "matrix" "xform" 1.0000001689446287 0.99999981119873882 1.0000000000023532 -2.1892369245176462e-006
		 1.6651615937328454e-007 -0.028204901204363544 0 13.172225952148437 -0.010484218597412109
		 -2.2624572011409327e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999994688902427
		 0.99999964907703121 0.9999997615785674 no;
	setAttr ".xm[4]" -type "matrix" "xform" 1.0000000024905971 1.0000001811124715 0.99999988079097701 -7.1029897622292964e-007
		 -9.4556596983295609e-008 -0.030011643812429788 0 13.1722412109375 -0.010482311248779297
		 2.4398104869760573e-007 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.9999998310553998
		 1.0000001888012968 0.99999999999764677 no;
	setAttr ".xm[5]" -type "matrix" "xform" 0.9999999638304804 0.99999984771845774 0.99999994039663542 1.5123392842905402e-006
		 4.8217124838210652e-007 -0.055834258718596728 0 13.171951293945313 -0.010468482971191406
		 -3.1250294796336675e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999999750940294
		 0.99999981888756129 1.0000001192090371 no;
	setAttr ".xm[6]" -type "matrix" "xform" 1.0000001295162955 0.99999984382977225 0.99999998254859934 3.0096154489287947
		 -0.097352827171090256 -3.0926530686999398 0 -8.78253173828125 -0.23029947280883789
		 11.00208568572998 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999994688902427
		 0.99999964907703121 0.9999997615785674 no;
	setAttr ".xm[7]" -type "matrix" "xform" 0.99999992422177075 0.99999969302986635 0.99999997514822248 -3.009617985781758
		 0.097352682527862583 -3.0926532991768054 0 -8.7825241088867187 -0.23027396202087402
		 -11.002081871032715 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999994688902427
		 0.99999964907703121 0.9999997615785674 no;
	setAttr ".xm[8]" -type "matrix" "xform" 1.0000002223489739 1.0000004559471316 1.0000001738870989 3.0387273998484639
		 -0.097352249166978738 -3.1200629860641769 0 0 1.8400081899017096e-005 11.002087593078613 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000596038645 1.0000000596031913
		 1.0000000596040053 no;
	setAttr ".xm[9]" -type "matrix" "xform" 1.0000001185553529 0.9999995830959354 1.0000001192093704 -3.3294795923240571e-007
		 2.0861623198129769e-007 -0.053979840841108261 0 51.782379150390625 3.5762786865234375e-007
		 -1.1444091796875e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999977765107551
		 0.99999954405307623 0.99999982611293126 no;
	setAttr ".xm[10]" -type "matrix" "xform" 0.99999991380956732 1.0000001006286001 0.99999990496362223 -0.00081255781534768444
		 -0.099035374725674849 0.065473638374875853 0 44.666515350341797 1.1920928955078125e-006
		 -5.7220458984375e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999988144466123
		 1.0000004169042385 0.99999988079064384 no;
	setAttr ".xm[11]" -type "matrix" "xform" 1.0000001582045204 1.0000002407679043 1.0000002411587441 -3.0387248071593986
		 0.097352764481145562 -3.1200627383750952 0 0 -8.8364322436973453e-006 -11.002087593078613 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000596038645 1.0000000596031913
		 1.0000000596040053 no;
	setAttr ".xm[12]" -type "matrix" "xform" 0.99999970233252766 1.0000000570276375 0.99999976158148673 3.5297123565015925e-007
		 2.9802331258879938e-008 -0.053979870792054248 0 51.782382965087891 -5.9604644775390625e-008
		 3.814697265625e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999984179550461
		 0.99999975923215367 0.99999975884131409 no;
	setAttr ".xm[13]" -type "matrix" "xform" 1.0000004244894483 1.0000002524345488 1.0000005871117097 0.00081274664732636551
		 0.099035391369708931 0.065473162302226773 0 44.666542053222656 -2.384185791015625e-007
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.000000297667561 0.99999994297236572
		 1.00000023841857 no;
	setAttr ".xm[14]" -type "matrix" "xform" 0.99999964237240324 0.9999997615817019 0.99999952316285889 -2.4962841661228006e-007
		 -1.1175874892187045e-007 1.5707970556907573 0 13.581240653991699 19.248565673828125
		 -1.9073486328125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999957551073193
		 0.99999974756551491 0.99999941288863503 no;
	setAttr ".xm[15]" -type "matrix" "xform" 0.99999988079077584 0.99999976158155579
		 1.0000000000000973 4.9532605302982827e-007 3.0547384088918126e-007 1.5707961330797779 0 13.581253051757812
		 19.248559951782227 -1.1444091796875e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000861904401
		 0.99999989937140998 1.0000000950363868 no;
	setAttr ".xm[16]" -type "matrix" "xform" 1.0000001978757871 1.000000252635032 1.0000001192099499 -2.4871831639066478e-007
		 -1.1667652835521814e-006 0.40597302139292468 0 15.716537475585937 0.37741661071777344
		 1.0183066478930414e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000361695209
		 1.0000001522815654 1.000000059603368 no;
	setAttr ".xm[17]" -type "matrix" "xform" 0.9999999536490306 0.99999969835479541 0.99999984348064808 -0.11577133413514405
		 -1.0882814494303381 2.837475123522323 0 -5.6907196044921875 0.033100128173828125
		 9.0506420135498047 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.9999998021242521
		 0.99999974736503183 0.9999998807900643 no;
	setAttr ".xm[18]" -type "matrix" "xform" 1.0000002342040111 1.0000000606910231 1.0000003578749088 0.11826795674914937
		 0.30118028365902227 -0.063671703820297493 0 18.740142822265625 -9.5367431640625e-006
		 3.0517578125e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000463509715
		 1.0000003016452956 1.0000001565193763 no;
	setAttr ".xm[19]" -type "matrix" "xform" 0.99999970197697474 1.0000000558887645 0.99999993668315523 0.0004806108689189578
		 -6.2584895665904175e-007 -7.4505828173705259e-008 0 14.25946044921875 -4.76837158203125e-007
		 -1.52587890625e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999976579604377
		 0.99999993930898057 0.9999996421252193 no;
	setAttr ".xm[20]" -type "matrix" "xform" 1.0000000404725218 1.0000003619287867 1.0000001257636708 0.11922917200318557
		 0.30117984452516405 -0.063671785651128771 0 18.740142822265625 -9.5367431640625e-006
		 3.0517578125e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000463509715
		 1.0000003016452956 1.0000001565193763 no;
	setAttr ".xm[21]" -type "matrix" "xform" 1.0000002028776087 0.99999978722044258 1.0000003020494674 0.016366932856979148
		 -0 -0.39770865139932521 0 28.518943786621094 9.5367431640625e-007 -3.0517578125e-005 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999995952747989 0.99999963807134429
		 0.99999987423634495 no;
	setAttr ".xm[22]" -type "matrix" "xform" 0.99999993318351255 0.99999979004873008
		 1.0000001366613578 -0.0019921889659453239 3.0246902471939815e-007 -0.26505057788486985 0 11.895172119140625
		 -3.814697265625e-006 -1.7111306078732014e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 
		0 0 0 1 0.9999998021242521 0.99999974736503183 0.9999998807900643 no;
	setAttr ".xm[23]" -type "matrix" "xform" 0.99999988079135049 0.99999994372082024
		 0.99999976468765306 0.016366915382959812 1.102686059794666e-006 2.5331977049347463e-007 0 12.437114715576172
		 -7.62939453125e-006 -1.52587890625e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999979712243248
		 1.0000002127796026 0.99999969795062382 no;
	setAttr ".xm[24]" -type "matrix" "xform" 1.000000027860952 0.99999951441406609 1.0000000223498076 0.11576075966752872
		 1.0882796378292605 2.8374657981508649 0 -5.6906890869140625 0.033145904541015625
		 -9.0506401062011719 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.9999998021242521
		 0.99999974736503183 0.9999998807900643 no;
	setAttr ".xm[25]" -type "matrix" "xform" 0.99999977808228757 1.000000247477846 0.99999984308453682 -0.11826775642339941
		 -0.30118023810181344 -0.063671638188148208 0 18.740150451660156 0 0 0 0 0 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999997213904879 1.0000004855861697 0.99999997765019288 no;
	setAttr ".xm[26]" -type "matrix" "xform" 1.000000715256137 1.0000002347223746 1.0000003539209918 -0.00048065176115108114
		 8.9406903214261636e-007 -1.1175862901785681e-008 0 14.25946044921875 1.9073486328125e-006
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000002219177617 0.99999975252221529
		 1.0000001569154877 no;
	setAttr ".xm[27]" -type "matrix" "xform" 0.9999998749595681 1.0000004012673778 0.99999999315980681 -0.11922878793944661
		 -0.30117973990315289 -0.063671661232616264 0 18.740150451660156 0 0 0 0 0 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999997213904879 1.0000004855861697 0.99999997765019288 no;
	setAttr ".xm[28]" -type "matrix" "xform" 0.9999999512001444 0.99999998806490431 0.99999970483236988 -0.016367182838321989
		 8.9406971526133352e-008 -0.39770882177832367 0 28.518928527832031 1.9073486328125e-006
		 -1.52587890625e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001250404476
		 0.99999959873278321 1.0000000068401933 no;
	setAttr ".xm[29]" -type "matrix" "xform" 1.0000003576288763 1.0000000018543864 1.0000003032519997 -0.016366825070227384
		 -1.1026855339927616e-006 8.940693518865043e-007 0 12.437145233154297 0 0 0 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000487998579 1.0000000119350958 1.0000002951677172 no;
	setAttr ".xm[30]" -type "matrix" "xform" 1.0000002605908522 1.0000001940956409 1.0000000000000071 -7.4505791507989324e-008
		 1.7881388772890945e-007 -0.3977087887806745 0 28.518943786621094 9.5367431640625e-007
		 -3.0517578125e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999995952747989
		 0.99999963807134429 0.99999987423634495 no;
	setAttr ".xm[31]" -type "matrix" "xform" 0.99999971654809927 0.99999983397048497
		 0.99999972897809009 -1.5215679262398571 0.076878369376020272 0.03074362236106435 0 24.874237060546875
		 1.1444091796875e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999973940921572
		 0.99999980590439674 0.99999999999999289 no;
	setAttr ".xm[32]" -type "matrix" "xform" 0.99999990226889646 0.99999985885898002
		 0.99999988079073932 -5.960465318805383e-008 -8.9406975900928492e-008 -0.39770855140652528 0 28.518928527832031
		 1.9073486328125e-006 -1.52587890625e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001250404476
		 0.99999959873278321 1.0000000068401933 no;
	setAttr ".xm[33]" -type "matrix" "xform" 0.99999998520877253 0.99999999761616654
		 1.0000001589933782 1.5215674824720247 -0.076878199227987831 0.030743060458079674 0 24.874259948730469
		 5.7220458984375e-006 3.0517578125e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000977311132
		 1.00000014114104 1.0000001192092749 no;
	setAttr ".xm[34]" -type "matrix" "xform" 1.000000000000038 0.99999988389959038 0.99999976546203295 0.014554892306264401
		 -2.7567148208617465e-007 -1.3038516044616699e-008 0 25.891181945800781 -7.7486038208007813e-007
		 5.7220458984375e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.9999998704837213
		 1.0000001561702521 1.000000017451401 no;
	setAttr ".xm[35]" -type "matrix" "xform" 0.99999982156917622 0.99999964956450282
		 1.0000001259993103 0.0018946760614982727 5.9604655410698432e-008 -0.053979868080140485 0 51.782379150390625
		 3.5762786865234375e-007 -1.1444091796875e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 
		0 0 0 1 0.99999977765107551 0.99999954405307623 0.99999982611293126 no;
	setAttr ".xm[36]" -type "matrix" "xform" 1.0000002384186975 1.0000000091837387 0.99999988992080846 0.0018959554851417713
		 4.76837044516276e-007 9.6857524667376055e-008 0 22.333263397216797 4.76837158203125e-007
		 -9.5367431640625e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001784308556
		 1.0000003504356201 0.99999987400070556 no;
	setAttr ".xm[37]" -type "matrix" "xform" 0.99999988079071056 1.0000001243668135 0.99999982480278804 -0.014555031280095467
		 -0 9.3132268563779405e-009 0 25.891189575195313 -1.0728836059570313e-006 -5.7220458984375e-006 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.000000075778235 1.0000003069702279
		 1.0000000248517782 no;
	setAttr ".xm[38]" -type "matrix" "xform" 0.9999997614484023 0.9999998839917692 1.0000000661698047 -0.001894555942159799
		 2.6077038309952847e-007 -0.053979860136434583 0 51.782382965087891 -5.9604644775390625e-008
		 3.814697265625e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999984179550461
		 0.99999975923215367 0.99999975884131409 no;
	setAttr ".xm[39]" -type "matrix" "xform" 1.0000001192093215 0.99999994978403051 0.99999989019895941 -0.0018960636315179819
		 -2.5331971009734209e-007 -7.4505797087455143e-009 0 22.333274841308594 -4.76837158203125e-007
		 3.814697265625e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000002385516547
		 1.0000001160082443 0.99999993383019958 no;
	setAttr ".xm[40]" -type "matrix" "xform" 1.0000005235781002 1.0000003346113244 1.0000006421406049 1.561606073850931
		 0.79467651782431015 0.5157619694185418 0 2.8994979858398438 0.53240966796875
		 -4.333038330078125 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.000000283451981
		 1.0000001660295426 1.0000002710219833 no;
	setAttr ".xm[41]" -type "matrix" "xform" 0.99999968039159182 0.99999935516906502
		 0.99999934434914295 -2.6822107444656078e-007 4.470349786915825e-007 0.18000994395112602 0 5.9040565490722656
		 -7.62939453125e-006 7.62939453125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999947642217391
		 0.99999966538878748 0.99999935785980743 no;
	setAttr ".xm[42]" -type "matrix" "xform" 1.000000200763222 1.0000001782113717 1.0000002384187163 -1.4901158538293799e-008
		 -4.3213358786506404e-007 0.17130172623777964 0 3.00909423828125 0 0 0 0 0 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000003196085103 1.0000006448313508 1.0000006556512868 no;
	setAttr ".xm[43]" -type "matrix" "xform" 1.0000001383163986 1.0000004022476627 1.0000002461959572 -0.036115778414829776
		 0.10409673650770257 0.29057471526399276 0 12.988391876220703 -1.183349609375
		 -1.3129692077636719 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.000000283451981
		 1.0000001660295426 1.0000002710219833 no;
	setAttr ".xm[44]" -type "matrix" "xform" 0.99999986820465092 0.99999998428256942
		 0.99999958276787837 4.1723251998569692e-007 4.1723256841705847e-007 0.33056471955649824 0 5.7415695190429687
		 1.52587890625e-005 -7.62939453125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999986168362054
		 0.99999959775249903 0.99999975380410344 no;
	setAttr ".xm[45]" -type "matrix" "xform" 1.0000001302794153 0.99999970358575585 1.0000000000002831 -4.4517232262171283e-007
		 -2.9802318505066688e-008 0.20405760875909204 0 3.565155029296875 -1.52587890625e-005
		 7.62939453125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001317953664
		 1.0000000157174309 1.0000004172322956 no;
	setAttr ".xm[46]" -type "matrix" "xform" 1.0000001780715493 1.0000000916909475 0.99999994229263101 0.27640492068945943
		 0.33116566255372137 0.29648532150325174 0 12.355052947998047 -0.7883758544921875
		 -4.8366165161132812 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.000000283451981
		 1.0000001660295426 1.0000002710219833 no;
	setAttr ".xm[47]" -type "matrix" "xform" 1.000000035586172 1.0000003083848088 1.0000001192095183 4.3213354135823445e-007
		 1.7881392796286965e-007 0.3258680992145091 0 5.2433128356933594 0 1.9073486328125e-006 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999982192848247 0.99999990830906094
		 1.0000000577073722 no;
	setAttr ".xm[48]" -type "matrix" "xform" 0.99999984410880671 0.99999991667053378
		 0.99999994039563411 -4.2468312941336958e-007 -4.4703490550424936e-007 0.15334583407964364 0 3.033355712890625
		 -1.52587890625e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999996441382921
		 0.99999969161528635 0.99999988079049595 no;
	setAttr ".xm[49]" -type "matrix" "xform" 1.0000000812367122 1.0000005685065965 1.0000002711644294 -0.26997830763474306
		 -0.118726712339716 0.45512569892765881 0 12.939460754394531 -0.7145538330078125
		 2.3609771728515625 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.000000283451981
		 1.0000001660295426 1.0000002710219833 no;
	setAttr ".xm[50]" -type "matrix" "xform" 1.0000003126838433 0.9999999440890931 1.0000000000000013 -2.1886081727134104e-007
		 -8.9406939206980698e-008 0.25963631721913277 0 4.7870559692382812 7.62939453125e-006
		 -3.814697265625e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.9999999187632943
		 0.99999943149372672 0.99999972883564414 no;
	setAttr ".xm[51]" -type "matrix" "xform" 0.99999955320642619 0.9999999653697319 0.9999997019768776 -2.7939678206025009e-007
		 2.2351751777390729e-007 0.2427485524540367 0 3.2427291870117187 -1.52587890625e-005
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999968731625455 1.0000000559109101
		 0.99999999999999867 no;
	setAttr ".xm[52]" -type "matrix" "xform" 1.0000001662727316 1.0000001676620343 1.0000002727634776 -0.51103386712734811
		 -0.28662319346341275 0.51562334575428126 0 11.267040252685547 0.47991943359375
		 5.7823066711425781 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.000000283451981
		 1.0000001660295426 1.0000002710219833 no;
	setAttr ".xm[53]" -type "matrix" "xform" 0.9999999219617417 1.0000001328968116 0.99999988079120883 -1.0542570143574608e-006
		 1.6391278592379328e-007 0.25819333320714505 0 3.8518218994140625 0 -7.62939453125e-006 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999983372729606 0.99999983233799383
		 0.9999997272365968 no;
	setAttr ".xm[54]" -type "matrix" "xform" 1.0000002862720332 1.0000000661031785 1.0000002384188384 7.1898098007628395e-007
		 1.9371504006482237e-007 0.28763671457245055 0 2.1845703125 3.814697265625e-006
		 3.814697265625e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000780382643
		 0.9999998671032061 1.0000001192088053 no;
	setAttr ".xm[55]" -type "matrix" "xform" 1.0000000354776202 1.0000001067088209 1.0000000531495399 -1.5616059799756796
		 -0.79467658963335086 0.51576253214646095 0 2.899505615234375 0.5324249267578125
		 4.3330459594726562 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000147912276
		 1.0000000023838336 0.99999984100664707 no;
	setAttr ".xm[56]" -type "matrix" "xform" 1.0000000535840212 0.999999941636738 1.0000000000001279 4.6193602396939675e-007
		 4.1723249107075184e-007 0.18000999720475502 0 5.9040489196777344 -1.52587890625e-005
		 -7.62939453125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999996452238105
		 0.99999989329119054 0.9999999468504629 no;
	setAttr ".xm[57]" -type "matrix" "xform" 0.99999972359407208 0.99999971851380376
		 0.9999998211860982 5.9604661553281959e-008 2.0861631437665466e-007 0.17130141560165618 0 3.00909423828125
		 1.52587890625e-005 -1.52587890625e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999994641598167
		 1.0000000583632653 0.9999999999998721 no;
	setAttr ".xm[58]" -type "matrix" "xform" 0.99999993840375934 0.99999994909266843
		 0.99999996207735697 0.03611626164521179 -0.10409722184363959 0.29057575975294364 0 12.988407135009766
		 -1.183319091796875 1.3129653930664063 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000147912276
		 1.0000000023838336 0.99999984100664707 no;
	setAttr ".xm[59]" -type "matrix" "xform" 1.0000004090186112 1.0000001658226041 1.0000000000003126 -2.9802317445805857e-007
		 8.0466237534597304e-007 0.33056299007238304 0 5.7415657043457031 7.62939453125e-006
		 7.62939453125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000615962445
		 1.0000000509073341 1.0000000379226444 no;
	setAttr ".xm[60]" -type "matrix" "xform" 0.99999957679595675 0.99999972774277146
		 1.0000000000000597 1.5459958947703319e-007 -2.9802335000164424e-007 0.20405787546466345 0 3.5651702880859375
		 -7.62939453125e-006 -7.62939453125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999959098155611
		 0.99999983417742344 0.99999999999968736 no;
	setAttr ".xm[61]" -type "matrix" "xform" 1.0000003230899479 1.0000000596593139 1.0000002002838713 -0.27640517057747305
		 -0.33116523451605812 0.29648519929003103 0 12.355060577392578 -0.788360595703125
		 4.8366241455078125 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000147912276
		 1.0000000023838336 0.99999984100664707 no;
	setAttr ".xm[62]" -type "matrix" "xform" 0.99999949487351614 0.99999988215987368
		 0.99999976158158299 4.9173837734352519e-007 2.682210369748103e-007 0.32586724381994309 0 5.2432937622070312
		 1.52587890625e-005 -7.62939453125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999967691015645
		 0.99999994034068962 0.99999979971616881 no;
	setAttr ".xm[63]" -type "matrix" "xform" 1.0000002410590725 1.0000000008858883 1.0000002384189792 -3.6507844892597871e-007
		 6.5565093447873775e-007 0.15334645124146376 0 3.0333633422851562 -1.52587890625e-005
		 3.814697265625e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000005051267391
		 1.0000001178401403 1.0000002384184739 no;
	setAttr ".xm[64]" -type "matrix" "xform" 1.000000138399171 1.0000001595580146 1.0000000056081628 0.26997877166003792
		 0.11872658546651263 0.45512666599833557 0 12.939456939697266 -0.7145233154296875
		 -2.3609809875488281 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000147912276
		 1.0000000023838336 0.99999984100664707 no;
	setAttr ".xm[65]" -type "matrix" "xform" 0.9999998302171178 0.9999998378681737 0.99999994039540141 2.2561293027964269e-007
		 3.278256019238299e-007 0.2596349652577859 0 4.7870559692382812 0 3.814697265625e-006 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999986160084819 0.99999984044201085
		 0.99999999439183718 no;
	setAttr ".xm[66]" -type "matrix" "xform" 1.0000000626267573 1.0000000733722449 0.99999994039537565 -3.2037494216109141e-007
		 1.4901160260636365e-007 0.24274862587152635 0 3.24273681640625 0 0 0 0 0 0 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001697829111 1.0000001621318526 1.0000000596046021 no;
	setAttr ".xm[67]" -type "matrix" "xform" 1.0000000993654021 1.0000002219559081 1.0000000366619102 0.51103483306852548
		 0.28662346174237274 0.51562321421204682 0 11.267044067382812 0.47991943359375
		 -5.7823066711425781 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000147912276
		 1.0000000023838336 0.99999984100664707 no;
	setAttr ".xm[68]" -type "matrix" "xform" 1.0000003177546397 0.9999998915235363 1.0000000000000089 1.3131649726553211e-007
		 -1.0430809521255257e-007 0.25819319785900224 0 3.851837158203125 7.62939453125e-006
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999990063460775 0.9999997780441412
		 0.99999996333809116 no;
	setAttr ".xm[69]" -type "matrix" "xform" 0.99999985879136744 0.99999981854446973
		 0.99999982118611352 -7.8231110463171416e-008 -2.6822093936437311e-007 0.28763653024720753 0 2.1845779418945312
		 -1.52587890625e-005 -7.62939453125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999968224546121
		 1.0000001084764754 0.99999999999999112 no;
	setAttr -s 70 ".m";
	setAttr -s 70 ".p";
	setAttr -s 70 ".g[0:69]" yes no no no no no no no yes yes no yes yes 
		no no no no no no no yes no no no no no no yes no no yes no yes no no no no no no 
		no no no no no no no no no no no no no no no no no no no no no no no no no no no 
		no no no no;
	setAttr ".bp" yes;
createNode script -n "uiConfigurationScriptNode";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"top\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n"
		+ "                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n"
		+ "                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n"
		+ "                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n            modelEditor -e \n                -pluginObjects \"gpuCacheDisplayFilter\" 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n"
		+ "            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n"
		+ "            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"side\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n"
		+ "                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n"
		+ "                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n"
		+ "            modelEditor -e \n                -pluginObjects \"gpuCacheDisplayFilter\" 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n"
		+ "            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n"
		+ "            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"front\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n"
		+ "                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n"
		+ "                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n"
		+ "                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n            modelEditor -e \n                -pluginObjects \"gpuCacheDisplayFilter\" 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n"
		+ "            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n"
		+ "            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n"
		+ "            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n"
		+ "                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 1\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n"
		+ "                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n"
		+ "                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n            modelEditor -e \n                -pluginObjects \"gpuCacheDisplayFilter\" 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n"
		+ "            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n"
		+ "            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n"
		+ "            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            outlinerEditor -e \n                -showShapes 0\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n"
		+ "                -showAttributes 0\n                -showConnected 0\n                -showAnimCurvesOnly 0\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 1\n                -showAssets 1\n                -showContainedOnly 1\n                -showPublishedAsConnected 0\n                -showContainerContents 1\n                -ignoreDagHierarchy 0\n                -expandConnections 0\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 0\n                -highlightActive 1\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"defaultSetFilter\" \n                -showSetMembers 1\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n"
		+ "                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 0\n                -ignoreHiddenAttribute 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -showShapes 0\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n            -showAttributes 0\n"
		+ "            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n"
		+ "            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"graphEditor\" -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n"
		+ "                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n"
		+ "                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n"
		+ "                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -classicMode 1\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n"
		+ "                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n"
		+ "                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n"
		+ "                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -classicMode 1\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dopeSheetPanel\" -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n"
		+ "                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n"
		+ "                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n"
		+ "                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n"
		+ "                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n"
		+ "                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"clipEditorPanel\" -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n"
		+ "                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"sequenceEditorPanel\" (localizedPanelLabel(\"Camera Sequencer\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"sequenceEditorPanel\" -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperGraphPanel\" -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n"
		+ "                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n"
		+ "                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n"
		+ "                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperShadePanel\" -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" == $panelName) {\n"
		+ "\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"visorPanel\" -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"nodeEditorPanel\" (localizedPanelLabel(\"Node Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"nodeEditorPanel\" -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -defaultPinnedState 0\n                -ignoreAssets 1\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n"
		+ "                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -keyReleaseCommand \"nodeEdKeyReleaseCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                $editorName;;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -defaultPinnedState 0\n                -ignoreAssets 1\n"
		+ "                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -keyReleaseCommand \"nodeEdKeyReleaseCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                $editorName;;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"createNodePanel\" (localizedPanelLabel(\"Create Node\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"createNodePanel\" -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Texture Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"polyTexturePlacementPanel\" -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"renderWindowPanel\" -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"blendShapePanel\" (localizedPanelLabel(\"Blend Shape\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\tblendShapePanel -unParent -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tblendShapePanel -edit -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynRelEdPanel\" -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n"
		+ "\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"relationshipPanel\" -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"referenceEditorPanel\" -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"componentEditorPanel\" -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynPaintScriptedPanelType\" -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"scriptEditorPanel\" -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-defaultImage \"\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"single\\\" -ps 1 100 100 $gMainPane;\"\n"
		+ "\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        setFocus `paneLayout -q -p1 $gMainPane`;\n        sceneUIReplacement -deleteRemaining;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 5 -size 12 -divisions 5 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 120 -ast 1 -aet 200 ";
	setAttr ".st" 6;
select -ne :time1;
	setAttr ".o" 1;
	setAttr ".unw" 1;
select -ne :renderPartition;
	setAttr -s 4 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 2 ".u";
select -ne :defaultRenderingList1;
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
select -ne :initialShadingGroup;
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultResolution;
	setAttr ".pa" 1;
select -ne :hardwareRenderGlobals;
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
select -ne :hardwareRenderingGlobals;
	setAttr ".otfna" -type "stringArray" 22 "NURBS Curves" "NURBS Surfaces" "Polygons" "Subdiv Surface" "Particles" "Particle Instance" "Fluids" "Strokes" "Image Planes" "UI" "Lights" "Cameras" "Locators" "Joints" "IK Handles" "Deformers" "Motion Trails" "Components" "Hair Systems" "Follicles" "Misc. UI" "Ornaments"  ;
	setAttr ".otfva" -type "Int32Array" 22 0 1 1 1 1 1
		 1 1 1 0 0 0 0 0 0 0 0 0
		 0 0 0 0 ;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
connectAttr "Bip01.s" "Bip01_Pelvis.is";
connectAttr "Bip01_Pelvis.s" "Bip01_Spine.is";
connectAttr "Bip01_Spine.s" "Bip01_Spine1.is";
connectAttr "Bip01_Spine1.s" "Bip01_Spine2.is";
connectAttr "Bip01_Spine2.s" "Bip01_Spine3.is";
connectAttr "Bip01_Spine3.s" "Bip01_Neck.is";
connectAttr "Bip01_Neck.s" "Bip01_Head.is";
connectAttr "Bip01_Neck.s" "Bip01_L_Clavicle.is";
connectAttr "Bip01_L_Clavicle.s" "Bip01_L_UpperArm.is";
connectAttr "Bip01_L_UpperArm.s" "Bip01_L_Forearm.is";
connectAttr "Bip01_L_Forearm.s" "Bip01_L_Hand.is";
connectAttr "Bip01_L_Hand.s" "Bip01_L_Finger0.is";
connectAttr "Bip01_L_Finger0.s" "Bip01_L_Finger01.is";
connectAttr "Bip01_L_Finger01.s" "Bip01_L_Finger02.is";
connectAttr "Bip01_L_Hand.s" "Bip01_L_Finger1.is";
connectAttr "Bip01_L_Finger1.s" "Bip01_L_Finger11.is";
connectAttr "Bip01_L_Finger11.s" "Bip01_L_Finger12.is";
connectAttr "Bip01_L_Hand.s" "Bip01_L_Finger2.is";
connectAttr "Bip01_L_Finger2.s" "Bip01_L_Finger21.is";
connectAttr "Bip01_L_Finger21.s" "Bip01_L_Finger22.is";
connectAttr "Bip01_L_Hand.s" "Bip01_L_Finger3.is";
connectAttr "Bip01_L_Finger3.s" "Bip01_L_Finger31.is";
connectAttr "Bip01_L_Finger31.s" "Bip01_L_Finger32.is";
connectAttr "Bip01_L_Hand.s" "Bip01_L_Finger4.is";
connectAttr "Bip01_L_Finger4.s" "Bip01_L_Finger41.is";
connectAttr "Bip01_L_Finger41.s" "Bip01_L_Finger42.is";
connectAttr "Bip01_L_Hand.s" "Gundummy02.is";
connectAttr "Bip01_L_UpperArm.s" "Bip01_L_Foretwist.is";
connectAttr "Bip01_L_Foretwist.s" "Bip01_L_Foretwist1.is";
connectAttr "Bip01_L_Clavicle.s" "Bip01_LUpArmTwist.is";
connectAttr "Bip01_LUpArmTwist.s" "Bip01_LUpArmTwist1.is";
connectAttr "Bip01_Neck.s" "Bip01_R_Clavicle.is";
connectAttr "Bip01_R_Clavicle.s" "Bip01_R_UpperArm.is";
connectAttr "Bip01_R_UpperArm.s" "Bip01_R_Forearm.is";
connectAttr "Bip01_R_Forearm.s" "Bip01_R_Hand.is";
connectAttr "Bip01_R_Hand.s" "Bip01_R_Finger0.is";
connectAttr "Bip01_R_Finger0.s" "Bip01_R_Finger01.is";
connectAttr "Bip01_R_Finger01.s" "Bip01_R_Finger02.is";
connectAttr "Bip01_R_Hand.s" "Bip01_R_Finger1.is";
connectAttr "Bip01_R_Finger1.s" "Bip01_R_Finger11.is";
connectAttr "Bip01_R_Finger11.s" "Bip01_R_Finger12.is";
connectAttr "Bip01_R_Hand.s" "Bip01_R_Finger2.is";
connectAttr "Bip01_R_Finger2.s" "Bip01_R_Finger21.is";
connectAttr "Bip01_R_Finger21.s" "Bip01_R_Finger22.is";
connectAttr "Bip01_R_Hand.s" "Bip01_R_Finger3.is";
connectAttr "Bip01_R_Finger3.s" "Bip01_R_Finger31.is";
connectAttr "Bip01_R_Finger31.s" "Bip01_R_Finger32.is";
connectAttr "Bip01_R_Hand.s" "Bip01_R_Finger4.is";
connectAttr "Bip01_R_Finger4.s" "Bip01_R_Finger41.is";
connectAttr "Bip01_R_Finger41.s" "Bip01_R_Finger42.is";
connectAttr "Bip01_R_Hand.s" "Gundummy.is";
connectAttr "Bip01_R_UpperArm.s" "Bip01_R_Foretwist.is";
connectAttr "Bip01_R_Foretwist.s" "Bip01_R_Foretwist1.is";
connectAttr "Bip01_R_Clavicle.s" "Bip01_RUpArmTwist.is";
connectAttr "Bip01_RUpArmTwist.s" "Bip01_RUpArmTwist1.is";
connectAttr "Bip01_Spine.s" "Bip01_LThighTwist.is";
connectAttr "Bip01_LThighTwist.s" "Bip01_LThighTwist1.is";
connectAttr "Bip01_Spine.s" "Bip01_RThighTwist.is";
connectAttr "Bip01_RThighTwist.s" "Bip01_RThighTwist1.is";
connectAttr "Bip01_Pelvis.s" "Bip01_L_Thigh.is";
connectAttr "Bip01_L_Thigh.s" "Bip01_L_Calf.is";
connectAttr "Bip01_L_Calf.s" "Bip01_L_Foot.is";
connectAttr "Bip01_L_Foot.s" "Bip01_L_Toe0.is";
connectAttr "Bip01_L_Thigh.s" "Bip01_LCalfTwist.is";
connectAttr "Bip01_LCalfTwist.s" "Bip01_LCalfTwist1.is";
connectAttr "Bip01_Pelvis.s" "Bip01_R_Thigh.is";
connectAttr "Bip01_R_Thigh.s" "Bip01_R_Calf.is";
connectAttr "Bip01_R_Calf.s" "Bip01_R_Foot.is";
connectAttr "Bip01_R_Foot.s" "Bip01_R_Toe0.is";
connectAttr "Bip01_R_Thigh.s" "Bip01_RCalfTwist.is";
connectAttr "Bip01_RCalfTwist.s" "Bip01_RCalfTwist1.is";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Louie_Green_Hood_on_MeshSG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Louie_Green_Hood_on_MeshSG1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Louie_Green_Hood_on_MeshSG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Louie_Green_Hood_on_MeshSG1.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "Guard_NoRain_Mat_ncl1_1.oc" "Guard_NoRain_Mat.c";
connectAttr "Guard_NoRain_Mat.oc" "Louie_Green_Hood_on_MeshSG.ss";
connectAttr "Louie_Green_Hood_on_MeshSG.msg" "materialInfo1.sg";
connectAttr "Guard_NoRain_Mat.msg" "materialInfo1.m";
connectAttr "Guard_NoRain_Mat_ncl1_1.msg" "materialInfo1.t" -na;
connectAttr "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.oc" "Guard_A_Head_A2_FaceFX_Mat.c"
		;
connectAttr "Guard_A_Head_A2_FaceFX_Mat.oc" "Louie_Green_Hood_on_MeshSG1.ss";
connectAttr "Louie_Green_Hood_on_MeshSG1.msg" "materialInfo2.sg";
connectAttr "Guard_A_Head_A2_FaceFX_Mat.msg" "materialInfo2.m";
connectAttr "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.msg" "materialInfo2.t" -na;
connectAttr "place2dTexture1.o" "Guard_NoRain_Mat_ncl1_1.uv";
connectAttr "place2dTexture1.ofu" "Guard_NoRain_Mat_ncl1_1.ofu";
connectAttr "place2dTexture1.ofv" "Guard_NoRain_Mat_ncl1_1.ofv";
connectAttr "place2dTexture1.rf" "Guard_NoRain_Mat_ncl1_1.rf";
connectAttr "place2dTexture1.reu" "Guard_NoRain_Mat_ncl1_1.reu";
connectAttr "place2dTexture1.rev" "Guard_NoRain_Mat_ncl1_1.rev";
connectAttr "place2dTexture1.vt1" "Guard_NoRain_Mat_ncl1_1.vt1";
connectAttr "place2dTexture1.vt2" "Guard_NoRain_Mat_ncl1_1.vt2";
connectAttr "place2dTexture1.vt3" "Guard_NoRain_Mat_ncl1_1.vt3";
connectAttr "place2dTexture1.vc1" "Guard_NoRain_Mat_ncl1_1.vc1";
connectAttr "place2dTexture1.ofs" "Guard_NoRain_Mat_ncl1_1.fs";
connectAttr "place2dTexture2.o" "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.uv";
connectAttr "place2dTexture2.ofu" "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.ofu";
connectAttr "place2dTexture2.ofv" "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.ofv";
connectAttr "place2dTexture2.rf" "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.rf";
connectAttr "place2dTexture2.reu" "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.reu";
connectAttr "place2dTexture2.rev" "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.rev";
connectAttr "place2dTexture2.vt1" "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.vt1";
connectAttr "place2dTexture2.vt2" "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.vt2";
connectAttr "place2dTexture2.vt3" "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.vt3";
connectAttr "place2dTexture2.vc1" "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.vc1";
connectAttr "place2dTexture2.ofs" "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.fs";
connectAttr "Bip01.msg" "bindPose1.m[0]";
connectAttr "Bip01_Pelvis.msg" "bindPose1.m[1]";
connectAttr "Bip01_Spine.msg" "bindPose1.m[2]";
connectAttr "Bip01_Spine1.msg" "bindPose1.m[3]";
connectAttr "Bip01_Spine2.msg" "bindPose1.m[4]";
connectAttr "Bip01_Spine3.msg" "bindPose1.m[5]";
connectAttr "Bip01_LThighTwist.msg" "bindPose1.m[6]";
connectAttr "Bip01_RThighTwist.msg" "bindPose1.m[7]";
connectAttr "Bip01_L_Thigh.msg" "bindPose1.m[8]";
connectAttr "Bip01_L_Calf.msg" "bindPose1.m[9]";
connectAttr "Bip01_L_Foot.msg" "bindPose1.m[10]";
connectAttr "Bip01_R_Thigh.msg" "bindPose1.m[11]";
connectAttr "Bip01_R_Calf.msg" "bindPose1.m[12]";
connectAttr "Bip01_R_Foot.msg" "bindPose1.m[13]";
connectAttr "Bip01_R_Toe0.msg" "bindPose1.m[14]";
connectAttr "Bip01_L_Toe0.msg" "bindPose1.m[15]";
connectAttr "Bip01_Neck.msg" "bindPose1.m[16]";
connectAttr "Bip01_L_Clavicle.msg" "bindPose1.m[17]";
connectAttr "Bip01_LUpArmTwist.msg" "bindPose1.m[18]";
connectAttr "Bip01_LUpArmTwist1.msg" "bindPose1.m[19]";
connectAttr "Bip01_L_UpperArm.msg" "bindPose1.m[20]";
connectAttr "Bip01_L_Foretwist.msg" "bindPose1.m[21]";
connectAttr "Bip01_Head.msg" "bindPose1.m[22]";
connectAttr "Bip01_L_Foretwist1.msg" "bindPose1.m[23]";
connectAttr "Bip01_R_Clavicle.msg" "bindPose1.m[24]";
connectAttr "Bip01_RUpArmTwist.msg" "bindPose1.m[25]";
connectAttr "Bip01_RUpArmTwist1.msg" "bindPose1.m[26]";
connectAttr "Bip01_R_UpperArm.msg" "bindPose1.m[27]";
connectAttr "Bip01_R_Foretwist.msg" "bindPose1.m[28]";
connectAttr "Bip01_R_Foretwist1.msg" "bindPose1.m[29]";
connectAttr "Bip01_L_Forearm.msg" "bindPose1.m[30]";
connectAttr "Bip01_L_Hand.msg" "bindPose1.m[31]";
connectAttr "Bip01_R_Forearm.msg" "bindPose1.m[32]";
connectAttr "Bip01_R_Hand.msg" "bindPose1.m[33]";
connectAttr "Bip01_LThighTwist1.msg" "bindPose1.m[34]";
connectAttr "Bip01_LCalfTwist.msg" "bindPose1.m[35]";
connectAttr "Bip01_LCalfTwist1.msg" "bindPose1.m[36]";
connectAttr "Bip01_RThighTwist1.msg" "bindPose1.m[37]";
connectAttr "Bip01_RCalfTwist.msg" "bindPose1.m[38]";
connectAttr "Bip01_RCalfTwist1.msg" "bindPose1.m[39]";
connectAttr "Bip01_L_Finger0.msg" "bindPose1.m[40]";
connectAttr "Bip01_L_Finger01.msg" "bindPose1.m[41]";
connectAttr "Bip01_L_Finger02.msg" "bindPose1.m[42]";
connectAttr "Bip01_L_Finger2.msg" "bindPose1.m[43]";
connectAttr "Bip01_L_Finger21.msg" "bindPose1.m[44]";
connectAttr "Bip01_L_Finger22.msg" "bindPose1.m[45]";
connectAttr "Bip01_L_Finger1.msg" "bindPose1.m[46]";
connectAttr "Bip01_L_Finger11.msg" "bindPose1.m[47]";
connectAttr "Bip01_L_Finger12.msg" "bindPose1.m[48]";
connectAttr "Bip01_L_Finger3.msg" "bindPose1.m[49]";
connectAttr "Bip01_L_Finger31.msg" "bindPose1.m[50]";
connectAttr "Bip01_L_Finger32.msg" "bindPose1.m[51]";
connectAttr "Bip01_L_Finger4.msg" "bindPose1.m[52]";
connectAttr "Bip01_L_Finger41.msg" "bindPose1.m[53]";
connectAttr "Bip01_L_Finger42.msg" "bindPose1.m[54]";
connectAttr "Bip01_R_Finger0.msg" "bindPose1.m[55]";
connectAttr "Bip01_R_Finger01.msg" "bindPose1.m[56]";
connectAttr "Bip01_R_Finger02.msg" "bindPose1.m[57]";
connectAttr "Bip01_R_Finger2.msg" "bindPose1.m[58]";
connectAttr "Bip01_R_Finger21.msg" "bindPose1.m[59]";
connectAttr "Bip01_R_Finger22.msg" "bindPose1.m[60]";
connectAttr "Bip01_R_Finger1.msg" "bindPose1.m[61]";
connectAttr "Bip01_R_Finger11.msg" "bindPose1.m[62]";
connectAttr "Bip01_R_Finger12.msg" "bindPose1.m[63]";
connectAttr "Bip01_R_Finger3.msg" "bindPose1.m[64]";
connectAttr "Bip01_R_Finger31.msg" "bindPose1.m[65]";
connectAttr "Bip01_R_Finger32.msg" "bindPose1.m[66]";
connectAttr "Bip01_R_Finger4.msg" "bindPose1.m[67]";
connectAttr "Bip01_R_Finger41.msg" "bindPose1.m[68]";
connectAttr "Bip01_R_Finger42.msg" "bindPose1.m[69]";
connectAttr "bindPose1.w" "bindPose1.p[0]";
connectAttr "bindPose1.m[0]" "bindPose1.p[1]";
connectAttr "bindPose1.m[1]" "bindPose1.p[2]";
connectAttr "bindPose1.m[2]" "bindPose1.p[3]";
connectAttr "bindPose1.m[3]" "bindPose1.p[4]";
connectAttr "bindPose1.m[4]" "bindPose1.p[5]";
connectAttr "bindPose1.m[2]" "bindPose1.p[6]";
connectAttr "bindPose1.m[2]" "bindPose1.p[7]";
connectAttr "bindPose1.m[1]" "bindPose1.p[8]";
connectAttr "bindPose1.m[8]" "bindPose1.p[9]";
connectAttr "bindPose1.m[9]" "bindPose1.p[10]";
connectAttr "bindPose1.m[1]" "bindPose1.p[11]";
connectAttr "bindPose1.m[11]" "bindPose1.p[12]";
connectAttr "bindPose1.m[12]" "bindPose1.p[13]";
connectAttr "bindPose1.m[13]" "bindPose1.p[14]";
connectAttr "bindPose1.m[10]" "bindPose1.p[15]";
connectAttr "bindPose1.m[5]" "bindPose1.p[16]";
connectAttr "bindPose1.m[16]" "bindPose1.p[17]";
connectAttr "bindPose1.m[17]" "bindPose1.p[18]";
connectAttr "bindPose1.m[18]" "bindPose1.p[19]";
connectAttr "bindPose1.m[17]" "bindPose1.p[20]";
connectAttr "bindPose1.m[20]" "bindPose1.p[21]";
connectAttr "bindPose1.m[16]" "bindPose1.p[22]";
connectAttr "bindPose1.m[21]" "bindPose1.p[23]";
connectAttr "bindPose1.m[16]" "bindPose1.p[24]";
connectAttr "bindPose1.m[24]" "bindPose1.p[25]";
connectAttr "bindPose1.m[25]" "bindPose1.p[26]";
connectAttr "bindPose1.m[24]" "bindPose1.p[27]";
connectAttr "bindPose1.m[27]" "bindPose1.p[28]";
connectAttr "bindPose1.m[28]" "bindPose1.p[29]";
connectAttr "bindPose1.m[20]" "bindPose1.p[30]";
connectAttr "bindPose1.m[30]" "bindPose1.p[31]";
connectAttr "bindPose1.m[27]" "bindPose1.p[32]";
connectAttr "bindPose1.m[32]" "bindPose1.p[33]";
connectAttr "bindPose1.m[6]" "bindPose1.p[34]";
connectAttr "bindPose1.m[8]" "bindPose1.p[35]";
connectAttr "bindPose1.m[35]" "bindPose1.p[36]";
connectAttr "bindPose1.m[7]" "bindPose1.p[37]";
connectAttr "bindPose1.m[11]" "bindPose1.p[38]";
connectAttr "bindPose1.m[38]" "bindPose1.p[39]";
connectAttr "bindPose1.m[31]" "bindPose1.p[40]";
connectAttr "bindPose1.m[40]" "bindPose1.p[41]";
connectAttr "bindPose1.m[41]" "bindPose1.p[42]";
connectAttr "bindPose1.m[31]" "bindPose1.p[43]";
connectAttr "bindPose1.m[43]" "bindPose1.p[44]";
connectAttr "bindPose1.m[44]" "bindPose1.p[45]";
connectAttr "bindPose1.m[31]" "bindPose1.p[46]";
connectAttr "bindPose1.m[46]" "bindPose1.p[47]";
connectAttr "bindPose1.m[47]" "bindPose1.p[48]";
connectAttr "bindPose1.m[31]" "bindPose1.p[49]";
connectAttr "bindPose1.m[49]" "bindPose1.p[50]";
connectAttr "bindPose1.m[50]" "bindPose1.p[51]";
connectAttr "bindPose1.m[31]" "bindPose1.p[52]";
connectAttr "bindPose1.m[52]" "bindPose1.p[53]";
connectAttr "bindPose1.m[53]" "bindPose1.p[54]";
connectAttr "bindPose1.m[33]" "bindPose1.p[55]";
connectAttr "bindPose1.m[55]" "bindPose1.p[56]";
connectAttr "bindPose1.m[56]" "bindPose1.p[57]";
connectAttr "bindPose1.m[33]" "bindPose1.p[58]";
connectAttr "bindPose1.m[58]" "bindPose1.p[59]";
connectAttr "bindPose1.m[59]" "bindPose1.p[60]";
connectAttr "bindPose1.m[33]" "bindPose1.p[61]";
connectAttr "bindPose1.m[61]" "bindPose1.p[62]";
connectAttr "bindPose1.m[62]" "bindPose1.p[63]";
connectAttr "bindPose1.m[33]" "bindPose1.p[64]";
connectAttr "bindPose1.m[64]" "bindPose1.p[65]";
connectAttr "bindPose1.m[65]" "bindPose1.p[66]";
connectAttr "bindPose1.m[33]" "bindPose1.p[67]";
connectAttr "bindPose1.m[67]" "bindPose1.p[68]";
connectAttr "bindPose1.m[68]" "bindPose1.p[69]";
connectAttr "Bip01.bps" "bindPose1.wm[0]";
connectAttr "Bip01_Pelvis.bps" "bindPose1.wm[1]";
connectAttr "Bip01_Spine.bps" "bindPose1.wm[2]";
connectAttr "Bip01_Spine1.bps" "bindPose1.wm[3]";
connectAttr "Bip01_Spine2.bps" "bindPose1.wm[4]";
connectAttr "Bip01_Spine3.bps" "bindPose1.wm[5]";
connectAttr "Bip01_LThighTwist.bps" "bindPose1.wm[6]";
connectAttr "Bip01_RThighTwist.bps" "bindPose1.wm[7]";
connectAttr "Bip01_L_Thigh.bps" "bindPose1.wm[8]";
connectAttr "Bip01_L_Calf.bps" "bindPose1.wm[9]";
connectAttr "Bip01_L_Foot.bps" "bindPose1.wm[10]";
connectAttr "Bip01_R_Thigh.bps" "bindPose1.wm[11]";
connectAttr "Bip01_R_Calf.bps" "bindPose1.wm[12]";
connectAttr "Bip01_R_Foot.bps" "bindPose1.wm[13]";
connectAttr "Bip01_R_Toe0.bps" "bindPose1.wm[14]";
connectAttr "Bip01_L_Toe0.bps" "bindPose1.wm[15]";
connectAttr "Bip01_Neck.bps" "bindPose1.wm[16]";
connectAttr "Bip01_L_Clavicle.bps" "bindPose1.wm[17]";
connectAttr "Bip01_LUpArmTwist.bps" "bindPose1.wm[18]";
connectAttr "Bip01_LUpArmTwist1.bps" "bindPose1.wm[19]";
connectAttr "Bip01_L_UpperArm.bps" "bindPose1.wm[20]";
connectAttr "Bip01_L_Foretwist.bps" "bindPose1.wm[21]";
connectAttr "Bip01_Head.bps" "bindPose1.wm[22]";
connectAttr "Bip01_L_Foretwist1.bps" "bindPose1.wm[23]";
connectAttr "Bip01_R_Clavicle.bps" "bindPose1.wm[24]";
connectAttr "Bip01_RUpArmTwist.bps" "bindPose1.wm[25]";
connectAttr "Bip01_RUpArmTwist1.bps" "bindPose1.wm[26]";
connectAttr "Bip01_R_UpperArm.bps" "bindPose1.wm[27]";
connectAttr "Bip01_R_Foretwist.bps" "bindPose1.wm[28]";
connectAttr "Bip01_R_Foretwist1.bps" "bindPose1.wm[29]";
connectAttr "Bip01_L_Forearm.bps" "bindPose1.wm[30]";
connectAttr "Bip01_L_Hand.bps" "bindPose1.wm[31]";
connectAttr "Bip01_R_Forearm.bps" "bindPose1.wm[32]";
connectAttr "Bip01_R_Hand.bps" "bindPose1.wm[33]";
connectAttr "Bip01_LThighTwist1.bps" "bindPose1.wm[34]";
connectAttr "Bip01_LCalfTwist.bps" "bindPose1.wm[35]";
connectAttr "Bip01_LCalfTwist1.bps" "bindPose1.wm[36]";
connectAttr "Bip01_RThighTwist1.bps" "bindPose1.wm[37]";
connectAttr "Bip01_RCalfTwist.bps" "bindPose1.wm[38]";
connectAttr "Bip01_RCalfTwist1.bps" "bindPose1.wm[39]";
connectAttr "Bip01_L_Finger0.bps" "bindPose1.wm[40]";
connectAttr "Bip01_L_Finger01.bps" "bindPose1.wm[41]";
connectAttr "Bip01_L_Finger02.bps" "bindPose1.wm[42]";
connectAttr "Bip01_L_Finger2.bps" "bindPose1.wm[43]";
connectAttr "Bip01_L_Finger21.bps" "bindPose1.wm[44]";
connectAttr "Bip01_L_Finger22.bps" "bindPose1.wm[45]";
connectAttr "Bip01_L_Finger1.bps" "bindPose1.wm[46]";
connectAttr "Bip01_L_Finger11.bps" "bindPose1.wm[47]";
connectAttr "Bip01_L_Finger12.bps" "bindPose1.wm[48]";
connectAttr "Bip01_L_Finger3.bps" "bindPose1.wm[49]";
connectAttr "Bip01_L_Finger31.bps" "bindPose1.wm[50]";
connectAttr "Bip01_L_Finger32.bps" "bindPose1.wm[51]";
connectAttr "Bip01_L_Finger4.bps" "bindPose1.wm[52]";
connectAttr "Bip01_L_Finger41.bps" "bindPose1.wm[53]";
connectAttr "Bip01_L_Finger42.bps" "bindPose1.wm[54]";
connectAttr "Bip01_R_Finger0.bps" "bindPose1.wm[55]";
connectAttr "Bip01_R_Finger01.bps" "bindPose1.wm[56]";
connectAttr "Bip01_R_Finger02.bps" "bindPose1.wm[57]";
connectAttr "Bip01_R_Finger2.bps" "bindPose1.wm[58]";
connectAttr "Bip01_R_Finger21.bps" "bindPose1.wm[59]";
connectAttr "Bip01_R_Finger22.bps" "bindPose1.wm[60]";
connectAttr "Bip01_R_Finger1.bps" "bindPose1.wm[61]";
connectAttr "Bip01_R_Finger11.bps" "bindPose1.wm[62]";
connectAttr "Bip01_R_Finger12.bps" "bindPose1.wm[63]";
connectAttr "Bip01_R_Finger3.bps" "bindPose1.wm[64]";
connectAttr "Bip01_R_Finger31.bps" "bindPose1.wm[65]";
connectAttr "Bip01_R_Finger32.bps" "bindPose1.wm[66]";
connectAttr "Bip01_R_Finger4.bps" "bindPose1.wm[67]";
connectAttr "Bip01_R_Finger41.bps" "bindPose1.wm[68]";
connectAttr "Bip01_R_Finger42.bps" "bindPose1.wm[69]";
connectAttr "Louie_Green_Hood_on_MeshSG.pa" ":renderPartition.st" -na;
connectAttr "Louie_Green_Hood_on_MeshSG1.pa" ":renderPartition.st" -na;
connectAttr "Guard_NoRain_Mat.msg" ":defaultShaderList1.s" -na;
connectAttr "Guard_A_Head_A2_FaceFX_Mat.msg" ":defaultShaderList1.s" -na;
connectAttr "place2dTexture1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture2.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "Guard_NoRain_Mat_ncl1_1.msg" ":defaultTextureList1.tx" -na;
connectAttr "Guard_A_Head_A2_FaceFX_Mat_ncl1_1.msg" ":defaultTextureList1.tx" -na
		;
dataStructure -fmt "raw" -as "name=externalContentTable:string=node:string=key:string=upath:uint32=upathcrc:string=rpath:string=roles";
applyMetadata -fmt "raw" -v "channel\nname externalContentTable\nstream\nname v1.0\nindexType numeric\nstructure externalContentTable\n0\n\"Guard_NoRain_Mat_ncl1_1\" \"fileTextureName\" \"C:/Project/NagaGame/Arts/animations/Guard_A4_Raincoat_D.tga\" 1046872817 \"C:/Project/NagaGame/Arts/animations/Guard_A4_Raincoat_D.tga\" \"sourceImages\"\n1\n\"Guard_A_Head_A2_FaceFX_Mat_ncl1_1\" \"fileTextureName\" \"Guard_A_Head_A2_FaceFX_Mat\" 2510539110 \"\" \"sourceImages\"\nendStream\nendChannel\nendAssociations\n" 
		-scn;
// End of bruce_rig.ma
