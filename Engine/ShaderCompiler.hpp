#pragma once
#include <windows.h>
#include <wrl/client.h>
#include <string>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <stdexcept>

#include "ShaderInclude.hpp"

#pragma comment(lib, "d3dcompiler.lib")

Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(
	std::wstring const& filename,
	std::string const& entrypoint,
	std::string const& profile
) {
	Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob{};
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob{};

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(_DEBUG)
	flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ShaderInclude include("D:/projects/brixelizer-test/Engine/Plugins/FidelityFX/include/FidelityFX");

	HRESULT hr = D3DCompileFromFile(
		filename.c_str(),
		nullptr,
		&include,
		entrypoint.c_str(),
		profile.c_str(),
		flags,
		0,
		&shaderBlob,
		&errorBlob
	);

	if (FAILED(hr)) {
		if (errorBlob) {
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		}

		throw std::runtime_error("Shader compilation failed");
	}

	return shaderBlob;
}