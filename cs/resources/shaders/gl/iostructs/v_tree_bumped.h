
out gl_PerVertex { vec4 gl_Position; };

layout(location = 0) in vec4	P;		// (float,float,float,1)
layout(location = 1) in vec4	Nh;		// (nx,ny,nz)
layout(location = 2) in vec3	T;		// tangent
layout(location = 3) in vec3	B;		// binormal
layout(location = 4) in vec4	tc;		// (u,v,frac,???)

#if defined(USE_R2_STATIC_SUN) && !defined(USE_LM_HEMI)
layout(location = 0) out vec4	tcdh;		// Texture coordinates,         w=sun_occlusion
#else
layout(location = 0) out vec2	tcdh;		// Texture coordinates
#endif
layout(location = 1) out vec4	position;	// position + hemi
layout(location = 2) out vec3	M1;			// nmap 2 eye - 1
layout(location = 3) out vec3	M2;			// nmap 2 eye - 2
layout(location = 4) out vec3	M3;			// nmap 2 eye - 3
#if defined(USE_PARALLAX) || defined(USE_STEEPPARALLAX)
layout(location = 5) out vec3	eye;		// vector to point in tangent space
  #ifdef USE_TDETAIL
layout(location = 6) out vec2	tcdbump;	// d-bump
    #ifdef USE_LM_HEMI
layout(location = 7) out vec2	lmh;		// lm-hemi
    #endif
  #else
    #ifdef USE_LM_HEMI
layout(location = 6) out vec2	lmh;		// lm-hemi
    #endif
  #endif
#else
  #ifdef USE_TDETAIL
layout(location = 5) out vec2	tcdbump;	// d-bump
    #ifdef USE_LM_HEMI
layout(location = 6) out vec2	lmh;		// lm-hemi
    #endif
  #else
    #ifdef USE_LM_HEMI
layout(location = 5) out vec2	lmh;		// lm-hemi
    #endif
  #endif
#endif

p_bumped _main ( v_tree I );

void main()
{
	v_tree I;
	I.P		= P;
	I.Nh	= Nh;
	I.T		= T;
	I.B		= B;
	I.tc	= tc;

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