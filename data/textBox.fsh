uniform sampler2D texture1;
uniform vec4 color;
out vec4 PixelColor;
in vec2 v_uv1;


void main()
{
    PixelColor = texture(texture1, v_uv1) * color; 
}

