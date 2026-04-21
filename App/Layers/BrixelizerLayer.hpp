#pragma once

#include <d3d12.h>
#include <wrl/client.h>
#include <memory>

#include <Shader.hpp>
#include <BrixelizerShader.hpp>
#include <Model.hpp>
#include <Core/Layer.hpp>
#include <Camera.hpp>
#include <Input/UserInput.hpp>
#include <Scene/SceneBuilder.hpp>
#include <Brixelizer/BrixelizerContext.hpp>
#include <Core/Application.hpp>

#include "../Game/PlayerController.hpp"

class BrixelizerLayer : public Core::Layer {
public:
    BrixelizerLayer();
    ~BrixelizerLayer();

    void OnUpdate(float deltaTime);
    void OnRender();
    void OnEvent(Core::Event& event);

private:
    std::unique_ptr<BrixelizerShader> m_LightingShader;

    Camera           m_Camera{};
    SceneBuilder     m_SceneBuilder { Core::Application::Get().GetDX().GetDevice() };
    Input::UserInput m_Input{};
    PlayerController m_PlayerController { m_Camera, m_Input };
    Model            m_Model;
    std::unique_ptr<Brixelizer::BrixelizerContext> m_BrixelizerContext;
    std::vector<Brixelizer::MeshInstance> m_BrixelizerMeshInstances{};
};