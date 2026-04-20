#pragma once
#include <Camera.hpp>

namespace AppConfig {
	constexpr float FOV_DEG     = 45.0f;
	constexpr float NEAR_PLANE  = 0.1f;
	constexpr float FAR_PLANE   = 5000.0f;
	constexpr float ASPECT      = 1280.0f / 720.0f;
	constexpr float MODEL_SCALE = 0.01f;
}

struct SceneConstants {
	DirectX::XMFLOAT4X4 model{};
	DirectX::XMFLOAT4X4 view{};
	DirectX::XMFLOAT4X4 proj{};
	DirectX::XMFLOAT3   lightPosition{};  
	float _padding0{};
	DirectX::XMFLOAT3   cameraPosition{}; 
	float _padding1{};
};

class SceneBuilder {
public:
	SceneConstants Build(Camera const& camera) const noexcept {
		using namespace DirectX;

		SceneConstants scene{};

		XMStoreFloat4x4(&scene.model, XMMatrixScaling(
			AppConfig::MODEL_SCALE, AppConfig::MODEL_SCALE, AppConfig::MODEL_SCALE
		));

		XMStoreFloat4x4(&scene.view, camera.GetViewMatrix());
		XMStoreFloat4x4(&scene.proj, XMMatrixPerspectiveFovLH(
			XMConvertToRadians(AppConfig::FOV_DEG),
			AppConfig::ASPECT,
			AppConfig::NEAR_PLANE,
			AppConfig::FAR_PLANE)
		);

		scene.lightPosition  = camera.GetPosition();
		scene.cameraPosition = camera.GetPosition();

		return scene;
	}
};