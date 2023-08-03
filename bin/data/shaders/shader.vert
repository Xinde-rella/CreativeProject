#version 410

// vertex shader

      uniform mat4 modelViewProjectionMatrix; // from OF programmable renderer
      uniform mat4 projectionMatrix;
      uniform mat4 viewMatrix;
      uniform mat4 modelMatrix;
         
      uniform float appTime;
 
      in vec4 position;
      in vec3 normal;
      in vec2 texcoord;
      in vec3 color;
      out vec3 vposition;
      out vec3 vnormal;
      out vec2 vtexcoord;
      out vec3 vcolor;
 
      void main(){
          vnormal = normal;
          vposition = (modelMatrix * position).xyz;
          vtexcoord = texcoord;
          vcolor = color;
          vec4 pos = position;
          pos.z += 0.1*sin(355./133. * 4. * pos.x + appTime);
          //gl_Position = modelViewProjectionMatrix * pos;
          gl_Position = projectionMatrix * viewMatrix * vec4(vposition, 1.);
      }
