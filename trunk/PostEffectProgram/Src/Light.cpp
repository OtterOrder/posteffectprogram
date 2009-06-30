#include "Light.h"

//------------------------------------------------------------------------------------------------------------------------------
Light::Light(Type _type)
{
	m_type = _type;

	m_position		= Vector3f(0.f, 0.f, 0.f);
	m_direction		= Vector3f(0.f, 0.f, 1.f);
	SetAngle(0.2f);

	m_Diffuse		= Vector3f(0.5f, 0.5f, 0.5f);
	m_Specular		= Vector3f(1.f, 1.f, 1.f);

	m_attenuation	= 0.f;
	m_intensity		= 1.f;
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
DirectionalLight::DirectionalLight()
: Light (Directional)
{
	m_type = Directional;

	m_position		= Vector3f(0.f, 200.f, 0.f);
	m_direction		= Vector3f(0.f, -1.f, 0.f);
	Light::SetAngle(3.14f);
}

//------------------------------------------------------------------------------------------------------------------------------
PointLight::PointLight()
: Light (Point)
{
	Light::SetAngle(6.28f);
}

//------------------------------------------------------------------------------------------------------------------------------
SpotLight::SpotLight()
: Light (Spot)
{
	m_direction		= Vector3f(0.f, -1.f, 0.f);
	Light::SetAngle(1.57f);
}
