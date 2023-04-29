uniform sampler2D texture;

void main() {
    // Get the color of the current pixel
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    // If the pixel is transparent, set its color to black
    if (color.a == 0.0) {
        color = vec4(0.0, 0.0, 0.0, 0.4);
    }
    // If the pixel is black, set its alpha value to 0 to make it transparent
    //    else if (color.r == 0.0 && color.g == 0.0 && color.b == 0.0) {
    //        color.a = 0.0;
    //    }
    else {
        color.a = 0.0;
    }


    // Set the new color of the pixel
    gl_FragColor = color;
}