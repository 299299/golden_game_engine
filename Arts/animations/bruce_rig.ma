//Maya ASCII 2015 scene
//Name: bruce_rig.ma
//Last modified: Sun, Dec 14, 2014 08:40:43 PM
//Codeset: 936
requires maya "2015";
requires -nodeType "dx11Shader" "dx11Shader" "1.0";
requires -nodeType "hkNodeOptions" "hctMayaSceneExport" "2014.1.0.1 (2014.1 r1)";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2015";
fileInfo "version" "2015";
fileInfo "cutIdentifier" "201402282131-909040";
fileInfo "osv" "Microsoft Windows 7 Ultimate Edition, 64-bit Windows 7 Service Pack 1 (Build 7601)\n";
createNode transform -s -n "persp";
	setAttr ".v" no;
	setAttr ".t" -type "double3" -367.08285831613068 208.84910068086538 296.11611188935126 ;
	setAttr ".r" -type "double3" -17.738352728994194 -398.99999999992889 1.0231522903038409e-015 ;
createNode camera -s -n "perspShape" -p "persp";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 624.8556501775854;
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
	setAttr ".r" -type "double3" 0 0 -89.999921452826385 ;
	setAttr ".s" -type "double3" 2.54 2.54 2.54 ;
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
	setAttr ".r" -type "double3" -89.999918037739732 -90 0 ;
	setAttr ".s" -type "double3" 1 0.99999988079173363 0.99999988079173363 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 3.9499525391981077e-022 2.54 8.4599012125160873e-016 0
		 7.1156007054345156e-006 -1.1279864165330039e-015 2.5399995458076434 0 2.5399995458076434 1.0084983022315201e-021 -7.1156007057165132e-006 0
		 0 277.86429916381837 0 1;
	setAttr ".radi" 1.8449945640563967;
	setAttr -k on ".MaxHandle" 2;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_Spine" -p "Bip01_Pelvis";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 8.7856826782226563 -0.0096882926300168037 1.2197416253911797e-005 ;
	setAttr ".r" -type "double3" -0.00023719255326303676 -8.0621322696333521e-005 -0.84526706080737757 ;
	setAttr ".s" -type "double3" 0.9999998617009932 0.99999992129299176 1.0000000000095588 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 3.4746657293642738e-006 2.5397232484817507 -0.037470476506444521 0
		 -3.778692007975905e-006 0.037470478744415815 2.5397233998373792 0 2.5400000000280265 -3.4185442337310104e-006 3.8295399373157085e-006 0
		 3.0916166191775348e-005 300.17993300268557 -0.024608263362418017 1;
	setAttr ".radi" 2.556699771881104;
	setAttr -k on ".MaxHandle" 3;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_Spine1" -p "Bip01_Spine";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 12.174758911132813 -0.010385632514953613 -2.8812792152166367e-008 ;
	setAttr ".r" -type "double3" -1.9191819637426392e-008 2.4708897318288188e-006 -0.89089287885498247 ;
	setAttr ".s" -type "double3" 1.0000001840995125 1.0000001840705506 1.0000000000000009 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -9.2339037216916745e-007 2.5388338711961231 -0.076953297587860681 0
		 1.2171419472915822e-005 0.076953282037767412 2.538834871001916 0 2.539999999999965 5.5421359998695042e-007 -1.2193818622758117e-005 0
		 -7.8406677368169074e-006 331.10005908471715 -0.50716201674607442 1;
	setAttr ".radi" 2.7393224430084233;
	setAttr -k on ".MaxHandle" 4;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_Spine2" -p "Bip01_Spine1";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 13.044387817382812 -0.010385990142822266 -2.8798240236938e-008 ;
	setAttr ".r" -type "double3" -1.9219301919275909e-008 2.4708835131788939e-006 -0.89089207802862036 ;
	setAttr ".s" -type "double3" 1.0000000646584639 1.0000000646874243 1.0000000000000009 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -5.696447957562274e-007 2.5373307737486721 -0.11641804452791397 0
		 1.4982758216391463e-005 0.11641804453193196 2.5373307738221467 0 2.5399999999999801 -1.1767148364288119e-007 -1.4993120533985354e-005 0
		 -5.7612759960621891e-006 364.21679707101219 -1.5373298628537628 1;
	setAttr ".radi" 2.739318037033081;
	setAttr -k on ".MaxHandle" 5;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_Spine3" -p "Bip01_Spine2";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 13.04437255859375 -0.010384559631347656 -6.5246174926869571e-005 ;
	setAttr ".r" -type "double3" -4.9599777048946942e-006 8.1901514227382193e-005 -0.93649889361059235 ;
	setAttr ".s" -type "double3" 0.99999994274081483 0.99999994273979698 1.0000000000010254 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -2.2333300000000001e-007 2.5350890000000001 -0.15787499999999999 0
		 -3.4587699999999998e-006 0.15787499999999999 2.5350890000000001 0 2.54 4.3788299999999998e-007 3.4382e-006 0
		 -4.3603500000000005e-006 397.31346200000002 -3.0823469999999999 1;
	setAttr ".radi" 3.3432356643676759;
	setAttr -k on ".MaxHandle" 6;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_Neck" -p "Bip01_Spine3";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 15.851211547851563 -1.4802713394165039 -2.1056894183857366e-006 ;
	setAttr ".r" -type "double3" -3.0110701398797641e-006 -3.078876662395242e-005 11.171298071802173 ;
	setAttr ".s" -type "double3" 1.0000001888389383 1.0000001888387953 1.0000000000001457 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 4.7569600000000005e-007 2.5176419999999999 0.33627200000000002 0
		 -3.4834399999999998e-006 -0.33627200000000002 2.5176419999999999 0 2.54 -9.3268299999999994e-007 3.3898000000000001e-006 0
		 -8.1289999999999996e-006 437.26396899999997 -9.3374780000000008 1;
	setAttr ".radi" 2.6930751228332523;
	setAttr -k on ".MaxHandle" 7;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_Head" -p "Bip01_Neck";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 12.824172973632813 -2.86102294921875e-005 -8.0035533756017685e-011 ;
	setAttr ".r" -type "double3" -0.11940598042264819 2.1036196345194013e-005 -7.6077511849881283 ;
	setAttr ".s" -type "double3" 0.99999988640765658 0.9999998325769438 1.0000001450242231 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0 2.54 0 0 -0.0052968099999999999 0 2.5399949999999998 0
		 2.5399949999999998 0 0.0052968099999999999 0 -2.0286900000000003e-006 469.55064099999998 -5.0251429999999999 1;
	setAttr ".radi" 0.87936058044433607;
	setAttr -k on ".MaxHandle" 8;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_HeadNub" -p "Bip01_Head";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 21.5841064453125 9.5367431640625e-007 -4.6566128730773926e-010 ;
	setAttr ".r" -type "double3" 1.0672170578144722e-007 -8.7871449037041438e-007 1.3258396891468276e-005 ;
	setAttr ".s" -type "double3" 0.99999988079073732 1.0000000000000242 1.0000001192092949 ;
	setAttr ".ssc" no;
	setAttr ".radi" 4.5326655578613293;
	setAttr -k on ".MaxHandle" 124;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Clavicle" -p "Bip01_Neck";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" -2.381134033203125 2.5143413543701172 6.362119197845459 ;
	setAttr ".r" -type "double3" -2.6072089691734326 -63.468439093822042 171.11602738456418 ;
	setAttr ".s" -type "double3" 0.99999998433146364 0.99999973128375919 0.99999984635350614 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 2.2725080000000002 -1.134314 0.025270999999999998 0
		 -0.051608500000000002 -0.159857 -2.53444 0 1.133421 2.26702 -0.16607 0 16.159752000000001 430.423495 -3.8078219999999998 1;
	setAttr ".radi" 3.9016842269897474;
	setAttr -k on ".MaxHandle" 48;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_UpperArm" -p "Bip01_L_Clavicle";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 18.579452514648438 1.9073486328125e-006 -1.52587890625e-005 ;
	setAttr ".r" -type "double3" 2.1745258264779639 17.484129183531227 -3.4013072883590914 ;
	setAttr ".s" -type "double3" 1.0000004382287226 1.0000000571532539 1.0000000948630015 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.8260947057480781 -1.7520646721670041 0.21737777085677124 0
		 0.15016356412678378 -0.15746965077203123 -2.5306625772295779 0 1.7590991094410628 1.8322329310892143 -0.0096292455703866631 0
		 58.381694274186273 409.34869147571931 -3.3383924093906248 1;
	setAttr ".radi" 5.6861294746398938;
	setAttr -k on ".MaxHandle" 49;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Forearm" -p "Bip01_L_UpperArm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 27.076797485351563 -4.76837158203125e-007 -3.0517578125e-005 ;
	setAttr ".r" -type "double3" -3.4150941830212833e-006 5.122643153291736e-006 -23.375357965193651 ;
	setAttr ".s" -type "double3" 0.99999975095236426 1.0000001177083486 0.99999976158142334 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.6166401925283753 -1.5457877740959276 1.2035845952904525 0
		 0.86234775014678944 -0.83968275525847658 -2.2367142760648084 0 1.7590988859780081 1.832232305997656 -0.0096292689842160818 0
		 107.82643705575157 361.90833532599021 2.5475029704905325 1;
	setAttr ".radi" 5.5433450317382826;
	setAttr -k on ".MaxHandle" 50;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Hand" -p "Bip01_L_Forearm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 26.396884918212891 7.62939453125e-006 -1.52587890625e-005 ;
	setAttr ".r" -type "double3" -86.805457130588437 4.14598852651946 6.7735812345401447 ;
	setAttr ".s" -type "double3" 1.0000004379632215 1.0000002975967377 1.0000001721369147 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.5754159999999999 -1.762232 0.92962400000000001 0
		 -1.837906 -1.742944 -0.189329 0 0.769262 -0.55523199999999995 -2.3561740000000002 0
		 150.50062 321.10408200000001 34.318252000000001 1;
	setAttr ".radi" 1.0297149896621705;
	setAttr -k on ".MaxHandle" 51;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger0" -p "Bip01_L_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.4199371337890625 1.073486328125 -4.1273365020751953 ;
	setAttr ".r" -type "double3" 86.231966117600564 36.841188359173557 26.583488032287995 ;
	setAttr ".s" -type "double3" 0.99999969504655806 0.99999987606655683 0.99999984286330212 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.0080518299999999994 -1.5525150000000001 2.0102820000000001 0
		 0.81081300000000001 -1.9035439999999999 -1.47333 0 2.407098 0.64638799999999996 0.48955599999999999 0
		 149.165052 317.26020799999998 46.089367000000003 1;
	setAttr ".radi" 0.88679025650024423;
	setAttr -k on ".MaxHandle" 52;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger01" -p "Bip01_L_Finger0";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 4.2228050231933594 -1.52587890625e-005 0 ;
	setAttr ".r" -type "double3" 3.4150940595121706e-006 3.415093698503949e-006 7.9435501546884382 ;
	setAttr ".s" -type "double3" 1.0000002595836328 1.0000001538740062 1.0000001192092907 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.12002699999999999 -1.800684 1.787382 0 0.80191999999999997 -1.670725 -1.7370099999999999 0
		 2.407098 0.64638799999999996 0.48955599999999999 0 149.19904199999999 310.70421299999998 54.578403000000002 1;
	setAttr ".radi" 0.81118146657943735;
	setAttr -k on ".MaxHandle" 53;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger02" -p "Bip01_L_Finger01";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.8627700805664062 1.52587890625e-005 -7.62939453125e-006 ;
	setAttr ".r" -type "double3" -9.3915113152002295e-006 -8.5377360549514523e-007 9.8148553231541946 ;
	setAttr ".s" -type "double3" 1.0000000477368338 0.99999987154008163 1.00000011920929 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.25496999999999997 -2.0591279999999998 1.465122 0
		 0.76972300000000005 -1.339318 -2.0162719999999998 0 2.4070969999999998 0.64638799999999996 0.48955599999999999 0
		 149.66268600000001 303.74861099999998 61.482675999999998 1;
	setAttr ".radi" 0.75550360679626483;
	setAttr -k on ".MaxHandle" 54;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger0Nub" -p "Bip01_L_Finger02";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 3.5976333618164062 7.62939453125e-006 -1.52587890625e-005 ;
	setAttr ".r" -type "double3" -2.5613215494215544e-006 2.6466992499130218e-005 -1.8783026934868286e-005 ;
	setAttr ".s" -type "double3" 0.99999964237229177 0.99999976158148585 0.99999970197689181 ;
	setAttr ".ssc" no;
	setAttr ".radi" 0.75550360679626483;
	setAttr -k on ".MaxHandle" 125;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger1" -p "Bip01_L_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 10.714435577392578 -0.5559539794921875 -4.2694988250732422 ;
	setAttr ".r" -type "double3" 14.628375977711462 9.3933382137148413 12.6466677069435 ;
	setAttr ".s" -type "double3" 0.99999984176324686 0.99999998200302043 0.99999978602629269 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.99403900000000001 -1.9822820000000001 1.2385660000000001 0
		 -1.830476 -1.4971639999999999 -0.92706999999999995 0 1.4535629999999999 -0.52977200000000002 -2.014472 0
		 165.11773099999999 305.56235700000002 54.443570999999999 1;
	setAttr ".radi" 1.0106136846542357;
	setAttr -k on ".MaxHandle" 55;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger11" -p "Bip01_L_Finger1";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 4.8124427795410156 7.62939453125e-006 0 ;
	setAttr ".r" -type "double3" -5.5495281378106824e-006 -3.4150941875323478e-006 14.544833519082216 ;
	setAttr ".s" -type "double3" 1.0000001163874284 1.0000001014184718 1.00000011920929 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.50247799999999998 -2.2947470000000001 0.96604900000000005 0
		 -2.021452 -0.95135499999999995 -1.20841 0 1.4535640000000001 -0.52977200000000002 -2.0144709999999999 0
		 169.90149 296.02272599999998 60.404122999999998 1;
	setAttr ".radi" 0.55068883895874021;
	setAttr -k on ".MaxHandle" 56;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger12" -p "Bip01_L_Finger11";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.6223373413085938 1.52587890625e-005 -1.9073486328125e-006 ;
	setAttr ".r" -type "double3" 1.003184040756e-005 0 5.7238211010250186 ;
	setAttr ".s" -type "double3" 0.99999999955452212 0.99999999360996283 0.99999994039535922 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.29836800000000002 -2.3781880000000002 0.84071399999999996 0
		 -2.0614880000000002 -0.71775 -1.298732 0 1.4535629999999999 -0.52977200000000002 -2.0144709999999999 0
		 171.21914200000001 290.00514700000002 62.937393999999998 1;
	setAttr ".radi" 0.67713126897811904;
	setAttr -k on ".MaxHandle" 57;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger1Nub" -p "Bip01_L_Finger12";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 3.2244338989257813 2.288818359375e-005 0 ;
	setAttr ".r" -type "double3" -1.2806603167107466e-005 1.5367928380528053e-005 1.7075475978364913e-006 ;
	setAttr ".s" -type "double3" 0.99999982118610209 1.0000001192093215 1.0000003576278877 ;
	setAttr ".ssc" no;
	setAttr ".radi" 0.67713126897811904;
	setAttr -k on ".MaxHandle" 126;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger2" -p "Bip01_L_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 11.282051086425781 -0.7739715576171875 -1.4246807098388672 ;
	setAttr ".r" -type "double3" 1.1703534121507251 3.8125935170124188 10.824469846447004 ;
	setAttr ".s" -type "double3" 0.99999976502204113 0.99999984297554045 0.99999972044748697 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.148414 -2.0167280000000001 1.0322549999999999 0 -2.0833200000000001 -1.3948069999999999 -0.40729399999999999 0
		 0.89023600000000003 -0.66251000000000004 -2.284767 0 168.60108500000001 303.36256800000001 48.309638 1;
	setAttr ".radi" 1.0790805387496951;
	setAttr -k on ".MaxHandle" 58;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger21" -p "Bip01_L_Finger2";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 5.1384735107421875 -7.62939453125e-006 -5.7220458984375e-006 ;
	setAttr ".r" -type "double3" 0 1.7075472284205988e-006 18.307697941925422 ;
	setAttr ".s" -type "double3" 1.000000037529029 0.99999972692487837 1.000000000000008 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.43587399999999998 -2.3527840000000002 0.85206700000000002 0
		 -2.3386089999999999 -0.69071400000000005 -0.71093099999999998 0 0.89023699999999995 -0.66251000000000004 -2.284767 0
		 174.502217 292.999596 53.613897999999999 1;
	setAttr ".radi" 0.6214189624786377;
	setAttr -k on ".MaxHandle" 59;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger22" -p "Bip01_L_Finger21";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.959136962890625 7.62939453125e-006 5.7220458984375e-006 ;
	setAttr ".r" -type "double3" -2.7747639894241643e-006 -3.4150941437730418e-006 3.3157117424363807 ;
	setAttr ".s" -type "double3" 1.0000001292009288 1.0000001300627785 0.99999994039535545 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.29988500000000001 -2.3887960000000001 0.80952199999999996 0
		 -2.3599049999999999 -0.55347800000000003 -0.75902199999999997 0 0.89023600000000003 -0.66251000000000004 -2.284767 0
		 175.792002 286.03744399999999 56.135261 1;
	setAttr ".radi" 0.65709149122238175;
	setAttr -k on ".MaxHandle" 60;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger2Nub" -p "Bip01_L_Finger22";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 3.1290054321289063 -7.62939453125e-006 0 ;
	setAttr ".r" -type "double3" 2.6680429625911048e-005 -6.8301932411241003e-006 -3.1589643740200711e-005 ;
	setAttr ".s" -type "double3" 0.99999940395371134 0.99999988079099655 0.99999970197689769 ;
	setAttr ".ssc" no;
	setAttr ".radi" 0.65709149122238175;
	setAttr -k on ".MaxHandle" 127;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger3" -p "Bip01_L_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 11.279922485351563 -0.903228759765625 1.1801109313964844 ;
	setAttr ".r" -type "double3" -0.90261731930883349 -3.9600513443698206 9.9396793121463709 ;
	setAttr ".s" -type "double3" 0.99999981269670213 1.0000001008813486 0.9999998402886402 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.2847040000000001 -2.0701160000000001 0.71816100000000005 0
		 -2.0927419999999999 -1.4059159999999999 -0.308919 0 0.64927999999999997 -0.43545499999999998 -2.4166940000000001 0
		 170.839088 302.14531699999998 42.194803 1;
	setAttr ".radi" 0.98335571765899688;
	setAttr -k on ".MaxHandle" 61;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger31" -p "Bip01_L_Finger3";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 4.6826515197753906 7.62939453125e-006 -1.9073486328125e-006 ;
	setAttr ".r" -type "double3" -1.2806603940028411e-006 -8.537736813037059e-007 14.876095303435791 ;
	setAttr ".s" -type "double3" 0.99999995894449223 1.0000000588560052 1.0000001192092938 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.70438000000000001 -2.361672 0.61478200000000005 0
		 -2.35242 -0.82733699999999999 -0.48293799999999998 0 0.649281 -0.43545400000000001 -2.4166940000000001 0
		 176.85490300000001 292.45174200000002 45.557693999999998 1;
	setAttr ".radi" 0.55878551959991452;
	setAttr -k on ".MaxHandle" 62;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger32" -p "Bip01_L_Finger31";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.660888671875 -1.52587890625e-005 -7.62939453125e-006 ;
	setAttr ".r" -type "double3" 7.2570781199604848e-006 3.4150944614994592e-006 13.908408792063712 ;
	setAttr ".s" -type "double3" 1.0000000361650081 0.99999970693137086 1.0000001192092949 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.118273 -2.491298 0.48067399999999999 0 -2.4527619999999999 -0.235402 -0.61655599999999999 0
		 0.64928200000000003 -0.43545499999999998 -2.4166949999999998 0 178.729187 286.16757100000001 47.193562999999997 1;
	setAttr ".radi" 0.71259701728820812;
	setAttr -k on ".MaxHandle" 63;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger3Nub" -p "Bip01_L_Finger32";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 3.3933181762695312 7.62939453125e-006 3.814697265625e-006 ;
	setAttr ".r" -type "double3" -1.0245282533686065e-005 8.5377364625156962e-007 1.3660378340025243e-005 ;
	setAttr ".s" -type "double3" 1.0000000000000284 1.0000001192093178 1.0000000000000184 ;
	setAttr ".ssc" no;
	setAttr ".radi" 0.71259701728820812;
	setAttr -k on ".MaxHandle" 128;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger4" -p "Bip01_L_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 10.60528564453125 -0.1732940673828125 3.8393726348876953 ;
	setAttr ".r" -type "double3" -4.1181134513090241 -11.289424720252658 7.5851067215382386 ;
	setAttr ".s" -type "double3" 0.99999973179403689 0.99999968427654418 0.99999986812787223 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.4441040000000001 -2.0473219999999999 0.41789700000000002 0
		 -2.0601660000000002 -1.4799119999999999 -0.13104399999999999 0 0.34910999999999998 -0.26444699999999999 -2.501957 0
		 170.48033100000001 300.58546999999999 35.163744999999999 1;
	setAttr ".radi" 0.70554250001907359;
	setAttr -k on ".MaxHandle" 64;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger41" -p "Bip01_L_Finger4";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.3597221374511719 -3.814697265625e-005 0 ;
	setAttr ".r" -type "double3" -1.9209905345234889e-006 0 14.793461990913112 ;
	setAttr ".s" -type "double3" 0.99999995341912506 1.0000000882579043 0.99999994039535645 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.87020399999999998 -2.3573330000000001 0.370583 0
		 -2.360608 -0.90810500000000005 -0.233404 0 0.34910999999999998 -0.26444600000000001 -2.501957 0
		 175.33212700000001 293.70701400000002 36.567765999999999 1;
	setAttr ".radi" 0.42467428922653205;
	setAttr -k on ".MaxHandle" 65;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger42" -p "Bip01_L_Finger41";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.0222625732421875 -7.62939453125e-006 -3.814697265625e-006 ;
	setAttr ".r" -type "double3" -9.6049516288911966e-007 3.8419810160811851e-006 25.417111488747135 ;
	setAttr ".s" -type "double3" 1.0000001020439686 1.0000001969233494 1.0000001192092909 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.227216 -2.5189219999999999 0.23453499999999999 0
		 -2.5056120000000002 0.191576 -0.36987399999999998 0 0.34911599999999998 -0.26444699999999999 -2.5019559999999998 0
		 177.09192300000001 288.93990200000002 37.317191999999999 1;
	setAttr ".radi" 0.62527934789657602;
	setAttr -k on ".MaxHandle" 66;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Finger4Nub" -p "Bip01_L_Finger42";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 2.9775161743164062 -7.62939453125e-006 -1.9073486328125e-006 ;
	setAttr ".r" -type "double3" -1.3020051209556282e-005 -4.2688689945905804e-007 -3.1589630559971891e-005 ;
	setAttr ".s" -type "double3" 0.99999982118621766 0.99999976158163795 0.99999982118609765 ;
	setAttr ".ssc" no;
	setAttr ".radi" 0.62527934789657602;
	setAttr -k on ".MaxHandle" 129;
	setAttr ".fbxID" 5;
createNode joint -n "Gundummy02" -p "Bip01_L_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" -3.814697265625e-006 -1.52587890625e-005 -3.814697265625e-006 ;
	setAttr ".r" -type "double3" -2.6466992499131749e-005 -1.7075478013920509e-006 1.1952834609744446e-005 ;
	setAttr ".s" -type "double3" 0.99999970197679833 0.99999964237224204 0.99999976158153558 ;
	setAttr ".ssc" no;
	setAttr ".radi" 3.3271616484853443e-006;
	setAttr -k on ".MaxHandle" 67;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Foretwist" -p "Bip01_L_Forearm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 1.52587890625e-005 7.62939453125e-006 -1.52587890625e-005 ;
	setAttr ".r" -type "double3" 1.069009609514521 0 1.0245281312353604e-005 ;
	setAttr ".s" -type "double3" 1.0000002384185951 1.0000000645867473 1.0000001244590095 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.6166389999999999 -1.545793 1.203578 0 0.89501200000000003 -0.80534799999999995 -2.2365080000000002 0
		 1.7427079999999999 1.8475760000000001 0.0321052 0 107.826403 361.90818100000001 2.5475789999999998 1;
	setAttr ".radi" 2.7716683101654054;
	setAttr -k on ".MaxHandle" 68;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Foretwist1" -p "Bip01_L_Foretwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 13.198421478271484 -5.7220458984375e-006 4.57763671875e-005 ;
	setAttr ".r" -type "double3" 1.0690071757040911 0 2.5613209387547799e-006 ;
	setAttr ".s" -type "double3" 1.0000000000000009 0.99999994456417463 1.0000001829412566 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.6166389999999999 -1.545795 1.2035769999999999 0 0.92736700000000005 -0.77073899999999995 -2.2355209999999999 0
		 1.7257089999999999 1.8622780000000001 0.073824299999999995 0 129.16353100000001 341.50617 18.432897000000001 1;
	setAttr ".radi" 2.7716683101654054;
	setAttr -k on ".MaxHandle" 69;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_LUpArmTwist" -p "Bip01_L_UpperArm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 0 4.76837158203125e-007 0 ;
	setAttr ".r" -type "double3" 5.5708723776900395e-005 0 -8.5377384980714181e-007 ;
	setAttr ".s" -type "double3" 0.99999976158142101 1.0000001192097623 0.99999988079116209 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.826092 -1.7520659999999999 0.21737600000000001 0
		 0.15016499999999999 -0.157467 -2.5306630000000001 0 1.7591019999999999 1.83223 -0.00962615 0
		 58.381635000000003 409.34854100000001 -3.3383050000000001 1;
	setAttr ".radi" 1.8953778934478762;
	setAttr -k on ".MaxHandle" 70;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_LUpArmTwist1" -p "Bip01_LUpArmTwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 9.025604248046875 4.76837158203125e-007 0 ;
	setAttr ".r" -type "double3" -1.8783021337089687e-005 -1.7075472925031871e-006 -6.403302346886954e-007 ;
	setAttr ".s" -type "double3" 1.0000000000000004 0.99999994039540907 1.0000000000000528 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.826092 -1.7520659999999999 0.21737699999999999 0
		 0.15016499999999999 -0.157467 -2.5306630000000001 0 1.7591019999999999 1.8322309999999999 -0.0096261599999999999 0
		 74.86327 393.53508799999997 -1.3763460000000001 1;
	setAttr ".radi" 1.8953764915466311;
	setAttr -k on ".MaxHandle" 71;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_LUpArmTwist2" -p "Bip01_LUpArmTwist1";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 9.025604248046875 -2.384185791015625e-006 1.52587890625e-005 ;
	setAttr ".r" -type "double3" -1.8356134488519623e-005 5.1226421828428162e-006 6.4033027285535383e-007 ;
	setAttr ".s" -type "double3" 0.99999994039535933 0.99999994039540663 1.0000000000000573 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1.8260940000000001 -1.752065 0.21737699999999999 0
		 0.15016499999999999 -0.157467 -2.5306630000000001 0 1.7591000000000001 1.8322320000000001 -0.0096262599999999993 0
		 91.344812000000005 377.72163399999999 0.58560800000000002 1;
	setAttr ".radi" 1.8953764915466311;
	setAttr -k on ".MaxHandle" 72;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Clavicle" -p "Bip01_Neck";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" -2.381134033203125 2.5143775939941406 -6.3621058464050293 ;
	setAttr ".r" -type "double3" 2.606501100759834 63.468370798719782 171.11540244650126 ;
	setAttr ".s" -type "double3" 1.0000001797254661 0.99999991526991772 0.99999980972816982 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -2.2725080000000002 -1.1343129999999999 0.025277999999999998 0
		 0.051600600000000003 -0.159858 -2.53444 0 1.133421 -2.26702 0.16606599999999999 0
		 -16.159772 430.423495 -3.8077709999999998 1;
	setAttr ".radi" 3.9016818237304687;
	setAttr -k on ".MaxHandle" 73;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_UpperArm" -p "Bip01_R_Clavicle";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 18.579429626464844 3.814697265625e-006 0 ;
	setAttr ".r" -type "double3" -2.1745253321407749 -17.484133500398414 -3.4013100937704661 ;
	setAttr ".s" -type "double3" 0.9999999014533778 1.0000001106433771 1.0000000237390849 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.82609281367123 -1.7520646852659456 0.21738280514338146 0
		 -0.1501709194978717 -0.15746946272640916 -2.5306627572930989 0 1.7590998508781988 -1.8322319428644811 0.0096238528439651083 0
		 -58.381661438678705 409.34873310643781 -3.3382337860763736 1;
	setAttr ".radi" 5.6861322784423836;
	setAttr -k on ".MaxHandle" 74;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Forearm" -p "Bip01_R_UpperArm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 27.076812744140625 -9.5367431640625e-007 3.0517578125e-005 ;
	setAttr ".r" -type "double3" -1.7075474046372485e-006 -1.7075471318912402e-006 -23.37533458639226 ;
	setAttr ".s" -type "double3" 1.000000094060038 0.9999999343303384 0.99999988079071089 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.6166365488805481 -1.5457886245110166 1.2035887875544118 0
		 -0.86235309063319343 -0.83968163931117434 -2.2367125257862979 0 1.7590996636565412 -1.8322317034018019 0.0096237491677538256 0
		 -107.82638078119419 361.90834994276327 2.5478024297117319 1;
	setAttr ".radi" 5.543346633911133;
	setAttr -k on ".MaxHandle" 75;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Hand" -p "Bip01_R_Forearm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 26.396877288818359 0 0 ;
	setAttr ".r" -type "double3" 86.805449422993448 -4.1459839304654098 6.7735547140114587 ;
	setAttr ".s" -type "double3" 0.99999989572232895 1.0000000091880086 0.99999991005435274 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.575426 -1.7622450000000001 0.92958300000000005 0
		 1.837909 -1.7429410000000001 -0.189332 0 0.76923600000000003 0.55520099999999994 2.3561890000000001 0
		 -150.50094899999999 321.103656 34.317580999999997 1;
	setAttr ".radi" 1.0297142887115482;
	setAttr -k on ".MaxHandle" 76;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger0" -p "Bip01_R_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.4199371337890625 1.073486328125 4.1273288726806641 ;
	setAttr ".r" -type "double3" -86.231956323201842 -36.841167785095635 26.583474663506724 ;
	setAttr ".s" -type "double3" 0.99999997551227582 0.99999995180202395 0.99999985407738001 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.0080726500000000007 -1.5525420000000001 2.0102600000000002 0
		 -0.81079699999999999 -1.903524 -1.473365 0 2.4071020000000001 -0.64638099999999998 -0.489539 0
		 -149.16548800000001 317.25964599999998 46.088659999999997 1;
	setAttr ".radi" 0.88679125785827639;
	setAttr -k on ".MaxHandle" 77;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger01" -p "Bip01_R_Finger0";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 4.2228126525878906 -7.62939453125e-006 0 ;
	setAttr ".r" -type "double3" 8.5377333554552059e-007 -4.2688671758752103e-006 7.9435450812010666 ;
	setAttr ".s" -type "double3" 1.0000002472278287 1.0000003639210355 1.0000003576278722 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.120043 -1.800705 1.7873600000000001 0 -0.80190099999999997 -1.6707050000000001 -1.7370369999999999 0
		 2.4071030000000002 -0.64637999999999995 -0.489539 0 -149.19959499999999 310.70353499999999 54.577646999999999 1;
	setAttr ".radi" 0.8111804652214053;
	setAttr -k on ".MaxHandle" 78;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger02" -p "Bip01_R_Finger01";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.8627548217773437 0 1.52587890625e-005 ;
	setAttr ".r" -type "double3" -4.2688680803720619e-006 -2.5613211693983752e-006 9.8148497572410758 ;
	setAttr ".s" -type "double3" 0.99999990995131904 1.0000000353456469 0.99999994039535633 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.25498399999999999 -2.0591469999999998 1.4650920000000001 0
		 -0.76970099999999997 -1.3392919999999999 -2.0162969999999998 0 2.4071030000000002 -0.64638099999999998 -0.489539 0
		 -149.663297 303.74783600000001 61.481766 1;
	setAttr ".radi" 0.75550270557403576;
	setAttr -k on ".MaxHandle" 79;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger0Nub" -p "Bip01_R_Finger02";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 3.597625732421875 0 -2.288818359375e-005 ;
	setAttr ".r" -type "double3" 7.6839664802655635e-006 -2.3905673494156135e-005 179.99998804716327 ;
	setAttr ".s" -type "double3" 0.9999995231629506 0.99999952316286189 0.99999988079079849 ;
	setAttr ".ssc" no;
	setAttr ".radi" 0.75550270557403576;
	setAttr -k on ".MaxHandle" 130;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger1" -p "Bip01_R_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 10.714420318603516 -0.555938720703125 4.2694950103759766 ;
	setAttr ".r" -type "double3" -14.628363716366701 -9.3933201561258901 12.646661297990322 ;
	setAttr ".s" -type "double3" 1.0000000121947425 1.000000061850338 0.99999995753601933 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.99405299999999996 -1.9822979999999999 1.238529 0
		 1.8304860000000001 -1.497152 -0.92706999999999995 0 1.453541 0.52974500000000002 2.014494 0
		 -165.11829299999999 305.56167799999997 54.442549 1;
	setAttr ".radi" 1.0106148862838744;
	setAttr -k on ".MaxHandle" 80;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger11" -p "Bip01_R_Finger1";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 4.8124504089355469 0 -1.9073486328125e-006 ;
	setAttr ".r" -type "double3" 4.2688671233473013e-007 -8.5377351226765906e-007 14.544815275540156 ;
	setAttr ".s" -type "double3" 1.0000001569314729 1.0000002595327193 1.0000000000000058 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.502494 -2.294759 0.96601400000000004 0 2.0214639999999999 -0.95134300000000005 -1.208399 0
		 1.453541 0.52974399999999999 2.0144950000000001 0 -169.902129 296.021931 60.402926000000001 1;
	setAttr ".radi" 0.55068673610687269;
	setAttr -k on ".MaxHandle" 81;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger12" -p "Bip01_R_Finger11";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.622314453125 -7.62939453125e-006 -7.62939453125e-006 ;
	setAttr ".r" -type "double3" -8.537740972732156e-007 1.7075479008859101e-006 5.7238231446205754 ;
	setAttr ".s" -type "double3" 0.99999964370971872 0.99999947173189829 0.99999964237213146 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.29837799999999998 -2.378199 0.84067999999999998 0
		 2.0615009999999998 -0.71773299999999995 -1.298718 0 1.453541 0.52974500000000002 2.014494 0
		 -171.21984 290.00435299999998 62.936109999999999 1;
	setAttr ".radi" 0.67713352203369159;
	setAttr -k on ".MaxHandle" 82;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger1Nub" -p "Bip01_R_Finger12";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 3.2244415283203125 7.62939453125e-006 1.9073486328125e-006 ;
	setAttr ".r" -type "double3" 2.1344336067400825e-007 -1.4514152851385619e-005 179.9999692641469 ;
	setAttr ".s" -type "double3" 0.99999994039553119 1.0000002384187749 0.99999994039542239 ;
	setAttr ".ssc" no;
	setAttr ".radi" 0.67713352203369159;
	setAttr -k on ".MaxHandle" 131;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger2" -p "Bip01_R_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 11.282058715820313 -0.77398681640625 1.4246826171875 ;
	setAttr ".r" -type "double3" -1.1703400001343349 -3.8125824875333398 10.824460551785888 ;
	setAttr ".s" -type "double3" 0.9999999644522729 0.99999995835001831 0.9999998852106905 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.148425 -2.0167410000000001 1.032216 0 2.0833249999999999 -1.3948020000000001 -0.40729100000000001 0
		 0.890212 0.66247900000000004 2.2847849999999998 0 -168.60155 303.36194799999998 48.308573000000003 1;
	setAttr ".radi" 1.0790831422805787;
	setAttr -k on ".MaxHandle" 83;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger21" -p "Bip01_R_Finger2";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 5.1384925842285156 -1.52587890625e-005 0 ;
	setAttr ".r" -type "double3" -7.25707503534008e-006 -8.5377356589725852e-007 18.307696869175967 ;
	setAttr ".s" -type "double3" 1.0000000941166822 1.0000001319813359 0.999999940395359 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.43588399999999999 -2.3527969999999998 0.85202999999999995 0
		 2.3386179999999999 -0.69070399999999998 -0.71091499999999996 0 0.89021099999999997 0.66247800000000001 2.284786 0
		 -174.502759 292.99893700000001 53.612614000000001 1;
	setAttr ".radi" 0.62141530752182006;
	setAttr -k on ".MaxHandle" 84;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger22" -p "Bip01_R_Finger21";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.9591217041015625 7.62939453125e-006 -1.9073486328125e-006 ;
	setAttr ".r" -type "double3" 8.1108499834430271e-006 4.2688684454506627e-006 3.3157114826565315 ;
	setAttr ".s" -type "double3" 0.99999994982448093 0.99999995758114879 0.99999988079071056 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.29989500000000002 -2.3888060000000002 0.80948799999999999 0
		 2.3599130000000001 -0.55346799999999996 -0.75900199999999995 0 0.89020999999999995 0.66247999999999996 2.284786 0
		 -175.79258400000001 286.03670699999998 56.133879999999998 1;
	setAttr ".radi" 0.65708908796310439;
	setAttr -k on ".MaxHandle" 85;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger2Nub" -p "Bip01_R_Finger22";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 3.1289901733398438 0 0 ;
	setAttr ".r" -type "double3" -1.5794817162877188e-005 1.8783031413093409e-005 -179.99999316980677 ;
	setAttr ".s" -type "double3" 0.99999940395361309 0.99999970197681509 0.99999982118615338 ;
	setAttr ".ssc" no;
	setAttr ".radi" 0.65708908796310439;
	setAttr -k on ".MaxHandle" 132;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger3" -p "Bip01_R_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 11.279930114746094 -0.9032440185546875 -1.1801185607910156 ;
	setAttr ".r" -type "double3" 0.90262260363083546 3.9600590342594875 9.9396685188563882 ;
	setAttr ".s" -type "double3" 1.0000000316071613 0.99999994396551961 0.99999967038284554 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.2847120000000001 -2.070125 0.71812100000000001 0
		 2.0927449999999999 -1.4059120000000001 -0.30891600000000002 0 0.64925600000000006 0.435423 2.4167070000000002 0
		 -170.839495 302.144813 42.193683999999998 1;
	setAttr ".radi" 0.98335591793060328;
	setAttr -k on ".MaxHandle" 86;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger31" -p "Bip01_R_Finger3";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 4.6826438903808594 0 0 ;
	setAttr ".r" -type "double3" -1.0672169868369422e-006 -2.5613209747494289e-006 14.876087825416278 ;
	setAttr ".s" -type "double3" 0.9999999859468427 1.0000000665071409 1.0000002384185795 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.70438599999999996 -2.3616799999999998 0.61474399999999996 0
		 2.3524259999999999 -0.82733100000000004 -0.48292499999999999 0 0.64925600000000006 0.435423 2.4167070000000002 0
		 -176.855368 292.45116100000001 45.556386000000003 1;
	setAttr ".radi" 0.55878291606903085;
	setAttr -k on ".MaxHandle" 87;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger32" -p "Bip01_R_Finger31";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.6608734130859375 0 3.814697265625e-006 ;
	setAttr ".r" -type "double3" -4.2688689883607743e-007 0 13.908422864970689 ;
	setAttr ".s" -type "double3" 0.99999997417781272 0.99999982264557674 0.999999940395357 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.11827699999999999 -2.491304 0.48063899999999998 0
		 2.452769 -0.23539399999999999 -0.61653400000000003 0 0.64925699999999997 0.435423 2.4167070000000002 0
		 -178.729614 286.16699 47.192149000000001 1;
	setAttr ".radi" 0.71259746789932266;
	setAttr -k on ".MaxHandle" 88;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger3Nub" -p "Bip01_R_Finger32";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 3.3933181762695312 -7.62939453125e-006 -1.9073486328125e-006 ;
	setAttr ".r" -type "double3" -1.2593159780988856e-005 -1.6221700245668524e-005 179.99999871933946 ;
	setAttr ".s" -type "double3" 0.99999994039539553 1.0000001192093297 1.0000000000000149 ;
	setAttr ".ssc" no;
	setAttr ".radi" 0.71259746789932266;
	setAttr -k on ".MaxHandle" 133;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger4" -p "Bip01_R_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 10.605270385742188 -0.173309326171875 -3.8393745422363281 ;
	setAttr ".r" -type "double3" 4.1181253275324794 11.289433391068194 7.58510051143727 ;
	setAttr ".s" -type "double3" 1.0000001154747933 1.0000000332139476 0.99999987606729601 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.4441079999999999 -2.0473270000000001 0.41785499999999998 0
		 2.060168 -1.479911 -0.13104299999999999 0 0.34908499999999998 0.26441399999999998 2.5019640000000001 0
		 -170.48066 300.58504399999998 35.162602 1;
	setAttr ".radi" 0.70554605484008803;
	setAttr -k on ".MaxHandle" 89;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger41" -p "Bip01_R_Finger4";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 3.3597373962402344 0 0 ;
	setAttr ".r" -type "double3" -1.0672170541449319e-006 2.5613209104572383e-006 14.79346111891847 ;
	setAttr ".s" -type "double3" 1.0000000110480278 1.0000000034384391 1.00000011920929 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.87020500000000001 -2.3573379999999999 0.37054399999999998 0
		 2.360611 -0.90810000000000002 -0.23339299999999999 0 0.34908499999999998 0.26441399999999998 2.5019640000000001 0
		 -175.33249599999999 293.706549 36.566496000000001 1;
	setAttr ".radi" 0.4246743392944336;
	setAttr -k on ".MaxHandle" 90;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger42" -p "Bip01_R_Finger41";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 2.022247314453125 7.62939453125e-006 3.814697265625e-006 ;
	setAttr ".r" -type "double3" -5.3360861809071457e-007 -3.8419823553755383e-006 25.417117198862609 ;
	setAttr ".s" -type "double3" 0.99999975344931991 0.99999983286726779 1.0000001192092935 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.227215 -2.5189249999999999 0.23450499999999999 0
		 2.505617 0.191583 -0.36984 0 0.34908299999999998 0.26441399999999998 2.5019650000000002 0
		 -177.092311 288.93937899999997 37.315840000000001 1;
	setAttr ".radi" 0.6252791976928711;
	setAttr -k on ".MaxHandle" 91;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Finger4Nub" -p "Bip01_R_Finger42";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 2.9775161743164062 -7.62939453125e-006 0 ;
	setAttr ".r" -type "double3" 2.1451055190562466e-005 -2.988207939990836e-006 179.999957738202 ;
	setAttr ".s" -type "double3" 0.99999994039562856 1.0000003576285714 0.99999988079082203 ;
	setAttr ".ssc" no;
	setAttr ".radi" 0.6252791976928711;
	setAttr -k on ".MaxHandle" 134;
	setAttr ".fbxID" 5;
createNode joint -n "Gundummy" -p "Bip01_R_Hand";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" -1.52587890625e-005 0 -3.814697265625e-006 ;
	setAttr ".r" -type "double3" 5.1226424881761624e-006 1.0245283755018945e-005 -6.8301891700127188e-006 ;
	setAttr ".s" -type "double3" 1.0000000000000231 0.99999988079071844 0.99999988079072644 ;
	setAttr ".ssc" no;
	setAttr ".radi" 2.0521733586065244e-006;
	setAttr -k on ".MaxHandle" 92;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Foretwist" -p "Bip01_R_Forearm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 7.62939453125e-006 3.814697265625e-006 -1.52587890625e-005 ;
	setAttr ".r" -type "double3" -1.0690077746056794 5.1226424881761192e-006 1.7075474960587113e-006 ;
	setAttr ".s" -type "double3" 0.99999988079071489 1.0000001832192862 1.0000000640307205 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.6166529999999999 -1.545809 1.203541 0 -0.89498699999999998 -0.80531900000000001 -2.2365279999999998 0
		 1.7427079999999999 -1.8475760000000001 -0.032109499999999999 0 -107.826442 361.90821999999997 2.5478830000000001 1;
	setAttr ".radi" 2.7716693115234379;
	setAttr -k on ".MaxHandle" 93;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Foretwist1" -p "Bip01_R_Foretwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 13.198421478271484 0 -3.0517578125e-005 ;
	setAttr ".r" -type "double3" -1.0690040180726639 -8.537737480293447e-006 5.9764162362054691e-006 ;
	setAttr ".s" -type "double3" 0.99999988079072699 0.99999970507507197 1.0000001241810024 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.6166529999999999 -1.5458080000000001 1.203541 0
		 -0.92734399999999995 -0.77071000000000001 -2.2355390000000002 0 1.7257070000000001 -1.862279 -0.073828500000000005 0
		 -129.16370499999999 341.50593800000001 18.432742000000001 1;
	setAttr ".radi" 2.7716693115234379;
	setAttr -k on ".MaxHandle" 94;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_RUpArmTwist" -p "Bip01_R_UpperArm";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 7.62939453125e-006 0 3.0517578125e-005 ;
	setAttr ".r" -type "double3" -5.6989394284106659e-005 6.8301883557908159e-006 -1.4941037028292479e-006 ;
	setAttr ".s" -type "double3" 1.0000001192092969 0.99999994039585016 1.0000000000004767 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.826092 -1.7520659999999999 0.21738299999999999 0
		 -0.150173 -0.157467 -2.5306630000000001 0 1.759101 -1.8322309999999999 0.0096208700000000001 0
		 -58.381717000000002 409.34858000000003 -3.3381219999999998 1;
	setAttr ".radi" 1.8953780937194824;
	setAttr -k on ".MaxHandle" 95;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_RUpArmTwist1" -p "Bip01_RUpArmTwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 9.0255966186523437 9.5367431640625e-007 -3.0517578125e-005 ;
	setAttr ".r" -type "double3" 1.8996464761374852e-005 0 8.5377374802935577e-007 ;
	setAttr ".s" -type "double3" 0.99999988079071056 0.99999994039541018 1.0000000000000577 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.826092 -1.7520659999999999 0.21738299999999999 0
		 -0.150173 -0.157467 -2.530662 0 1.759101 -1.8322309999999999 0.0096209799999999995 0
		 -74.863298999999998 393.53512599999999 -1.376117 1;
	setAttr ".radi" 1.8953744888305664;
	setAttr -k on ".MaxHandle" 96;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_RUpArmTwist2" -p "Bip01_RUpArmTwist1";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 9.0255889892578125 4.76837158203125e-007 -1.52587890625e-005 ;
	setAttr ".r" -type "double3" 1.8783015739314348e-005 -1.7075474960587109e-006 1.2806606220440338e-006 ;
	setAttr ".s" -type "double3" 0.99999988079071112 1.0000002384186331 1.0000000000000473 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -1.826092 -1.752065 0.21738299999999999 0 -0.150173 -0.157467 -2.5306630000000001 0
		 1.759101 -1.8322320000000001 0.0096209899999999994 0 -91.34487 377.72167300000001 0.58588799999999996 1;
	setAttr ".radi" 1.8953744888305664;
	setAttr -k on ".MaxHandle" 97;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Thigh" -p "Bip01_Pelvis";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" -1.52587890625e-005 1.8906783225247636e-005 10.18528938293457 ;
	setAttr ".r" -type "double3" 171.58042887163168 -5.1724648439984886 -178.47479128595603 ;
	setAttr ".s" -type "double3" 1.0000006759433269 0.99999998366050347 1.0000003973256029 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.22899100517909321 -2.5287621927261359 -0.067331966010578767 0
		 0.37040167105520638 -0.033360747577907364 2.5126255480911834 0 -2.5023925465168815 -0.23634196057431883 0.36575519177341015 0
		 25.870630406707754 277.86426040649417 -2.4451231516323582e-005 1;
	setAttr ".radi" 1.615135988686234e-006;
	setAttr -k on ".MaxHandle" 98;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_LThighTwist" -p "Bip01_L_Thigh";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" -7.62939453125e-006 -1.1920928955078125e-007 -1.9073486328125e-006 ;
	setAttr ".r" -type "double3" -1.5541344699078248e-006 8.5377384980714202e-007 -2.1344346245178551e-007 ;
	setAttr ".s" -type "double3" 0.99999976158142101 1.0000002384185793 1.000000000000002 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.228995 -2.5287609999999998 -0.067313300000000006 0
		 0.37040200000000001 -0.033341599999999999 2.5126270000000002 0 -2.5023919999999999 -0.236343 0.365757 0
		 25.870635 277.86429900000002 -2.6061600000000001e-005 1;
	setAttr ".radi" 5.1390839767456065;
	setAttr -k on ".MaxHandle" 99;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_LThighTwist1" -p "Bip01_LThighTwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 24.471817016601563 -2.384185791015625e-007 -1.9073486328125e-006 ;
	setAttr ".r" -type "double3" 9.938460628032707e-007 8.537736971404718e-007 5.3360856071279488e-008 ;
	setAttr ".s" -type "double3" 0.99999994039535534 0.9999998211860659 0.99999988079071089 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.228995 -2.5287609999999998 -0.067313200000000004 0
		 0.37040099999999998 -0.033341700000000002 2.5126270000000002 0 -2.5023919999999999 -0.236343 0.36575600000000003 0
		 31.474557000000001 215.98092500000001 -1.6473040000000001 1;
	setAttr ".radi" 5.1390839767456065;
	setAttr -k on ".MaxHandle" 100;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Calf" -p "Bip01_L_Thigh";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 48.943630218505859 -4.1723251342773438e-007 0 ;
	setAttr ".r" -type "double3" 5.8696919245950303e-006 0 -2.6113050168155523 ;
	setAttr ".s" -type "double3" 0.99999978906105702 1.0000003225696827 1.0000000000000009 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.2118776412650796 -2.5246158741888167 -0.18173746603792851 0
		 0.38044976393980334 -0.14853682083162489 2.5069496326231957 0 -2.502392585492232 -0.23634194535740372 0.36575493494791156 0
		 37.078281333013635 154.09745874908731 -3.2954963458873618 1;
	setAttr ".radi" 9.7695830154418939;
	setAttr -k on ".MaxHandle" 101;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Foot" -p "Bip01_L_Calf";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 46.521804809570313 9.5367431640625e-007 -1.9073486328125e-006 ;
	setAttr ".r" -type "double3" -1.1685043144301634 -5.8380951541883572 3.3995182853147541 ;
	setAttr ".s" -type "double3" 0.9999999830524251 1.0000000320114972 0.99999989520903854 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.021676299999999999 -2.5399029999999998 0.0046356399999999999 0
		 0.41839100000000001 0.0010018200000000001 2.5053040000000002 0 -2.5052099999999999 0.022143800000000002 0.41836600000000002 0
		 46.935831999999998 36.647801999999999 -11.747023 1;
	setAttr ".radi" 4.2300783920288083;
	setAttr -k on ".MaxHandle" 102;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Toe0" -p "Bip01_L_Foot";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 14.424516677856445 14.059968948364258 -9.5367431640625e-006 ;
	setAttr ".r" -type "double3" -9.6049549169639429e-007 2.5146307053741886e-006 100.75187048437904 ;
	setAttr ".s" -type "double3" 0.99999979603414968 0.99999985459239293 0.99999982118606601 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.41508899999999999 0.47481800000000002 2.4604569999999999 0
		 -0.056757200000000001 2.4951270000000001 -0.47193400000000002 0 -2.5052099999999999 0.022144 0.41836600000000002 0
		 52.505704999999999 0.024988799999999999 23.544354999999999 1;
	setAttr ".radi" 1.5303857946395878;
	setAttr -k on ".MaxHandle" 103;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_L_Toe0Nub" -p "Bip01_L_Toe0";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 7.2875499725341797 -2.1457672119140625e-006 3.814697265625e-006 ;
	setAttr ".r" -type "double3" -1.2966690343945878e-005 2.8014451107212927e-007 179.99999146226253 ;
	setAttr ".s" -type "double3" 0.99999988079072155 0.99999976158145054 0.99999976158146053 ;
	setAttr ".ssc" no;
	setAttr ".radi" 1.5303857946395878;
	setAttr -k on ".MaxHandle" 135;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_LCalfTwist" -p "Bip01_L_Calf";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" -3.814697265625e-006 0 0 ;
	setAttr ".r" -type "double3" -0.27507988621564672 1.2806605457107072e-006 1.0672171214255897e-006 ;
	setAttr ".s" -type "double3" 0.99999994039535567 1.0000000809262208 0.99999996113033551 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.21188699999999999 -2.5246179999999998 -0.18168799999999999 0
		 0.39245799999999997 -0.14735000000000001 2.5051679999999998 0 -2.5005359999999999 -0.23705399999999999 0.37778899999999999 0
		 37.078488 154.09755100000001 -3.2945820000000001 1;
	setAttr ".radi" 4.8847911071777359;
	setAttr -k on ".MaxHandle" 104;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_LCalfTwist1" -p "Bip01_LCalfTwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 23.260902404785156 0 -1.9073486328125e-006 ;
	setAttr ".r" -type "double3" -0.27508778977174991 4.2688682312579683e-007 -1.0672170578144923e-006 ;
	setAttr ".s" -type "double3" 1.0000000000000002 0.99999996237783284 0.99999990265538252 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.21188599999999999 -2.5246170000000001 -0.18168799999999999 0
		 0.40445799999999998 -0.14621000000000001 2.5033249999999998 0 -2.4986229999999998 -0.237758 0.38981100000000002 0
		 42.007159999999999 95.372657000000004 -7.5208050000000002 1;
	setAttr ".radi" 4.8847911071777359;
	setAttr -k on ".MaxHandle" 105;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Thigh" -p "Bip01_Pelvis";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 1.52587890625e-005 -9.3431335699278861e-006 -10.18528938293457 ;
	setAttr ".r" -type "double3" -171.5802694672534 5.1726312920439401 -178.47477611425106 ;
	setAttr ".s" -type "double3" 0.99999998805914603 0.99999995855775048 0.99999987456959283 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.22899857372627849 -2.5287597703933717 -0.067331288573363249 0
		 -0.37039444850030251 -0.03335967888006016 2.512626562535587 0 -2.5023915990508123 0.23634929372628546 -0.36574771446031795 0
		 -25.870630406639702 277.86433792114258 4.8742897297099173e-005 1;
	setAttr ".radi" 1.614656785022817e-006;
	setAttr -k on ".MaxHandle" 106;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_RThighTwist" -p "Bip01_R_Thigh";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" -7.62939453125e-006 -2.384185791015625e-007 0 ;
	setAttr ".r" -type "double3" 2.4746092578109443e-006 0 3.2016504101105362e-007 ;
	setAttr ".s" -type "double3" 1.0000002384185791 1.0000001192092904 1.0000004768371604 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.228995 -2.5287609999999998 -0.067312700000000003 0
		 -0.37039299999999997 -0.033341799999999998 2.5126270000000002 0 -2.5023930000000001 0.236343 -0.36574800000000002 0
		 -25.870633000000002 277.86429900000002 5.1054700000000004e-005 1;
	setAttr ".radi" 5.1390823745727552;
	setAttr -k on ".MaxHandle" 107;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_RThighTwist1" -p "Bip01_RThighTwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 24.471817016601563 1.1920928955078125e-007 1.9073486328125e-006 ;
	setAttr ".r" -type "double3" -1.0005160513364904e-007 0 1.0672171214255898e-007 ;
	setAttr ".s" -type "double3" 0.99999994039535522 0.99999994039535534 0.99999994039535522 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.228995 -2.5287609999999998 -0.0673126 0 -0.370394 -0.033341700000000002 2.5126270000000002 0
		 -2.5023930000000001 0.236343 -0.36575000000000002 0 -31.474549 215.980906 -1.6472119999999999 1;
	setAttr ".radi" 5.1390823745727552;
	setAttr -k on ".MaxHandle" 108;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Calf" -p "Bip01_R_Thigh";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 48.943649291992188 1.1920928955078125e-007 0 ;
	setAttr ".r" -type "double3" -4.1621451744176712e-006 4.2688668441075367e-007 -2.6113036164877377 ;
	setAttr ".s" -type "double3" 1.0000003249458189 1.0000003246063727 1.0000002384185807 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.21188565385610697 -2.5246148595943283 -0.18173687164179703 0
		 -0.38044296387977466 -0.14853557443851761 2.5069506755253386 0 -2.5023922233040405 0.23634933928626006 -0.36574761954862361 0
		 -37.078656331619555 154.09760657133393 -3.2953899318868873 1;
	setAttr ".radi" 9.7695806121826188;
	setAttr -k on ".MaxHandle" 109;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Foot" -p "Bip01_R_Calf";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 46.521808624267578 -1.6689300537109375e-006 0 ;
	setAttr ".r" -type "double3" 1.1685044803514879 5.8381079033808767 3.399516786063812 ;
	setAttr ".s" -type "double3" 1.0000000042498454 0.99999991238263353 0.99999997754203007 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 0.021677499999999999 -2.5399029999999998 0.0046332200000000004 0
		 -0.41838399999999998 0.00099931 2.505306 0 -2.5052120000000002 -0.022144500000000001 -0.41835899999999998 0
		 -46.935836999999999 36.647744000000003 -11.746893 1;
	setAttr ".radi" 4.2300779914855973;
	setAttr -k on ".MaxHandle" 110;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Toe0" -p "Bip01_R_Foot";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 14.424514770507813 14.059976577758789 0 ;
	setAttr ".r" -type "double3" -2.6680430102392822e-007 -1.4941038357180604e-006 100.75186793595208 ;
	setAttr ".s" -type "double3" 1.0000000302671259 0.99999986293210119 0.999999940395356 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.41508099999999998 0.47481600000000002 2.4604590000000002 0
		 0.056755300000000002 2.4951270000000001 -0.47193200000000002 0 -2.5052120000000002 -0.0221441 -0.41835800000000001 0
		 -52.505594000000002 0.024903999999999999 23.544468999999999 1;
	setAttr ".radi" 1.5303853940963748;
	setAttr -k on ".MaxHandle" 111;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_R_Toe0Nub" -p "Bip01_R_Toe0";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	setAttr ".t" -type "double3" 7.2875499725341797 2.384185791015625e-007 5.7220458984375e-006 ;
	setAttr ".r" -type "double3" 6.4566631997777011e-006 1.0365344438377632e-005 -1.0245282533686164e-005 ;
	setAttr ".s" -type "double3" 1.0000001192093217 1.0000000000000251 1.000000238418612 ;
	setAttr ".ssc" no;
	setAttr ".radi" 1.5303853940963748;
	setAttr -k on ".MaxHandle" 136;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_RCalfTwist" -p "Bip01_R_Calf";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" -3.814697265625e-006 -4.76837158203125e-007 0 ;
	setAttr ".r" -type "double3" 0.27507769866745718 0 -4.2688687401467789e-007 ;
	setAttr ".s" -type "double3" 0.99999988079071045 1.0000000807428979 0.99999996175184003 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.21188699999999999 -2.5246179999999998 -0.18168699999999999 0
		 -0.39244899999999999 -0.14735000000000001 2.505169 0 -2.5005380000000001 0.23705300000000001 -0.37778 0
		 -37.078477999999997 154.097532 -3.2944749999999998 1;
	setAttr ".radi" 4.8847899055480957;
	setAttr -k on ".MaxHandle" 112;
	setAttr ".fbxID" 5;
createNode joint -n "Bip01_RCalfTwist1" -p "Bip01_RCalfTwist";
	addAttr -is true -ci true -h true -k true -sn "MaxHandle" -ln "MaxHandle" -smn 
		0 -smx 0 -at "long";
	addAttr -ci true -h true -sn "fbxID" -ln "filmboxTypeID" -at "short";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".t" -type "double3" 23.260902404785156 2.384185791015625e-007 -3.814697265625e-006 ;
	setAttr ".r" -type "double3" 0.27508577428329711 4.2688682312579694e-007 6.403302346886954e-007 ;
	setAttr ".s" -type "double3" 1 0.99999972378761637 1.0000000216084286 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" -0.21188599999999999 -2.5246179999999998 -0.18168699999999999 0
		 -0.404451 -0.14621000000000001 2.5033270000000001 0 -2.4986250000000001 0.237757 -0.38980500000000001 0
		 -42.007165000000001 95.372618000000003 -7.5206860000000004 1;
	setAttr ".radi" 4.8847899055480957;
	setAttr -k on ".MaxHandle" 113;
	setAttr ".fbxID" 5;
createNode lightLinker -s -n "lightLinker1";
	setAttr -s 8 ".lnk";
	setAttr -s 8 ".slnk";
createNode displayLayerManager -n "layerManager";
createNode displayLayer -n "defaultLayer";
createNode renderLayerManager -n "renderLayerManager";
createNode renderLayer -n "defaultRenderLayer";
	setAttr ".g" yes;
createNode phong -n "BruceWayne_Suit_Torso_MIC";
	setAttr ".dc" 1;
	setAttr ".ambc" -type "float3" 0.588 0.588 0.588 ;
	setAttr ".sc" -type "float3" 0 0 0 ;
	setAttr ".rfl" 1;
	setAttr ".cp" 2;
createNode shadingEngine -n "BruceWayne_BodySG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo1";
createNode phong -n "BruceWayne_Suit_Legs_MIC";
	setAttr ".dc" 1;
	setAttr ".ambc" -type "float3" 0.588 0.588 0.588 ;
	setAttr ".sc" -type "float3" 0 0 0 ;
	setAttr ".rfl" 1;
	setAttr ".cp" 2;
createNode shadingEngine -n "BruceWayne_BodySG1";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo2";
createNode file -n "BruceWayne_Suit_Torso_MIC_ncl1_1";
	setAttr ".ftn" -type "string" "C:/Project/NagaGame/Arts/animations/BruceWayne_Suit_Torso_D.tga";
createNode place2dTexture -n "place2dTexture1";
createNode file -n "BruceWayne_Suit_Legs_MIC_ncl1_1";
	setAttr ".ftn" -type "string" "G:/umodel_resources/animations/Batman_OZ/Textures/BruceWayne_Suit_Legs_D.tga";
createNode place2dTexture -n "place2dTexture2";
createNode phong -n "BruceWayne_Head_MIC";
	setAttr ".dc" 1;
	setAttr ".ambc" -type "float3" 0.588 0.588 0.588 ;
	setAttr ".sc" -type "float3" 0 0 0 ;
	setAttr ".rfl" 1;
	setAttr ".cp" 2;
createNode shadingEngine -n "BruceWayne_HeadSG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo3";
createNode shadingEngine -n "BruceWayne_HeadSG1";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo4";
createNode phong -n "BruceWayne_Hair_MIC";
	setAttr ".dc" 1;
	setAttr ".ambc" -type "float3" 0.588 0.588 0.588 ;
	setAttr ".sc" -type "float3" 0 0 0 ;
	setAttr ".rfl" 1;
	setAttr ".cp" 2;
createNode shadingEngine -n "BruceWayne_HeadSG2";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo5";
createNode phong -n "Character_FakeShadow";
	setAttr ".dc" 1;
	setAttr ".ambc" -type "float3" 0.588 0.588 0.588 ;
	setAttr ".sc" -type "float3" 0 0 0 ;
	setAttr ".rfl" 1;
	setAttr ".cp" 2;
createNode shadingEngine -n "BruceWayne_HeadSG3";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo6";
createNode file -n "BruceWayne_Head_MIC_ncl1_1";
	setAttr ".ftn" -type "string" "G:/umodel_resources/animations/Batman_OZ/Textures/BruceWayne_Head_D.tga";
createNode place2dTexture -n "place2dTexture3";
createNode file -n "BruceWayne_OZ_Eyes_MIC_ncl1_1";
	setAttr ".ftn" -type "string" "G:/umodel_resources/animations/Batman_OZ/Textures/Batman_V3_Eye_High_D.tga";
createNode place2dTexture -n "place2dTexture4";
createNode file -n "BruceWayne_Hair_MIC_ncl1_1";
	setAttr ".ftn" -type "string" "G:/umodel_resources/animations/Batman_OZ/Textures/BruceWayne_Hair_D.tga";
createNode place2dTexture -n "place2dTexture5";
createNode file -n "Character_FakeShadow_ncl1_1";
	setAttr ".ftn" -type "string" "Character_FakeShadow";
createNode place2dTexture -n "place2dTexture6";
createNode dagPose -n "bindPose1";
	setAttr -s 72 ".wm";
	setAttr -s 111 ".xm";
	setAttr ".xm[0]" -type "matrix" "xform" 2.5399998486065893 2.5399998486065893 2.54 0
		 0 -1.5707949558880989 0 0 277.86429916381837 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0 0 1 -0.70710678118654746 0 0 0.70710678118654768 1 1 1 no;
	setAttr ".xm[1]" -type "matrix" "xform" 1 0.99999988079173363 0.99999988079173363 -1.5707948962835925
		 -1.5707963267948966 0 0 3.1554436208840472e-030 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
		 0 0 0 0 0 1 0 0 0 1 0.39370081086760178 0.39370081086760178 0.39370078740157477 no;
	setAttr ".xm[2]" -type "matrix" "xform" 0.9999998617009932 0.99999992129299176 1.0000000000095588 -4.1397910156520111e-006
		 -1.4071075283638524e-006 -0.014752693269743855 0 8.7856826782226563 -0.0096882926300168055
		 1.2197416253911797e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1 1.0000001192082806
		 1.0000001192082806 no;
	setAttr ".xm[3]" -type "matrix" "xform" 1.0000001840995125 1.0000001840705506 1.0000000000000009 -3.3496044212199491e-010
		 4.3125161274132617e-008 -0.015549014018590414 0 12.174758911132827 -0.010385632514953391
		 -2.8812792152193472e-008 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.000000138299026
		 1.0000000787070145 0.9999999999904412 no;
	setAttr ".xm[4]" -type "matrix" "xform" 1.0000000646584639 1.0000000646874243 1.0000000000000009 -3.3544009842623006e-010
		 4.3125052738216399e-008 -0.015549000041533659 0 13.044387817382784 -0.010385990142823598
		 -2.8798240236910895e-008 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999981590052134
		 0.99999981592948328 0.99999999999999911 no;
	setAttr ".xm[5]" -type "matrix" "xform" 0.99999994274081483 0.99999994273979698 1.0000000000010254 -8.6567941775924077e-008
		 1.4294510856367991e-006 -0.016344989134788924 0 13.044372558593722 -0.010384559631349433
		 -6.5246174926869544e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.9999999353415403
		 0.99999993531257991 0.99999999999999911 no;
	setAttr ".xm[6]" -type "matrix" "xform" 1.0000001888389383 1.0000001888387953 1.0000000000001457 -5.2553087949388096e-008
		 -5.3736535021610851e-007 0.19497593307464184 0 15.851211547851563 -1.4802713394165057
		 -2.10568941838574e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000572591885
		 1.0000000572602064 0.9999999999989746 no;
	setAttr ".xm[7]" -type "matrix" "xform" 1.0000001797254661 0.99999991526991772 0.99999980972816982 0.045492026165115579
		 1.1077320413142835 2.986527173566607 0 -2.381134033203125 2.5143775939941406
		 -6.3621058464050293 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999981116109737
		 0.99999981116124037 0.99999999999985434 no;
	setAttr ".xm[8]" -type "matrix" "xform" 0.9999999014533778 1.0000001106433771 1.0000000237390849 -0.037952626713879799
		 -0.30515569644019364 -0.059364060017611707 0 18.579429626464844 3.814697265625e-006
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999982027456624 1.0000000847300894
		 1.0000001902718665 no;
	setAttr ".xm[9]" -type "matrix" "xform" 1.000000094060038 0.9999999343303384 0.99999988079071089 -2.9802324344803874e-008
		 -2.9802319584488005e-008 -0.40797655228785185 0 27.076812744140625 -9.5367431640625e-007
		 3.0517578125e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.000000098546632
		 0.99999988935663509 0.99999997626091564 no;
	setAttr ".xm[10]" -type "matrix" "xform" 0.99999988079071489 1.0000001832192862 1.0000000640307205 -0.018657705396286531
		 8.9406977821227967e-008 2.9802325940409408e-008 0 7.62939453125e-006 3.814697265625e-006
		 -1.52587890625e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.9999999059399709
		 1.0000000656696659 1.0000001192093033 no;
	setAttr ".xm[11]" -type "matrix" "xform" 0.99999988079072699 0.99999970507507197
		 1.0000001241810024 -0.018657639832416952 -1.4901162970204514e-007 1.0430814079143258e-007 0 13.198421478271484
		 0 -3.0517578125e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001192092993
		 0.99999981678074734 0.9999999359692836 no;
	setAttr ".xm[12]" -type "matrix" "xform" 0.99999998433146364 0.99999973128375919
		 0.99999984635350614 -0.045504380799603741 -1.1077332332886809 2.9865380807934261 0 -2.381134033203125
		 2.5143413543701172 6.3621191978454581 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999981116109737
		 0.99999981116124037 0.99999999999985434 no;
	setAttr ".xm[13]" -type "matrix" "xform" 1.0000004382287226 1.0000000571532539 1.0000000948630015 0.037952635341691361
		 0.30515562109664784 -0.059364011053946342 0 18.579452514648438 1.9073486328125e-006
		 -1.52587890625e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000156685367
		 1.000000268716313 1.0000001536465175 no;
	setAttr ".xm[14]" -type "matrix" "xform" 0.99999975095236426 1.0000001177083486 0.99999976158142334 -5.9604637759427225e-008
		 8.9406989429685389e-008 -0.40797696032491126 0 27.076797485351563 -4.76837158203125e-007
		 -3.0517578125e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999956177146943
		 0.99999994284674931 0.99999990513700754 no;
	setAttr ".xm[15]" -type "matrix" "xform" 1.0000002384185951 1.0000000645867473 1.0000001244590095 0.01865773742148729
		 0 1.7881389169361599e-007 0 1.52587890625e-005 7.62939453125e-006 -1.52587890625e-005 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000002490476978 0.99999988229166525
		 1.0000002384186335 no;
	setAttr ".xm[16]" -type "matrix" "xform" 1.0000000000000009 0.99999994456417463 1.0000001829412566 0.01865769494348192
		 0 4.4703483581542942e-008 0 13.198421478271484 -5.7220458984375e-006 4.57763671875e-005 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999976158146175 0.99999993541325694
		 0.999999875541006 no;
	setAttr ".xm[17]" -type "matrix" "xform" 1.0000004379632215 1.0000002975967377 1.0000001721369147 -1.5150410356275574
		 0.072361150537672822 0.11822129469402778 0 26.396884918212891 7.62939453125e-006
		 -1.52587890625e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000002490476978
		 0.99999988229166525 1.0000002384186335 no;
	setAttr ".xm[18]" -type "matrix" "xform" 0.99999984176324686 0.99999998200302043
		 0.99999978602629269 0.25531332503070964 0.16394467958272677 0.22072599089180542 0 10.714435577392578
		 -0.5559539794921875 -4.2694988250732422 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999956203697038
		 0.9999997024033509 0.99999982786311492 no;
	setAttr ".xm[19]" -type "matrix" "xform" 1.0000001163874284 1.0000001014184718 1.00000011920929 -9.6857537936866027e-008
		 -5.9604637838160142e-008 0.25385523406241817 0 4.8124427795410156 7.62939453125e-006
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001582367781 1.0000000179969799
		 1.0000002139737532 no;
	setAttr ".xm[20]" -type "matrix" "xform" 0.99999999955452212 0.99999999360996283
		 0.99999994039535922 1.750886451465318e-007 0 0.099899524008013552 0 2.6223373413085938
		 1.52587890625e-005 -1.9073486328125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999988361258518
		 0.99999989858153848 0.99999988079072422 no;
	setAttr ".xm[21]" -type "matrix" "xform" 0.99999973179403689 0.99999968427654418
		 0.99999986812787223 -0.071874638696009657 -0.19703763202444863 0.13238508640599495 0 10.60528564453125
		 -0.1732940673828125 3.8393726348876953 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999956203697038
		 0.9999997024033509 0.99999982786311492 no;
	setAttr ".xm[22]" -type "matrix" "xform" 0.99999995341912506 1.0000000882579043 0.99999994039535645 -3.3527609727080679e-008
		 0 0.25819461951006928 0 3.3597221374511719 -3.814697265625e-005 0 0 0 0 0 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000002682060349 1.0000003157235555 1.0000001318721452 no;
	setAttr ".xm[23]" -type "matrix" "xform" 1.0000001020439686 1.0000001969233494 1.0000001192092909 -1.6763803041894389e-008
		 6.7055218529733886e-008 0.44361228182511508 0 2.0222625732421875 -7.62939453125e-006
		 -3.814697265625e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000465808772
		 0.99999991174210345 1.0000000596046472 no;
	setAttr ".xm[24]" -type "matrix" "xform" 0.99999969504655806 0.99999987606655683
		 0.99999984286330212 1.5050317292203217 0.64300003721498589 0.4639693928279342 0 2.4199371337890625
		 1.073486328125 -4.1273365020751953 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999956203697038
		 0.9999997024033509 0.99999982786311492 no;
	setAttr ".xm[25]" -type "matrix" "xform" 1.0000002595836328 1.0000001538740062 1.0000001192092907 5.9604635603786548e-008
		 5.9604629303004458e-008 0.13864110449661812 0 4.2228050231933594 -1.52587890625e-005
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000003049535349 1.0000001239334586
		 1.0000001571367225 no;
	setAttr ".xm[26]" -type "matrix" "xform" 1.0000000477368338 0.99999987154008163 1.00000011920929 -1.6391279418854698e-007
		 -1.4901160482513435e-008 0.17130154099593273 0 3.8627700805664062 1.52587890625e-005
		 -7.62939453125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999974041643458
		 0.99999984612601744 0.99999988079072355 no;
	setAttr ".xm[27]" -type "matrix" "xform" 0.99999976502204113 0.99999984297554045
		 0.99999972044748697 0.020426520453980364 0.066542309912057146 0.18892263860334524 0 11.282051086425781
		 -0.7739715576171875 -1.4246807098388672 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999956203697038
		 0.9999997024033509 0.99999982786311492 no;
	setAttr ".xm[28]" -type "matrix" "xform" 1.000000037529029 0.99999972692487837 1.000000000000008 0
		 2.9802321269243138e-008 0.31952960754718823 0 5.1384735107421875 -7.62939453125e-006
		 -5.7220458984375e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000002349780142
		 1.0000001570244843 1.0000002795525911 no;
	setAttr ".xm[29]" -type "matrix" "xform" 1.0000001292009288 1.0000001300627785 0.99999994039535545 -4.8428767581224782e-008
		 -5.9604637074416182e-008 0.057870086952553031 0 2.959136962890625 7.62939453125e-006
		 5.7220458984375e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999996247097245
		 1.0000002730751962 0.99999999999999201 no;
	setAttr ".xm[30]" -type "matrix" "xform" 0.99999981269670213 1.0000001008813486 0.9999998402886402 -0.015753644107464132
		 -0.069115934507281179 0.17348013058931938 0 11.279922485351563 -0.903228759765625
		 1.1801109313964844 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999956203697038
		 0.9999997024033509 0.99999982786311492 no;
	setAttr ".xm[31]" -type "matrix" "xform" 0.99999995894449223 1.0000000588560052 1.0000001192092938 -2.2351740475237421e-008
		 -1.490116180562242e-008 0.25963684288541949 0 4.6826515197753906 7.62939453125e-006
		 -1.9073486328125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001873033328
		 0.99999989911866161 1.0000001597113852 no;
	setAttr ".xm[32]" -type "matrix" "xform" 1.0000000361650081 0.99999970693137086 1.0000001192092949 1.2665990726775048e-007
		 5.9604642619788276e-008 0.24274752713483916 0 2.660888671875 -1.52587890625e-005
		 -7.62939453125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000410555094
		 0.99999994114399826 0.99999988079072044 no;
	setAttr ".xm[33]" -type "matrix" "xform" 0.99999989572232895 1.0000000091880086 0.99999991005435274 1.5150409011046475
		 -0.072361070321397034 0.11822083182348284 0 26.396877288818359 0 0 0 0 0 0 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.9999999059399709 1.0000000656696659 1.0000001192093033 no;
	setAttr ".xm[34]" -type "matrix" "xform" 1.0000000121947425 1.000000061850338 0.99999995753601933 -0.25531311102987286
		 -0.16394436441834459 0.22072587903447086 0 10.714420318603516 -0.555938720703125
		 4.2694950103759766 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001042776818
		 0.99999999081199153 1.0000000899456554 no;
	setAttr ".xm[35]" -type "matrix" "xform" 1.0000001569314729 1.0000002595327193 1.0000000000000058 7.4505786632549304e-009
		 -1.4901158855386849e-008 0.25385491565254198 0 4.8124504089355469 0 -1.9073486328125e-006 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999998780525756 0.99999993814966581
		 1.0000000424639826 no;
	setAttr ".xm[36]" -type "matrix" "xform" 0.99999964370971872 0.99999947173189829
		 0.99999964237213146 -1.4901169065659952e-008 2.9802333005976931e-008 0.099899559675484598 0 2.622314453125
		 -7.62939453125e-006 -7.62939453125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999984306855172
		 0.99999974046734807 0.99999999999999423 no;
	setAttr ".xm[37]" -type "matrix" "xform" 1.0000001154747933 1.0000000332139476 0.99999987606729601 0.071874845975211654
		 0.19703778335872857 0.13238497801928617 0 10.605270385742188 -0.173309326171875
		 -3.8393745422363281 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001042776818
		 0.99999999081199153 1.0000000899456554 no;
	setAttr ".xm[38]" -type "matrix" "xform" 1.0000000110480278 1.0000000034384391 1.00000011920929 -1.8626451428263659e-008
		 4.4703483087657658e-008 0.25819460429089169 0 3.3597373962402344 0 0 0 0 0 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999988452522004 0.99999996678605352 1.0000001239327194 no;
	setAttr ".xm[39]" -type "matrix" "xform" 0.99999975344931991 0.99999983286726779
		 1.0000001192092935 -9.3132273026999474e-009 -6.7055241904830003e-008 0.44361238148543086 0 2.022247314453125
		 7.62939453125e-006 3.814697265625e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999998895197229
		 0.99999999656156091 0.99999988079072422 no;
	setAttr ".xm[40]" -type "matrix" "xform" 0.99999997551227582 0.99999995180202395
		 0.99999985407738001 -1.5050315582758156 -0.64299967812958558 0.463969159498684 0 2.4199371337890625
		 1.073486328125 4.1273288726806641 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001042776818
		 0.99999999081199153 1.0000000899456554 no;
	setAttr ".xm[41]" -type "matrix" "xform" 1.0000002472278287 1.0000003639210355 1.0000003576278722 1.4901155771003669e-008
		 -7.4505787549334272e-008 0.13864101594755893 0 4.2228126525878906 -7.62939453125e-006
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000244877247 1.0000000481979783
		 1.0000001459226413 no;
	setAttr ".xm[42]" -type "matrix" "xform" 0.99999990995131904 1.0000000353456469 0.99999994039535633 -7.4505803335782408e-008
		 -4.4703487607033077e-008 0.17130144385242294 0 3.8627548217773437 0 1.52587890625e-005 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999975277223252 0.99999963607909692
		 0.99999964237225569 no;
	setAttr ".xm[43]" -type "matrix" "xform" 0.9999999644522729 0.99999995835001831 0.9999998852106905 -0.020426286370135022
		 -0.066542117411332438 0.18892247638090592 0 11.282058715820313 -0.77398681640625
		 1.4246826171875 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001042776818
		 0.99999999081199153 1.0000000899456554 no;
	setAttr ".xm[44]" -type "matrix" "xform" 1.0000000941166822 1.0000001319813359 0.999999940395359 -1.2665985343096824e-007
		 -1.4901159791399936e-008 0.3195295888241782 0 5.1384925842285156 -1.52587890625e-005
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000355477283 1.0000000416499835
		 1.0000001147893227 no;
	setAttr ".xm[45]" -type "matrix" "xform" 0.99999994982448093 0.99999995758114879
		 0.99999988079071056 1.4156103734640837e-007 7.4505809707606018e-008 0.057870082418539331 0 2.9591217041015625
		 7.62939453125e-006 -1.9073486328125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999990588332666
		 0.99999986801868157 1.0000000596046446 no;
	setAttr ".xm[46]" -type "matrix" "xform" 1.0000000316071613 0.99999994396551961 0.99999967038284554 0.015753736336281802
		 0.069116068721174984 0.17347994221087204 0 11.279930114746094 -0.9032440185546875
		 -1.1801185607910156 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001042776818
		 0.99999999081199153 1.0000000899456554 no;
	setAttr ".xm[47]" -type "matrix" "xform" 0.9999999859468427 1.0000000665071409 1.0000002384185795 -1.8626450253517625e-008
		 -4.4703484209768075e-008 0.25963671236935743 0 4.6826438903808594 0 0 0 0 0 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999996839283967 1.0000000560344835 1.000000329617263 no;
	setAttr ".xm[48]" -type "matrix" "xform" 0.99999997417781272 0.99999982264557674
		 0.999999940395357 -7.4505819183175002e-009 0 0.24274777275340118 0 2.6608734130859375
		 0 3.814697265625e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000140531575
		 0.99999993349286354 0.9999997615814773 no;
	setAttr ".xm[49]" -type "matrix" "xform" 1.0000006759433269 0.99999998366050347 1.0000003973256029 2.9946434157939117
		 -0.090276541971428481 -3.114972739749617 0 -1.52587890625e-005 1.8906783225247636e-005
		 10.18528938293457 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1 1.0000001192082806
		 1.0000001192082806 no;
	setAttr ".xm[50]" -type "matrix" "xform" 0.99999976158142101 1.0000002384185793 1.000000000000002 -2.7124763518628275e-008
		 1.4901164746562182e-008 -3.7252911866405455e-009 0 -7.62939453125e-006 -1.1920928955078125e-007
		 -1.9073486328125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999932405712999
		 1.0000000163394969 0.99999960267455501 no;
	setAttr ".xm[51]" -type "matrix" "xform" 0.99999998805914603 0.99999995855775048
		 0.99999987456959283 -2.9946406336626681 0.090279447037855121 -3.1149724749534125 0 1.52587890625e-005
		 -9.3431335699278861e-006 -10.18528938293457 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 
		0 0 0 1 1 1.0000001192082806 1.0000001192082806 no;
	setAttr ".xm[52]" -type "matrix" "xform" 1.0000002384185791 1.0000001192092904 1.0000004768371604 4.3190079249134181e-008
		 0 5.5879341154255592e-009 0 -7.62939453125e-006 -2.384185791015625e-007 0 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000119408541 1.0000000414422512
		 1.0000001254304229 no;
	setAttr ".xm[53]" -type "matrix" "xform" 1.0000001192092969 0.99999994039585016 1.0000000000004767 -9.9465256897489794e-007
		 1.1920927533992765e-007 -2.6077028980609293e-008 0 7.62939453125e-006 0 3.0517578125e-005 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.000000098546632 0.99999988935663509
		 0.99999997626091564 no;
	setAttr ".xm[54]" -type "matrix" "xform" 0.99999994039535534 0.9999998211860659 0.99999988079071089 1.7345886053899418e-008
		 1.4901162082026129e-008 9.3132263012663306e-010 0 24.471817016601563 -2.384185791015625e-007
		 -1.9073486328125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000002384186359
		 0.99999976158147752 0.999999999999998 no;
	setAttr ".xm[55]" -type "matrix" "xform" 0.99999976158142101 1.0000001192097623 0.99999988079116209 9.7230065199096282e-007
		 0 -1.4901164746562179e-008 0 0 4.76837158203125e-007 0 0 0 0 0 0 0 0 0 0 0 0
		 0 0 0 0 0 0 0 1 0 0 0 1 0.99999956177146943 0.99999994284674931 0.99999990513700754 no;
	setAttr ".xm[56]" -type "matrix" "xform" 0.99999988079071056 0.99999994039541018
		 1.0000000000000577 3.3155085632507008e-007 0 1.4901162970204707e-008 0 9.0255966186523437
		 9.5367431640625e-007 -3.0517578125e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999988079071733
		 1.0000000596041534 0.99999999999952327 no;
	setAttr ".xm[57]" -type "matrix" "xform" 0.99999988079071112 1.0000002384186331 1.0000000000000473 3.2782546810495222e-007
		 -2.9802325940409402e-008 2.2351744455307058e-008 0 9.0255889892578125 4.76837158203125e-007
		 -1.52587890625e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001192093038
		 1.0000000596045933 0.99999999999994227 no;
	setAttr ".xm[58]" -type "matrix" "xform" 1.0000000000000004 0.99999994039540907 1.0000000000000528 -3.2782556580456277e-007
		 -2.9802322387695303e-008 -1.1175870895385742e-008 0 9.025604248046875 4.76837158203125e-007
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000002384186359 0.99999988079025193
		 1.0000001192088521 no;
	setAttr ".xm[59]" -type "matrix" "xform" 0.99999994039535933 0.99999994039540663
		 1.0000000000000573 -3.2037498476355269e-007 8.9406972492156522e-008 1.1175871561519597e-008 0 9.025604248046875
		 -2.384185791015625e-006 1.52587890625e-005 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 
		0 0 0 1 0.99999999999999956 1.0000000596045944 0.99999999999994715 no;
	setAttr ".xm[60]" -type "matrix" "xform" 1.0000003249458189 1.0000003246063727 1.0000002384185807 -7.2643137239582016e-008
		 7.4505781758896013e-009 -0.045575845876946304 0 48.943649291992188 1.1920928955078125e-007
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000119408541 1.0000000414422512
		 1.0000001254304229 no;
	setAttr ".xm[61]" -type "matrix" "xform" 0.99999988079071045 1.0000000807428979 0.99999996175184003 0.0048010115405559464
		 0 -7.4505814851023537e-009 0 -3.814697265625e-006 -4.76837158203125e-007 0 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999967505428666 0.99999967539373269
		 0.99999976158147619 no;
	setAttr ".xm[62]" -type "matrix" "xform" 0.99999978906105702 1.0000003225696827 1.0000000000000009 1.02445450161906e-007
		 0 -0.045575870317277278 0 48.943630218505859 -4.1723251342773438e-007 0 0 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999932405712999 1.0000000163394969
		 0.99999960267455501 no;
	setAttr ".xm[63]" -type "matrix" "xform" 0.99999994039535567 1.0000000809262208 0.99999996113033551 -0.0048010497204743997
		 2.2351743123039183e-008 1.8626452602532661e-008 0 -3.814697265625e-006 0 0 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000002109389874 0.99999967743042129
		 0.99999999999999911 no;
	setAttr ".xm[64]" -type "matrix" "xform" 0.9999999830524251 1.0000000320114972 0.99999989520903854 -0.020394247610565439
		 -0.10189398248531285 0.059332787060494455 0 46.521804809570313 9.5367431640625e-007
		 -1.9073486328125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000002109389874
		 0.99999967743042129 0.99999999999999911 no;
	setAttr ".xm[65]" -type "matrix" "xform" 0.99999979603414968 0.99999985459239293
		 0.99999982118606601 -1.6763808780663934e-008 4.3888585280527055e-008 1.758451867495308 0 14.424516677856445
		 14.059968948364258 -9.5367431640625e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000169475751
		 0.99999996798850377 1.0000001047909723 no;
	setAttr ".xm[66]" -type "matrix" "xform" 1.0000000042498454 0.99999991238263353 0.99999997754203007 0.020394250506438852
		 0.10189420500069929 0.059332760893629204 0 46.521808624267578 -1.6689300537109375e-006
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999967505428666 0.99999967539373269
		 0.99999976158147619 no;
	setAttr ".xm[67]" -type "matrix" "xform" 1.0000000302671259 0.99999986293210119 0.999999940395356 -4.6566135113496261e-009
		 -2.6077031299956607e-008 1.7584518230168671 0 14.424514770507813 14.059976577758789
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999999575015464 1.0000000876173742
		 1.0000000224579704 no;
	setAttr ".xm[68]" -type "matrix" "xform" 0.99999994039535522 0.99999994039535534
		 0.99999994039535522 -1.746229931487437e-009 0 1.8626452602532661e-009 0 24.471817016601563
		 1.1920928955078125e-007 1.9073486328125e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 
		0 0 0 1 0.99999976158147774 0.99999988079072377 0.99999952316306695 no;
	setAttr ".xm[69]" -type "matrix" "xform" 1 0.99999972378761637 1.0000000216084286 0.0048011524866414792
		 7.4505805969238281e-009 1.1175870895385742e-008 0 23.260902404785156 2.384185791015625e-007
		 -3.814697265625e-006 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001192093038
		 0.99999991925710863 1.0000000382481615 no;
	setAttr ".xm[70]" -type "matrix" "xform" 1.0000000000000002 0.99999996237783284 0.99999990265538252 -0.0048011876635510164
		 7.4505805969238265e-009 -1.862645149230957e-008 0 23.260902404785156 0 -1.9073486328125e-006 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000596046479 0.99999991907378571
		 1.0000000388696659 no;
	setAttr ".xm[71]" -type "matrix" "xform" 0.99999988640765658 0.9999998325769438 1.0000001450242231 -0.0020840275049471011
		 3.6715088831963301e-007 -0.13278030685054304 0 12.824172973632813 -2.86102294921875e-005
		 -8.0035533756017685e-011 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.99999981116109737
		 0.99999981116124037 0.99999999999985434 no;
	setAttr ".xm[72]" -type "matrix" "xform" 1.0000001480870624 1.0000003146505045 1.0000001701421017 -0.21897911343915705
		 -1.5687108314336655 -1.5705819461515003 0 2.84716796875 11.19731616973877 3.3251931667327881 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564 1.0000001674230843
		 0.99999985497579791 no;
	setAttr ".xm[73]" -type "matrix" "xform" 1.0000000563894522 1.000000028843566 0.99999982735667869 -1.7280514749951998
		 -1.5688448484131641 -1.4136770955091249 0 -1.738616943359375 3.8094263076782227
		 0.0079449191689491272 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[74]" -type "matrix" "xform" 1.0000001474344096 1.0000000673953122 1.0000001515750323 0.34752812837233915
		 -1.5687111444052151 -1.5707980870721532 0 2.8271636962890625 11.197317123413086
		 3.3251931667327881 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[75]" -type "matrix" "xform" 0.9999999962063113 1.0000001380512955 0.99999994749304066 -1.7451100015609076
		 -1.568845144817093 -1.4136220904583707 0 -0.901275634765625 16.132286071777344
		 0.033658366650342941 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[76]" -type "matrix" "xform" 1.0000000235924613 1.0000000756485699 1.0000001223635941 -0.217759379341396
		 -1.5687133671666731 -1.571876978393079 0 2.8471527099609375 11.211082458496094
		 -3.2784907817840576 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[77]" -type "matrix" "xform" 1.0000002637881238 0.99999999349884894 1.0000003120249548 0.34836656442344621
		 -1.5687125144379526 -1.5717187687411922 0 2.8271484375 11.211081504821777 -3.2784907817840576 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564 1.0000001674230843
		 0.99999985497579791 no;
	setAttr ".xm[78]" -type "matrix" "xform" 0.99999993143851784 0.99999988813947382
		 1.0000000147943893 -0.0067105007518256628 -0.00073273864048162881 -0.00040054495930104216 0 0.0015409030020236969
		 -3.9849047660827637 -2.6629180908203125 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0.999999943610551
		 0.9999999711564348 1.0000001726433512 no;
	setAttr ".xm[79]" -type "matrix" "xform" 1.0000001984674323 1.0000003473465331 1.0000004387806261 0.059642302555750926
		 -0.00061948007022061215 -0.00070001172733712505 0 0.0015816092491149902 -2.6669435501098633
		 0.0414581298828125 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000000685614869
		 1.0000001118605386 0.99999998520561095 no;
	setAttr ".xm[80]" -type "matrix" "xform" 1.0000002805419907 1.000000363181069 1.0000003292387143 -1.6829400970679087
		 -0.64100961930982625 -1.6111610667736238 0 -0.88177490234375 13.886350631713867
		 1.5694594383239746 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[81]" -type "matrix" "xform" 0.9999997555285921 1.0000002101564867 0.99999983480905763 -1.6155134567782627
		 -1.0798123633385248 -1.5889340138829136 0 1.045745849609375 12.83452033996582
		 3.9287219047546387 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[82]" -type "matrix" "xform" 1.0000000862219931 1.000000074620073 1.0000000147697876 -1.8322635404877183
		 -0.71883467281011759 -1.6909321444615208 0 1.4221343994140625 13.220524787902832
		 1.8776724338531494 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[83]" -type "matrix" "xform" 1.0000001068910378 1.0000000644057836 1.0000000547628549 -2.0044956830548832
		 -0.5298000209191811 -1.1701054124144912 0 1.41448974609375 11.68546199798584
		 5.8484487533569336 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[84]" -type "matrix" "xform" 1.0000000307484245 1.000000224216538 0.99999995782995488 -1.7836399765074815
		 -1.0443067223604325 -1.5765062851028353 0 4.56695556640625 13.26071834564209
		 4.2466583251953125 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[85]" -type "matrix" "xform" 1.0000000051930817 1.0000001002046257 1.0000001655309008 -2.7140012349790177
		 -1.3361256872871976 -0.53794005836128023 0 4.235015869140625 14.085427284240723
		 1.7951710224151611 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[86]" -type "matrix" "xform" 1.0000000258485908 1.0000001397744225 0.99999999983555554 -1.4201089638041928
		 -0.35745000397773863 -2.1809352573220804 0 4.0710296630859375 11.310193061828613
		 6.0741987228393555 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[87]" -type "matrix" "xform" 1.0000000535957694 1.0000001933226301 1.0000000168539824 -1.6559164486085725
		 -1.5688462805092858 -1.4134369568351097 0 -3.6468048095703125 14.258105278015137
		 0.02973468042910099 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[88]" -type "matrix" "xform" 0.99999991820062217 0.99999999194854372
		 0.9999999375526667 -1.6445848784454293 -0.9638407228755721 -1.5505453191981857 0 -3.6117401123046875
		 13.807672500610352 1.4456225633621216 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[89]" -type "matrix" "xform" 1.0000001591643473 1.0000002295620594 1.0000002028690769 -0.69257326297520794
		 -0.69818832432785027 -2.8228101242701942 0 -1.929779052734375 12.960015296936035
		 2.9313311576843262 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[90]" -type "matrix" "xform" 0.99999993746792715 1.0000002472249989 0.99999996539572411 -1.5805925673417358
		 -1.0974777000170493 -1.4896962520809345 0 -4.20208740234375 12.579263687133789
		 2.9253342151641846 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[91]" -type "matrix" "xform" 1.0000000063632424 1.0000002519237401 1.0000000558256148 -0.84231947842755883
		 -1.5508836192213971 -2.2961140727350671 0 4.137420654296875 14.20120906829834
		 0.029600765556097031 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[92]" -type "matrix" "xform" 0.9999999920110243 1.0000000117998205 0.99999981503904489 -1.5832245129597877
		 -0.44299922366316519 -1.4449758889885631 0 -3.2087554931640625 9.1115598678588867
		 5.7742323875427246 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[93]" -type "matrix" "xform" 1.0000003963968027 1.0000004211351243 1.000000097105296 -1.7851463132116778
		 -1.1734387038878102 -1.7567499426538198 0 7.52313232421875 11.866493225097656
		 4.4020452499389648 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[94]" -type "matrix" "xform" 1.0000002194593527 1.0000002711308678 1.0000001272873076 -1.6064633766253493
		 -0.88777493896186066 -1.5479181099254224 0 -4.2841644287109375 13.48287296295166
		 1.6956325769424438 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[95]" -type "matrix" "xform" 0.99999999378990523 1.0000003645268212 0.99999997865954326 -1.7134193241947271
		 -1.5688463836407522 -1.413691623431292 0 -4.34368896484375 14.030208587646484
		 0.029259419068694115 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[96]" -type "matrix" "xform" 1.0000001256821371 1.0000001743971356 1.0000000947367684 1.5349754644133731
		 -0.89194231365026722 1.5937945468512054 0 -4.2841644287109375 13.48982048034668
		 -1.6394128799438477 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[97]" -type "matrix" "xform" 1.0000000432513445 1.0000000355978338 0.99999997451245226 1.4968558849849192
		 -0.96800847213428365 1.5911711732704874 0 -3.6117401123046875 13.813577651977539
		 -1.3880501985549927 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[98]" -type "matrix" "xform" 1.0000002042130622 1.0000002171630722 1.0000001077754777 0.41205346103368801
		 -1.3382330480984097 2.6187699939217284 0 4.235015869140625 14.092792510986328
		 -1.7364223003387451 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[99]" -type "matrix" "xform" 1.000000207556798 1.0000001942805745 0.99999994850437834 1.4588618080548141
		 -0.64517506203013908 1.5303073382612256 0 -0.88177490234375 13.89277458190918
		 -1.511557936668396 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[100]" -type "matrix" "xform" 1.0000001592386358 1.0000000002639513 0.99999997927175843 1.5262374286601859
		 -1.0839803983855336 1.5525192127722804 0 1.045745849609375 12.850784301757813
		 -3.8751707077026367 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[101]" -type "matrix" "xform" 0.99999991450936943 0.99999982731635417
		 0.99999989609536444 1.3099938694647892 -0.72297393483841466 1.4502229449392923 0 1.4221038818359375
		 13.228241920471191 -1.8225302696228027 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[102]" -type "matrix" "xform" 1.0000000273783125 1.000000060349159 1.0000000262383459 1.1352069401359861
		 -0.53363786685964743 1.972445460355569 0 1.4145050048828125 11.709738731384277
		 -5.7996892929077148 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[103]" -type "matrix" "xform" 1.0000000386989976 0.99999999347088819
		 0.99999996045569495 1.3579982986037269 -1.0484757189162397 1.5650467803250712 0 4.5669708251953125
		 13.278307914733887 -4.1913270950317383 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[104]" -type "matrix" "xform" 0.99999998513048804 1.0000000205693171
		 0.99999985097120181 1.7240441188814206 -0.36086827396202847 0.95975935228712461 0 4.0710296630859375
		 11.335417747497559 -6.0269870758056641 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[105]" -type "matrix" "xform" 1.0000000101321698 1.000000212642292 1.0000001344686817 2.4541921311339898
		 -0.69948986652983947 0.31545461687037707 0 -1.929779052734375 12.972107887268066
		 -2.8772652149200439 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[106]" -type "matrix" "xform" 0.99999998753150698 1.0000000583305906
		 1.0000000218649741 1.5602500967195703 -1.1016328005296625 1.6525635755287997 0 -4.2020721435546875
		 12.59134578704834 -2.8728713989257813 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[107]" -type "matrix" "xform" 1.0000002002407453 1.0000001084366184 1.0000000268035909 1.5577865685074372
		 -0.44713402576022299 1.6968672540377487 0 -3.208770751953125 9.135554313659668
		 -5.7362251281738281 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[108]" -type "matrix" "xform" 1.000000093616213 1.0000001189838987 0.9999999427847539 1.3582950676815273
		 -1.1775756519166827 1.3830042891299288 0 7.5231170654296875 11.884737968444824
		 -4.3525280952453613 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[109]" -type "matrix" "xform" 1.0000000267302838 1.0000000295002953 0.99999988356190239 -1.5705562845547287
		 -1.5687118612882316 -1.5712538158527896 0 2.8371734619140625 11.19731616973877
		 3.3251991271972656 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr ".xm[110]" -type "matrix" "xform" 0.99999999909091764 1.0000000640630855
		 0.99999976694950732 -1.57041327403677 -1.5687541445251787 -1.5712632890493685 0 2.8364410400390625
		 11.211989402770996 -3.2774474620819092 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1.0000001135923564
		 1.0000001674230843 0.99999985497579791 no;
	setAttr -s 72 ".m";
	setAttr -s 73 ".p";
	setAttr -s 111 ".g[0:110]" yes no no no no no no no yes yes no no no 
		yes yes no no no no no no no no no no no no no no no no no no no no no no no no no 
		no no no no no no no no no yes no yes no no no no no no no no yes no yes no no no 
		no no no no no no no yes no no no no no no no no no no no no no no no no no no no 
		no no no no no no no no no no no no no no no no no no;
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
		+ "                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n"
		+ "                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n"
		+ "                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n            modelEditor -e \n                -pluginObjects \"gpuCacheDisplayFilter\" 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n"
		+ "            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n"
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
		+ "                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -keyReleaseCommand \"nodeEdKeyReleaseCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                $editorName;\n\t\t\tif (`objExists nodeEditorPanel1Info`) nodeEditor -e -restoreInfo nodeEditorPanel1Info $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n"
		+ "                -defaultPinnedState 0\n                -ignoreAssets 1\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -keyReleaseCommand \"nodeEdKeyReleaseCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                $editorName;\n\t\t\tif (`objExists nodeEditorPanel1Info`) nodeEditor -e -restoreInfo nodeEditorPanel1Info $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"createNodePanel\" (localizedPanelLabel(\"Create Node\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"createNodePanel\" -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Texture Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"polyTexturePlacementPanel\" -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"renderWindowPanel\" -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"blendShapePanel\" (localizedPanelLabel(\"Blend Shape\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\tblendShapePanel -unParent -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tblendShapePanel -edit -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" == $panelName) {\n"
		+ "\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynRelEdPanel\" -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"relationshipPanel\" -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"referenceEditorPanel\" -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"componentEditorPanel\" -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynPaintScriptedPanelType\" -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"scriptEditorPanel\" -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n"
		+ "        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-defaultImage \"\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"vertical2\\\" -ps 1 41 100 -ps 2 59 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Outliner\")) \n\t\t\t\t\t\"outlinerPanel\"\n\t\t\t\t\t\"$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\\\"Outliner\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\noutlinerEditor -e \\n    -showShapes 0\\n    -showReferenceNodes 0\\n    -showReferenceMembers 0\\n    -showAttributes 0\\n    -showConnected 0\\n    -showAnimCurvesOnly 0\\n    -showMuteInfo 0\\n    -organizeByLayer 1\\n    -showAnimLayerWeight 1\\n    -autoExpandLayers 1\\n    -autoExpand 0\\n    -showDagOnly 1\\n    -showAssets 1\\n    -showContainedOnly 1\\n    -showPublishedAsConnected 0\\n    -showContainerContents 1\\n    -ignoreDagHierarchy 0\\n    -expandConnections 0\\n    -showUpstreamCurves 1\\n    -showUnitlessCurves 1\\n    -showCompounds 1\\n    -showLeafs 1\\n    -showNumericAttrsOnly 0\\n    -highlightActive 1\\n    -autoSelectNewObjects 0\\n    -doNotSelectNewObjects 0\\n    -dropIsParent 1\\n    -transmitFilters 0\\n    -setFilter \\\"defaultSetFilter\\\" \\n    -showSetMembers 1\\n    -allowMultiSelection 1\\n    -alwaysToggleSelect 0\\n    -directSelect 0\\n    -displayMode \\\"DAG\\\" \\n    -expandObjects 0\\n    -setsIgnoreFilters 1\\n    -containersIgnoreFilters 0\\n    -editAttrName 0\\n    -showAttrValues 0\\n    -highlightSecondary 0\\n    -showUVAttrsOnly 0\\n    -showTextureNodesOnly 0\\n    -attrAlphaOrder \\\"default\\\" \\n    -animLayerFilterOptions \\\"allAffecting\\\" \\n    -sortOrder \\\"none\\\" \\n    -longNames 0\\n    -niceNames 1\\n    -showNamespace 1\\n    -showPinIcons 0\\n    -mapMotionTrails 0\\n    -ignoreHiddenAttribute 0\\n    $editorName\"\n"
		+ "\t\t\t\t\t\"outlinerPanel -edit -l (localizedPanelLabel(\\\"Outliner\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\noutlinerEditor -e \\n    -showShapes 0\\n    -showReferenceNodes 0\\n    -showReferenceMembers 0\\n    -showAttributes 0\\n    -showConnected 0\\n    -showAnimCurvesOnly 0\\n    -showMuteInfo 0\\n    -organizeByLayer 1\\n    -showAnimLayerWeight 1\\n    -autoExpandLayers 1\\n    -autoExpand 0\\n    -showDagOnly 1\\n    -showAssets 1\\n    -showContainedOnly 1\\n    -showPublishedAsConnected 0\\n    -showContainerContents 1\\n    -ignoreDagHierarchy 0\\n    -expandConnections 0\\n    -showUpstreamCurves 1\\n    -showUnitlessCurves 1\\n    -showCompounds 1\\n    -showLeafs 1\\n    -showNumericAttrsOnly 0\\n    -highlightActive 1\\n    -autoSelectNewObjects 0\\n    -doNotSelectNewObjects 0\\n    -dropIsParent 1\\n    -transmitFilters 0\\n    -setFilter \\\"defaultSetFilter\\\" \\n    -showSetMembers 1\\n    -allowMultiSelection 1\\n    -alwaysToggleSelect 0\\n    -directSelect 0\\n    -displayMode \\\"DAG\\\" \\n    -expandObjects 0\\n    -setsIgnoreFilters 1\\n    -containersIgnoreFilters 0\\n    -editAttrName 0\\n    -showAttrValues 0\\n    -highlightSecondary 0\\n    -showUVAttrsOnly 0\\n    -showTextureNodesOnly 0\\n    -attrAlphaOrder \\\"default\\\" \\n    -animLayerFilterOptions \\\"allAffecting\\\" \\n    -sortOrder \\\"none\\\" \\n    -longNames 0\\n    -niceNames 1\\n    -showNamespace 1\\n    -showPinIcons 0\\n    -mapMotionTrails 0\\n    -ignoreHiddenAttribute 0\\n    $editorName\"\n"
		+ "\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        setFocus `paneLayout -q -p1 $gMainPane`;\n        sceneUIReplacement -deleteRemaining;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 5 -size 12 -divisions 5 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 120 -ast 1 -aet 200 ";
	setAttr ".st" 6;
createNode hyperGraphInfo -n "nodeEditorPanel1Info";
createNode hyperView -n "hyperView1";
	setAttr ".dag" no;
createNode hyperLayout -n "hyperLayout1";
	setAttr ".ihi" 0;
	setAttr ".hyp[0].nvs" 1920;
	setAttr ".anf" yes;
createNode dx11Shader -n "dx11Shader1";
	setAttr ".omo" -type "float3" 1 1 1 ;
	setAttr ".vpar" -type "stringArray" 0  ;
	setAttr ".upar" -type "stringArray" 0  ;
createNode hkNodeOptions -n "hkNodeOptions1";
	addAttr -ci true -sn "EMesh" -ln "ExportMeshes" -dv 1 -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "EMat" -ln "ExportMaterials" -dv 1 -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "EAttr" -ln "ExportAttributes" -dv 1 -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "EAnno" -ln "ExportAnnotations" -dv 1 -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "EL" -ln "ExportLights" -dv 1 -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "EC" -ln "ExportCameras" -dv 1 -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "VO" -ln "VisibleOnly" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "SO" -ln "SelectedOnly" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "RT" -ln "RangeType" -dv 1 -min 0 -max 2 -en "Current Time:Current Range:Specific Range" 
		-at "enum";
	addAttr -ci true -sn "ST" -ln "StartTime" -at "time";
	addAttr -ci true -sn "ET" -ln "EndTime" -at "time";
	addAttr -ci true -sn "UOF" -ln "UseOptionsFile" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "OF" -ln "OptionsFile" -dt "string";
	addAttr -ci true -sn "FS" -ln "FilterSetup" -dt "Int32Array";
	addAttr -ci true -sn "EV" -ln "EnvironmentVariables" -dt "string";
	addAttr -ci true -sn "RP" -ln "UseRotatePivot" -dv 1 -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "OP" -ln "UseOldPhysics" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "NSV" -ln "DoNotSplitVertices" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "ASA" -ln "GetAutoSkinAttachments" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "KFS" -ln "StoreKeyFrameSamplePoints" -dv 1 -min 0 -max 1 -at "bool";
	setAttr ".FS" -type "Int32Array" 3805 60 63 120 109 108 32
		 118 101 114 115 105 111 110 61 34 49 46 48
		 34 32 101 110 99 111 100 105 110 103 61 34
		 117 116 102 45 56 34 63 62 10 60 104 107
		 111 112 116 105 111 110 115 62 10 9 60 104
		 107 111 98 106 101 99 116 32 99 108 97 115
		 115 61 34 104 99 116 67 111 110 102 105 103
		 117 114 97 116 105 111 110 83 101 116 68 97
		 116 97 34 62 10 9 9 60 104 107 112 97
		 114 97 109 32 110 97 109 101 61 34 102 105
		 108 116 101 114 77 97 110 97 103 101 114 86
		 101 114 115 105 111 110 34 62 54 53 53 51
		 54 60 47 104 107 112 97 114 97 109 62 10
		 9 9 60 104 107 112 97 114 97 109 32 110
		 97 109 101 61 34 97 99 116 105 118 101 67
		 111 110 102 105 103 117 114 97 116 105 111 110
		 34 62 48 60 47 104 107 112 97 114 97 109
		 62 10 9 60 47 104 107 111 98 106 101 99
		 116 62 10 9 60 104 107 111 98 106 101 99
		 116 32 99 108 97 115 115 61 34 104 99 116
		 67 111 110 102 105 103 117 114 97 116 105 111
		 110 68 97 116 97 34 62 10 9 9 60 104
		 107 112 97 114 97 109 32 110 97 109 101 61
		 34 99 111 110 102 105 103 117 114 97 116 105
		 111 110 78 97 109 101 34 62 68 101 102 97
		 117 108 116 60 47 104 107 112 97 114 97 109
		 62 10 9 9 60 104 107 112 97 114 97 109
		 32 110 97 109 101 61 34 110 117 109 70 105
		 108 116 101 114 115 34 62 51 60 47 104 107
		 112 97 114 97 109 62 10 9 60 47 104 107
		 111 98 106 101 99 116 62 10 9 60 104 107
		 111 98 106 101 99 116 32 110 97 109 101 61
		 34 67 114 101 97 116 101 32 83 107 101 108
		 101 116 111 110 115 34 32 99 108 97 115 115
		 61 34 104 99 116 70 105 108 116 101 114 68
		 97 116 97 34 62 10 9 9 60 104 107 112
		 97 114 97 109 32 110 97 109 101 61 34 105
		 100 34 62 55 54 57 56 51 49 55 56 52
		 60 47 104 107 112 97 114 97 109 62 10 9
		 9 60 104 107 112 97 114 97 109 32 110 97
		 109 101 61 34 118 101 114 34 62 54 54 48
		 53 54 60 47 104 107 112 97 114 97 109 62
		 10 9 9 60 104 107 112 97 114 97 109 32
		 110 97 109 101 61 34 104 97 115 79 112 116
		 105 111 110 115 34 62 116 114 117 101 60 47
		 104 107 112 97 114 97 109 62 10 9 60 47
		 104 107 111 98 106 101 99 116 62 10 9 60
		 104 107 111 98 106 101 99 116 32 110 97 109
		 101 61 34 67 114 101 97 116 101 32 83 107
		 101 108 101 116 111 110 115 34 32 99 108 97
		 115 115 61 34 104 99 116 67 114 101 97 116
		 101 83 107 101 108 101 116 111 110 79 112 116
		 105 111 110 115 34 62 10 9 9 60 104 107
		 112 97 114 97 109 32 110 97 109 101 61 34
		 109 111 118 101 84 111 79 114 105 103 105 110
		 34 62 102 97 108 115 101 60 47 104 107 112
		 97 114 97 109 62 10 9 9 60 104 107 112
		 97 114 97 109 32 110 97 109 101 61 34 97
		 117 116 111 109 97 116 105 99 34 62 102 97
		 108 115 101 60 47 104 107 112 97 114 97 109
		 62 10 9 9 60 104 107 112 97 114 97 109
		 32 110 97 109 101 61 34 114 105 103 78 111
		 100 101 115 34 62 66 105 112 48 49 95 80
		 101 108 118 105 115 59 66 105 112 48 49 95
		 76 95 84 104 105 103 104 59 66 105 112 48
		 49 95 76 95 67 97 108 102 59 66 105 112
		 48 49 95 76 95 70 111 111 116 59 66 105
		 112 48 49 95 76 95 84 111 101 48 59 66
		 105 112 48 49 95 76 67 97 108 102 84 119
		 105 115 116 59 66 105 112 48 49 95 76 67
		 97 108 102 84 119 105 115 116 49 59 66 105
		 112 48 49 95 76 84 104 105 103 104 84 119
		 105 115 116 59 66 105 112 48 49 95 76 84
		 104 105 103 104 84 119 105 115 116 49 59 66
		 105 112 48 49 95 82 95 84 104 105 103 104
		 59 66 105 112 48 49 95 82 95 67 97 108
		 102 59 66 105 112 48 49 95 82 95 70 111
		 111 116 59 66 105 112 48 49 95 82 95 84
		 111 101 48 59 66 105 112 48 49 95 82 67
		 97 108 102 84 119 105 115 116 59 66 105 112
		 48 49 95 82 67 97 108 102 84 119 105 115
		 116 49 59 66 105 112 48 49 95 82 84 104
		 105 103 104 84 119 105 115 116 59 66 105 112
		 48 49 95 82 84 104 105 103 104 84 119 105
		 115 116 49 59 66 105 112 48 49 95 83 112
		 105 110 101 59 66 105 112 48 49 95 83 112
		 105 110 101 49 59 66 105 112 48 49 95 83
		 112 105 110 101 50 59 66 105 112 48 49 95
		 83 112 105 110 101 51 59 66 105 112 48 49
		 95 78 101 99 107 59 66 105 112 48 49 95
		 72 101 97 100 59 70 99 70 88 95 66 108
		 111 119 67 104 101 101 107 95 76 59 70 99
		 70 88 95 66 108 111 119 67 104 101 101 107
		 95 82 59 70 99 70 88 95 66 111 116 78
		 111 115 101 59 70 99 70 88 95 67 104 101
		 101 107 95 76 59 70 99 70 88 95 67 104
		 101 101 107 95 82 59 70 99 70 88 95 69
		 121 66 114 119 95 73 110 110 101 114 95 76
		 59 70 99 70 88 95 69 121 66 114 119 95
		 73 110 110 101 114 95 82 59 70 99 70 88
		 95 69 121 66 114 119 95 77 105 100 95 76
		 59 70 99 70 88 95 69 121 66 114 119 95
		 77 105 100 95 82 59 70 99 70 88 95 69
		 121 66 114 119 95 79 117 116 101 114 95 76
		 59 70 99 70 88 95 69 121 66 114 119 95
		 79 117 116 101 114 95 82 59 70 99 70 120
		 95 69 121 101 95 76 59 70 99 70 120 95
		 69 121 101 95 82 59 70 99 70 88 95 69
		 121 76 100 95 66 111 116 116 111 109 95 76
		 59 70 99 70 88 95 69 121 76 100 95 66
		 111 116 116 111 109 95 82 59 70 99 70 88
		 95 69 121 76 100 95 84 111 112 95 76 59
		 70 99 70 88 95 69 121 76 100 95 84 111
		 112 95 82 59 70 99 70 88 95 70 114 72
		 101 97 100 95 67 110 116 114 59 70 99 70
		 88 95 70 114 72 101 97 100 95 76 59 70
		 99 70 88 95 70 114 72 101 97 100 95 82
		 59 70 99 70 88 95 73 110 115 105 100 101
		 67 104 101 101 107 95 76 59 70 99 70 88
		 95 73 110 115 105 100 101 67 104 101 101 107
		 95 82 59 70 99 70 88 95 74 97 119 59
		 70 99 70 88 95 84 111 110 103 117 101 95
		 48 49 59 70 99 70 88 95 84 111 110 103
		 117 101 95 48 50 59 70 99 70 88 95 77
		 111 117 116 104 95 48 49 59 70 99 70 88
		 95 77 111 117 116 104 95 48 50 59 70 99
		 70 88 95 77 111 117 116 104 95 48 51 59
		 70 99 70 88 95 77 111 117 116 104 95 48
		 52 59 70 99 70 88 95 77 111 117 116 104
		 95 48 53 59 70 99 70 88 95 77 111 117
		 116 104 95 48 54 59 70 99 70 88 95 77
		 111 117 116 104 95 48 55 59 70 99 70 88
		 95 77 111 117 116 104 95 48 56 59 70 99
		 70 88 95 78 111 115 101 95 76 59 70 99
		 70 88 95 78 111 115 101 95 82 59 70 99
		 70 88 95 79 117 116 101 114 69 121 101 95
		 76 59 70 99 70 88 95 79 117 116 101 114
		 69 121 101 95 82 59 70 99 70 88 95 80
		 105 110 99 104 95 76 59 70 99 70 88 95
		 80 105 110 99 104 95 82 59 66 105 112 48
		 49 95 76 95 67 108 97 118 105 99 108 101
		 59 66 105 112 48 49 95 76 95 85 112 112
		 101 114 65 114 109 59 66 105 112 48 49 95
		 76 95 70 111 114 101 97 114 109 59 66 105
		 112 48 49 95 76 95 70 111 114 101 116 119
		 105 115 116 59 66 105 112 48 49 95 76 95
		 70 111 114 101 116 119 105 115 116 49 59 66
		 105 112 48 49 95 76 95 72 97 110 100 59
		 66 105 112 48 49 95 76 95 70 105 110 103
		 101 114 48 59 66 105 112 48 49 95 76 95
		 70 105 110 103 101 114 48 49 59 66 105 112
		 48 49 95 76 95 70 105 110 103 101 114 48
		 50 59 66 105 112 48 49 95 76 95 70 105
		 110 103 101 114 49 59 66 105 112 48 49 95
		 76 95 70 105 110 103 101 114 49 49 59 66
		 105 112 48 49 95 76 95 70 105 110 103 101
		 114 49 50 59 66 105 112 48 49 95 76 95
		 70 105 110 103 101 114 50 59 66 105 112 48
		 49 95 76 95 70 105 110 103 101 114 50 49
		 59 66 105 112 48 49 95 76 95 70 105 110
		 103 101 114 50 50 59 66 105 112 48 49 95
		 76 95 70 105 110 103 101 114 51 59 66 105
		 112 48 49 95 76 95 70 105 110 103 101 114
		 51 49 59 66 105 112 48 49 95 76 95 70
		 105 110 103 101 114 51 50 59 66 105 112 48
		 49 95 76 95 70 105 110 103 101 114 52 59
		 66 105 112 48 49 95 76 95 70 105 110 103
		 101 114 52 49 59 66 105 112 48 49 95 76
		 95 70 105 110 103 101 114 52 50 59 66 105
		 112 48 49 95 76 85 112 65 114 109 84 119
		 105 115 116 59 66 105 112 48 49 95 76 85
		 112 65 114 109 84 119 105 115 116 49 59 66
		 105 112 48 49 95 76 85 112 65 114 109 84
		 119 105 115 116 50 59 66 105 112 48 49 95
		 82 95 67 108 97 118 105 99 108 101 59 66
		 105 112 48 49 95 82 95 85 112 112 101 114
		 65 114 109 59 66 105 112 48 49 95 82 95
		 70 111 114 101 97 114 109 59 66 105 112 48
		 49 95 82 95 70 111 114 101 116 119 105 115
		 116 59 66 105 112 48 49 95 82 95 70 111
		 114 101 116 119 105 115 116 49 59 66 105 112
		 48 49 95 82 95 72 97 110 100 59 66 105
		 112 48 49 95 82 95 70 105 110 103 101 114
		 48 59 66 105 112 48 49 95 82 95 70 105
		 110 103 101 114 48 49 59 66 105 112 48 49
		 95 82 95 70 105 110 103 101 114 48 50 59
		 66 105 112 48 49 95 82 95 70 105 110 103
		 101 114 49 59 66 105 112 48 49 95 82 95
		 70 105 110 103 101 114 49 49 59 66 105 112
		 48 49 95 82 95 70 105 110 103 101 114 49
		 50 59 66 105 112 48 49 95 82 95 70 105
		 110 103 101 114 50 59 66 105 112 48 49 95
		 82 95 70 105 110 103 101 114 50 49 59 66
		 105 112 48 49 95 82 95 70 105 110 103 101
		 114 50 50 59 66 105 112 48 49 95 82 95
		 70 105 110 103 101 114 51 59 66 105 112 48
		 49 95 82 95 70 105 110 103 101 114 51 49
		 59 66 105 112 48 49 95 82 95 70 105 110
		 103 101 114 51 50 59 66 105 112 48 49 95
		 82 95 70 105 110 103 101 114 52 59 66 105
		 112 48 49 95 82 95 70 105 110 103 101 114
		 52 49 59 66 105 112 48 49 95 82 95 70
		 105 110 103 101 114 52 50 59 66 105 112 48
		 49 95 82 85 112 65 114 109 84 119 105 115
		 116 59 66 105 112 48 49 95 82 85 112 65
		 114 109 84 119 105 115 116 49 59 66 105 112
		 48 49 95 82 85 112 65 114 109 84 119 105
		 115 116 50 59 60 47 104 107 112 97 114 97
		 109 62 10 9 9 60 104 107 112 97 114 97
		 109 32 110 97 109 101 61 34 114 105 103 70
		 105 108 101 34 62 38 35 57 50 49 54 59
		 60 47 104 107 112 97 114 97 109 62 10 9
		 9 60 104 107 112 97 114 97 109 32 110 97
		 109 101 61 34 115 101 108 101 99 116 101 100
		 34 62 102 97 108 115 101 60 47 104 107 112
		 97 114 97 109 62 10 9 9 60 104 107 112
		 97 114 97 109 32 110 97 109 101 61 34 115
		 107 105 110 66 105 110 100 105 110 103 115 34
		 62 116 114 117 101 60 47 104 107 112 97 114
		 97 109 62 10 9 9 60 104 107 112 97 114
		 97 109 32 110 97 109 101 61 34 102 108 111
		 97 116 83 108 111 116 115 34 62 60 47 104
		 107 112 97 114 97 109 62 10 9 9 60 104
		 107 112 97 114 97 109 32 110 97 109 101 61
		 34 117 115 101 79 114 100 101 114 73 110 70
		 105 108 101 34 62 102 97 108 115 101 60 47
		 104 107 112 97 114 97 109 62 10 9 9 60
		 104 107 112 97 114 97 109 32 110 97 109 101
		 61 34 115 117 98 115 116 114 105 110 103 77
		 97 116 99 104 34 62 102 97 108 115 101 60
		 47 104 107 112 97 114 97 109 62 10 9 9
		 60 104 107 112 97 114 97 109 32 110 97 109
		 101 61 34 115 107 101 108 101 116 111 110 78
		 97 109 101 34 62 60 47 104 107 112 97 114
		 97 109 62 10 9 9 60 104 107 112 97 114
		 97 109 32 110 97 109 101 61 34 112 97 114
		 116 105 116 105 111 110 115 34 62 60 47 104
		 107 112 97 114 97 109 62 10 9 9 60 104
		 107 112 97 114 97 109 32 110 97 109 101 61
		 34 112 97 114 116 105 116 105 111 110 83 116
		 97 114 116 66 111 110 101 78 97 109 101 115
		 34 62 60 47 104 107 112 97 114 97 109 62
		 10 9 9 60 104 107 112 97 114 97 109 32
		 110 97 109 101 61 34 112 97 114 116 105 116
		 105 111 110 69 110 100 66 111 110 101 78 97
		 109 101 115 34 62 60 47 104 107 112 97 114
		 97 109 62 10 9 9 60 104 107 112 97 114
		 97 109 32 110 97 109 101 61 34 117 115 101
		 82 111 111 116 66 111 110 101 78 97 109 101
		 65 115 83 107 101 108 101 116 111 110 78 97
		 109 101 34 62 116 114 117 101 60 47 104 107
		 112 97 114 97 109 62 10 9 60 47 104 107
		 111 98 106 101 99 116 62 10 9 60 104 107
		 111 98 106 101 99 116 32 110 97 109 101 61
		 34 67 114 101 97 116 101 32 83 107 105 110
		 115 34 32 99 108 97 115 115 61 34 104 99
		 116 70 105 108 116 101 114 68 97 116 97 34
		 62 10 9 9 60 104 107 112 97 114 97 109
		 32 110 97 109 101 61 34 105 100 34 62 51
		 56 53 55 54 56 48 48 51 60 47 104 107
		 112 97 114 97 109 62 10 9 9 60 104 107
		 112 97 114 97 109 32 110 97 109 101 61 34
		 118 101 114 34 62 54 53 53 51 57 60 47
		 104 107 112 97 114 97 109 62 10 9 9 60
		 104 107 112 97 114 97 109 32 110 97 109 101
		 61 34 104 97 115 79 112 116 105 111 110 115
		 34 62 116 114 117 101 60 47 104 107 112 97
		 114 97 109 62 10 9 60 47 104 107 111 98
		 106 101 99 116 62 10 9 60 104 107 111 98
		 106 101 99 116 32 110 97 109 101 61 34 67
		 114 101 97 116 101 32 83 107 105 110 115 34
		 32 99 108 97 115 115 61 34 104 99 116 67
		 114 101 97 116 101 83 107 105 110 79 112 116
		 105 111 110 115 34 62 10 9 9 60 104 107
		 112 97 114 97 109 32 110 97 109 101 61 34
		 115 105 109 112 108 105 102 121 66 105 110 100
		 105 110 103 115 34 62 116 114 117 101 60 47
		 104 107 112 97 114 97 109 62 10 9 9 60
		 104 107 112 97 114 97 109 32 110 97 109 101
		 61 34 109 111 118 101 77 101 115 104 101 115
		 84 111 83 107 101 108 101 116 111 110 83 112
		 97 99 101 34 62 102 97 108 115 101 60 47
		 104 107 112 97 114 97 109 62 10 9 9 60
		 104 107 112 97 114 97 109 32 110 97 109 101
		 61 34 98 111 110 101 76 105 109 105 116 34
		 62 45 49 60 47 104 107 112 97 114 97 109
		 62 10 9 9 60 104 107 112 97 114 97 109
		 32 110 97 109 101 61 34 105 103 110 111 114
		 101 66 111 110 101 115 73 110 83 107 105 110
		 34 62 116 114 117 101 60 47 104 107 112 97
		 114 97 109 62 10 9 60 47 104 107 111 98
		 106 101 99 116 62 10 9 60 104 107 111 98
		 106 101 99 116 32 110 97 109 101 61 34 86
		 105 101 119 32 88 77 76 34 32 99 108 97
		 115 115 61 34 104 99 116 70 105 108 116 101
		 114 68 97 116 97 34 62 10 9 9 60 104
		 107 112 97 114 97 109 32 110 97 109 101 61
		 34 105 100 34 62 51 50 53 57 54 49 54
		 49 60 47 104 107 112 97 114 97 109 62 10
		 9 9 60 104 107 112 97 114 97 109 32 110
		 97 109 101 61 34 118 101 114 34 62 54 53
		 55 57 50 60 47 104 107 112 97 114 97 109
		 62 10 9 9 60 104 107 112 97 114 97 109
		 32 110 97 109 101 61 34 104 97 115 79 112
		 116 105 111 110 115 34 62 116 114 117 101 60
		 47 104 107 112 97 114 97 109 62 10 9 60
		 47 104 107 111 98 106 101 99 116 62 10 9
		 60 104 107 111 98 106 101 99 116 32 110 97
		 109 101 61 34 86 105 101 119 32 88 77 76
		 34 32 99 108 97 115 115 61 34 104 99 116
		 86 105 101 119 88 109 108 79 112 116 105 111
		 110 115 34 62 10 9 9 60 104 107 112 97
		 114 97 109 32 110 97 109 101 61 34 101 120
		 101 99 117 116 101 77 111 100 97 108 108 121
		 34 62 102 97 108 115 101 60 47 104 107 112
		 97 114 97 109 62 10 9 60 47 104 107 111
		 98 106 101 99 116 62 10 60 47 104 107 111
		 112 116 105 111 110 115 62 ;
select -ne :time1;
	setAttr ".o" 1;
	setAttr ".unw" 1;
select -ne :renderPartition;
	setAttr -s 8 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 8 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 6 ".u";
select -ne :defaultRenderingList1;
select -ne :defaultTextureList1;
	setAttr -s 6 ".tx";
select -ne :initialShadingGroup;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	setAttr ".ren" -type "string" "mayaHardware2";
	setAttr -k on ".mbf";
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
	setAttr ".aoon" yes;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
connectAttr "Bip01.s" "Bip01_Pelvis.is";
connectAttr "Bip01_Pelvis.s" "Bip01_Spine.is";
connectAttr "Bip01_Spine.s" "Bip01_Spine1.is";
connectAttr "Bip01_Spine1.s" "Bip01_Spine2.is";
connectAttr "Bip01_Spine2.s" "Bip01_Spine3.is";
connectAttr "Bip01_Spine3.s" "Bip01_Neck.is";
connectAttr "Bip01_Neck.s" "Bip01_Head.is";
connectAttr "Bip01_Head.s" "Bip01_HeadNub.is";
connectAttr "Bip01_Neck.s" "Bip01_L_Clavicle.is";
connectAttr "Bip01_L_Clavicle.s" "Bip01_L_UpperArm.is";
connectAttr "Bip01_L_UpperArm.s" "Bip01_L_Forearm.is";
connectAttr "Bip01_L_Forearm.s" "Bip01_L_Hand.is";
connectAttr "Bip01_L_Hand.s" "Bip01_L_Finger0.is";
connectAttr "Bip01_L_Finger0.s" "Bip01_L_Finger01.is";
connectAttr "Bip01_L_Finger01.s" "Bip01_L_Finger02.is";
connectAttr "Bip01_L_Finger02.s" "Bip01_L_Finger0Nub.is";
connectAttr "Bip01_L_Hand.s" "Bip01_L_Finger1.is";
connectAttr "Bip01_L_Finger1.s" "Bip01_L_Finger11.is";
connectAttr "Bip01_L_Finger11.s" "Bip01_L_Finger12.is";
connectAttr "Bip01_L_Finger12.s" "Bip01_L_Finger1Nub.is";
connectAttr "Bip01_L_Hand.s" "Bip01_L_Finger2.is";
connectAttr "Bip01_L_Finger2.s" "Bip01_L_Finger21.is";
connectAttr "Bip01_L_Finger21.s" "Bip01_L_Finger22.is";
connectAttr "Bip01_L_Finger22.s" "Bip01_L_Finger2Nub.is";
connectAttr "Bip01_L_Hand.s" "Bip01_L_Finger3.is";
connectAttr "Bip01_L_Finger3.s" "Bip01_L_Finger31.is";
connectAttr "Bip01_L_Finger31.s" "Bip01_L_Finger32.is";
connectAttr "Bip01_L_Finger32.s" "Bip01_L_Finger3Nub.is";
connectAttr "Bip01_L_Hand.s" "Bip01_L_Finger4.is";
connectAttr "Bip01_L_Finger4.s" "Bip01_L_Finger41.is";
connectAttr "Bip01_L_Finger41.s" "Bip01_L_Finger42.is";
connectAttr "Bip01_L_Finger42.s" "Bip01_L_Finger4Nub.is";
connectAttr "Bip01_L_Hand.s" "Gundummy02.is";
connectAttr "Bip01_L_Forearm.s" "Bip01_L_Foretwist.is";
connectAttr "Bip01_L_Foretwist.s" "Bip01_L_Foretwist1.is";
connectAttr "Bip01_L_UpperArm.s" "Bip01_LUpArmTwist.is";
connectAttr "Bip01_LUpArmTwist.s" "Bip01_LUpArmTwist1.is";
connectAttr "Bip01_LUpArmTwist1.s" "Bip01_LUpArmTwist2.is";
connectAttr "Bip01_Neck.s" "Bip01_R_Clavicle.is";
connectAttr "Bip01_R_Clavicle.s" "Bip01_R_UpperArm.is";
connectAttr "Bip01_R_UpperArm.s" "Bip01_R_Forearm.is";
connectAttr "Bip01_R_Forearm.s" "Bip01_R_Hand.is";
connectAttr "Bip01_R_Hand.s" "Bip01_R_Finger0.is";
connectAttr "Bip01_R_Finger0.s" "Bip01_R_Finger01.is";
connectAttr "Bip01_R_Finger01.s" "Bip01_R_Finger02.is";
connectAttr "Bip01_R_Finger02.s" "Bip01_R_Finger0Nub.is";
connectAttr "Bip01_R_Hand.s" "Bip01_R_Finger1.is";
connectAttr "Bip01_R_Finger1.s" "Bip01_R_Finger11.is";
connectAttr "Bip01_R_Finger11.s" "Bip01_R_Finger12.is";
connectAttr "Bip01_R_Finger12.s" "Bip01_R_Finger1Nub.is";
connectAttr "Bip01_R_Hand.s" "Bip01_R_Finger2.is";
connectAttr "Bip01_R_Finger2.s" "Bip01_R_Finger21.is";
connectAttr "Bip01_R_Finger21.s" "Bip01_R_Finger22.is";
connectAttr "Bip01_R_Finger22.s" "Bip01_R_Finger2Nub.is";
connectAttr "Bip01_R_Hand.s" "Bip01_R_Finger3.is";
connectAttr "Bip01_R_Finger3.s" "Bip01_R_Finger31.is";
connectAttr "Bip01_R_Finger31.s" "Bip01_R_Finger32.is";
connectAttr "Bip01_R_Finger32.s" "Bip01_R_Finger3Nub.is";
connectAttr "Bip01_R_Hand.s" "Bip01_R_Finger4.is";
connectAttr "Bip01_R_Finger4.s" "Bip01_R_Finger41.is";
connectAttr "Bip01_R_Finger41.s" "Bip01_R_Finger42.is";
connectAttr "Bip01_R_Finger42.s" "Bip01_R_Finger4Nub.is";
connectAttr "Bip01_R_Hand.s" "Gundummy.is";
connectAttr "Bip01_R_Forearm.s" "Bip01_R_Foretwist.is";
connectAttr "Bip01_R_Foretwist.s" "Bip01_R_Foretwist1.is";
connectAttr "Bip01_R_UpperArm.s" "Bip01_RUpArmTwist.is";
connectAttr "Bip01_RUpArmTwist.s" "Bip01_RUpArmTwist1.is";
connectAttr "Bip01_RUpArmTwist1.s" "Bip01_RUpArmTwist2.is";
connectAttr "Bip01_Pelvis.s" "Bip01_L_Thigh.is";
connectAttr "Bip01_L_Thigh.s" "Bip01_LThighTwist.is";
connectAttr "Bip01_LThighTwist.s" "Bip01_LThighTwist1.is";
connectAttr "Bip01_L_Thigh.s" "Bip01_L_Calf.is";
connectAttr "Bip01_L_Calf.s" "Bip01_L_Foot.is";
connectAttr "Bip01_L_Foot.s" "Bip01_L_Toe0.is";
connectAttr "Bip01_L_Toe0.s" "Bip01_L_Toe0Nub.is";
connectAttr "Bip01_L_Calf.s" "Bip01_LCalfTwist.is";
connectAttr "Bip01_LCalfTwist.s" "Bip01_LCalfTwist1.is";
connectAttr "Bip01_Pelvis.s" "Bip01_R_Thigh.is";
connectAttr "Bip01_R_Thigh.s" "Bip01_RThighTwist.is";
connectAttr "Bip01_RThighTwist.s" "Bip01_RThighTwist1.is";
connectAttr "Bip01_R_Thigh.s" "Bip01_R_Calf.is";
connectAttr "Bip01_R_Calf.s" "Bip01_R_Foot.is";
connectAttr "Bip01_R_Foot.s" "Bip01_R_Toe0.is";
connectAttr "Bip01_R_Toe0.s" "Bip01_R_Toe0Nub.is";
connectAttr "Bip01_R_Calf.s" "Bip01_RCalfTwist.is";
connectAttr "Bip01_RCalfTwist.s" "Bip01_RCalfTwist1.is";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BruceWayne_BodySG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BruceWayne_BodySG1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BruceWayne_HeadSG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BruceWayne_HeadSG1.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BruceWayne_HeadSG2.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "BruceWayne_HeadSG3.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BruceWayne_BodySG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BruceWayne_BodySG1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BruceWayne_HeadSG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BruceWayne_HeadSG1.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BruceWayne_HeadSG2.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "BruceWayne_HeadSG3.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "BruceWayne_Suit_Torso_MIC_ncl1_1.oc" "BruceWayne_Suit_Torso_MIC.c";
connectAttr "BruceWayne_Suit_Torso_MIC.oc" "BruceWayne_BodySG.ss";
connectAttr "BruceWayne_BodySG.msg" "materialInfo1.sg";
connectAttr "BruceWayne_Suit_Torso_MIC.msg" "materialInfo1.m";
connectAttr "BruceWayne_Suit_Torso_MIC_ncl1_1.msg" "materialInfo1.t" -na;
connectAttr "BruceWayne_Suit_Legs_MIC_ncl1_1.oc" "BruceWayne_Suit_Legs_MIC.c";
connectAttr "BruceWayne_Suit_Legs_MIC.oc" "BruceWayne_BodySG1.ss";
connectAttr "BruceWayne_BodySG1.msg" "materialInfo2.sg";
connectAttr "BruceWayne_Suit_Legs_MIC.msg" "materialInfo2.m";
connectAttr "BruceWayne_Suit_Legs_MIC_ncl1_1.msg" "materialInfo2.t" -na;
connectAttr "place2dTexture1.o" "BruceWayne_Suit_Torso_MIC_ncl1_1.uv";
connectAttr "place2dTexture1.ofu" "BruceWayne_Suit_Torso_MIC_ncl1_1.ofu";
connectAttr "place2dTexture1.ofv" "BruceWayne_Suit_Torso_MIC_ncl1_1.ofv";
connectAttr "place2dTexture1.rf" "BruceWayne_Suit_Torso_MIC_ncl1_1.rf";
connectAttr "place2dTexture1.reu" "BruceWayne_Suit_Torso_MIC_ncl1_1.reu";
connectAttr "place2dTexture1.rev" "BruceWayne_Suit_Torso_MIC_ncl1_1.rev";
connectAttr "place2dTexture1.vt1" "BruceWayne_Suit_Torso_MIC_ncl1_1.vt1";
connectAttr "place2dTexture1.vt2" "BruceWayne_Suit_Torso_MIC_ncl1_1.vt2";
connectAttr "place2dTexture1.vt3" "BruceWayne_Suit_Torso_MIC_ncl1_1.vt3";
connectAttr "place2dTexture1.vc1" "BruceWayne_Suit_Torso_MIC_ncl1_1.vc1";
connectAttr "place2dTexture1.ofs" "BruceWayne_Suit_Torso_MIC_ncl1_1.fs";
connectAttr "place2dTexture2.o" "BruceWayne_Suit_Legs_MIC_ncl1_1.uv";
connectAttr "place2dTexture2.ofu" "BruceWayne_Suit_Legs_MIC_ncl1_1.ofu";
connectAttr "place2dTexture2.ofv" "BruceWayne_Suit_Legs_MIC_ncl1_1.ofv";
connectAttr "place2dTexture2.rf" "BruceWayne_Suit_Legs_MIC_ncl1_1.rf";
connectAttr "place2dTexture2.reu" "BruceWayne_Suit_Legs_MIC_ncl1_1.reu";
connectAttr "place2dTexture2.rev" "BruceWayne_Suit_Legs_MIC_ncl1_1.rev";
connectAttr "place2dTexture2.vt1" "BruceWayne_Suit_Legs_MIC_ncl1_1.vt1";
connectAttr "place2dTexture2.vt2" "BruceWayne_Suit_Legs_MIC_ncl1_1.vt2";
connectAttr "place2dTexture2.vt3" "BruceWayne_Suit_Legs_MIC_ncl1_1.vt3";
connectAttr "place2dTexture2.vc1" "BruceWayne_Suit_Legs_MIC_ncl1_1.vc1";
connectAttr "place2dTexture2.ofs" "BruceWayne_Suit_Legs_MIC_ncl1_1.fs";
connectAttr "BruceWayne_Head_MIC_ncl1_1.oc" "BruceWayne_Head_MIC.c";
connectAttr "BruceWayne_Head_MIC.oc" "BruceWayne_HeadSG.ss";
connectAttr "BruceWayne_HeadSG.msg" "materialInfo3.sg";
connectAttr "BruceWayne_Head_MIC.msg" "materialInfo3.m";
connectAttr "BruceWayne_Head_MIC_ncl1_1.msg" "materialInfo3.t" -na;
connectAttr "dx11Shader1.oc" "BruceWayne_HeadSG1.ss";
connectAttr "BruceWayne_HeadSG1.msg" "materialInfo4.sg";
connectAttr "dx11Shader1.msg" "materialInfo4.m";
connectAttr "BruceWayne_Hair_MIC_ncl1_1.oc" "BruceWayne_Hair_MIC.c";
connectAttr "BruceWayne_Hair_MIC.oc" "BruceWayne_HeadSG2.ss";
connectAttr "BruceWayne_HeadSG2.msg" "materialInfo5.sg";
connectAttr "BruceWayne_Hair_MIC.msg" "materialInfo5.m";
connectAttr "BruceWayne_Hair_MIC_ncl1_1.msg" "materialInfo5.t" -na;
connectAttr "Character_FakeShadow_ncl1_1.oc" "Character_FakeShadow.c";
connectAttr "Character_FakeShadow.oc" "BruceWayne_HeadSG3.ss";
connectAttr "BruceWayne_HeadSG3.msg" "materialInfo6.sg";
connectAttr "Character_FakeShadow.msg" "materialInfo6.m";
connectAttr "Character_FakeShadow_ncl1_1.msg" "materialInfo6.t" -na;
connectAttr "place2dTexture3.o" "BruceWayne_Head_MIC_ncl1_1.uv";
connectAttr "place2dTexture3.ofu" "BruceWayne_Head_MIC_ncl1_1.ofu";
connectAttr "place2dTexture3.ofv" "BruceWayne_Head_MIC_ncl1_1.ofv";
connectAttr "place2dTexture3.rf" "BruceWayne_Head_MIC_ncl1_1.rf";
connectAttr "place2dTexture3.reu" "BruceWayne_Head_MIC_ncl1_1.reu";
connectAttr "place2dTexture3.rev" "BruceWayne_Head_MIC_ncl1_1.rev";
connectAttr "place2dTexture3.vt1" "BruceWayne_Head_MIC_ncl1_1.vt1";
connectAttr "place2dTexture3.vt2" "BruceWayne_Head_MIC_ncl1_1.vt2";
connectAttr "place2dTexture3.vt3" "BruceWayne_Head_MIC_ncl1_1.vt3";
connectAttr "place2dTexture3.vc1" "BruceWayne_Head_MIC_ncl1_1.vc1";
connectAttr "place2dTexture3.ofs" "BruceWayne_Head_MIC_ncl1_1.fs";
connectAttr "place2dTexture4.o" "BruceWayne_OZ_Eyes_MIC_ncl1_1.uv";
connectAttr "place2dTexture4.ofu" "BruceWayne_OZ_Eyes_MIC_ncl1_1.ofu";
connectAttr "place2dTexture4.ofv" "BruceWayne_OZ_Eyes_MIC_ncl1_1.ofv";
connectAttr "place2dTexture4.rf" "BruceWayne_OZ_Eyes_MIC_ncl1_1.rf";
connectAttr "place2dTexture4.reu" "BruceWayne_OZ_Eyes_MIC_ncl1_1.reu";
connectAttr "place2dTexture4.rev" "BruceWayne_OZ_Eyes_MIC_ncl1_1.rev";
connectAttr "place2dTexture4.vt1" "BruceWayne_OZ_Eyes_MIC_ncl1_1.vt1";
connectAttr "place2dTexture4.vt2" "BruceWayne_OZ_Eyes_MIC_ncl1_1.vt2";
connectAttr "place2dTexture4.vt3" "BruceWayne_OZ_Eyes_MIC_ncl1_1.vt3";
connectAttr "place2dTexture4.vc1" "BruceWayne_OZ_Eyes_MIC_ncl1_1.vc1";
connectAttr "place2dTexture4.ofs" "BruceWayne_OZ_Eyes_MIC_ncl1_1.fs";
connectAttr "place2dTexture5.o" "BruceWayne_Hair_MIC_ncl1_1.uv";
connectAttr "place2dTexture5.ofu" "BruceWayne_Hair_MIC_ncl1_1.ofu";
connectAttr "place2dTexture5.ofv" "BruceWayne_Hair_MIC_ncl1_1.ofv";
connectAttr "place2dTexture5.rf" "BruceWayne_Hair_MIC_ncl1_1.rf";
connectAttr "place2dTexture5.reu" "BruceWayne_Hair_MIC_ncl1_1.reu";
connectAttr "place2dTexture5.rev" "BruceWayne_Hair_MIC_ncl1_1.rev";
connectAttr "place2dTexture5.vt1" "BruceWayne_Hair_MIC_ncl1_1.vt1";
connectAttr "place2dTexture5.vt2" "BruceWayne_Hair_MIC_ncl1_1.vt2";
connectAttr "place2dTexture5.vt3" "BruceWayne_Hair_MIC_ncl1_1.vt3";
connectAttr "place2dTexture5.vc1" "BruceWayne_Hair_MIC_ncl1_1.vc1";
connectAttr "place2dTexture5.ofs" "BruceWayne_Hair_MIC_ncl1_1.fs";
connectAttr "place2dTexture6.o" "Character_FakeShadow_ncl1_1.uv";
connectAttr "place2dTexture6.ofu" "Character_FakeShadow_ncl1_1.ofu";
connectAttr "place2dTexture6.ofv" "Character_FakeShadow_ncl1_1.ofv";
connectAttr "place2dTexture6.rf" "Character_FakeShadow_ncl1_1.rf";
connectAttr "place2dTexture6.reu" "Character_FakeShadow_ncl1_1.reu";
connectAttr "place2dTexture6.rev" "Character_FakeShadow_ncl1_1.rev";
connectAttr "place2dTexture6.vt1" "Character_FakeShadow_ncl1_1.vt1";
connectAttr "place2dTexture6.vt2" "Character_FakeShadow_ncl1_1.vt2";
connectAttr "place2dTexture6.vt3" "Character_FakeShadow_ncl1_1.vt3";
connectAttr "place2dTexture6.vc1" "Character_FakeShadow_ncl1_1.vc1";
connectAttr "place2dTexture6.ofs" "Character_FakeShadow_ncl1_1.fs";
connectAttr "Bip01.msg" "bindPose1.m[0]";
connectAttr "Bip01_Pelvis.msg" "bindPose1.m[1]";
connectAttr "Bip01_Spine.msg" "bindPose1.m[2]";
connectAttr "Bip01_Spine1.msg" "bindPose1.m[3]";
connectAttr "Bip01_Spine2.msg" "bindPose1.m[4]";
connectAttr "Bip01_Spine3.msg" "bindPose1.m[5]";
connectAttr "Bip01_Neck.msg" "bindPose1.m[6]";
connectAttr "Bip01_R_Clavicle.msg" "bindPose1.m[7]";
connectAttr "Bip01_R_UpperArm.msg" "bindPose1.m[8]";
connectAttr "Bip01_R_Forearm.msg" "bindPose1.m[9]";
connectAttr "Bip01_R_Foretwist.msg" "bindPose1.m[10]";
connectAttr "Bip01_R_Foretwist1.msg" "bindPose1.m[11]";
connectAttr "Bip01_L_Clavicle.msg" "bindPose1.m[12]";
connectAttr "Bip01_L_UpperArm.msg" "bindPose1.m[13]";
connectAttr "Bip01_L_Forearm.msg" "bindPose1.m[14]";
connectAttr "Bip01_L_Foretwist.msg" "bindPose1.m[15]";
connectAttr "Bip01_L_Foretwist1.msg" "bindPose1.m[16]";
connectAttr "Bip01_L_Hand.msg" "bindPose1.m[17]";
connectAttr "Bip01_L_Finger1.msg" "bindPose1.m[18]";
connectAttr "Bip01_L_Finger11.msg" "bindPose1.m[19]";
connectAttr "Bip01_L_Finger12.msg" "bindPose1.m[20]";
connectAttr "Bip01_L_Finger4.msg" "bindPose1.m[21]";
connectAttr "Bip01_L_Finger41.msg" "bindPose1.m[22]";
connectAttr "Bip01_L_Finger42.msg" "bindPose1.m[23]";
connectAttr "Bip01_L_Finger0.msg" "bindPose1.m[24]";
connectAttr "Bip01_L_Finger01.msg" "bindPose1.m[25]";
connectAttr "Bip01_L_Finger02.msg" "bindPose1.m[26]";
connectAttr "Bip01_L_Finger2.msg" "bindPose1.m[27]";
connectAttr "Bip01_L_Finger21.msg" "bindPose1.m[28]";
connectAttr "Bip01_L_Finger22.msg" "bindPose1.m[29]";
connectAttr "Bip01_L_Finger3.msg" "bindPose1.m[30]";
connectAttr "Bip01_L_Finger31.msg" "bindPose1.m[31]";
connectAttr "Bip01_L_Finger32.msg" "bindPose1.m[32]";
connectAttr "Bip01_R_Hand.msg" "bindPose1.m[33]";
connectAttr "Bip01_R_Finger1.msg" "bindPose1.m[34]";
connectAttr "Bip01_R_Finger11.msg" "bindPose1.m[35]";
connectAttr "Bip01_R_Finger12.msg" "bindPose1.m[36]";
connectAttr "Bip01_R_Finger4.msg" "bindPose1.m[37]";
connectAttr "Bip01_R_Finger41.msg" "bindPose1.m[38]";
connectAttr "Bip01_R_Finger42.msg" "bindPose1.m[39]";
connectAttr "Bip01_R_Finger0.msg" "bindPose1.m[40]";
connectAttr "Bip01_R_Finger01.msg" "bindPose1.m[41]";
connectAttr "Bip01_R_Finger02.msg" "bindPose1.m[42]";
connectAttr "Bip01_R_Finger2.msg" "bindPose1.m[43]";
connectAttr "Bip01_R_Finger21.msg" "bindPose1.m[44]";
connectAttr "Bip01_R_Finger22.msg" "bindPose1.m[45]";
connectAttr "Bip01_R_Finger3.msg" "bindPose1.m[46]";
connectAttr "Bip01_R_Finger31.msg" "bindPose1.m[47]";
connectAttr "Bip01_R_Finger32.msg" "bindPose1.m[48]";
connectAttr "Bip01_L_Thigh.msg" "bindPose1.m[49]";
connectAttr "Bip01_LThighTwist.msg" "bindPose1.m[50]";
connectAttr "Bip01_R_Thigh.msg" "bindPose1.m[51]";
connectAttr "Bip01_RThighTwist.msg" "bindPose1.m[52]";
connectAttr "Bip01_RUpArmTwist.msg" "bindPose1.m[53]";
connectAttr "Bip01_LThighTwist1.msg" "bindPose1.m[54]";
connectAttr "Bip01_LUpArmTwist.msg" "bindPose1.m[55]";
connectAttr "Bip01_RUpArmTwist1.msg" "bindPose1.m[56]";
connectAttr "Bip01_RUpArmTwist2.msg" "bindPose1.m[57]";
connectAttr "Bip01_LUpArmTwist1.msg" "bindPose1.m[58]";
connectAttr "Bip01_LUpArmTwist2.msg" "bindPose1.m[59]";
connectAttr "Bip01_R_Calf.msg" "bindPose1.m[60]";
connectAttr "Bip01_RCalfTwist.msg" "bindPose1.m[61]";
connectAttr "Bip01_L_Calf.msg" "bindPose1.m[62]";
connectAttr "Bip01_LCalfTwist.msg" "bindPose1.m[63]";
connectAttr "Bip01_L_Foot.msg" "bindPose1.m[64]";
connectAttr "Bip01_L_Toe0.msg" "bindPose1.m[65]";
connectAttr "Bip01_R_Foot.msg" "bindPose1.m[66]";
connectAttr "Bip01_R_Toe0.msg" "bindPose1.m[67]";
connectAttr "Bip01_RThighTwist1.msg" "bindPose1.m[68]";
connectAttr "Bip01_RCalfTwist1.msg" "bindPose1.m[69]";
connectAttr "Bip01_LCalfTwist1.msg" "bindPose1.m[70]";
connectAttr "Bip01_Head.msg" "bindPose1.m[71]";
connectAttr "bindPose1.w" "bindPose1.p[0]";
connectAttr "bindPose1.m[0]" "bindPose1.p[1]";
connectAttr "bindPose1.m[1]" "bindPose1.p[2]";
connectAttr "bindPose1.m[2]" "bindPose1.p[3]";
connectAttr "bindPose1.m[3]" "bindPose1.p[4]";
connectAttr "bindPose1.m[4]" "bindPose1.p[5]";
connectAttr "bindPose1.m[5]" "bindPose1.p[6]";
connectAttr "bindPose1.m[6]" "bindPose1.p[7]";
connectAttr "bindPose1.m[7]" "bindPose1.p[8]";
connectAttr "bindPose1.m[8]" "bindPose1.p[9]";
connectAttr "bindPose1.m[9]" "bindPose1.p[10]";
connectAttr "bindPose1.m[10]" "bindPose1.p[11]";
connectAttr "bindPose1.m[6]" "bindPose1.p[12]";
connectAttr "bindPose1.m[12]" "bindPose1.p[13]";
connectAttr "bindPose1.m[13]" "bindPose1.p[14]";
connectAttr "bindPose1.m[14]" "bindPose1.p[15]";
connectAttr "bindPose1.m[15]" "bindPose1.p[16]";
connectAttr "bindPose1.m[14]" "bindPose1.p[17]";
connectAttr "bindPose1.m[17]" "bindPose1.p[18]";
connectAttr "bindPose1.m[18]" "bindPose1.p[19]";
connectAttr "bindPose1.m[19]" "bindPose1.p[20]";
connectAttr "bindPose1.m[17]" "bindPose1.p[21]";
connectAttr "bindPose1.m[21]" "bindPose1.p[22]";
connectAttr "bindPose1.m[22]" "bindPose1.p[23]";
connectAttr "bindPose1.m[17]" "bindPose1.p[24]";
connectAttr "bindPose1.m[24]" "bindPose1.p[25]";
connectAttr "bindPose1.m[25]" "bindPose1.p[26]";
connectAttr "bindPose1.m[17]" "bindPose1.p[27]";
connectAttr "bindPose1.m[27]" "bindPose1.p[28]";
connectAttr "bindPose1.m[28]" "bindPose1.p[29]";
connectAttr "bindPose1.m[17]" "bindPose1.p[30]";
connectAttr "bindPose1.m[30]" "bindPose1.p[31]";
connectAttr "bindPose1.m[31]" "bindPose1.p[32]";
connectAttr "bindPose1.m[9]" "bindPose1.p[33]";
connectAttr "bindPose1.m[33]" "bindPose1.p[34]";
connectAttr "bindPose1.m[34]" "bindPose1.p[35]";
connectAttr "bindPose1.m[35]" "bindPose1.p[36]";
connectAttr "bindPose1.m[33]" "bindPose1.p[37]";
connectAttr "bindPose1.m[37]" "bindPose1.p[38]";
connectAttr "bindPose1.m[38]" "bindPose1.p[39]";
connectAttr "bindPose1.m[33]" "bindPose1.p[40]";
connectAttr "bindPose1.m[40]" "bindPose1.p[41]";
connectAttr "bindPose1.m[41]" "bindPose1.p[42]";
connectAttr "bindPose1.m[33]" "bindPose1.p[43]";
connectAttr "bindPose1.m[43]" "bindPose1.p[44]";
connectAttr "bindPose1.m[44]" "bindPose1.p[45]";
connectAttr "bindPose1.m[33]" "bindPose1.p[46]";
connectAttr "bindPose1.m[46]" "bindPose1.p[47]";
connectAttr "bindPose1.m[47]" "bindPose1.p[48]";
connectAttr "bindPose1.m[1]" "bindPose1.p[49]";
connectAttr "bindPose1.m[49]" "bindPose1.p[50]";
connectAttr "bindPose1.m[1]" "bindPose1.p[51]";
connectAttr "bindPose1.m[51]" "bindPose1.p[52]";
connectAttr "bindPose1.m[8]" "bindPose1.p[53]";
connectAttr "bindPose1.m[50]" "bindPose1.p[54]";
connectAttr "bindPose1.m[13]" "bindPose1.p[55]";
connectAttr "bindPose1.m[53]" "bindPose1.p[56]";
connectAttr "bindPose1.m[56]" "bindPose1.p[57]";
connectAttr "bindPose1.m[55]" "bindPose1.p[58]";
connectAttr "bindPose1.m[58]" "bindPose1.p[59]";
connectAttr "bindPose1.m[51]" "bindPose1.p[60]";
connectAttr "bindPose1.m[60]" "bindPose1.p[61]";
connectAttr "bindPose1.m[49]" "bindPose1.p[62]";
connectAttr "bindPose1.m[62]" "bindPose1.p[63]";
connectAttr "bindPose1.m[62]" "bindPose1.p[64]";
connectAttr "bindPose1.m[64]" "bindPose1.p[65]";
connectAttr "bindPose1.m[60]" "bindPose1.p[66]";
connectAttr "bindPose1.m[66]" "bindPose1.p[67]";
connectAttr "bindPose1.m[52]" "bindPose1.p[68]";
connectAttr "bindPose1.m[61]" "bindPose1.p[69]";
connectAttr "bindPose1.m[63]" "bindPose1.p[70]";
connectAttr "bindPose1.m[6]" "bindPose1.p[71]";
connectAttr "bindPose1.m[71]" "bindPose1.p[73]";
connectAttr "Bip01.bps" "bindPose1.wm[0]";
connectAttr "Bip01_Pelvis.bps" "bindPose1.wm[1]";
connectAttr "Bip01_Spine.bps" "bindPose1.wm[2]";
connectAttr "Bip01_Spine1.bps" "bindPose1.wm[3]";
connectAttr "Bip01_Spine2.bps" "bindPose1.wm[4]";
connectAttr "Bip01_Spine3.bps" "bindPose1.wm[5]";
connectAttr "Bip01_Neck.bps" "bindPose1.wm[6]";
connectAttr "Bip01_R_Clavicle.bps" "bindPose1.wm[7]";
connectAttr "Bip01_R_UpperArm.bps" "bindPose1.wm[8]";
connectAttr "Bip01_R_Forearm.bps" "bindPose1.wm[9]";
connectAttr "Bip01_R_Foretwist.bps" "bindPose1.wm[10]";
connectAttr "Bip01_R_Foretwist1.bps" "bindPose1.wm[11]";
connectAttr "Bip01_L_Clavicle.bps" "bindPose1.wm[12]";
connectAttr "Bip01_L_UpperArm.bps" "bindPose1.wm[13]";
connectAttr "Bip01_L_Forearm.bps" "bindPose1.wm[14]";
connectAttr "Bip01_L_Foretwist.bps" "bindPose1.wm[15]";
connectAttr "Bip01_L_Foretwist1.bps" "bindPose1.wm[16]";
connectAttr "Bip01_L_Hand.bps" "bindPose1.wm[17]";
connectAttr "Bip01_L_Finger1.bps" "bindPose1.wm[18]";
connectAttr "Bip01_L_Finger11.bps" "bindPose1.wm[19]";
connectAttr "Bip01_L_Finger12.bps" "bindPose1.wm[20]";
connectAttr "Bip01_L_Finger4.bps" "bindPose1.wm[21]";
connectAttr "Bip01_L_Finger41.bps" "bindPose1.wm[22]";
connectAttr "Bip01_L_Finger42.bps" "bindPose1.wm[23]";
connectAttr "Bip01_L_Finger0.bps" "bindPose1.wm[24]";
connectAttr "Bip01_L_Finger01.bps" "bindPose1.wm[25]";
connectAttr "Bip01_L_Finger02.bps" "bindPose1.wm[26]";
connectAttr "Bip01_L_Finger2.bps" "bindPose1.wm[27]";
connectAttr "Bip01_L_Finger21.bps" "bindPose1.wm[28]";
connectAttr "Bip01_L_Finger22.bps" "bindPose1.wm[29]";
connectAttr "Bip01_L_Finger3.bps" "bindPose1.wm[30]";
connectAttr "Bip01_L_Finger31.bps" "bindPose1.wm[31]";
connectAttr "Bip01_L_Finger32.bps" "bindPose1.wm[32]";
connectAttr "Bip01_R_Hand.bps" "bindPose1.wm[33]";
connectAttr "Bip01_R_Finger1.bps" "bindPose1.wm[34]";
connectAttr "Bip01_R_Finger11.bps" "bindPose1.wm[35]";
connectAttr "Bip01_R_Finger12.bps" "bindPose1.wm[36]";
connectAttr "Bip01_R_Finger4.bps" "bindPose1.wm[37]";
connectAttr "Bip01_R_Finger41.bps" "bindPose1.wm[38]";
connectAttr "Bip01_R_Finger42.bps" "bindPose1.wm[39]";
connectAttr "Bip01_R_Finger0.bps" "bindPose1.wm[40]";
connectAttr "Bip01_R_Finger01.bps" "bindPose1.wm[41]";
connectAttr "Bip01_R_Finger02.bps" "bindPose1.wm[42]";
connectAttr "Bip01_R_Finger2.bps" "bindPose1.wm[43]";
connectAttr "Bip01_R_Finger21.bps" "bindPose1.wm[44]";
connectAttr "Bip01_R_Finger22.bps" "bindPose1.wm[45]";
connectAttr "Bip01_R_Finger3.bps" "bindPose1.wm[46]";
connectAttr "Bip01_R_Finger31.bps" "bindPose1.wm[47]";
connectAttr "Bip01_R_Finger32.bps" "bindPose1.wm[48]";
connectAttr "Bip01_L_Thigh.bps" "bindPose1.wm[49]";
connectAttr "Bip01_LThighTwist.bps" "bindPose1.wm[50]";
connectAttr "Bip01_R_Thigh.bps" "bindPose1.wm[51]";
connectAttr "Bip01_RThighTwist.bps" "bindPose1.wm[52]";
connectAttr "Bip01_RUpArmTwist.bps" "bindPose1.wm[53]";
connectAttr "Bip01_LThighTwist1.bps" "bindPose1.wm[54]";
connectAttr "Bip01_LUpArmTwist.bps" "bindPose1.wm[55]";
connectAttr "Bip01_RUpArmTwist1.bps" "bindPose1.wm[56]";
connectAttr "Bip01_RUpArmTwist2.bps" "bindPose1.wm[57]";
connectAttr "Bip01_LUpArmTwist1.bps" "bindPose1.wm[58]";
connectAttr "Bip01_LUpArmTwist2.bps" "bindPose1.wm[59]";
connectAttr "Bip01_R_Calf.bps" "bindPose1.wm[60]";
connectAttr "Bip01_RCalfTwist.bps" "bindPose1.wm[61]";
connectAttr "Bip01_L_Calf.bps" "bindPose1.wm[62]";
connectAttr "Bip01_LCalfTwist.bps" "bindPose1.wm[63]";
connectAttr "Bip01_L_Foot.bps" "bindPose1.wm[64]";
connectAttr "Bip01_L_Toe0.bps" "bindPose1.wm[65]";
connectAttr "Bip01_R_Foot.bps" "bindPose1.wm[66]";
connectAttr "Bip01_R_Toe0.bps" "bindPose1.wm[67]";
connectAttr "Bip01_RThighTwist1.bps" "bindPose1.wm[68]";
connectAttr "Bip01_RCalfTwist1.bps" "bindPose1.wm[69]";
connectAttr "Bip01_LCalfTwist1.bps" "bindPose1.wm[70]";
connectAttr "Bip01_Head.bps" "bindPose1.wm[71]";
connectAttr "hyperView1.msg" "nodeEditorPanel1Info.b[0]";
connectAttr "hyperLayout1.msg" "hyperView1.hl";
connectAttr "dx11Shader1.msg" "hyperLayout1.hyp[0].dn";
connectAttr "BruceWayne_BodySG.pa" ":renderPartition.st" -na;
connectAttr "BruceWayne_BodySG1.pa" ":renderPartition.st" -na;
connectAttr "BruceWayne_HeadSG.pa" ":renderPartition.st" -na;
connectAttr "BruceWayne_HeadSG1.pa" ":renderPartition.st" -na;
connectAttr "BruceWayne_HeadSG2.pa" ":renderPartition.st" -na;
connectAttr "BruceWayne_HeadSG3.pa" ":renderPartition.st" -na;
connectAttr "BruceWayne_Suit_Torso_MIC.msg" ":defaultShaderList1.s" -na;
connectAttr "BruceWayne_Suit_Legs_MIC.msg" ":defaultShaderList1.s" -na;
connectAttr "BruceWayne_Head_MIC.msg" ":defaultShaderList1.s" -na;
connectAttr "dx11Shader1.msg" ":defaultShaderList1.s" -na;
connectAttr "BruceWayne_Hair_MIC.msg" ":defaultShaderList1.s" -na;
connectAttr "Character_FakeShadow.msg" ":defaultShaderList1.s" -na;
connectAttr "place2dTexture1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture2.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture3.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture4.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture5.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture6.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "BruceWayne_Suit_Torso_MIC_ncl1_1.msg" ":defaultTextureList1.tx" -na
		;
connectAttr "BruceWayne_Suit_Legs_MIC_ncl1_1.msg" ":defaultTextureList1.tx" -na;
connectAttr "BruceWayne_Head_MIC_ncl1_1.msg" ":defaultTextureList1.tx" -na;
connectAttr "BruceWayne_OZ_Eyes_MIC_ncl1_1.msg" ":defaultTextureList1.tx" -na;
connectAttr "BruceWayne_Hair_MIC_ncl1_1.msg" ":defaultTextureList1.tx" -na;
connectAttr "Character_FakeShadow_ncl1_1.msg" ":defaultTextureList1.tx" -na;
dataStructure -fmt "raw" -as "name=externalContentTable:string=node:string=key:string=upath:uint32=upathcrc:string=rpath:string=roles";
applyMetadata -fmt "raw" -v "channel\nname externalContentTable\nstream\nname v1.0\nindexType numeric\nstructure externalContentTable\n0\n\"BruceWayne_Suit_Torso_MIC_ncl1_1\" \"fileTextureName\" \"C:/Project/NagaGame/Arts/animations/BruceWayne_Suit_Torso_D.tga\" 1126695858 \"C:/Project/NagaGame/Arts/animations/BruceWayne_Suit_Torso_D.tga\" \"sourceImages\"\n1\n\"BruceWayne_Suit_Legs_MIC_ncl1_1\" \"fileTextureName\" \"G:/umodel_resources/animations/Batman_OZ/Textures/BruceWayne_Suit_Legs_D.tga\" 3933860481 \"\" \"sourceImages\"\n2\n\"BruceWayne_Head_MIC_ncl1_1\" \"fileTextureName\" \"G:/umodel_resources/animations/Batman_OZ/Textures/BruceWayne_Head_D.tga\" 3479611922 \"C:/Project/NagaGame/Arts/animations/BruceWayne_Head_D.tga\" \"sourceImages\"\n3\n\"BruceWayne_OZ_Eyes_MIC_ncl1_1\" \"fileTextureName\" \"G:/umodel_resources/animations/Batman_OZ/Textures/Batman_V3_Eye_High_D.tga\" 3372366589 \"\" \"sourceImages\"\n4\n\"BruceWayne_Hair_MIC_ncl1_1\" \"fileTextureName\" \"G:/umodel_resources/animations/Batman_OZ/Textures/BruceWayne_Hair_D.tga\" 1164003679 \"C:/Project/NagaGame/Arts/animations/BruceWayne_Hair_D.tga\" \"sourceImages\"\n5\n\"Character_FakeShadow_ncl1_1\" \"fileTextureName\" \"Character_FakeShadow\" 122788588 \"\" \"sourceImages\"\nendStream\nendChannel\nendAssociations\n" 
		-scn;
// End of bruce_rig.ma
