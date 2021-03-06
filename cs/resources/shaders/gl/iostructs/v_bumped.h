
out gl_PerVertex { vec4 gl_Position; };

layout(location = POSITION)		in vec4	P;	// (float,float,float,1)
layout(location = NORMAL)		in vec4	Nh;	// (nx,ny,nz,hemi occlusion)
layout(location = TANGENT)		in vec4	T;	// tangent
layout(location = BINORMAL)		in vec4	B;	// binormal
layout(location = TEXCOORD0)	in vec2	tc;	// (u,v)
layout(location = TEXCOORD1)	in vec2	lm;	// (lmu,lmv)
layout(location = COLOR0)		in vec4	color;	// (r,g,b,dir-occlusion)	//	Swizzle before use!!!

#if defined(USE_R2_STATIC_SUN) && !defined(USE_LM_HEMI)
layout(location = TEXCOORD0) out vec4	tcdh;		// Texture coordinates,         w=sun_occlusion
#else
layout(location = TEXCOORD0) out vec2	tcdh;		// Texture coordinates
#endif
layout(location = TEXCOORD1) out vec4	position;	// position + hemi
layout(location = TEXCOORD2) out vec3	M1;			// nmap 2 eye - 1
layout(location = TEXCOORD3) out vec3	M2;			// nmap 2 eye - 2
layout(location = TEXCOORD4) out vec3	M3;			// nmap 2 eye - 3
#if defined(USE_PARALLAX) || defined(USE_STEEPPARALLAX)
layout(location = TEXCOORD5) out vec3	eye;		// vector to point in tangent space
  #ifdef USE_TDETAIL
layout(location = TEXCOORD6) out vec2	tcdbump;	// d-bump
    #ifdef USE_LM_HEMI
layout(location = TEXCOORD7) out vec2	lmh;		// lm-hemi
    #endif
  #else
    #ifdef USE_LM_HEMI
layout(location = TEXCOORD6) out vec2	lmh;		// lm-hemi
    #endif
  #endif
#else
  #ifdef USE_TDETAIL
layout(location = TEXCOORD5) out vec2	tcdbump;	// d-bump
    #ifdef USE_LM_HEMI
layout(location = TEXCOORD6) out vec2	lmh;		// lm-hemi
    #endif
  #else
    #ifdef USE_LM_HEMI
layout(location = TEXCOORD5) out vec2	lmh;		// lm-hemi
    #endif
  #endif
#endif

p_bumped _main( v_static I );

void main()
{
	v_static I;
	I.P		= P;
	I.Nh	= Nh;
	I.T		= T;
	I.B		= B;
	I.tc	= tc;
#if	defined(USE_LM_HEMI)
	I.lmh	= lm;
#else
	I.color = color;
//	I.color.rgb 	= I.color.bgr;	//	Swizzle to compensate DX9/OGL format mismatch
#endif

	p_bumped O = _main(I);

	tcdh		= O.tcdh;
	position	= O.position;
	M1			= O.M1;
	M2			= O.M2;
	M3			= O.M3;
#if defined(USE_PARALLAX) || defined(USE_STEEPPARALLAX)
	eye			= O.eye;
#endif
#ifdef USE_TDETAIL
	tcdbump		= O.tcdbump;
#endif
#ifdef USE_LM_HEMI
	lmh			= O.lmh;
#endif
	gl_Position = O.hpos;
}
