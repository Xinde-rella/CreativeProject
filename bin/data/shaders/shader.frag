#version 410

// fragment shader

struct Light {
    vec3 pos;
    float strength;
    float halfDist;
    float ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 diffuse;
    vec3 specular;
    float shine;
};

struct LightFall {
    vec3 diffuse;
    vec3 specular;
};

// In-place addition : a += b
void addTo(inout LightFall a, in LightFall b){
    a.diffuse += b.diffuse;
    a.specular += b.specular;
}

// Compute light components falling on surface
LightFall computeLightFall (vec3 pos, vec3 N, vec3 eye, in Light lt, in Material mt){
    vec3 lightDist = lt.pos - pos;
    float hh = lt.halfDist * lt.halfDist;
    float atten = lt.strength * hh/(hh + dot(lightDist, lightDist));
    vec3 L = normalize(lightDist);

    // diffuse
    float d = max(dot(N, L) , 0.);
    d += lt.ambient;

    // specular
    vec3 V = normalize(eye - pos);
    vec3 H = normalize(L + V);
    float s = pow(max(dot(N, H), 0.), mt.shine);

    LightFall fall ;
    fall.diffuse = lt.diffuse *(d*atten);
    fall.specular = lt.specular *(s*atten);
    return fall ;
 }

 // Get final color reflected off material
 vec3 lightColor(in LightFall f , in Material mt){
     return f.diffuse * mt.diffuse + f.specular * mt.specular;
 }



  uniform sampler2D tex; // texture (ID) passed in from the CPU
  uniform sampler2D tex2; // texture (ID) passed in from the CPU
  uniform float texturing;
  uniform float texturing2;
  uniform vec3 eye;
  uniform vec3 lightPosition;
  uniform sampler2D envirMap;

  in vec3 vposition;
  in vec3 vnormal;
  in vec3 vcolor;
  in vec2 vtexcoord; // interpolant from vertex shader
  out vec4 fragColor;
 
vec3 calcReflection (vec3 I, vec3 N, in sampler2D envirMap){
    vec3 rayDir = reflect(I, N);
    
    // Convert ray direction from Cartesian to polar coords
    float theta = atan(rayDir.x, rayDir.z);
    float phi = asin(rayDir.y);

    // Map polar coord to texture coord in the environment map
    const float oneOverPi = 113./355.;
    vec2 uv = vec2(0.5 + 0.5*theta*oneOverPi, 0.5 - phi*oneOverPi);

    // Lookup the color from the environment map
    return texture(envirMap, uv).rgb;
}
 
void main(){
    vec3 pos = vposition;
    vec3 normal = normalize(vnormal);

    Light light1;
    light1.pos = lightPosition;
    light1.strength = 1.;
    light1.halfDist = 200.;
    light1.ambient = 0.2;
    light1.diffuse = vec3 (0.2, 1., 0.3); //grey green light
    light1.specular = light1.diffuse;

    Light light2 = light1;
    light2.strength =1.0;
    light2.pos = vec3(120, -50, -100);
    light2.diffuse = vec3 (1. ,0. ,1.); //pink light
    light2.specular = light2.diffuse;

    Material mtrl;
    mtrl.diffuse = vec3(0.2, 0.4, 0.7);
    mtrl.specular = vec3(1., 1., 1.);
    mtrl.shine = 200.;

    LightFall fall = computeLightFall(pos, normal, eye, light1, mtrl);
    addTo(fall, computeLightFall(pos, normal, eye, light2, mtrl));

    vec3 col = lightColor(fall, mtrl);
    vec3 col2 = texture(tex, vtexcoord).rgb;
    col = mix(vcolor, col, texturing);

    vec3 I = -normalize(eye - pos); // incident ray

    // Add the effect of reflections
    float reflectivity = 1.;
    vec3 reflCol = calcReflection(I, normal, envirMap);
    col2 = mix(col, reflCol, reflectivity);

    //fragColor = vec4(col, 1.) ;


    //       vec3 col = lightColor(fall, mtrl);
    //       vec3 col2 = texture(tex, vtexcoord).rgb;
    //
    //         col = mix(vcolor, col, texturing);
    //
    fragColor = vec4(col+col2, 1.);
}




