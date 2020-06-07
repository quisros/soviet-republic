## Lighting maps

Real objects usually consist of several materials.
Diffuse and specular maps allow us to influence the lighting of objects more precisely.

### Diffuse maps

Required: a system to retrieve a color value for a fragment based on its position on the object. 
So we use a diffuse map, sort of an image wrapped around the object that we can index for
unique color values per fragment.

The earlier defined vec3 diffuse color is replace with the diffuse map.
Since we now control ambient with the light, we can remove ambient color too as it is the same as diffuse color.

### Specular maps

Specular maps are usually black and white images as we only care about the intensity.
The intensity of the specular highlight comes from the brightness of each pixel in the image.
