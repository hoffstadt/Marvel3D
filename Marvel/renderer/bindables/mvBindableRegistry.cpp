#include "mvCommonBindables.h"
#include <assert.h>
#include "mvGraphics.h"

namespace Marvel {

	std::unordered_map<std::string, std::shared_ptr<mvBindable>> mvBindableRegistry::m_bindables;

	void mvBindableRegistry::Initialize(mvGraphics& graphics)
	{
		m_bindables.try_emplace("vs_texture", std::make_shared<mvVertexShader>(graphics, "../../Marvel/shaders/vs_phong.hlsl"));
		m_bindables.try_emplace("ps_texture", std::make_shared<mvPixelShader>(graphics, "../../Marvel/shaders/ps_phong.hlsl"));
		m_bindables.try_emplace("gs_null", std::make_shared<mvNullGeometryShader>(graphics));
		m_bindables.try_emplace("sampler", std::make_shared<mvSampler>(graphics));
		m_bindables.try_emplace("transCBuf", std::make_shared<mvTransformConstantBuffer>(graphics));
		m_bindables.try_emplace("blender", std::make_shared<mvBlender>(graphics, true));
	}

	std::shared_ptr<mvBindable> mvBindableRegistry::GetBindable(const std::string& ID)
	{
		if (m_bindables.find(ID) == m_bindables.end())
			return nullptr;

		return m_bindables.at(ID);
	}

	std::shared_ptr<mvBindable> mvBindableRegistry::AddBindable(const std::string& ID, std::shared_ptr<mvBindable> bindable)
	{
		assert(m_bindables.find(ID) == m_bindables.end());

		m_bindables.try_emplace(ID, bindable);

		return bindable;
	}

}