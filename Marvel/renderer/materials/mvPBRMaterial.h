#pragma once
#include <memory>
#include <filesystem>
#include <vector>
#include "mvBindable.h"
#include "mvMaterial.h"
#include "mvConstantBuffer.h"
#include "mvVertexLayout.h"
#include "mvPhongMaterialCBuf.h"
#include "mvPBRMaterialCBuf.h"

namespace Marvel {

	//-----------------------------------------------------------------------------
	// forward declarations
	//-----------------------------------------------------------------------------
	class mvGraphics;
	struct mvObjMaterial;

	//-----------------------------------------------------------------------------
	// mvMaterial
	//-----------------------------------------------------------------------------
	class mvPBRMaterial : public mvMaterial
	{

	public:

		mvPBRMaterial(mvGraphics& graphics, const std::string& path, const mvObjMaterial& material);

		void showControls() override { m_material->showControls(); }

	private:

		std::shared_ptr<mvPBRMaterialCBuf> m_material = nullptr;


	};

}