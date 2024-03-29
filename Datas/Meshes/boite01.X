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


Frame Bo_te04 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.178661,9.806995,1.000000;;
 }

 Mesh  {
  20;
  10.074462;-0.126866;-4.282380;,
  18.639221;-0.126866;-4.282380;,
  10.074462;-0.126866;4.282380;,
  18.639221;-0.126866;4.282380;,
  10.074462;8.437894;-4.282380;,
  18.639221;8.437894;-4.282380;,
  10.074462;8.437894;4.282380;,
  18.639221;8.437894;4.282380;,
  10.074462;-0.126866;-4.282380;,
  18.639221;8.437894;-4.282380;,
  18.639221;-0.126866;-4.282380;,
  10.074462;8.437894;-4.282380;,
  18.639221;-0.126866;4.282380;,
  18.639221;8.437894;-4.282380;,
  18.639221;-0.126866;4.282380;,
  10.074462;8.437894;4.282380;,
  10.074462;-0.126866;4.282380;,
  18.639221;8.437894;4.282380;,
  10.074462;-0.126866;4.282380;,
  10.074462;8.437894;-4.282380;;
  12;
  3;0,3,2;,
  3;3,0,1;,
  3;4,7,5;,
  3;7,4,6;,
  3;8,9,10;,
  3;9,8,11;,
  3;1,7,12;,
  3;7,1,13;,
  3;14,15,16;,
  3;15,14,17;,
  3;18,19,0;,
  3;19,18,6;;

  MeshNormals  {
   6;
   0.000000;-1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;0.000000;-1.000000;,
   1.000000;0.000000;0.000000;,
   0.000000;0.000000;1.000000;,
   -1.000000;0.000000;0.000000;;
   12;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;,
   3;5,5,5;,
   3;5,5,5;;
  }

  MeshTextureCoords  {
   20;
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;0.000000;;
  }
 }
}