#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 fragColor;

const float offset = 1.0 / 32.0;

uniform int tilemapMode;
uniform int occupied;
uniform int mp;
uniform ivec2 selPos;
uniform ivec2 tilePos;

uniform vec3 color;
uniform int outlined;
uniform sampler2D texture2D[2];

void main(){
	vec4 fragmentColor;
	if (outlined == 0)
		fragmentColor = texture(texture2D[0], TexCoord);
	else{
		vec4 col = texture(texture2D[0], TexCoord);
		if (col.a > 0.5)
			fragmentColor = col;
		else {
			float a = texture(texture2D[0], vec2(TexCoord.x + offset, TexCoord.y)).a +
				texture(texture2D[0], vec2(TexCoord.x, TexCoord.y - offset)).a +
				texture(texture2D[0], vec2(TexCoord.x - offset, TexCoord.y)).a +
				texture(texture2D[0], vec2(TexCoord.x, TexCoord.y + offset)).a;
			if (col.a < 1.0 && a > 0.0)
				fragmentColor = vec4(color, 0.8);
			else
				fragmentColor = col;
		}
	}
	if (tilemapMode == 1){
		ivec2 selToTile = selPos - tilePos;
		int dist = abs(selToTile.x) + abs(selToTile.y);
		if (occupied == 0 && mp >= dist){
			fragmentColor = mix(fragmentColor, vec4(1.0, 0.0, 0.0, 1.0), 0.3); 
		}
	}
	fragColor = fragmentColor;
}

