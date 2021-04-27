#pragma once

#include <memory>
#include "mvPass.h"
#include "mvVertexBuffer.h"
#include "mvIndexBuffer.h"

namespace Marvel {

	//-----------------------------------------------------------------------------
	// forward declarations
	//-----------------------------------------------------------------------------
	class mvGraphics;

	//-----------------------------------------------------------------------------
	// mvLambertianPass
	//-----------------------------------------------------------------------------
	class mvSkyboxPass : public mvPass
	{

	public:

		mvSkyboxPass(mvGraphics& graphics, const char* skybox);

		void execute(mvGraphics& graphics) const override;

	private:

		std::shared_ptr<mvVertexBuffer> m_vertexBuffer;
		std::shared_ptr<mvIndexBuffer>  m_indexBuffer;

	};

}