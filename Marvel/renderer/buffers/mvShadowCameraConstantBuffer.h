#pragma once
#include <memory>
#include "mvBuffer.h"
#include "mvConstantBuffer.h"
#include "mvMath.h"

namespace Marvel {

	//-----------------------------------------------------------------------------
	// forward declarations
	//-----------------------------------------------------------------------------
	class mvDrawable;
	class mvGraphics;
	class mvCamera;
	class mvOrthoCamera;

	//-----------------------------------------------------------------------------
	// mvTransformUniform
	//-----------------------------------------------------------------------------
	class mvShadowCameraConstantBuffer : public mvBuffer
	{

		struct ShadowCameraInfo
		{
			glm::mat4 pointShadowView = glm::identity<glm::mat4>();
			glm::mat4 directShadowView = glm::identity<glm::mat4>();
			glm::mat4 directShadowProjection = glm::identity<glm::mat4>();
		};

	public:

		mvShadowCameraConstantBuffer(mvGraphics& graphics);

		void bind(mvGraphics& graphics) override;
		void setCamera(const mvCamera* camera);
		void setOrthoCamera(const mvOrthoCamera* camera);

	private:

		std::unique_ptr<mvVertexConstantBuffer> m_buf;
		const mvCamera*                         m_camera = nullptr;
		const mvOrthoCamera*                    m_orthocamera = nullptr;
		ShadowCameraInfo                        m_buffer;

	};

}