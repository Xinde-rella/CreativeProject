#version 410

      // Fragment program
      in vec2 spriteCoord; // sprite coordinate in [ -1 ,1]
      out vec4 fragColor;
 
      void main(){
          float rsqr = dot(spriteCoord, spriteCoord);
          if(rsqr > 1.) discard;
          vec3 col = vec3 (0. ,1. ,1.);
          float a = 1. - rsqr; // inverted parabola
    //      a *= a; // smooth ends
          float w = 0.5; // attenuation width
          float wsqr = w*w;
          a *= wsqr/(wsqr + rsqr);
          col *= a;
          fragColor = vec4(col , 1.);
      }
