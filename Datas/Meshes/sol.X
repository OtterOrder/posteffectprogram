xof 0303txt 0032
template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}


Frame Plan01 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh  {
  25;
  -47.510136;0.000000;-49.680313;,
  -23.755068;0.000000;-49.680313;,
  0.000000;0.000000;-49.680313;,
  23.755068;0.000000;-49.680313;,
  47.510136;0.000000;-49.680313;,
  -47.510136;0.000000;-24.840157;,
  -23.755068;0.000000;-24.840157;,
  0.000000;0.000000;-24.840157;,
  23.755068;0.000000;-24.840157;,
  47.510136;0.000000;-24.840157;,
  -47.510136;0.000000;0.000000;,
  -23.755068;0.000000;0.000000;,
  0.000000;0.000000;0.000000;,
  23.755068;0.000000;0.000000;,
  47.510136;0.000000;0.000000;,
  -47.510136;0.000000;24.840157;,
  -23.755068;0.000000;24.840157;,
  0.000000;0.000000;24.840157;,
  23.755068;0.000000;24.840157;,
  47.510136;0.000000;24.840157;,
  -47.510136;0.000000;49.680313;,
  -23.755068;0.000000;49.680313;,
  0.000000;0.000000;49.680313;,
  23.755068;0.000000;49.680313;,
  47.510136;0.000000;49.680313;;
  32;
  3;0,6,1;,
  3;6,0,5;,
  3;1,7,2;,
  3;7,1,6;,
  3;2,8,3;,
  3;8,2,7;,
  3;3,9,4;,
  3;9,3,8;,
  3;5,11,6;,
  3;11,5,10;,
  3;6,12,7;,
  3;12,6,11;,
  3;7,13,8;,
  3;13,7,12;,
  3;8,14,9;,
  3;14,8,13;,
  3;10,16,11;,
  3;16,10,15;,
  3;11,17,12;,
  3;17,11,16;,
  3;12,18,13;,
  3;18,12,17;,
  3;13,19,14;,
  3;19,13,18;,
  3;15,21,16;,
  3;21,15,20;,
  3;16,22,17;,
  3;22,16,21;,
  3;17,23,18;,
  3;23,17,22;,
  3;18,24,19;,
  3;24,18,23;;

  MeshNormals  {
   1;
   0.000000;1.000000;0.000000;;
   32;
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;;
  }

  MeshTextureCoords  {
   25;
   0.000000;1.000000;,
   1.307542;1.000000;,
   2.615083;1.000000;,
   3.922625;1.000000;,
   5.230166;1.000000;,
   0.000000;-0.307541;,
   1.307542;-0.307541;,
   2.615083;-0.307541;,
   3.922625;-0.307541;,
   5.230166;-0.307541;,
   0.000000;-1.615083;,
   1.307542;-1.615083;,
   2.615083;-1.615083;,
   3.922625;-1.615083;,
   5.230166;-1.615083;,
   0.000000;-2.922625;,
   1.307542;-2.922625;,
   2.615083;-2.922625;,
   3.922625;-2.922625;,
   5.230166;-2.922625;,
   0.000000;-4.230166;,
   1.307542;-4.230166;,
   2.615083;-4.230166;,
   3.922625;-4.230166;,
   5.230166;-4.230166;;
  }
 }
}