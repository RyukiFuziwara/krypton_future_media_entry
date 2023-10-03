xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 115;
 -0.37893;-10.19452;-0.43504;,
 -0.54348;-10.19452;-0.03776;,
 -1.01978;-9.87627;-0.03776;,
 -0.71572;-9.87627;-0.77183;,
 -0.37893;-10.19452;0.35951;,
 -0.71572;-9.87627;0.69631;,
 0.01835;-10.19452;0.52407;,
 0.01835;-9.87627;1.00037;,
 0.58691;-10.19452;0.35951;,
 0.92370;-9.87627;0.69631;,
 0.75146;-10.19452;-0.03776;,
 1.22776;-9.87627;-0.03776;,
 0.58691;-10.19452;-0.43504;,
 0.92370;-9.87627;-0.77183;,
 0.01835;-10.19452;-0.59960;,
 0.01835;-9.87627;-1.07589;,
 -1.33803;-9.39997;-0.03776;,
 -0.94076;-9.39997;-0.99687;,
 -0.94076;-9.39997;0.92134;,
 0.01835;-9.39997;1.31862;,
 1.14874;-9.39997;0.92134;,
 1.54601;-9.39997;-0.03776;,
 1.14874;-9.39997;-0.99687;,
 0.01835;-9.39997;-1.39415;,
 -1.44979;-8.83814;-0.03776;,
 -1.01978;-8.83814;-1.07589;,
 -1.01978;-8.83814;1.00037;,
 0.01835;-8.83814;1.43037;,
 1.22776;-8.83814;1.00037;,
 1.65777;-8.83814;-0.03776;,
 1.22776;-8.83814;-1.07589;,
 0.01835;-8.83814;-1.50590;,
 -1.33803;-8.27631;-0.03776;,
 -0.94076;-8.27631;-0.99687;,
 -0.94076;-8.27631;0.92134;,
 0.01835;-8.27631;1.31862;,
 1.14874;-8.27631;0.92134;,
 1.54601;-8.27631;-0.03776;,
 1.14874;-8.27631;-0.99687;,
 0.01835;-8.27631;-1.39415;,
 -1.01978;-7.80001;-0.03776;,
 -0.71572;-7.80001;-0.77183;,
 -0.71572;-7.80001;0.69631;,
 0.01835;-7.80001;1.00037;,
 0.92370;-7.80001;0.69631;,
 1.22776;-7.80001;-0.03776;,
 0.92370;-7.80001;-0.77183;,
 0.01835;-7.80001;-1.07589;,
 -0.54348;-7.48176;-0.03776;,
 -0.37893;-7.48176;-0.43504;,
 -0.37893;-7.48176;0.35951;,
 0.01835;-7.48176;0.52407;,
 0.58691;-7.48176;0.35951;,
 0.75146;-7.48176;-0.03776;,
 0.58691;-7.48176;-0.43504;,
 0.01835;-7.48176;-0.59960;,
 0.01835;-10.30628;-0.03776;,
 0.01835;-7.37000;-0.03776;,
 1.07911;-9.57685;-0.06043;,
 0.80048;-9.57021;0.61244;,
 0.80048;-9.57021;-0.73331;,
 0.08018;-9.55418;-1.01202;,
 0.08018;-9.55418;0.89116;,
 -0.59250;-9.57021;-0.73331;,
 -0.59250;-9.57021;0.61244;,
 -0.87113;-9.57685;-0.06043;,
 -1.21357;-7.45295;-0.06043;,
 -0.84952;-7.44427;-0.93958;,
 -0.84952;-7.44427;0.81872;,
 0.02939;-7.42332;1.18288;,
 1.05750;-7.44427;0.81872;,
 1.42155;-7.45295;-0.06043;,
 1.05750;-7.44427;-0.93958;,
 0.02939;-7.42332;-1.30374;,
 -1.37590;-4.94187;-0.06043;,
 -0.98185;-4.93248;-1.01202;,
 -0.98185;-4.93248;0.89116;,
 -0.03054;-4.90980;1.28532;,
 1.18983;-4.93248;0.89116;,
 1.58388;-4.94187;-0.06043;,
 1.18983;-4.93248;-1.01202;,
 -0.03054;-4.90980;-1.40618;,
 4.29670;-7.94706;-0.06043;,
 3.24074;-8.08114;2.79288;,
 3.24074;-8.08114;-2.91374;,
 0.69142;-8.40483;-4.09562;,
 0.69142;-8.40483;3.97476;,
 -1.85789;-8.72852;-2.91374;,
 -1.85789;-8.72852;2.79288;,
 -2.91385;-8.86260;-0.06043;,
 -3.29772;-3.64302;-0.06043;,
 -2.32214;-3.51916;-2.69655;,
 -2.32214;-3.51916;2.57568;,
 0.03312;-3.22011;3.66760;,
 2.38838;-2.92106;2.57568;,
 3.36396;-2.79719;-0.06043;,
 2.38838;-2.92106;-2.69655;,
 0.03312;-3.22011;-3.78846;,
 -2.79579;-1.34177;-0.06043;,
 -2.04912;-1.24696;-2.07803;,
 -2.04912;-1.24696;1.95716;,
 -0.24648;-1.01809;2.79288;,
 1.55616;-0.78920;1.95716;,
 2.30284;-0.69440;-0.06043;,
 1.55616;-0.78920;-2.07803;,
 -0.24648;-1.01809;-2.91374;,
 -2.09486;-0.69440;-0.06043;,
 -1.31711;-0.39338;-1.15235;,
 -1.31711;-0.39338;1.03148;,
 -0.34152;-0.26952;1.48377;,
 0.54950;-0.26952;1.48377;,
 1.03816;-0.09434;-0.06043;,
 0.63406;-0.14564;-1.15235;,
 -0.42608;-0.14564;-1.15235;,
 -0.83018;-0.09434;-0.06043;;
 
 130;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 4;3,2,16,17;,
 4;2,5,18,16;,
 4;5,7,19,18;,
 4;7,9,20,19;,
 4;9,11,21,20;,
 4;11,13,22,21;,
 4;13,15,23,22;,
 4;15,3,17,23;,
 4;17,16,24,25;,
 4;16,18,26,24;,
 4;18,19,27,26;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,17,25,31;,
 4;25,24,32,33;,
 4;24,26,34,32;,
 4;26,27,35,34;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,25,33,39;,
 4;33,32,40,41;,
 4;32,34,42,40;,
 4;34,35,43,42;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,33,41,47;,
 4;41,40,48,49;,
 4;40,42,50,48;,
 4;42,43,51,50;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,41,49,55;,
 3;1,0,56;,
 3;4,1,56;,
 3;6,4,56;,
 3;8,6,56;,
 3;10,8,56;,
 3;12,10,56;,
 3;14,12,56;,
 3;0,14,56;,
 3;49,48,57;,
 3;48,50,57;,
 3;50,51,57;,
 3;51,52,57;,
 3;52,53,57;,
 3;53,54,57;,
 3;54,55,57;,
 3;55,49,57;,
 3;58,59,60;,
 3;60,59,61;,
 3;59,62,61;,
 3;61,62,63;,
 3;62,64,63;,
 3;64,65,63;,
 4;63,65,66,67;,
 4;65,64,68,66;,
 4;64,62,69,68;,
 4;62,59,70,69;,
 4;59,58,71,70;,
 4;58,60,72,71;,
 4;60,61,73,72;,
 4;61,63,67,73;,
 4;67,66,74,75;,
 4;66,68,76,74;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,73,81,80;,
 4;73,67,75,81;,
 3;79,80,78;,
 3;78,80,77;,
 3;80,81,77;,
 3;77,81,76;,
 3;81,75,76;,
 3;75,74,76;,
 3;82,83,84;,
 3;84,83,85;,
 3;83,86,85;,
 3;85,86,87;,
 3;86,88,87;,
 3;88,89,87;,
 4;87,89,90,91;,
 4;89,88,92,90;,
 4;88,86,93,92;,
 4;86,83,94,93;,
 4;83,82,95,94;,
 4;82,84,96,95;,
 4;84,85,97,96;,
 4;85,87,91,97;,
 4;91,90,98,99;,
 4;90,92,100,98;,
 4;92,93,101,100;,
 4;93,94,102,101;,
 4;94,95,103,102;,
 4;95,96,104,103;,
 4;96,97,105,104;,
 4;97,91,99,105;,
 4;99,98,106,107;,
 4;98,100,108,106;,
 4;100,101,109,108;,
 4;101,102,110,109;,
 4;102,103,111,110;,
 4;103,104,112,111;,
 4;104,105,113,112;,
 4;105,99,107,113;,
 3;107,106,114;,
 3;106,108,114;,
 3;108,109,114;,
 3;109,110,114;,
 3;110,111,114;,
 3;111,112,114;,
 3;112,113,114;,
 3;113,107,114;;
 
 MeshMaterialList {
  3;
  130;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
 "data\\TEXTURE\\miku.png";
   }
  }
  Material {
   0.800000;0.762400;0.702400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  139;
  -0.269136;-0.924734;-0.269132;,
  -0.380614;-0.924734;0.000001;,
  -0.269134;-0.924735;0.269132;,
  -0.019042;-0.923141;0.383990;,
  0.239861;-0.932475;0.270106;,
  0.359294;-0.933224;0.000001;,
  0.239862;-0.932474;-0.270107;,
  -0.019042;-0.923140;-0.383993;,
  -0.498495;-0.709231;-0.498491;,
  -0.704978;-0.709230;0.000001;,
  -0.498495;-0.709230;0.498493;,
  -0.026038;-0.704567;0.709160;,
  0.476006;-0.715210;0.511755;,
  0.704978;-0.709229;0.000001;,
  0.476006;-0.715211;-0.511753;,
  -0.026038;-0.704568;-0.709158;,
  -0.652735;-0.384551;-0.652731;,
  -0.923104;-0.384550;0.000001;,
  -0.652734;-0.384549;0.652734;,
  -0.026351;-0.380908;0.924238;,
  0.632714;-0.388647;0.669795;,
  0.923104;-0.384550;0.000001;,
  0.632716;-0.388649;-0.669793;,
  -0.026351;-0.380911;-0.924236;,
  -0.707108;0.000000;-0.707105;,
  -1.000000;0.000000;0.000001;,
  -0.707106;0.000000;0.707107;,
  -0.026447;-0.000000;0.999650;,
  0.688151;0.000000;0.725567;,
  1.000000;-0.000000;0.000001;,
  0.688153;0.000000;-0.725565;,
  -0.026447;0.000000;-0.999650;,
  -0.652735;0.384551;-0.652731;,
  -0.923104;0.384550;0.000001;,
  -0.652734;0.384549;0.652734;,
  -0.026351;0.380908;0.924238;,
  0.632714;0.388647;0.669795;,
  0.923104;0.384550;0.000001;,
  0.632716;0.388649;-0.669793;,
  -0.026351;0.380911;-0.924236;,
  -0.498495;0.709231;-0.498492;,
  -0.704978;0.709229;0.000001;,
  -0.498495;0.709230;0.498493;,
  -0.026038;0.704566;0.709160;,
  0.476007;0.715209;0.511755;,
  0.704978;0.709229;0.000001;,
  0.476007;0.715210;-0.511754;,
  -0.026038;0.704568;-0.709159;,
  -0.269136;0.924734;-0.269133;,
  -0.380615;0.924734;0.000001;,
  -0.269134;0.924735;0.269132;,
  -0.019042;0.923141;0.383991;,
  0.239861;0.932475;0.270107;,
  0.359295;0.933224;0.000001;,
  0.239863;0.932474;-0.270107;,
  -0.019042;0.923139;-0.383994;,
  -0.017397;-0.999849;0.000001;,
  -0.017397;0.999849;0.000001;,
  0.023824;-0.999716;-0.000000;,
  0.023824;-0.999716;-0.000000;,
  0.023824;-0.999716;-0.000000;,
  0.008468;-0.999964;-0.000000;,
  -0.022774;-0.999741;0.000000;,
  -0.023824;-0.999716;0.000000;,
  -0.023036;-0.999735;0.000000;,
  -0.006893;-0.999976;0.000000;,
  -0.702043;-0.105045;-0.704345;,
  -0.993708;-0.111999;0.000001;,
  -0.702044;-0.105046;0.704344;,
  -0.025705;-0.092592;0.995372;,
  0.683666;-0.101701;0.722674;,
  0.993708;-0.111999;0.000001;,
  0.683666;-0.101700;-0.722675;,
  -0.025705;-0.092590;-0.995372;,
  -0.705351;-0.057537;-0.706520;,
  -0.997917;-0.064510;0.000000;,
  -0.705351;-0.057537;0.706520;,
  -0.032927;-0.045278;0.998432;,
  0.681708;-0.053628;0.729657;,
  0.997917;-0.064510;-0.000000;,
  0.681708;-0.053628;-0.729657;,
  -0.032927;-0.045278;-0.998432;,
  0.125961;-0.992035;-0.000000;,
  0.125963;-0.992035;-0.000000;,
  0.125962;-0.992035;-0.000000;,
  0.125960;-0.992035;-0.000000;,
  0.125961;-0.992035;-0.000000;,
  0.125964;-0.992035;-0.000000;,
  0.125962;-0.992035;-0.000000;,
  0.125960;-0.992035;-0.000000;,
  -0.737844;0.113680;-0.665330;,
  -0.997470;0.071094;0.000000;,
  -0.737844;0.113680;0.665329;,
  -0.027239;0.214524;0.976339;,
  0.686020;0.294471;0.665330;,
  0.948051;0.318120;0.000001;,
  0.686020;0.294470;-0.665330;,
  -0.027238;0.214524;-0.976339;,
  -0.632328;0.573446;-0.520886;,
  -0.855736;0.517413;0.000001;,
  -0.640676;0.562591;0.522518;,
  -0.093047;0.645431;0.758130;,
  0.461405;0.707953;0.534704;,
  0.688362;0.725362;0.002918;,
  0.465380;0.719006;-0.516189;,
  -0.086972;0.667356;-0.739643;,
  -0.414193;0.881323;-0.227405;,
  -0.543546;0.839380;0.000000;,
  -0.410667;0.879524;0.240397;,
  -0.117104;0.934131;0.337173;,
  0.121496;0.960997;0.248443;,
  0.210528;0.977388;0.019779;,
  0.123531;0.972872;-0.195602;,
  -0.126929;0.948358;-0.290699;,
  -0.169276;0.985351;0.020735;,
  -0.697147;-0.152257;-0.700574;,
  -0.987250;-0.159175;0.000001;,
  -0.697148;-0.152259;0.700573;,
  -0.018398;-0.139858;0.990001;,
  0.684012;-0.149170;0.714056;,
  0.987250;-0.159175;0.000001;,
  0.684011;-0.149169;-0.714057;,
  -0.018398;-0.139855;-0.990001;,
  0.023823;0.999716;0.000000;,
  0.020329;0.999793;0.000000;,
  0.021202;0.999775;0.000000;,
  0.004444;0.999990;0.000000;,
  -0.009697;0.999953;0.000000;,
  -0.023830;0.999716;0.000000;,
  -0.023829;0.999716;0.000000;,
  -0.023823;0.999716;0.000000;,
  -0.732853;-0.036985;-0.679381;,
  -0.997307;-0.073346;0.000000;,
  -0.732853;-0.036985;0.679381;,
  -0.007391;0.058203;0.998277;,
  0.718841;0.147337;0.679381;,
  0.983991;0.178219;0.000000;,
  0.718841;0.147336;-0.679382;,
  -0.007390;0.058202;-0.998277;;
  130;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,8,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,24,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,24,32,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,32,40,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,40,48,55;,
  3;1,0,56;,
  3;2,1,56;,
  3;3,2,56;,
  3;4,3,56;,
  3;5,4,56;,
  3;6,5,56;,
  3;7,6,56;,
  3;0,7,56;,
  3;48,49,57;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,48,57;,
  3;63,62,64;,
  3;64,62,65;,
  3;62,61,65;,
  3;65,61,58;,
  3;61,60,58;,
  3;60,59,58;,
  4;115,116,67,66;,
  4;116,117,68,67;,
  4;117,118,69,68;,
  4;118,119,70,69;,
  4;119,120,71,70;,
  4;120,121,72,71;,
  4;121,122,73,72;,
  4;122,115,66,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,73,81,80;,
  4;73,66,74,81;,
  3;123,124,125;,
  3;125,124,126;,
  3;124,127,126;,
  3;126,127,128;,
  3;127,129,128;,
  3;129,130,128;,
  3;87,86,88;,
  3;88,86,89;,
  3;86,85,89;,
  3;89,85,82;,
  3;85,84,82;,
  3;84,83,82;,
  4;131,132,91,90;,
  4;132,133,92,91;,
  4;133,134,93,92;,
  4;134,135,94,93;,
  4;135,136,95,94;,
  4;136,137,96,95;,
  4;137,138,97,96;,
  4;138,131,90,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,90,98,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,102,110,109;,
  4;102,103,111,110;,
  4;103,104,112,111;,
  4;104,105,113,112;,
  4;105,98,106,113;,
  3;106,107,114;,
  3;107,108,114;,
  3;108,109,114;,
  3;109,110,114;,
  3;110,111,114;,
  3;111,112,114;,
  3;112,113,114;,
  3;113,106,114;;
 }
 MeshTextureCoords {
  115;
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.114910;0.829180;,
  0.098270;0.829370;,
  0.131550;0.829370;,
  0.138440;0.829810;,
  0.091380;0.829810;,
  0.131550;0.830250;,
  0.098270;0.830250;,
  0.114910;0.830430;,
  0.114910;0.771900;,
  0.136650;0.771660;,
  0.093170;0.771660;,
  0.084160;0.771080;,
  0.093170;0.770500;,
  0.114910;0.770260;,
  0.136650;0.770500;,
  0.145650;0.771080;,
  0.114910;0.702690;,
  0.138440;0.702430;,
  0.091380;0.702430;,
  0.081630;0.701810;,
  0.091380;0.701180;,
  0.114910;0.700920;,
  0.138440;0.701180;,
  0.148180;0.701810;,
  0.811480;0.206630;,
  0.770490;0.209020;,
  0.852460;0.209020;,
  0.869440;0.214780;,
  0.753520;0.214780;,
  0.852460;0.220550;,
  0.770490;0.220550;,
  0.811480;0.222940;,
  0.811480;0.129990;,
  0.849340;0.127790;,
  0.773610;0.127790;,
  0.757930;0.122460;,
  0.773610;0.117140;,
  0.811480;0.114930;,
  0.849340;0.117140;,
  0.865030;0.122460;,
  0.811480;0.089020;,
  0.840460;0.087330;,
  0.782500;0.087330;,
  0.770490;0.083250;,
  0.782500;0.079180;,
  0.811480;0.077490;,
  0.840460;0.079180;,
  0.852460;0.083250;,
  0.811480;0.073040;,
  0.827160;0.072130;,
  0.795790;0.072130;,
  0.789300;0.069930;,
  0.795790;0.067720;,
  0.811480;0.066810;,
  0.827160;0.067720;,
  0.833660;0.069930;,
  0.811480;0.065240;;
 }
}
