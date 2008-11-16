// Earth fragment shader blends day/night/cloud/gloss textures based on local time of day.

uniform sampler2D EarthDay, EarthNight, EarthCloudGloss;

const bool cloudCover = true;

varying float Diffuse;
varying vec3  Specular;
varying vec2  TexCoord;

const float Terminator = 0.3;
const float InvTerminator = 1.0 / (2.0 * Terminator);

void main (void)
{
    // separate maps are packed into the color components of this texture
    // clouds.r = cloud opacity
    // clouds.g = water glossiness
    vec2  cg     = texture2D(EarthCloudGloss, TexCoord).rg;
    float clouds = cg.r * float(cloudCover);
    float gloss  = cg.g;

    // load daytime color, plus a specular component modulated by the gloss map  
    vec3 daytime   = texture2D(EarthDay, TexCoord).rgb * Diffuse + Specular * gloss;
    
    // mix in diffusely-lit clouds, modulated by the cloud opacity
    daytime = mix(daytime, vec3(abs(Diffuse)), clouds);

    // load night image, modulated by cloud opacity
    vec3 nighttime = texture2D(EarthNight, TexCoord).rgb * (1.0 - clouds);

    // assume day, to start
    vec3 color = daytime;
 
    // if fully dark, select night
    if (Diffuse < -Terminator)
    {
        color = nighttime;
    }

    // within the twilight zone, mix night/day
    if (abs(Diffuse) < Terminator )
    {
        color = mix(nighttime, daytime, (Diffuse + Terminator) * InvTerminator);
    }
    
    gl_FragColor = vec4 (color, 1.0);
}
