#include "mvMaterial.h"
#include "mvGraphics.h"
#include "mvCommonBindables.h"
#include "assimp/Importer.hpp"
#include "assimp/Scene.h"
#include "assimp/postprocess.h"

namespace Marvel {

	mvMaterial::mvMaterial(mvGraphics& graphics, const aiMaterial& material, const std::string& path)
	{

		std::shared_ptr<mvPixelConstantBuffer> buf;
		std::unique_ptr<mvBuffer>              bufferRaw;

		mvBufferLayout layout(std::make_shared<mvBufferLayoutEntry>(Struct));
		auto& root = layout.getRoot();

		mvTechnique phong;
		mvStep step("Lambertian");
		std::string shaderCode = "Phong";
		aiString texFileName;

		// create vertex layout
		m_layout.append(ElementType::Position3D);
		m_layout.append(ElementType::Normal);

		bool hasTexture = false;
		bool hasGlossAlpha = false;
		bool hasAlpha = false;

		// diffuse
		if (material.GetTexture(aiTextureType_DIFFUSE, 0, &texFileName) == aiReturn_SUCCESS)
		{
			hasTexture = true;
			shaderCode += "Dif";
			m_layout.append(ElementType::Texture2D);
			auto texture = std::make_shared<mvTexture>(graphics, path + texFileName.C_Str());
			step.addBindable(texture);

			if (texture->hasAlpha())
			{
				hasAlpha = true;
				shaderCode += "Msk";
			}
		}
		else
			root->add(Float3, std::string("materialColor"));
		step.addBindable(std::make_shared<mvRasterizer>(graphics, hasAlpha));

		// specular
		if (material.GetTexture(aiTextureType_SPECULAR, 0, &texFileName) == aiReturn_SUCCESS)
		{
			hasTexture = true;
			shaderCode += "Spc";
			m_layout.append(ElementType::Texture2D);
			auto texture = std::make_shared<mvTexture>(graphics, path + texFileName.C_Str(), 1);
			step.addBindable(texture);
			hasGlossAlpha = texture->hasAlpha();

			root->add(Bool, std::string("useGlossAlpha"));
			root->add(Bool, std::string("useSpecularMap"));

		}
		root->add(Float3, std::string("specularColor"));
		root->add(Float, std::string("specularWeight"));
		root->add(Float, std::string("specularGloss"));

		// normals
		if (material.GetTexture(aiTextureType_NORMALS, 0, &texFileName) == aiReturn_SUCCESS)
		{
			hasTexture = true;
			shaderCode += "Nrm";
			step.addBindable(std::make_shared<mvTexture>(graphics, path + texFileName.C_Str(), 2));
			m_layout.append(ElementType::Texture2D);
			m_layout.append(ElementType::Tangent);
			m_layout.append(ElementType::Bitangent);
			root->add(Bool, std::string("useNormalMap"));
			root->add(Float, std::string("normalMapWeight"));
		}

		root->finalize(0);

		bufferRaw = std::make_unique<mvBuffer>(std::move(layout));
		bufferRaw->getElement("useGlossAlpha").setIfExists(hasGlossAlpha);
		bufferRaw->getElement("useSpecularMap").setIfExists(true);
		bufferRaw->getElement("specularWeight").setIfExists(1.0f);
		bufferRaw->getElement("useNormalMap").setIfExists(true);
		bufferRaw->getElement("normalMapWeight").setIfExists(1.0f);

		if (auto r = bufferRaw->getElement("materialColor"); r.exists())
		{
			aiColor3D color = { 0.45f,0.45f,0.85f };
			material.Get(AI_MATKEY_COLOR_DIFFUSE, color);
			r = reinterpret_cast<glm::vec3&>(color);
		}

		if (auto r = bufferRaw->getElement("specularColor"); r.exists())
		{
			aiColor3D color = { 0.18f,0.18f,0.18f };
			material.Get(AI_MATKEY_COLOR_SPECULAR, color);
			r = reinterpret_cast<glm::vec3&>(color);
		}

		if (auto r = bufferRaw->getElement("specularGloss"); r.exists())
		{
			float gloss = 8.0f;
			material.Get(AI_MATKEY_SHININESS, gloss);
			r = gloss;
		}

		buf = std::make_shared<mvPixelConstantBuffer>(graphics, *root.get(), 1, bufferRaw.get());

		// create vertex shader
		auto vshader = mvBindableRegistry::GetBindable(shaderCode + "_VS");

		step.addBindable(vshader);
		step.addBindable(std::make_shared<mvInputLayout>(graphics, m_layout,
			static_cast<mvVertexShader*>(vshader.get())));
		step.addBindable(mvBindableRegistry::GetBindable(shaderCode + "_PS"));
		step.addBindable(mvBindableRegistry::GetBindable("transCBuf"));
		step.addBindable(mvBindableRegistry::GetBindable("blender"));

		if(hasTexture)
			step.addBindable(mvBindableRegistry::GetBindable("sampler"));
		
		step.addBindable(buf);

		phong.addStep(step);
		m_techniques.push_back(phong);
	}

	std::vector<mvTechnique> mvMaterial::getTechniques() const
	{
		return m_techniques;
	}

	const mvVertexLayout& mvMaterial::getLayout() const
	{
		return m_layout;
	}

}