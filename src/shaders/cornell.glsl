#version 420

// --------------------------------------------------
// Uniforms
// --------------------------------------------------
uniform samplerCube sSky;
uniform mat4 uModelViewProjection;
uniform mat3 uModelView;
uniform vec3 uEyePos;
uniform vec2 uPlanes;


// --------------------------------------------------
// Vertex shader
// --------------------------------------------------
#ifdef _VERTEX_
void main() {
	// extract vertices (rockNroll)
	int r = int(gl_VertexID > 6);
	int i = r==1 ? 13-gl_VertexID : gl_VertexID;
	int x = int(i<3 || i==4);
	int y = r ^ int(i>0 && i<4);
	int z = r ^ int(i<2 || i>5);
	// send position
	gl_Position.xyz = vec3(x,y,z)*2.0-1.0;
}
#endif

// --------------------------------------------------
// Geometry shader
// --------------------------------------------------
#ifdef _GEOMETRY_
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;
layout(location=0) flat out vec3 oNormal;
layout(location=1) out vec3 oTexCoord;
layout(location=2) out vec3 oEyeToPos;

void main() {
	const float BOX_SIZE=200.0;
	vec3 p1 = gl_in[0].gl_Position.xyz*BOX_SIZE;
	vec3 p2 = gl_in[1].gl_Position.xyz*BOX_SIZE;
	vec3 p3 = gl_in[2].gl_Position.xyz*BOX_SIZE;
	vec3 e1 = normalize(p2-p1);
	vec3 e2 = normalize(p3-p1);
	oNormal = uModelView*normalize(cross(e1,e2));

	oTexCoord = gl_in[0].gl_Position.xyz;
	oEyeToPos = uEyePos-p1;
	gl_Position = uModelViewProjection * vec4(p1,1);
	EmitVertex();

	oTexCoord = gl_in[1].gl_Position.xyz;
	oEyeToPos = uEyePos-p2;
	gl_Position = uModelViewProjection * vec4(p2,1);
	EmitVertex();

	oTexCoord = gl_in[2].gl_Position.xyz;
	oEyeToPos = uEyePos-p3;
	gl_Position = uModelViewProjection * vec4(p3,1);
	EmitVertex();

	EndPrimitive();
}
#endif


// --------------------------------------------------
// Fragment shader
// --------------------------------------------------
#ifdef _FRAGMENT_
layout(location=0) flat in vec3 iNormal;
layout(location=1) in vec3 iTexCoord;
layout(location=2) in vec3 iEyeToPos;
layout(location=0) out vec4 oNd;
layout(location=1) out vec3 oAlbedo;

void main() {
	oAlbedo = texture(sSky, normalize(iTexCoord)).rgb;
	oNd.rgb = iNormal*0.5+0.5;
	oNd.a = length(iEyeToPos)*uPlanes.x+uPlanes.y;
}
#endif


