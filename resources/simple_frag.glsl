// #version 330 core 
// in vec3 fragNor;
// out vec4 color;

// uniform vec3 MatAmb;
// uniform vec3 LightDir; // Direction to the light source
// uniform int colorMode;

// void main()
// {
//     vec3 normal = normalize(fragNor);

//     if(colorMode == 0) {
//         color = vec4(normal, 1.0);
//     } 
//     else if(colorMode == 1) {
//         // adds shadows to colored scene
//         float lambertian = max(dot(normal, -LightDir), 0.0);
//         vec3 lightColor = vec3(1.0, 1.0, 1.0);
//         vec3 finalColor = MatAmb * lambertian * lightColor;
//         finalColor += MatAmb;

//         color = vec4(finalColor, 1.0);
//     }
// }



#version 330 core
in vec3 fragNor;
out vec4 color;

uniform vec3 MatAmb;
uniform vec3 LightDir; // Direction to the light source
uniform int colorMode;

void main()
{
    vec3 normal = normalize(fragNor);
    vec3 lightDir = normalize(-LightDir); // Normalizing light direction

    if (colorMode == 0) {
        color = vec4(normal, 1.0);
    }
    else if (colorMode == 1) {
        // Lambertian (diffuse) reflection
        float lambertian = max(dot(normal, lightDir), 0.0);
        vec3 lightColor = vec3(1.0, 1.0, 1.0);

        // Specular reflection (Phong model)
        vec3 viewDir = normalize(-vec3(gl_FragCoord)); // View direction (assuming camera at origin)
        vec3 reflectDir = reflect(-lightDir, normal);
        float specular = pow(max(dot(reflectDir, viewDir), 0.0), 32.0); // Shininess factor (adjustable)

        // Combining ambient, diffuse, and specular reflections
        vec3 finalColor = MatAmb + (MatAmb * lambertian + specular) * lightColor;

        color = vec4(finalColor, 1.0);
    }
}
