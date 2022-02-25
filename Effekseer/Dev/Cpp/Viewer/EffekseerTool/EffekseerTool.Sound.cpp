﻿
//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "EffekseerTool.Sound.h"

#ifdef _WIN32

#endif
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace EffekseerTool
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Sound::Sound()
	: m_sound(nullptr)
	, m_manager(nullptr)
	, m_mute(false)
	, m_volume(1.0f)
{
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Sound::~Sound()
{
	if (m_sound != nullptr)
	{
		m_sound.Reset();
	}

	if (m_manager)
	{
		m_manager->Release();
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool Sound::Initialize()
{
	m_manager = osm::Manager::Create();
	if (m_manager == nullptr)
	{
		return false;
	}

	if (!m_manager->Initialize())
	{
		return false;
	}

	m_sound = EffekseerSound::Sound::Create(m_manager);
	if (m_sound == nullptr)
	{
		return false;
	}

	return true;
}

void Sound::Update()
{
	// m_sound->Update();
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Sound::SetVolume(float volume)
{
	m_volume = volume;

	if (m_sound != nullptr)
	{
		// m_sound->SetMasterVolume(volume);
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Sound::SetMute(bool mute)
{
	m_mute = mute;

	if (m_sound != nullptr)
	{
		m_sound->SetMute(mute);
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Sound::SetListener(const Effekseer::Vector3D& pos, const Effekseer::Vector3D& at, const Effekseer::Vector3D& up)
{
	if (m_sound != nullptr)
	{
		m_sound->SetListener(pos, at, up);
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace EffekseerTool
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
