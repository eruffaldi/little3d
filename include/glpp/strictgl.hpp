#pragma once


namespace glpp
{
	enum class BT { ARRAY = GL_ARRAY_BUFFER, ELEMENT = GL_ELEMENT_ARRAY_BUFFER }; 
	enum class TT { T2D = GL_TEXTURE_2D, T3D = GL_TEXTURE_3D }; 
	enum class EN { CULL_FACE= GL_CULL_FACE };
	enum class BU { STATIC_DRAW = GL_STATIC_DRAW}; 
	enum class DT { UNSIGNED_INT = GL_UNSIGNED_INT};
	enum class PT { TRIANGLES = GL_TRIANGLES}; 
	enum class CM { COLOR = GL_COLOR_BUFFER_BIT, DEPTH = GL_DEPTH_BUFFER_BIT, COLOR_DEPTH = GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT};
}

template <class T>
struct type2gl
{
};

template <>
struct type2gl<GLfloat>
{
	static constexpr GLenum value = GL_UNSIGNED_INT;
};

template <>
struct type2gl<GLuint>
{
	static constexpr GLenum value = GL_UNSIGNED_INT;
};

template <>
struct type2gl<GLubyte>
{
	static constexpr GLenum value = GL_UNSIGNED_BYTE;
};


template <GLenum q>
struct gl2type
{
};

template <>
struct gl2type<GL_UNSIGNED_INT>
{
	using type = GLuint;
};

template <>
struct gl2type<GL_UNSIGNED_BYTE>
{
	using type = GLubyte;
};

template <>
struct gl2type<GL_FLOAT>
{
	using type = GLfloat;
};
