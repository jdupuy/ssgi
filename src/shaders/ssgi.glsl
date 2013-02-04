#version 420

// --------------------------------------------------
// Uniforms
// --------------------------------------------------
uniform sampler2DRect sNd; // normal + depth
uniform sampler2DRect sKa; // albedo
uniform vec2 uScreenSize;  // screen dimensions


// --------------------------------------------------
// Vertex shader
// --------------------------------------------------
#ifdef _VERTEX_
layout(location=0) out vec2 oTexCoord;
void main() {
	oTexCoord = vec2(gl_VertexID & 1, gl_VertexID >> 1 & 1);
	gl_Position = vec4(oTexCoord*2.0-1.0,0,1);
}
#endif //_VERTEX_


// --------------------------------------------------
// Fragment shader
// --------------------------------------------------
#ifdef _FRAGMENT_
layout(location=0) in vec2 iTexCoord;
layout(location=0) out vec4 oColour;
void main() {
	vec2 st = iTexCoord*uScreenSize;
	vec4 t1 = texture(sNd,st);
	vec3 t2 = texture(sKa,st).rgb;
	oColour.rgb = t2;
	oColour.rgb = t1.aaaa;
}
#endif // _FRAGMENT_

