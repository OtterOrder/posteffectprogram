#include "Light.h"

//******************************************************************************************************************************
Light::Light()
{
	m_type = None;

	m_position		= Vector3f(0.f, 0.f, 0.f);
	m_direction		= Vector3f(0.f, 0.f, 1.f);
	SetAngle(0.2f);

	m_Diffuse		= Vector4f(0.5f, 0.5f, 0.5f, 1.f);
	m_Specular		= Vector4f(1.f, 1.f, 1.f, 1.f);

	m_attenuation	= 0.f;
	m_intensity		= 1.f;
}

//******************************************************************************************************************************
DirectionalLight::DirectionalLight()
{
	m_type = Directional;

	m_position		= Vector3f(0.f, 200.f, 0.f);
	m_direction		= Vector3f(0.f, -1.f, 0.f);
	Light::SetAngle(3.14f);

	m_Diffuse		= Vector4f(0.5f, 0.5f, 0.5f, 1.f);
	m_Specular		= Vector4f(1.f, 1.f, 1.f, 1.f);

	m_attenuation	= 0.f;
	m_intensity		= 1.f;
}

//******************************************************************************************************************************
PointLight::PointLight()
{
	m_type = Point;

	m_position		= Vector3f(0.f, 0.f, 0.f);
	m_direction		= Vector3f(0.f, 0.f, 0.f);
	Light::SetAngle(6.28f);

	m_Diffuse		= Vector4f(0.5f, 0.5f, 0.5f, 1.f);
	m_Specular		= Vector4f(1.f, 1.f, 1.f, 1.f);

	m_attenuation	= 0.f;
	m_intensity		= 1.f;
}

//******************************************************************************************************************************
SpotLight::SpotLight()
{
	m_type = Spot;

	m_position		= Vector3f(0.f, 0.f, 0.f);
	m_direction		= Vector3f(0.f, -1.f, 0.f);
	Light::SetAngle(1.57f);

	m_Diffuse		= Vector4f(0.5f, 0.5f, 0.5f, 1.f);
	m_Specular		= Vector4f(1.f, 1.f, 1.f, 1.f);

	m_attenuation	= 0.f;
	m_intensity		= 1.f;
}