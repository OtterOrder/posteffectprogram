#include "Misc.h"

//******************************************************************************************************************************
class Light
{
public:
	DefineVectorIterator(Light, Iterator);

	typedef enum
	{
		None,
		Directional,
		Point,
		Spot
	} Type;

protected:
	Type		m_type;

	Vector3f	m_position;
	Vector3f	m_direction;
	float		m_angle;

	float		m_scalarHalfAngle;

	Vector4f	m_Diffuse;
	Vector4f	m_Specular;

	float		m_attenuation;
	float		m_intensity;

public:
	Light ();
	virtual ~Light ()	{};

	virtual inline Vector3f		GetPosition		()	{ return m_position; };
	virtual inline Vector3f		GetDirection	()	{ return m_direction; };
	virtual inline float		GetAngle		()	{ return m_angle; };
	virtual inline Vector4f		GetDiffuse		()	{ return m_Diffuse; };
	virtual inline Vector4f		GetSpecular		()	{ return m_Specular; };
	virtual inline float		GetAttenuation	()	{ return m_attenuation; };
	virtual inline float		GetIntensity	()	{ return m_intensity; };

	virtual inline void			SetPosition		(Vector3f _position)		{ m_position = _position; };
	virtual inline void			SetDirection	(Vector3f _direction)		{ m_direction = _direction; };
	virtual inline void			SetAngle		(float _angle)				{ m_angle = _angle; m_scalarHalfAngle = cos(m_angle/2.f); };
	virtual inline void			SetDiffuse		(Vector4f _diffuse)			{ m_Diffuse = _diffuse; };
	virtual inline void			SetSpecular		(Vector4f _specular)		{ m_Specular = _specular; };
	virtual inline void			SetAttenuation	(float _attenuation)		{ m_attenuation = _attenuation; };
	virtual inline void			SetIntensity	(float _intensity)			{ m_intensity = _intensity; };
};

//******************************************************************************************************************************
class DirectionalLight : public Light
{
public:
	DirectionalLight();

	virtual inline void SetAngle (float) {};
};

//******************************************************************************************************************************
class PointLight : public Light
{
public:
	PointLight();

	virtual inline void SetAngle (float) {};
	virtual inline void SetDirection (Vector3f)		{};
};

//******************************************************************************************************************************
class SpotLight : public Light
{
public:
	SpotLight();
};