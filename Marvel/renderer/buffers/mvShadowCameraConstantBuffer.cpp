#include "mvShadowCameraConstantBuffer.h"
#include "drawables/mvDrawable.h"
#include "mvGraphics.h"
#include "mvDrawable.h"
#include "mvCamera.h"

namespace Marvel {

	mvShadowCameraConstantBuffer::mvShadowCameraConstantBuffer(mvGraphics& graphics)
	{
		m_buf = std::make_unique<mvVertexConstantBuffer>(graphics, 1, &m_buffer);
	}

	void mvShadowCameraConstantBuffer::bind(mvGraphics& graphics)
	{
		m_buffer.pointShadowView = m_camera->getMatrix();
		m_buffer.directShadowView = m_orthocamera->getMatrix();
		m_buffer.directShadowProjection = m_orthocamera->getProjection();

		m_buf->update(graphics, m_buffer);
		m_buf->bind(graphics);
	}

	void mvShadowCameraConstantBuffer::setCamera(const mvCamera* camera)
	{
		m_camera = camera;
	}

	void mvShadowCameraConstantBuffer::setOrthoCamera(const mvOrthoCamera* camera)
	{
		m_orthocamera = camera;
	}
}