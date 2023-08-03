#version 410
         // Vertex program
         uniform mat4 modelViewProjectionMatrix;
         uniform float spriteRadius;
         uniform mat4 cameraMatrix;
         in vec4 position;
         in vec2 texcoord;
         out vec2 spriteCoord; // sprite coordinate in [ -1 ,1]
         
         void main(){
             spriteCoord = texcoord * 2. - 1.;
             vec4 pos = position;
             switch(gl_VertexID % 4){
                 case 0: spriteCoord = vec2( -1., -1.); break;
                 case 1: spriteCoord = vec2( 1., -1.); break;
                 case 2: spriteCoord = vec2( 1., 1.); break;
                 case 3: spriteCoord = vec2( -1., 1.); break;
         }
 
         vec4 offset = vec4(spriteCoord * spriteRadius, 0., 0.);
//         vec4 offset = vec4(0.);

             switch(gl_VertexID % 4){
                 case 0: offset.x =- spriteRadius; offset.y =- spriteRadius; break;
                 case 1: offset.x = spriteRadius; offset.y =- spriteRadius; break;
                 case 2: offset.x = spriteRadius; offset.y = spriteRadius; break;
                 case 3: offset.x =- spriteRadius; offset.y = spriteRadius; break;
             }
             
         offset = cameraMatrix * offset;
         pos += offset;
 
         gl_Position = modelViewProjectionMatrix * pos;
         }


